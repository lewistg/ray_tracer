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

#include "vector.h"

namespace gmath
{
	Vector::Vector():_components(NULL), _dimensions(0)
	{
		
	}
	
	Vector::Vector(int len):_dimensions(len)
	{
		assert(len > 0);
		_components = new float[len];
	}
	
	Vector::Vector(const float* source, int len):_dimensions(len)
	{
		assert(len > 0);
		_components = new float[len];
		for(int i = 0; i < len; i++)
			_components[i] = source[i];
	}
	
	Vector::Vector(const Vector& orig):_components(NULL), _dimensions(0)
	{
		copy(orig);
	}
	
	const Vector& Vector::operator = (const Vector& rSide)
	{
		if(&rSide == this)
			return *this;
		
		copy(rSide);
		
		return rSide;
	}
	
	const Vector& Vector::operator += (const Vector& rSide)
	{
		assert(_dimensions == rSide._dimensions);
		
		for(int i = 0; i < _dimensions; i++)
			_components[i] += rSide._components[i];
		
		return *this;
	}
	
	Vector::~Vector()
	{	
		if(_components != NULL)
			delete[] _components;
	}
	
	void Vector::scale(float scaleFactor)
	{
		for(int i = 0; i < _dimensions; i++)
			_components[i] *= scaleFactor;
	}
	
	float& Vector::operator[] (int column) const
	{
		assert(column >= 0);
		assert(column < _dimensions);
		return _components[column];
	}
	
	float Vector::getComp(int index) const
	{
		assert(index >= 0);
		assert(index < _dimensions);
		return _components[index];
	}
	
	bool Vector::operator == (const Vector& rSide)
	{
		if(_dimensions != rSide._dimensions)
			return false;
		
		for(int i = 0; i < _dimensions; i++)
			if(_components[i] != rSide._components[i])
				return false;
		
		return true;
	}
	
	bool Vector::operator != (const Vector& rSide)
	{
		return !(*this == rSide);
	}
	
	int Vector::getDimensions() const
	{
		return _dimensions;
	}
	
	string Vector::toString() const
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
	
	void Vector::copy(const Vector& rowToCopy)
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
			_components = new float[_dimensions];
			for(int i = 0; i < _dimensions; i++)
				_components[i] = rowToCopy._components[i];
		}
	}
	
	float dot(const Vector& v1, const Vector& v2)
	{
		assert(v1.getDimensions() == v2.getDimensions());
		float product = 0;
		for(int i = 0; i < v1.getDimensions(); i++)
		{	
			product += ((const float) v1[i]) * ((const float) v2[i]);
		}
			
		return product;
	}	
	
	const float* Vector::getData() const
	{
		return _components;
	}
	
	float& x(const Vector& v)
	{
		assert(v.getDimensions() >= 1);
		return v[0];
	}
	
	float& y(const Vector& v)
	{
		assert(v.getDimensions() >= 2);
		return v[1];
	}	
	
	float& z(const Vector& v)
	{
		assert(v.getDimensions() >= 3);
		return v[2];
	}	
	
	float& w(const Vector& v)
	{
		assert(v.getDimensions() >= 4);
		return v[3];
	}		
	
	float& r(const Vector& v)
	{
		assert(v.getDimensions() >= 1);
		return v[0];
	}
	
	float& g(const Vector& v)
	{
		assert(v.getDimensions() >= 2);
		return v[1];
	}	
	
	float& b(const Vector& v)
	{
		assert(v.getDimensions() >= 3);
		return v[2];
	}	
	
	float& a(const Vector& v)
	{
		assert(v.getDimensions() >= 4);
		return v[3];
	}		
	
	Vector cross(const Vector& v1, const Vector& v2)
	{
		assert(v1.getDimensions() >= 3);
		assert(v2.getDimensions() >= 3);
		
		Vector result(3);
		
		const int X = 0;
		const int Y = 1;
		const int Z = 2;
		
		result[X] = y(v1) * z(v2) - z(v1) * y(v2);
		result[Y] = -(x(v1) * z(v2) - z(v1) * x(v2));
		result[Z] = x(v1) * y(v2) - y(v1) * x(v2);
				
		return result;
	}	
}