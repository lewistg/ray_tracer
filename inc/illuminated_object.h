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
		void setColor(const mvl::GVector4f color);

		/**
		 * Gets the color for the object 
		 */
		mvl::GVector4f getColor() const;

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
		 * being traced to this object (i.e. the light ray emanates
		 * from this object). 
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
		virtual mvl::GVector3f getNormal(const mvl::GVector3f& pointOnObj) const = 0;

		/**
		 * Helper function for preventing intersecting with same
		 * object at the same point
		 */
		bool verySmall(float t) const;

	private:
		/**Color of the object*/
		mvl::GVector4f _color;
		/**The reflection coefficient, somewhere in the range [0, 1]*/
		float _kReflect;
		/**The diffuse and ambient coefficient, somewhere in the range [0, 1]*/
		float _kDiffuse;

		/**
		 * Traces shadow rays spawned by the incoming ray and returns the diffuse
		 * and ambient contributions.
         * @param incomingRay
         * @param scene
         * @param intensitySum
         */
		mvl::GVector4f getDiffuseAmbientIntensity(const LightRay& incomingRay, const Scene& scene) const;

		/**
		 * Traces a the reflecting ray spawned by the incoming ray 
		 * returns the resulting contribution.
		 * @param incomingRay - The light ray that struck the object.
		 * @param scene - The scene being ray traced.
		 * @param intensitySum - The running total of intensity that the incoming 
		 * ray receives by striking this object. 
		 * @return The contribution from reflection will be added to the 
		 * intensitySum.  
         */
		mvl::GVector4f getReflectionIntensity(const LightRay& incomingRay, const Scene& scene) const;

		// Undefined canonicals
		IlluminatedObject(const IlluminatedObject& cpy);
		const IlluminatedObject& operator=(const IlluminatedObject& _rhs);
};

#endif