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

/*	
 * File:   Matrix.h
 * Author: ty
 *
 * Created on December 17, 2012, 9:31 AM
 */	

#ifndef MATRIX_H
#define	MATRIX_H

#include <string>
#include <sstream>
#include <iostream>
#include <assert.h>
#include <math.h>
#include "vector.h"

namespace gmath
{
	
	using namespace std;	

	/**
	 * An nxn matrix of floats
	 */
	class SquareMatrix
	{
		public:
			/**
			 * Default constructor
			 */
			SquareMatrix();
			
			/**
			 * Constructor with initial dimension
			 * @param orig
			 */
			SquareMatrix(int dimension);

			/**
			 * Copy constructor
			 * @param orig
			 */
			SquareMatrix(const SquareMatrix& orig);

			/**
			 * @param source Contains 16 floats in column-major 
			 */
			SquareMatrix(float source[], int dimension);

			/**
			 * Destructor
			 */
			virtual ~SquareMatrix();
			
			/**
			 * Overloaded assignment operator
             * @param rSide the right side of the = operator
             * @return a reference to rSide
             */
			const SquareMatrix& operator = (const SquareMatrix& rSide);
			
			/**
			 * Returns the row vector indexed by row.
			 * @pre i is a valid index
			 * @return a constant reference to the row vector
             */
			Vector getRowVec(int row) const;
			
			/**
			 * Returns the column vector indexed by col.
             * @param col
             * @return a constant reference to the column vector
             */
			Vector getColVec(int col) const;

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
			string toString();

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
			 * @return a row Vector corresponding to the row index
			 */
			Vector& operator[] (int row);
			
			/**
			* Overloaded equality operator. Checks to see if
			* all the entries are the same between each matrix.
			* @return true if they are and false otherwise
			*/
			bool operator == (const SquareMatrix& rSide);
			
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
			 * @return a SquareMatrix of the inverse
			 */
			SquareMatrix inverse();
			
		private:
			int _dimension;			// dimensions of the matrix
			Vector* _vectorRows;	// holds the matrix values
			
			/**
			 * Utility function for getting a minor matrix.
			 * @param row the row that should be "struck out"
			 * @param col the column that should be "struck out"
			 */
			SquareMatrix getMinor(int skipRow, int skipCol);
			
			/**
			* Utility matrix of cofactors.
			* @return a SquareMatrix of the cofactors
			*/
			SquareMatrix getCofactorMatrix();
	};
	
	/**
	* Multiplies two matrices
	* @param m1
	* @param m2
	* @return the result of the multiplication
	*/
	SquareMatrix mult(const SquareMatrix& m1, const SquareMatrix& m2);
	
	/**
	 * Transposes the matrix m.
	 */
	SquareMatrix transpose(const SquareMatrix& m);
	
	/**
	* Calculates the matrix of cofactors for a square matrix
	* @pre m is an nxn matrix
	* @param m
	* @return 
	*/
	SquareMatrix cofactorMatrix(const SquareMatrix& m);
}

namespace newVector {

template <class T>
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
		Vector(unsigned int len);

		/**
		* Constructs Vector from an array 
		* @param source
		* @param len of the array
		*/
		Vector(const T* source, unsigned int len);
		
		/**
		 * Copy constructor
		 * @param orig the matrix row to copy
		 * @return 
		 */
		Vector(const Vector<T>& orig);

		/**
		* Overloaded assignment operator
		* @param rSide right side of the assignment operator
		* @return 
		*/
		const Vector<T>& operator = (const Vector<T>& rSide);
		
		/**
		* Overloaded increment operator. Does compoenent-wise
		* addition.
		* @pre rSide has the same dimension of the rSide
		* @param rSide
		* @return 
		*/
		const Vector<T>& operator += (const Vector<T>& rSide);
		
		/**
		 * Destructor
		 */
		virtual ~Vector();

		/**
		* Scales the matrix
		* scaleFactor multiplier for all of the components
		 * todo: Move this out of the class 
		*/
		void scale(T scaleFactor);
		
		/**
		* Gets the dimension of the vector
		* @return a integer indicating the dimension of the Vector
		*/
		unsigned int getDimensions() const;
		
		/**
		 * Indexes into matrix row
		 * @param column
		 * @return 
		 */
		float& operator[] (unsigned int column) const;	
		
		/**
		* Gets a component of the vector by index
		* @pre The index is within the bounds of the vector
		* @param index the index of the component to be retrieved
		* @return a float containing the 
		*/
		float getComp(unsigned int index) const;
		
		/**
		 * Checks to see if two vectors are equal component wise;
		 */
		bool operator == (const Vector<T>& rSide);
		
		/**
		 * Checks to see if two vectors are in-equal component wise;
		 */			
		bool operator != (const Vector<T>& rSide);
		
		/**
		* Converts the vector to a float array
		* @return 
		*/
		const T* getData() const;
		
		/**
		 * Returns a string representing the matrix row
		 * @return a string with the row's string representation
		 */
		string toString() const;
	private:
		unsigned int _dimensions;	// length of the row
		T* _components;			// the raw values
		
		/**
		* Utility function for copying a matrix row into this one.
		* @param matrixToCopy
		*/
		void copy(const Vector<T>& matrixToCopy);
};

}


/*
 * Todo: Make this matrix class generic. 
 */
template <class T>
class Matrix
{
public:
    	/**
	 * Default constructor. Creates an empty matrix.
	 */
	Matrix();

	/**
	 * Copy constructor.
	 * @param m The matrix to copy 
	 */
	Matrix(const Matrix& mCpy);

	/**
	 * Constructs an nxm matrix.
	 */
	Matrix(unsigned int n, unsigned int m);

	/**
	 * Destructor. 
	 */
	~Matrix();
	
	/**
	 * Gets one of the row vectors 
         * @param row
         * @return 
         */
	gmath::Vector& operator[] (int row);
private:
};

/*
 * Performs a row reduction of the given matrix
 */
template <class T>
void rowReduce(Matrix<T>& m);

#endif	/* MATRIX_H */
