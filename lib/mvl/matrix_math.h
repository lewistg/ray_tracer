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

#ifndef _MATRIX_MATH_H_
#define _MATRIX_MATH_H_

#include <cmath>
#include <string>
#include <vector>
#include <memory>
#include "matrix.h"
#include "matrix_interface.h"
#include "vector_math.h"
#include "row_scale.h"
#include "swap_rows.h"
#include "replace_row.h"
#include "row_operation_list.h"
#include "null_row_operation_list.h"
#include "general_math_utils.h"

namespace mvl 
{
	/**
	 * Helper functions and structures for performing ref 
	 */
	namespace {
		struct MatrixCoord
		{
			MatrixCoord(bool valid): row(0), col(0), isValid(valid)
			{
			}

			MatrixCoord(unsigned int r, unsigned int c, bool valid)
				: row(r), 
				col(c), 
				isValid(valid)
			{
			}

			bool operator==(const MatrixCoord& rhs) const
			{
				return (row == rhs.row && col == rhs.col);
			}

			bool operator!=(const MatrixCoord& rhs) const
			{
				return !(*this == rhs);
			}

			std::string toString() const
			{
				std::stringstream matCoordString;
				matCoordString << "(row=" << row << ", col=" << col << ", valid=" << isValid << ")";
				return matCoordString.str();
			}

			unsigned int row;
			unsigned int col;
			bool isValid;		// clients may indicate if the 
								// coordinate should be treated as valid or not
		};

		/**
		 * Searches for the next pivot position. This pivot position
		 * is restricted to being in a row below the last pivot position and
		 * a column to the right.
		 * @param m
		 * @param topSubColVector
		 * @return 
		 */
		template <class T>
		MatrixCoord findPivotInSubCol(const IMatrix<T>& m, MatrixCoord topSubColVector)
		{
			assert(topSubColVector.isValid);

			MatrixCoord currentPivotPos(false);
			for(int i = topSubColVector.row; i < m.getNumRows(); i++)
			{
				if(m[i][topSubColVector.col] != 0)
				{
					if(!currentPivotPos.isValid  ||
						(std::abs(m[currentPivotPos.row][currentPivotPos.col]) < std::abs(m[i][topSubColVector.col])))
					{
						currentPivotPos = MatrixCoord(i, topSubColVector.col, true);
					}
				}
			}

			return currentPivotPos;
		}

		
		/**
		 * Searches for the next pivot column.  
		 * @param m The matrix to be searched
		 * @param prevPivotPos The last pivot position
		 * @return The pivot column index if one can be found and -1 otherwise.
		 */
		template <class T>
		MatrixCoord findNextPivotPos(const IMatrix<T>& m, const MatrixCoord& prevLeadingEntry)	
		{
			MatrixCoord nextPivotPos(false);
			for(unsigned int j = (prevLeadingEntry.isValid ? prevLeadingEntry.col + 1 : 0);
					j < m.getNumCols(); 
					j++)
			{
				unsigned int topSubCol = (prevLeadingEntry.isValid ? prevLeadingEntry.row + 1 : 0);
				MatrixCoord topSubColVector(topSubCol, j, true);
				nextPivotPos = findPivotInSubCol(m, topSubColVector);
				if(nextPivotPos.isValid)
					break;
			}

			return nextPivotPos; 
		}

		template <class T>
		void zeroOutEntriesBelowEntry(IMatrix<T>& m, 
				const MatrixCoord& entryPos,
				IRowOperationList<T>& operationList)
		{
			assert(entryPos.isValid);

			T leadingEntryValue = m[entryPos.row][entryPos.col];

			for(unsigned int rowToReplace = entryPos.row + 1; rowToReplace < m.getNumRows(); rowToReplace++)
			{
				T elimFactor = -(m[rowToReplace][entryPos.col] / leadingEntryValue);
				ReplaceRow<T> rowReplaceOp(rowToReplace, entryPos.row, elimFactor);
				rowReplaceOp.operation(m);
				operationList.add(rowReplaceOp);

				// ensure the value is zeroed out
				m[rowToReplace][entryPos.col] = 0;
			}
		}

		template <class T>
		void zeroOutEntriesAboveEntry(IMatrix<T>& m, 
				const MatrixCoord& entryPos, 
				IRowOperationList<T>& operationList)
		{
			assert(entryPos.isValid);

			T leadingEntryValue = m[entryPos.row][entryPos.col];

			for(int rowToReplace = entryPos.row - 1; rowToReplace >= 0; rowToReplace--)
			{
				T elimFactor = -(m[rowToReplace][entryPos.col] / leadingEntryValue);
				ReplaceRow<T> rowReplaceOp(static_cast<unsigned int>(rowToReplace), entryPos.row, elimFactor);
				rowReplaceOp.operation(m);
				operationList.add(rowReplaceOp);

				// ensure the value is zeroed out
				m[rowToReplace][entryPos.col] = 0;
			}
		}

		/**
		 * Puts the given matrix into row echelon form (ref)
		 * @param m
		 * @param operationList Storage for the basic row operations that
		 * were performed to put the matrix m into rref.
		 */
		template <class T>
		void ref(IMatrix<T>& m, IRowOperationList<T>& operationList)
		{
			MatrixCoord prevLeadingEntry(false);
			MatrixCoord pivotPos(false);
			while(true)
			{
				pivotPos = findNextPivotPos(m, prevLeadingEntry);
				if(prevLeadingEntry.isValid && pivotPos.isValid)
				{
					assert(prevLeadingEntry.col < pivotPos.col);
					assert(prevLeadingEntry.row < pivotPos.row);
				}

				if(!pivotPos.isValid)
					break;

				unsigned int nextLeadingEntryRow = (prevLeadingEntry.isValid ? prevLeadingEntry.row + 1 : 0);
				SwapRows<T> rowSwapOp(pivotPos.row, nextLeadingEntryRow);
				rowSwapOp.operation(m);
				operationList.add(rowSwapOp);

				MatrixCoord nextLeadingEntryPos = MatrixCoord(nextLeadingEntryRow, pivotPos.col, true);
				zeroOutEntriesBelowEntry(m, nextLeadingEntryPos, operationList);

				prevLeadingEntry = nextLeadingEntryPos;
			}
		}

		/**
		 * Utility function for finding the leading entry in a given row
		 * @param m
		 * @param row
		 * @return The coordinates of the leading entry 
		 */
		template <class T>
		MatrixCoord leadingEntryPos(const IMatrix<T>& m, unsigned int row)
		{
			MatrixCoord leadingEntryPos(false);
			for(unsigned int j = 0; j < m.getNumCols(); j++)
			{
				if(m[row][j] != 0)	
				{
					leadingEntryPos = MatrixCoord(row, j, true);
					break;
				}
			}

			return leadingEntryPos;
		}

		/**
		 * Puts a given matrix into reduced row echelon form (rref)
		 * @param m
		 * @param operationList Storage for the basic row operations that
		 * were performed to put the matrix m into rref.
		 */
		template <class T>
		void rref(IMatrix<T>& m, IRowOperationList<T>& operationList)
		{
			ref(m, operationList);

			for(unsigned int i = 0; i < m.getNumRows(); i++)
			{
				MatrixCoord leadingEntry = leadingEntryPos(m, i);
				T leadingEntryValue = m[leadingEntry.row][leadingEntry.col];
				RowScale<T> rowScaleOp(leadingEntry.row, static_cast<T>(1) / leadingEntryValue);
				rowScaleOp.operation(m);
				operationList.add(rowScaleOp);

				zeroOutEntriesAboveEntry(m, leadingEntry, operationList);
			}
		}
	}

	/**
	 * Puts the given matrix into row echelon form (ref)
	 * @param m
	 */
	template <class T>
	void ref(IMatrix<T>& m)
	{
		NullRowOperationList<T> nullOperationList;
		ref(m, nullOperationList);
	}

	/**
	 * Puts a given matrix into reduced row echelon form (rref)
	 * @param m
	 * @param operationList Storage for the basic row operations that
	 * were performed to put the matrix m into rref.
	 */
	template <class T>
	void rref(IMatrix<T>& m)
	{
		NullRowOperationList<T> nullOperationList;
		rref(m, nullOperationList);
	}

	/**
	 * Makes an identity matrix of the given dimension
	 * @return 
	 */
	template <class T>
	Matrix<T> makeIdentity(unsigned int dimension)
	{
		assert(dimension != 0);
		Matrix<T> identity(dimension, dimension);

		// place 1's on the diagonal
		for(int i = 0; i < dimension; i++)
			identity[i][i] = 1;

		return identity;
	}

	/**
	 * Checks for equality of matrices. Two matrices are equal
	 * if they have the same dimension and all their corresponding entries
	 * are within epsilon of each other.
	 * @pre epsilon Must be positive
	 * @return True for equality and false otherwise.
	 */
	template<class T>
	bool equal(const IMatrix<T>& m0, const IMatrix<T>& m1, T epsilon)
	{
		assert(epsilon >= 0);
		if(m0.getNumCols() != m1.getNumCols() && 
				m0.getNumRows() != m1.getNumRows())
			return false;

		for(int i = 0; i < m0.getNumRows(); i++) 
		{
			for(int j = 0; j < m0.getNumCols(); j++)
			{
				T difference = m0[i][j] - m1[i][j];
				if(difference > epsilon || difference < -epsilon)
					return false;
			}
		}

		return true;
	}

	/**
	 * Finds the inverse of a given matrix.
	 * @param m0 The matrix whose inverse is calculated.
	 * @param inverse Storage for the inverse matrix
	 * @return True is returned if the inverse is found and false otherwise.
	 * If there is an inverse it is loaded into the inverse argument. If 
	 * an inverse is not found, the inverse argument will contain garbage.
	 */
	template <class T>
	bool inverse(const IMatrix<T>& m, IMatrix<T>& inverse)
	{
		assert(m.getNumCols() == m.getNumRows());
		assert(m.getNumCols() > 0);

		RowOperationList<T> rowOperationList;
		Matrix<T> mCopy(m);
		rref(mCopy, rowOperationList);

		Matrix<T> identity = makeIdentity<T>(mCopy.getNumCols());
		if(!equal(mCopy, identity, static_cast<T>(SMALLEST_EPSILON)))
			return false;

		inverse = makeIdentity<T>(mCopy.getNumCols());
		rowOperationList.applyOperations(inverse);

		return true;
	}

	/**
	 * Multiplies two matrices
	 */
	template <class T>
	Matrix<T> mult(const IMatrix<T>& m0, const IMatrix<T>& m1)
	{
		assert(m0.getNumCols() == m1.getNumRows());

		Matrix<T> result(m0.getNumRows(), m1.getNumCols());
		for(int i = 0; i < m0.getNumRows(); i++)
			for(int j = 0; j < m1.getNumCols(); j++)
				result[i][j] = dot(m0[i], m1.getCol(j));

		return result; 
	}

	/**
	 * Multiplies a matrix by a vector
	 */
	template <class T> 
	Vector<T> mult(const IMatrix<T>& m, const IVector<T>& v)
	{
		assert(m.getNumCols() == v.getDimension());

		Vector<T> result(v.getDimension());
		for(int i = 0; i < m.getNumRows(); i++)
			for(int j = 0; j < v.getDimension(); j++)
				result[j] = dot(m[i], v);

		return result;
	}
}

#endif