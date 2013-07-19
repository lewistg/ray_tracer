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

#ifndef _ILLUMINATED_OBJECT_H_
#define _ILLUMINATED_OBJECT_H_

#include <math.h>
#include "light_ray.h"
#include "ray.h"

class Scene;

/**
 * Represents an object that can be illuminated by a
 * light of some kind. Contains material information about
 * the object as well.
 */
class IlluminatedObject 
{
	public:
		/**
		 * No-arg constructor
		 */
		IlluminatedObject();


		/**
		 * Indicates whether or not a ray strikes the object
		 * @param ray
		 * @return -1 if the ray doesn't strike the object, otherwise the positive
		 * parameter value for t to strike the object
		 */
		virtual float rayStrikesObject(const Ray& ray);

		/**
		 * Sets the color of the object
		 * @param color
		 */
		void setColor(const Vector4f color);

		/**
		 * Gets the color for the object 
		 */
		Vector4f getColor() const;

		/**
		 * Sets the diffuse and ambient coefficient
		 */
		void setDiffAmbCoeff(float kAmbDiff);

		/**
		 * Sets the reflectivity coefficient
		 */
		void setReflCoeff(float kRefl);

		/**
		 * Loads the light ray with the intensity that results from
		 * being traced from this object. 
		 * @param lightRay
		 * @param scene 
		 * @pre The light ray's current parameterized point is a point on the
		 * surface of the object
		 */
		void getIntensity(LightRay& lightRay, const Scene& scene) const;

	protected:
		/**
		 * Custom min function that finds the minimum of two t values,
		 * filtering out t's that are very small. If neither of the t's are
		 * positive or significant -1 is returned.
		 */
		float minAndSig(float t1, float t2);

		/**
		 * Gets the normal at a point on the object
		 * @param t
		 * @return 
		 */
		virtual Vector4f getNormal(const Vector4f& pointOnObj) const = 0;

		/**
		 * Helper function for preventing intersecting with same
		 * object at the same point
		 */
		bool verySmall(float t) const;

	private:
		/**Color of the object*/
		Vector4f _color;
		/**The reflection coefficient, somewhere in the range [0, 1]*/
		float _kReflect;
		/**The diffuse and ambient coefficient, somewhere in the range [0, 1]*/
		float _kDiffuse;

		/**
		 * Helper function for tracing reflected rays
		 */
		//void traceReflection(LightRay* reflectedRay, const Scene& scene)
};

#endif