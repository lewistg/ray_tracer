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

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <string>
#include <vector>
#include <memory>
#include "vector_interface.h"
#include "vector.h"
#include "matrix_interface.h"
#include "matrix_vector.h"


namespace mvl
{
	/**
	 * Standard matrix
	 */
	template <class T>
	class Matrix: public IMatrix<T> 
	{
	public:
		/**
		 * No arg constructor 
		 * @param numRows
		 * @param numCols
		 */
		Matrix();

		/**
		 * Constructs a new matrix given some raw data. 
		 * @param numRows
		 * @param numCols
		 * @param rowMajor: Flag that indicates how to interpret the data
		 */
		Matrix(T* rawMatData, unsigned int numRows, unsigned int numCols, bool rowMajor = true);

		/**
		 * Constructs a new matrix with the given dimensions.
		 * 
		 * @param numRows
		 * @param numColumns
		 */
		Matrix(unsigned int numRows, unsigned int numCols);

		/**
		 * Copy constructor
		 * 
		 * @param cpy
		 */
		Matrix(const Matrix& cpy);

		/**
		 *  Copy constructor for generic matrices
		 */
		Matrix(const IMatrix<T>& cpy);

		/**
		 * Copy constructor
		 */
		virtual ~Matrix();

		/**
		 * Override
		 */
		virtual const IMatrix<T>& operator=(const IMatrix<T>& rhs);

		/**
		 * Override
		 */
		virtual IVector<T>& getCol(unsigned int colIndex);

		/**
		 * Override
		 */
		virtual const IVector<T>& getCol(unsigned int colIndex) const;

		/**
		 * Override
		 */
		virtual const IVector<T>& operator[](unsigned int rowIndex) const;

		/**
		 * Override
		 */
		virtual IVector<T>& operator[](unsigned int rowIndex);

		/**
		 * Override 
		 */
		virtual unsigned int getNumRows() const;

		/**
		 * Override 
		 */
		virtual unsigned int getNumCols() const;

		/**
		 * Override 
		 */
		virtual std::string toString();

		/**
		 * Transposes the matrix. Attempts to minimize
		 */
		void transpose();


	private:
		/**Dimensions of the matrix*/
		unsigned int _numRows;
		unsigned int _numCols;
		/**Raw matrix data*/
		T* _mat;
		/**The matrix rows*/
		std::vector<MatrixVector<T> > _matRows;
		/**The matrix columns*/
		std::vector<MatrixVector<T> > _matCols;
		//MatrixVector<T> _cols;

		/**
		 * Helper function for copying another matrix
		 */
		void copy(const IMatrix<T>& cpy);

		/**
		 * Helper function for setting up the row and column vectors
		 */
		void createMatVectors();
	};

	//******************************************************************************
	// We must include the implementation in the same file to avoid compiler problems
	//******************************************************************************

	template <class T>
	Matrix<T>::Matrix():
		_numRows(0),
		_numCols(0),
		_mat(nullptr)
	{
		
	}

	template <class T>
	Matrix<T>::Matrix(T* rawMatData, unsigned int numRows, unsigned int numCols, bool rowMajor/*= true*/):
		_numRows(numRows),
		_numCols(numCols),
		_mat(nullptr)
	{
		assert(rowMajor == true);
		if(_numRows * _numCols > 0)
		{
			_mat = new T[numRows * numCols];
			for(int i = 0; i < _numRows * _numCols; i++)
				_mat[i] = rawMatData[i];
		}

		createMatVectors();
	}

	template <class T>
	Matrix<T>::Matrix(unsigned int numRows, unsigned int numCols):
		_numRows(numRows),
		_numCols(numCols),
		_mat(nullptr)
	{
		if(_numRows * _numCols > 0) 
		{
			_mat = new T[_numRows * _numCols];
			for(int i = 0; i < _numRows * _numCols; i++)
				_mat[i] = 0;

			createMatVectors();
		}
	}

	template <class T>
	Matrix<T>::Matrix(const IMatrix<T>& cpy):
		_numRows(0),
		_numCols(0),
		_mat(nullptr)
	{
		copy(cpy);
	}

	template <class T>
	Matrix<T>::Matrix(const Matrix<T>& cpy):
		_numRows(0),
		_numCols(0),
		_mat(nullptr)
	{
		copy(cpy);
	}

	template <class T>
	Matrix<T>::~Matrix()
	{
		if(_mat != nullptr)
		{
			delete[] _mat;
			_mat = nullptr;
		}
	}

	template <class T>
	const IMatrix<T>& Matrix<T>::operator=(const IMatrix<T>& rhs)
	{
		if(&rhs != this)
			copy(rhs);

		return *this;
	}

	template <class T>
	void Matrix<T>::copy(const IMatrix<T>& cpy)
	{
		if(_mat != nullptr)
		{
			delete[] _mat;
			_mat = nullptr;
		}

		_numRows = cpy.getNumRows();
		_numCols = cpy.getNumCols();

		if(_numRows * _numCols > 0)
		{
			_mat = new T[_numRows * _numCols];
			for(int i = 0; i < _numRows; i++)
			{
				for(int j = 0; j < _numCols; j++)
				{
					int rawMatDataIndex = (i * _numCols) + j;
					_mat[rawMatDataIndex] = cpy[i][j];
				}
			}

			createMatVectors();
		}
	}

	template <class T>
	void Matrix<T>::createMatVectors()
	{
		if(_numRows * _numCols > 0)
		{
			_matRows.resize(_numRows);
			for(int i = 0; i < _numRows; i++)
				_matRows[i].setDimension(_numCols);

			_matCols.resize(_numCols);
			for(int j = 0; j < _numCols; j++)
				_matCols[j].setDimension(_numRows);

			for(int i = 0; i < _numRows * _numCols; i++) 
			{
				int row = i / _numCols;
				int col = i % _numCols;
				_matRows[row].setEntryPtr(col, _mat[i]);
				_matCols[col].setEntryPtr(row, _mat[i]);
			}
		}
	}

	template <class T>
	const IVector<T>& Matrix<T>::operator[](unsigned int rowIndex) const
	{
		assert(rowIndex < _numRows);
		return _matRows[rowIndex];
	}

	template <class T>
	IVector<T>& Matrix<T>::operator[](unsigned int rowIndex)
	{
		assert(rowIndex < _numRows);
		return _matRows[rowIndex];
	}

	template <class T>
	IVector<T>& Matrix<T>::getCol(unsigned int colIndex)
	{
		assert(colIndex < _numCols);
		return _matCols[colIndex];
	}

	template <class T>
	const IVector<T>& Matrix<T>::getCol(unsigned int colIndex) const
	{
		assert(colIndex < _numCols);
		return _matCols[colIndex];
	}

	template <class T>
	unsigned int Matrix<T>::getNumRows() const
	{
		return _numRows;
	}

	template <class T>
	unsigned int Matrix<T>::getNumCols() const
	{
		return _numCols;
	}

	template <class T>
	std::string Matrix<T>::toString()
	{
		std::string matrixString = "[";

		if(_numRows > 0) 
		{
				matrixString += _matRows[0].toString();
				for(int i = 1; i < _numRows; i++)
					matrixString += ",\n" + _matRows[i].toString();

		}

		matrixString += "]";
		return matrixString;
	}

	template <class T>
	void Matrix<T>::transpose()
	{
		if(_numCols == 0 && _numRows == 0)	{
			assert(_mat == nullptr);
			return;
		}

		const unsigned int transMatCols = _numRows;
		
		// calculates the transposed position of i
		auto transposeMatIndex = [&](int i) {
			assert(i < _numCols * _numRows);
			int row = i / _numCols;
			int col = i % _numCols;

			int transMatRowIndex = col;
			int transMatColIndex = row;

			int iTransposed = (transMatRowIndex * transMatCols) + transMatColIndex;

			return iTransposed;
		};

		bool settledPos[_numCols * _numRows]; 
		for(int j = 0; j < _numCols * _numRows; j++)
			settledPos[j] = false;

		for(int i = 0; i < _numRows * _numCols; i++)
		{
			if(settledPos[i])
				continue;

			int toIndex = transposeMatIndex(i);
			int fromIndex = i; 

			if(toIndex == fromIndex)
				continue;

			T bumpedValue = _mat[fromIndex];
			T nextBumpedValue;
			while(true) 
			{
				nextBumpedValue = _mat[toIndex];

				_mat[toIndex] = bumpedValue; 
				settledPos[toIndex] = true;

				bool completedCycle = (toIndex == i);
				if(completedCycle)
					break;

				fromIndex = toIndex;
				toIndex = transposeMatIndex(fromIndex);
				bumpedValue = nextBumpedValue; 
			}
		}
		
		int oldNumRows = _numRows; 
		_numRows = _numCols;
		_numCols = oldNumRows;
		createMatVectors();
	}
}
#endif