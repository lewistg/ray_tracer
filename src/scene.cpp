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

#include "scene.h"

Scene::Scene()
{
    
}

void Scene::addObject(IlluminatedObject* object)
{
    _objects.push_back(object);
}

void Scene::addLight(LambertLight* light)
{
    _lights.push_back(light);
}

const IlluminatedObject* Scene::closestObj(Ray& ray) const
{
	IlluminatedObject* closestObj = NULL;
	float tForClosest = FLT_MAX;
	float t;
	for (vector<IlluminatedObject*>::const_iterator objItr = _objects.begin();
			objItr != _objects.end();
			objItr++)
	{
		t = (*objItr)->rayStrikesObject(ray);

		// if we have found a new closest object
		if (t > 0 && t < tForClosest/* && !verySmall(t)*/)
		{
			closestObj = *objItr;
			tForClosest = t;
		}
	}

	ray.setParam(tForClosest);
	return closestObj;
}

vector<LambertLight*> Scene::getLights() const
{
    return _lights;
}

bool Scene::verySmall(float t) const
{
    return t < 0.000002f;
}