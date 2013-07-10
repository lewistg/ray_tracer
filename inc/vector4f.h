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

#ifndef _VECTOR4F_H_
#define _VECTOR4F_H_

#include <string>
#include <assert.h>
#include "vector.h"

using namespace gmath;

/**
 * A vector of 4 floats
 */
class Vector4f
{
	public:
		/**
		 * Default constructor.
		 * @post x = 0, y = 0, z = 0, w = 1
		 */
		Vector4f();
		
		/**
		 * Constructs a new Vector4f.
	         * @param x
		 * @param y
		 * @param z
		 * @param w
		 */
		Vector4f(float x, float y, float z, float w);
		
		/**
		 * Constructs a new Vector4f from an array of floats.
         * @param source An array of 4 points containing the point
         */
		Vector4f(const float* source);
		
		/**
		 * Copy constructor
		 * @param orig the matrix row to copy
		 * @return 
		 */
		Vector4f(const Vector4f& orig);		
		
		/**
		 * Destructor
         */
		virtual ~Vector4f();
		
		/**
		 * Overloaded assignment operator
		 * @param rSide right side of the assignment operator
		 * @return 
		 */
		const Vector4f& operator = (const Vector4f& rSide);

		/**
		 * Overloaded increment operator. Does component-wise
		 * addition.
		 * @pre rSide has the same dimension of the rSide
		 * @param rSide
		 * @return 
		 */
		const Vector4f& operator += (const Vector4f& rSide);		

		/**
		 * Scales the matrix
		 * scaleFactor multiplier for all of the components
		 */
		void scale(float scaleFactor);

		/**
		 * Indexes into matrix row
		 * @pre 0 <= column <= 3
		 * @param column
		 * @return A reference to 
		 */
		float& operator[] (int column) const;	

		/**
		 * Gets a component of the vector by index
		 * @pre The index is within the bounds of the vector
		 * @param index the index of the component to be retrieved
		 * @return a float containing the 
		 */
		float getComp(int index) const;

		/**
		 * Checks to see if two vectors are equal component wise;
		 */
		bool operator == (const Vector4f& rSide);

		/**
		 * Checks to see if two vectors are in-equal component wise;
		 */			
		bool operator != (const Vector4f& rSide);

		/**
		 * Converts the vector to a float array
		 * @return 
		 */
		const float* getData() const;		
		
		/**
		 * Loads teh float array with the array of values
                 * @param floatArray
                 */
		void toArray(float* floatArray);
		
		/**
		 * Returns a string representing the matrix row
		 * @return a string with the row's string representation
		 */
		string toString() const;		
	private:
		Vector _vector;
};

/**
 * Gets the x component of the vector
 * @pre The vector has at least one dimension
 * @return float of the x coordinate
 */
float& x(const Vector4f& v);

/**
 * Gets the y component of the vector
 * @pre The vector has at least two dimension
 * @return float of the y coordinate
 */	
float& y(const Vector4f& v);

/**
 * Gets the z component of the vector
 * @pre The vector has at least three dimension
 * @return float of the z coordinate
 */	
float& z(const Vector4f& v);

/**
 * Gets the z component of the vector
 * @pre The vector has at least three dimension
 * @return float of the z coordinate
 */	
float& w(const Vector4f& v);	

/**
 * Gets the r component of the vector
 * @pre The vector has at least one dimension
 * @return float of the r coordinate
 */
float& r(const Vector4f& v);

/**
 * Gets the g component of the vector
 * @pre The vector has at least two dimension
 * @return float of the g coordinate
 */	
float& g(const Vector4f& v);

/**
 * Gets the b component of the vector
 * @pre The vector has at least three dimension
 * @return float of the b coordinate
 */	
float& b(const Vector4f& v);

/**
 * Gets the a component of the vector
 * @pre The vector has at least three dimension
 * @return float of the a coordinate
 */	
float& a(const Vector4f& v);	

/**
 * Adds two vectors together
 * @pre v1 and v2 have the same dimensions
 * @param v1
 * @param v2
 * @return A vector equal to v1 + v2. 
 */
Vector4f add(const Vector4f& v1, const Vector4f& v2);

/**
 * Subtracts one vector from another.
 * @pre v1 and v2 have the same dimensions
 * @param v1
 * @param v2
 * @return A vector equal to v1 - v2.
 */
Vector4f sub(const Vector4f& v1, const Vector4f& v2);

/**
 * Performs the dot product of two vectors
 * @pre The vectors have the same dimensions
 * @return A float of the dot product
 */
float dot(const Vector4f& v1, const Vector4f& v2);

/**
 * Performs the dot product of two vectors
 * using only the values of x,y,z
 * @return 
 */
float dot3f(const Vector4f& v1, const Vector4f& v2);

/**
 * Returns a scaled copy of the given vector
 * @param v1
 * @return 
 */
Vector4f scale(const Vector4f& v1, float scaleFactor);

/**
 * Performs the cross product of two vector
 * @pre The vectors have at least 3 dimensions
 * @return 
 */
Vector4f cross(const Vector4f& v1, const Vector4f& v2);

/**
 * Performs a point-wise multiplication of the two vectors
 * @param v1
 * @param v2
 * @return 
 */
Vector4f pwMult(const Vector4f& v1, const Vector4f& v2);

/**
 * Returns the magnitude of the vector
 * @param v
 */
float mag3f(const Vector4f& v);

/**
 * Normalizes the given vector
 * @param v
 */
void normalize(Vector4f* v);

/**
 * Rounds the components of a vector to ints
 */
void roundCompsToInt(Vector4f* v);

#endif