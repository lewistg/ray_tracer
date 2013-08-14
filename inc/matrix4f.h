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

#ifndef _MATRIX4F_H_
#define _MATRIX4F_H_

#include <assert.h>
#include "square_matrix_stack.h"
#include "graphics_vector.h"

using namespace gmath;

/**
 * A 4x4 matrix of 4 floats
 */
class Matrix4f
{
		public:
		/**
		 * Default constructor
		 */
		Matrix4f();

		/**
		 * Copy constructor
		 * @param orig
		 */
		Matrix4f(const Matrix4f& orig);

		/**
		 * @param source Contains 16 floats in column-major 
		 */
		Matrix4f(float source[]);

		/**
		 * Destructor
		 */
		virtual ~Matrix4f();

		/**
		 * Overloaded assignment operator
		 * @param rSide the right side of the = operator
		 * @return a reference to rSide
		 */
		const Matrix4f& operator = (const Matrix4f& rSide);

		/**
		 * Returns the row vector indexed by row.
		 * @pre i is a valid index
		 * @return a constant reference to the row vector
		 */
		mvl::GVector4f getRowVec(int row) const;

		/**
		 * Returns the column vector indexed by col.
		 * @param col
		 * @return a constant reference to the column vector
		 */
		mvl::GVector4f getColVec(int col) const;

		/**
		 * Returns the matrix as an array of floats
		 * @param columnMajorMat The matrix in column major form.
		 * This matrix should be 16 floats long
		 */
		void toArray(float* columnMajorMat);

		/**
		 * Converts the matrix to a string
		 * @return a string version of the matrix
		 */
		string toString() const;

		/**
		 * Inverts the matrix
		 */
		void invert();

		/**
		 * Gets the dimension of the matrix
		 */
		int getDimension() const;

		/**
		 * Scales the entries of the matrix
		 * @param scaleFactor multiplier for the entries
		 */
		void scaleEntries(float scaleFactor);

		/**
		 * Overload the 
		 * @param row
		 * @return a row mvl::GVector4f corresponding to the row index
		 */
		mvl::GVector4f& operator[] (int row);
		
		mvl::GVector4f& operator[] (int row) const;

		/**
		 * Overloaded equality operator. Checks to see if
		 * all the entries are the same between each matrix.
		 * @return true if they are and false otherwise
		 */
		bool operator == (const Matrix4f& rSide);
		
		bool operator == (const Matrix4f& rSide) const;

		/**
		 * Gets the determinant of the matrix
		 */
		float det();

		/**
		 * Indicates whether or not the matrix can be inverted
		 * @return true if it can be inverted and false otherwise
		 */
		bool canBeInverted();

		/**
		 * Gets the inverse matrix
		 * @pre this matrix has be be invertable
		 * @return a Matrix4f of the inverse
		 */
		Matrix4f inverse();

	private:
		static const int DIMENSION_FOUR = 4;
		int _dimension;			// dimensions of the matrix
		mvl::GVector4f* _vectorRows;	// holds the matrix values

		/**
		 * Utility function for getting a minor matrix.
		 * @param row the row that should be "struck out"
		 * @param col the column that should be "struck out"
		 */
		SquareMatrix getMinor(int skipRow, int skipCol);

		/**
		 * Utility matrix of cofactors.
		 * @return a Matrix4f of the cofactors
		 */
		Matrix4f getCofactorMatrix();
};

/*****************************************************************
 * Utility functions
 *****************************************************************/

/**
 * Multiplies two matrices
 * @param m1
 * @param m2
 * @return the result of the multiplication
 */
Matrix4f mult(const Matrix4f& m1, const Matrix4f& m2);

/**
 * Multiplies a matrix by a vector
 * @param m
 * @param v
 * @return 
 */
mvl::GVector4f mult(const Matrix4f& m, const mvl::GVector4f& v);

/**
 * Transposes the matrix m.
 */
Matrix4f transpose(const Matrix4f& m);

/**
 * Calculates the matrix of cofactors for a square matrix
 * @pre m is an nxn matrix
 * @param m
 * @return 
 */
Matrix4f cofactorMatrix(const Matrix4f& m);

/**
 * Anything values in m within a tolerance of 0 is set to zero
 */
bool practicallyIdentity(const Matrix4f& m, float tolerance = 0.0001);

#endif