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

#ifndef _RTRIANGLE_H_
#define _RTRIANGLE_H_

#include <cmath>
#include "illuminated_object.h"
#include "plane.h"


/**
 * Represents a triangle that can be raytraced
 */
class RTriangle: public IlluminatedObject 
{
	public:
		/**
		 * Constructs a new triangle from three points
		 * @param p0
		 * @param p1
		 * @param p2
		 */
		RTriangle(const Vector4f& p0, const Vector4f& p1, const Vector4f& p2);

		/**
		 * Override
		 */
		virtual float rayStrikesObject(const Ray& ray);

	protected:
		/**
		 * Override
		 */
		virtual Vector4f getNormal(const Vector4f& pointOnObj) const;

	private:
		/**Vertices of the triangle*/
		Vector4f _p0;
		Vector4f _p1;
		Vector4f _p2;
		/**Plane that contains the triangle*/
		Plane _plane;

		/**
		 * Helper for evaluating if a barycentric coordinate
		 * is within the triangle
		 */
		bool withinTri(float lambda);
};

#endif