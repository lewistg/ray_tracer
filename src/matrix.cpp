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

#include "matrix.h"

using namespace std;

namespace gmath
{
	SquareMatrix::SquareMatrix():_dimension(0), _vectorRows(NULL)
	{
	}
	
	SquareMatrix::SquareMatrix(int dimension):_dimension(dimension), _vectorRows(NULL)
	{
		assert(dimension > 0);
		_vectorRows = new Vector[_dimension];
		for(int i = 0; i < _dimension; i++)
			_vectorRows[i] = Vector(_dimension);
	}

	SquareMatrix::SquareMatrix(float source[], int dimension): _dimension(dimension), _vectorRows(NULL)
	{
		_vectorRows = new Vector[_dimension];
		
		for(int col = 0; col < _dimension; col++)
		{
			for(int row = 0; row < _dimension; row++)
			{
				if(col == 0)
					_vectorRows[row] = Vector(_dimension);
					
				_vectorRows[row][col] = source[(col * _dimension) + row];
			}			
		}				
	}
	
	SquareMatrix::SquareMatrix(const SquareMatrix& orig):_dimension(0), _vectorRows(NULL)
	{
		_dimension = orig._dimension;
		
		if(_dimension > 0)
		{
			_vectorRows = new Vector[_dimension];
			for(int row = 0; row < _dimension; row++)
				_vectorRows[row] = orig._vectorRows[row];
		}
	}

	SquareMatrix::~SquareMatrix() 
	{
		if(_vectorRows != NULL)
			delete[] _vectorRows;
	}
	
	const SquareMatrix& SquareMatrix::operator = (const SquareMatrix& rSide)
	{
		if(&rSide == this)
			return *this;
		
		if(_vectorRows != NULL)
		{
			delete[] _vectorRows;
			_vectorRows = NULL;
		}
		
		_dimension = rSide._dimension;
		if(_dimension > 0)
		{
			_vectorRows = new Vector[_dimension];
			for(int row = 0; row < _dimension; row++)
				_vectorRows[row] = rSide._vectorRows[row];			
		}	
		
		return *this;
	}
	
	int SquareMatrix::getDimension() const
	{
		return _dimension;
	}
	
	void SquareMatrix::scaleEntries(float scaleFactor)
	{
		for(int row = 0; row < _dimension; row++)
			_vectorRows[row].scale(scaleFactor);
	}
	
	Vector& SquareMatrix::operator[] (int row)
	{
		assert(row >= 0);
		assert(row < _dimension);
		return _vectorRows[row];
	}
	
	bool SquareMatrix::operator == (const SquareMatrix& rSide)
	{
		if(_dimension != rSide._dimension)
			return false;
		
		for(int row = 0; row < _dimension; row++)
			if(_vectorRows[row] != rSide._vectorRows[row])
				return false;
		
		return true;
	}
	
	void SquareMatrix::invert()
	{
		
	}
	
	Vector SquareMatrix::getRowVec(int row) const
	{
		return Vector(_vectorRows[row]);
	}
	
	Vector SquareMatrix::getColVec(int col) const
	{
		Vector colVec(_dimension);
		for(int row = 0; row < _dimension; row++)
		{
			Vector rowVec = (const Vector) _vectorRows[row];
			colVec[row] = (const float) rowVec[col];
		}
		
		return colVec;
	}

	void SquareMatrix::toArray(float* columnMajorMat) 
	{
		for(int row = 0; row < _dimension; row++)
			for(int column = 0; column < _dimension; column++)
				columnMajorMat[row * _dimension + column] = _vectorRows[row][column];
	}
	
	string SquareMatrix::toString()
	{
		stringstream matrixString;
		for(int i = 0; i < _dimension; i++)
		{
			matrixString << _vectorRows[i].toString();
			
			if(i < _dimension - 1)
				matrixString << "\n";
		}
		
		return matrixString.str();
	}
	
	float SquareMatrix::det()
	{
		if(_dimension == 2)
			return ((*this)[0][0] * (*this)[1][1]) - ((*this)[0][1] * (*this)[1][0]);

		// calculate the cofactor matrix
		float det = 0;
		const int COL = 0;
		for(int row = 0; row < _dimension; row++)
		{
			det += (*this)[row][COL] * 
					(pow(-1, row + COL) * getMinor(row, COL).det());
		}

		return det;
	}	
	
	bool SquareMatrix::canBeInverted()
	{
		return det() != 0;
	}
	
	SquareMatrix SquareMatrix::inverse()
	{
		assert(canBeInverted());
		SquareMatrix inverse = transpose(getCofactorMatrix());
		inverse.scaleEntries(1/det());
		return inverse;
	}
	
	SquareMatrix SquareMatrix::getMinor(int skipRow, int skipCol)
	{
		assert(_dimension > 1);
		SquareMatrix minorMat(_dimension - 1);
		int minorRow = 0;
		for(int row = 0; row < _dimension; row++)
		{
			if(row == skipRow)
				continue;
			
			int minorCol = 0;
			for(int col = 0; col < _dimension; col++)
			{
				if(col == skipCol)
					continue;
				
				minorMat[minorRow][minorCol] = (*this)[row][col];
				minorCol++;
			}
			
			minorRow++;
		}
			
		return minorMat;	
	}
	
	SquareMatrix SquareMatrix::getCofactorMatrix()
	{
		SquareMatrix cofactors(_dimension);
		int sign = 1;
		for(int row = 0; row < _dimension; row++)
		{
			for(int col = 0; col < _dimension; col++)
			{
				sign = (int) pow(-1, row + col);
				cofactors[row][col] = sign * getMinor(row, col).det();
			}
		}
			
		
		return cofactors;
	}
	
	SquareMatrix transpose(const SquareMatrix& m)
	{
		SquareMatrix mTransposed(m.getDimension());
		for(int row = 0; row < m.getDimension(); row++)
		{
			for(int col = 0; col < m.getDimension(); col++)
			{
				mTransposed[col][row] = m.getRowVec(row).getComp(col);
			}
		}
			
		
		return mTransposed;
	}
	
	SquareMatrix mult(const SquareMatrix& m1, const SquareMatrix& m2)
	{	
		assert(m1.getDimension() == m2.getDimension());
		SquareMatrix result(m1.getDimension());
		const int MATRIX_DIMENSION = m1.getDimension();
		for(int row = 0; row < MATRIX_DIMENSION; row++)
			for(int col = 0; col < MATRIX_DIMENSION; col++)
				result[row][col] = dot(m1.getRowVec(row), m2.getColVec(col));
		
		return result;
	}	
}
namespace newVector 
{
	template<class T>
	Vector<T>::Vector():_components(NULL), _dimensions(0)
	{

	}
	
	template<class T>
	Vector<T>::Vector(unsigned int len):_dimensions(len)
	{
		_components = new T[len];
	}
	
	template<class T>
	Vector<T>::Vector(const T* source, unsigned int len):_dimensions(len)
	{
		assert(source != NULL);
		_components = new float[len];
		for(int i = 0; i < len; i++)
			_components[i] = source[i];
	}
		
		template<class T>
	Vector<T>::Vector(const Vector<T>& orig):_components(NULL), _dimensions(0)
	{
		copy(orig);
	}
	
	template<class T>
	const Vector<T>& Vector<T>::operator = (const Vector<T>& rSide)
	{
		if(&rSide == this)
			return *this;
		
		copy(rSide);
		
		return rSide;
	}
	
	template<class T>
	const Vector<T>& Vector<T>::operator += (const Vector<T>& rSide)
	{
		assert(_dimensions == rSide._dimensions);
		
		for(int i = 0; i < _dimensions; i++)
			_components[i] += rSide._components[i];
		
		return *this;
	}
	
	template<class T>
	Vector<T>::~Vector()
	{	
		if(_components != NULL)
			delete[] _components;
	}
	
	template<class T>
	void Vector<T>::scale(T scaleFactor)
	{
		for(int i = 0; i < _dimensions; i++)
			_components[i] *= scaleFactor;
	}
	
	template<class T>
	float& Vector<T>::operator[] (unsigned int column) const
	{
		assert(column >= 0);
		assert(column < _dimensions);
		return _components[column];
	}
	
	template<class T>
	float Vector<T>::getComp(unsigned int index) const
	{
		assert(index < _dimensions);
		return _components[index];
	}
	
	template<class T>
	bool Vector<T>::operator == (const Vector<T>& rSide)
	{
		if(_dimensions != rSide._dimensions)
			return false;
		
		for(int i = 0; i < _dimensions; i++)
			if(_components[i] != rSide._components[i])
				return false;
		
		return true;
	}
	
	template<class T>
	bool Vector<T>::operator != (const Vector<T>& rSide)
	{
		return !(*this == rSide);
	}
	
	template<class T>
	unsigned int Vector<T>::getDimensions() const
	{
		return _dimensions;
	}
	
	template<class T>
	string Vector<T>::toString() const
	{
		stringstream rowString;
		for(int i = 0; i < _dimensions; i++)
		{
			rowString << _components[i];
			
			if(i < _dimensions - 1)
				rowString << ", ";
		}
			
		return rowString.str();
	}
	
	template<class T>
	void Vector<T>::copy(const Vector<T>& rowToCopy)
	{	
		if(_components != NULL && _dimensions != 0)
		{
			delete[] _components;
			_components = NULL;
			_dimensions = 0;
		}
		 
		_dimensions = rowToCopy._dimensions;
		
		if(_dimensions != 0)
		{
			_components = new T[_dimensions];
			for(int i = 0; i < _dimensions; i++)
				_components[i] = rowToCopy._components[i];
		}
	}
	
	template<class T>
	const T* Vector<T>::getData() const
	{
		return _components;
	}
};
