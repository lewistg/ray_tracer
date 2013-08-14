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

#ifndef _RAY_H_
#define _RAY_H_

#include "graphics_vector.h"

using namespace std;
/**
 * Represents a mathematical ray
 */
class Ray 
{
	public:
		/**
		 * No arg constructor
		 */
		Ray();

		/**
		 * Constructs a new ray
		 */
		Ray(const mvl::GVector3f& pos, const mvl::GVector3f& dir);

		/**
		 * Sets the current t
		 * @param t
		 * @return 
		 */
		void setParam(float t);

		/**
		 * Sets the position of the ray's origin of the ray
		 * @param dir
		 */
		void setOriginPos(const mvl::GVector3f& originPos);

		/**
		 * Sets the direction of the ray
		 * @return 
		 */
		void setDir(const mvl::GVector3f& dir);

		/**
		 * Gets the point associated with the current param
		 * @param t
		 * @return 
		 */
		mvl::GVector3f getPoint() const;

		/**
		 * Given the parameter t, find the point along the ray.
		 * Does not set the current t value
		 */
		mvl::GVector3f getPoint(float t) const;

		/**
		 * Gets the origin of the ray
		 */
		mvl::GVector3f getOrigin() const;

		/**
		 * Gets the direction of the vector
		 */
		mvl::GVector3f getDir() const;

		/**
		 * Gets the current parameter
		 * @return 
		 */
		float getParam();

		/**
		 * To string method
		 */
		string toString();

	private:
		/**Origin of the ray*/
		mvl::GVector3f _originPos;
		/**Direction of the ray*/
		mvl::GVector3f _dir;
		/**The current t value*/
		float _t;
};

#endif