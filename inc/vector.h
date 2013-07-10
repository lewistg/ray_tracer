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

#ifndef VECTOR_H
#define	VECTOR_H

#include <string>
#include <sstream>
#include <iostream>
#include <assert.h>
#include <math.h>

using namespace std;

namespace gmath
{
	/**
	 * A vector of floats
	 * @return 
	 */
	class Vector
	{
		public: 
			/**
			 * Empty constructor
			 * @param len
			 */
			Vector();

			/**
			 * Empty constructor
			 * @param len the length of the matrix 
			 */
			Vector(int len);

			/**
			* Constructs Vector from an array 
			* @param source
			* @param len of the array
			*/
			Vector(const float* source, int len);
			
			/**
			 * Copy constructor
			 * @param orig the matrix row to copy
			 * @return 
			 */
			Vector(const Vector& orig);

			/**
			* Overloaded assignment operator
			* @param rSide right side of the assignment operator
			* @return 
			*/
			const Vector& operator = (const Vector& rSide);
			
			/**
			* Overloaded increment operator. Does compoenent-wise
			* addition.
			* @pre rSide has the same dimension of the rSide
			* @param rSide
			* @return 
			*/
			const Vector& operator += (const Vector& rSide);
			
			/**
			 * Destructor
			 */
			virtual ~Vector();

			/**
			* Scales the matrix
			* scaleFactor multiplier for all of the components
			*/
			void scale(float scaleFactor);
			
			/**
			* Gets the dimension of the vector
			* @return a integer indicating the dimension of the Vector
			*/
			int getDimensions() const;
			
			/**
			 * Indexes into matrix row
			 * @param column
			 * @return 
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
			bool operator == (const Vector& rSide);
			
			/**
			 * Checks to see if two vectors are in-equal component wise;
			 */			
			bool operator != (const Vector& rSide);
			
			/**
			* Converts the vector to a float array
			* @return 
			*/
			const float* getData() const;
			
			/**
			 * Returns a string representing the matrix row
			 * @return a string with the row's string representation
			 */
			string toString() const;
		private:
			int _dimensions;		// length of the row
			float* _components;	// the raw values
			
			/**
			* Utility function for copying a matrix row into this one.
			* @param matrixToCopy
			*/
			void copy(const Vector& matrixToCopy);
	};
	
	/**
	 * Gets the x component of the vector
	 * @pre The vector has at least one dimension
     * @return float of the x coordinate
     */
	float& x(const Vector& v);
	
	/**
	 * Gets the y component of the vector
	 * @pre The vector has at least two dimension
     * @return float of the y coordinate
     */	
	float& y(const Vector& v);
	
	/**
	 * Gets the z component of the vector
	 * @pre The vector has at least three dimension
     * @return float of the z coordinate
     */	
	float& z(const Vector& v);
	
	/**
	 * Gets the z component of the vector
	 * @pre The vector has at least three dimension
     * @return float of the z coordinate
     */	
	float& w(const Vector& v);	

	/**
	 * Gets the r component of the vector
	 * @pre The vector has at least one dimension
     * @return float of the r coordinate
     */
	float& r(const Vector& v);
	
	/**
	 * Gets the g component of the vector
	 * @pre The vector has at least two dimension
     * @return float of the g coordinate
     */	
	float& g(const Vector& v);
	
	/**
	 * Gets the b component of the vector
	 * @pre The vector has at least three dimension
     * @return float of the b coordinate
     */	
	float& b(const Vector& v);
	
	/**
	 * Gets the a component of the vector
	 * @pre The vector has at least three dimension
	 * @return float of the a coordinate
	 */	
	float& a(const Vector& v);	
	
	
	/**
	 * Performs the dot product of two vectors
	 * @pre The vectors have the same dimensions
	 * @return A float of the dot product
	 */
	float dot(const Vector& v1, const Vector& v2);
	
	/**
	 * Adds two vectors together
	 * @pre v1 and v2 have the same dimensions
     * @param v1
     * @param v2
     * @return 
     */
	Vector add(const Vector& v1, const Vector& v2);
	
	/**
	 * Performs the cross product of two vector
	 * @pre The vectors have at least 3 dimensions
     * @return 
     */
	Vector cross(const Vector& v1, const Vector& v2);	
}


#endif	/* VECTOR_H */

