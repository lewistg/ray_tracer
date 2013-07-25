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

#include <cmath>
#include <vector>

#include "illuminated_object.h"

#include "sphere.h" // TODO: remove

#include "light_ray.h"
#include "lambert_light.h"
#include "scene.h"
#include "cstdlib"

IlluminatedObject::IlluminatedObject()
	:_color(Vector4f(0.2f, 0.2f, 0.2f, 1.0f)), 
	_kDiffuse(1.0f), 
	_kReflect(0.3f)
{
}

float IlluminatedObject::rayStrikesObject(const Ray& ray)
{
    float r = 5.0f;
    Vector4f center(0.0f, 0.0f, -6.0f, 1.0f);
    
    Vector4f deltaP = sub(center, ray.getOrigin());
    
    float discrim = pow(dot3f(deltaP, ray.getDir()), 2) - pow(mag3f(deltaP), 2) + pow(r, 2);
    if(discrim < 0)
	return -1;
    
    float a = dot3f(ray.getDir(), deltaP);
    float b = sqrt(discrim);
    
    float t1 = a + b;
    float t2 = a - b;
    
    return min(t1, t2);
}

void IlluminatedObject::setColor(const Vector4f color)
{
    _color = color;
}

Vector4f IlluminatedObject::getColor() const
{
    return _color;
}

Vector4f IlluminatedObject::getDiffuseAmbientIntensity(const LightRay& incomingRay, const Scene& scene) const
{
	// shoot a shadow ray at each light, if it hits it becomes an illumination
	// ray and we calculate its contribution
	Vector4f diffAmbLight;
	vector<LambertLight*> lightsInScene = scene.getLights();
	for (vector<LambertLight*>::const_iterator lightsItr = lightsInScene.begin();
			lightsItr != lightsInScene.end();
			lightsItr++)
	{
		// create a ray from intersection to the light
		Vector4f rayOrigin = incomingRay.getPoint();
		Vector4f dirToLight = sub((*lightsItr)->getPos(), rayOrigin);
		float distToLight = mag3f(dirToLight);
		normalize(&dirToLight);
		Ray rayToLight(rayOrigin, dirToLight);

		const IlluminatedObject* obstructingObj = scene.closestObj(rayToLight);
		float distToHider = ((obstructingObj == NULL) ?
				FLT_MAX :
				mag3f(sub(rayToLight.getOrigin(), rayToLight.getPoint())));

		bool objectIsHider = distToLight > distToHider;
		if (!objectIsHider)
		{
			float shade = max(dot3f(getNormal(incomingRay.getPoint()), dirToLight), 0.0f);
			Vector4f diffComp = scale((*lightsItr)->getDiffuse(), shade);
			diffAmbLight = add(diffAmbLight, diffComp);
		} 

		diffAmbLight = add(diffAmbLight, (*lightsItr)->getAmbient());
	}

	Vector4f diffAmbIntensity = pwMult(getColor(), diffAmbLight);
	diffAmbIntensity = scale(diffAmbIntensity, _kDiffuse);

	return diffAmbIntensity;

}

Vector4f IlluminatedObject::getReflectionIntensity(const LightRay& incomingRay, const Scene& scene) const
{
	Vector4f refelectionIntensity;

	if(_kReflect == 0)
		return refelectionIntensity;
	if(incomingRay.getDepth() >= 8)
		return refelectionIntensity;

	float c1 = -dot3f(getNormal(incomingRay.getPoint()), incomingRay.getDir());
	Vector4f reflectedDir = add(incomingRay.getDir(), scale(getNormal(incomingRay.getPoint()), 2 * c1));
	LightRay reflectedRay(incomingRay.getPoint(), reflectedDir, incomingRay.getDepth() + 1);

	const IlluminatedObject* object = scene.closestObj(reflectedRay);
	if (object != NULL)
		object->getIntensity(reflectedRay, scene);

	refelectionIntensity = scale(reflectedRay.getColor(), _kReflect);

	return refelectionIntensity; 
}

void IlluminatedObject::getIntensity(LightRay& incomingRay, const Scene& scene) const
{
	Vector4f diffuseAmbientIntensity = getDiffuseAmbientIntensity(incomingRay, scene);
	Vector4f reflectionIntensity = getReflectionIntensity(incomingRay, scene);

	Vector4f intensity = add(diffuseAmbientIntensity, reflectionIntensity);
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