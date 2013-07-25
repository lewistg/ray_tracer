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

#ifndef _SCENE_H_
#define _SCENE_H_

#include <cfloat>
#include <vector>
#include "illuminated_object.h"
#include "lambert_light.h"

using namespace std;

/**
 * A scene to be ray-traced. Basically it is a container for illuminated
 * objects and scenes
 */
class Scene 
{
    public:
	Scene();
	
	/**
	 * Adds an object to the scene
         * @param object
         */
	void addObject(IlluminatedObject* object);
	
	/**
	 * Adds a light to the scene
	 */
	void addLight(LambertLight* light);
	
	/**
	 * Finds closest object intersected by the ray. Sets the
	 * ray's t current t parameter to the value that 
	 * @post ray.
	 */
	const IlluminatedObject* closestObj(Ray& ray) const;
	
	/**
	 * Gets the lights in the scene
	 */
	vector<LambertLight*> getLights() const;
	
    private:
	/**Holds all of the objects in the scene*/
	vector<IlluminatedObject*> _objects;
	/**Holds all of the lights in the scene*/
	vector<LambertLight*> _lights;
	
	/**
	 * Helper function for preventing intersecting with same
	 * object at the same point
	 */
	bool verySmall(float t) const;
	
};

#endif