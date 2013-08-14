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

#include "matrix4f.h"

Matrix4f::Matrix4f():_vectorRows(new mvl::GVector4f[DIMENSION_FOUR])
{
}

Matrix4f::Matrix4f(float source[]):_vectorRows(NULL)
{
	_vectorRows = new mvl::GVector4f[DIMENSION_FOUR];

	for(int col = 0; col < DIMENSION_FOUR; col++)
		for(int row = 0; row < DIMENSION_FOUR; row++)
			_vectorRows[row][col] = source[(col * DIMENSION_FOUR) + row];			
}

Matrix4f::Matrix4f(const Matrix4f& orig):_vectorRows(NULL)
{
	_vectorRows = new mvl::GVector4f[DIMENSION_FOUR];
	for(int row = 0; row < DIMENSION_FOUR; row++)
		_vectorRows[row] = orig._vectorRows[row];
}

Matrix4f::~Matrix4f() 
{
	if(_vectorRows != NULL)
		delete[] _vectorRows;
}

const Matrix4f& Matrix4f::operator = (const Matrix4f& rSide)
{
	if(&rSide == this)
		return *this;

	if(_vectorRows != NULL)
	{
		delete[] _vectorRows;
		_vectorRows = NULL;
	}
	
	_vectorRows = new mvl::GVector4f[DIMENSION_FOUR];
	for(int row = 0; row < DIMENSION_FOUR; row++)
		_vectorRows[row] = rSide._vectorRows[row];			

	return *this;
}

int Matrix4f::getDimension() const
{
	return DIMENSION_FOUR;
}

void Matrix4f::scaleEntries(float scaleFactor)
{
	for(int row = 0; row < DIMENSION_FOUR; row++)
		_vectorRows[row].scale(scaleFactor);
}

mvl::GVector4f& Matrix4f::operator[] (int row)
{
	assert(row >= 0);
	assert(row < DIMENSION_FOUR);
	return _vectorRows[row];
}

mvl::GVector4f& Matrix4f::operator[] (int row) const
{
	assert(row >= 0);
	assert(row < DIMENSION_FOUR);
	return _vectorRows[row];	
}

bool Matrix4f::operator == (const Matrix4f& rSide)
{
	for(int row = 0; row < DIMENSION_FOUR; row++)
		if(_vectorRows[row] != rSide._vectorRows[row])
			return false;

	return true;
}

bool Matrix4f::operator == (const Matrix4f& rSide) const
{
	for(int row = 0; row < DIMENSION_FOUR; row++)
		if(_vectorRows[row] != rSide._vectorRows[row])
			return false;

	return true;
}

void Matrix4f::invert()
{

}

mvl::GVector4f Matrix4f::getRowVec(int row) const
{
	return mvl::GVector4f(_vectorRows[row]);
}

mvl::GVector4f Matrix4f::getColVec(int col) const
{
	mvl::GVector4f colVec;
	for(int row = 0; row < DIMENSION_FOUR; row++)
	{
		mvl::GVector4f rowVec = (const mvl::GVector4f) _vectorRows[row];
		colVec[row] = (const float) rowVec[col];
	}

	return colVec;
}

void Matrix4f::toArray(float* columnMajorMat) 
{
	for(int col = 0; col < DIMENSION_FOUR; col++)
		for(int row = 0; row < DIMENSION_FOUR; row++)
			columnMajorMat[col * DIMENSION_FOUR + row] = _vectorRows[row][col];
}

string Matrix4f::toString() const
{
	stringstream matrixString;
	for(int i = 0; i < DIMENSION_FOUR; i++)
	{
		matrixString << _vectorRows[i].toString();

		if(i < DIMENSION_FOUR - 1)
			matrixString << "\n";
	}

	return matrixString.str();
}

float Matrix4f::det()
{
	if(DIMENSION_FOUR == 2)
		return ((*this)[0][0] * (*this)[1][1]) - ((*this)[0][1] * (*this)[1][0]);

	// calculate the cofactor matrix
	float det = 0;
	const int COL = 0;
	for(int row = 0; row < DIMENSION_FOUR; row++)
	{
		det += (*this)[row][COL] * 
				(pow(-1, row + COL) * getMinor(row, COL).det());
	}

	return det;
}	

bool Matrix4f::canBeInverted()
{
	return det() != 0;
}

Matrix4f Matrix4f::inverse()
{
	assert(canBeInverted());
	
	Matrix4f inverse = transpose(getCofactorMatrix());
	inverse.scaleEntries(1/det());
	return inverse;
}

SquareMatrix Matrix4f::getMinor(int skipRow, int skipCol)
{
	assert(DIMENSION_FOUR > 1);
	SquareMatrix minorMat(DIMENSION_FOUR - 1);
	int minorRow = 0;
	for(int row = 0; row < DIMENSION_FOUR; row++)
	{
		if(row == skipRow)
			continue;

		int minorCol = 0;
		for(int col = 0; col < DIMENSION_FOUR; col++)
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

Matrix4f Matrix4f::getCofactorMatrix()
{
	Matrix4f cofactors;
	int sign = -1;
	for(int row = 0; row < DIMENSION_FOUR; row++)
	{
		for(int col = 0; col < DIMENSION_FOUR; col++)
		{
			sign = (int) pow(-1, row + col);
			cofactors[row][col] = sign * getMinor(row, col).det();
		}
	}


	return cofactors;
}

Matrix4f transpose(const Matrix4f& m)
{
	Matrix4f mTransposed;
	for(int row = 0; row < m.getDimension(); row++)
	{
		for(int col = 0; col < m.getDimension(); col++)
		{
			mTransposed[col][row] = m.getRowVec(row).getComp(col);
		}
	}


	return mTransposed;
}

Matrix4f mult(const Matrix4f& m1, const Matrix4f& m2)
{	
	assert(m1.getDimension() == m2.getDimension());
	Matrix4f result;
	const int MATRIX_DIMENSION = m1.getDimension();
	for(int row = 0; row < MATRIX_DIMENSION; row++)
		for(int col = 0; col < MATRIX_DIMENSION; col++)
			result[row][col] = dot(m1.getRowVec(row), m2.getColVec(col));

	return result;
}

mvl::GVector4f mult(const Matrix4f& m, const mvl::GVector4f& v)
{
    //cout << "Multiplying: " << m.toString() << endl;
    //cout << "By the vector: " << v.toString() << endl;
    
    
    mvl::GVector4f result;
    for(int row = 0; row < 4; row++)
	for(int col = 0; col < 4; col++)
	    result[row] = dot(m.getRowVec(row), v);
    
    return result;
}

bool practicallyIdentity(const Matrix4f& m, float tolerance)
{
	Matrix4f mCopy(m);
	
	for(int i = 0; i < 4; i++)
        {
            	for(int j = 0; j < 4; j++)
                {
                    if(i == j)
                    {
                        if(fabs(m[i][j] - 1) > tolerance)
                            return false;
                    }
                    else
                    {
                        if(fabs(m[i][j] - 0) > tolerance)
                            return false;
                    }
                }
        }
	
		
	return true;
}