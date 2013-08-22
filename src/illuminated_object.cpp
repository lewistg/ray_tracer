/**
 * Copyright (c) 2013, Ty G. Lewis 
 * All rights reserved.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Ty G. Lewis BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <memory>
#include <cmath>
#include <vector>
#include "vector_math.h"
#include "graphics_vector_utils.h"
#include "illuminated_object.h"
#include "sphere.h" // TODO: remove
#include "light_ray.h"
#include "lambert_light.h"
#include "scene.h"
#include "cstdlib"

IlluminatedObject::IlluminatedObject()
	:_color(mvl::GVector4f(0.2f, 0.2f, 0.2f, 1.0f)), 
	_kDiffuse(1.0f), 
	_kReflect(0.3f)
{
}

float IlluminatedObject::rayStrikesObject(const Ray& ray)
{
    float r = 5.0f;
    mvl::GVector3f center(0.0f, 0.0f, -6.0f);
    
    mvl::GVector3f deltaP = sub(center, ray.getOrigin());
    
    float discrim = pow(mvl::dot(deltaP, ray.getDir()), 2) - pow(deltaP.getMagnitude(), 2) + pow(r, 2);
    if(discrim < 0)
	return -1;
    
    float a = mvl::dot(ray.getDir(), deltaP);
    float b = sqrt(discrim);
    
    float t1 = a + b;
    float t2 = a - b;
    
    return min(t1, t2);
}

void IlluminatedObject::setColor(const mvl::GVector4f color)
{
    _color = color;
}

mvl::GVector4f IlluminatedObject::getColor() const
{
    return _color;
}

mvl::GVector4f IlluminatedObject::getDiffuseAmbientIntensity(const LightRay& incomingRay, const Scene& scene) const
{
	// shoot a shadow ray at each light, if it hits it becomes an illumination
	// ray and we calculate its contribution
	mvl::GVector4f diffAmbLight;
	vector<LambertLight*> lightsInScene = scene.getLights();
	for (vector<LambertLight*>::const_iterator lightsItr = lightsInScene.begin();
			lightsItr != lightsInScene.end();
			lightsItr++)
	{
		// create a ray from intersection to the light
		mvl::GVector3f rayOrigin = incomingRay.getPoint();
		mvl::GVector3f dirToLight = sub((*lightsItr)->getPos(), rayOrigin);
		float distToLight = dirToLight.getMagnitude();
		dirToLight.normalize();
		Ray rayToLight(rayOrigin, dirToLight);

		const shared_ptr<IlluminatedObject> obstructingObj = scene.closestObj(rayToLight);

		float distToHider = 0.0f;
		if(obstructingObj == NULL)
		{
			distToHider = FLT_MAX;
		}
		else
		{
			mvl::GVector3f diff = sub(rayToLight.getOrigin(), rayToLight.getPoint());
			distToHider = diff.getMagnitude();
		}

		bool objectIsHider = distToLight > distToHider;
		if (!objectIsHider)
		{
			float shade = max(mvl::dot(getNormal(incomingRay.getPoint()), dirToLight), 0.0f);
			mvl::GVector4f diffComp = mvl::scaledCopy((*lightsItr)->getDiffuse(), shade);
			diffAmbLight = mvl::add(diffAmbLight, diffComp);
		} 

		diffAmbLight = mvl::add(diffAmbLight, (*lightsItr)->getAmbient());
	}

	mvl::GVector4f diffAmbIntensity = mvl::pointwiseMult(getColor(), diffAmbLight);
	diffAmbIntensity.scale(_kDiffuse);

	return diffAmbIntensity;

}

mvl::GVector4f IlluminatedObject::getReflectionIntensity(const LightRay& incomingRay, const Scene& scene) const
{
	mvl::GVector4f refelectionIntensity;

	if(_kReflect == 0)
		return refelectionIntensity;
	if(incomingRay.getDepth() >= 8)
		return refelectionIntensity;

	float c1 = -mvl::dot(getNormal(incomingRay.getPoint()), incomingRay.getDir());
	mvl::GVector3f reflectedDir = add(incomingRay.getDir(), mvl::scaledCopy(getNormal(incomingRay.getPoint()), 2 * c1));
	LightRay reflectedRay(incomingRay.getPoint(), reflectedDir, incomingRay.getDepth() + 1);

	const std::shared_ptr<IlluminatedObject> object = scene.closestObj(reflectedRay);
	if (object != NULL)
		object->getIntensity(reflectedRay, scene);

	refelectionIntensity = mvl::scaledCopy(reflectedRay.getColor(), _kReflect);

	return refelectionIntensity; 
}

void IlluminatedObject::getIntensity(LightRay& incomingRay, const Scene& scene) const
{
	mvl::GVector4f diffuseAmbientIntensity = getDiffuseAmbientIntensity(incomingRay, scene);
	mvl::GVector4f reflectionIntensity = getReflectionIntensity(incomingRay, scene);

	mvl::GVector4f intensity = add(diffuseAmbientIntensity, reflectionIntensity);
	incomingRay.setColor(intensity);
}

bool IlluminatedObject::verySmall(float t) const
{
    return abs(t) < 0.01f;
}

float IlluminatedObject::minAndSig(float t1, float t2)
{
	if (t1 > 0 && !verySmall(t1))
	{
		if (t2 > 0 && !verySmall(t2))
			return min(t1, t2);
		else
			return t1;
	} 
	else if (t2 > 0 && !verySmall(t2))
	{
		return t2;
	}
    
    return -1;
}

void IlluminatedObject::setDiffAmbCoeff(float kAmbDiff)
{
    _kDiffuse = kAmbDiff;
}
	
void IlluminatedObject::setReflCoeff(float kRefl)
{
    _kReflect = kRefl;
}