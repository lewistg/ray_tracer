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

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "vector_interface.h"

#include <sstream>
#include <string>
#include <assert.h>

namespace mvl
{
	/**
	 * This vector is intended to be for numerical values: doubles, shorts, int 
	 */
	template <class T>
	class Vector: public IVector<T> 
	{
	public:
		/**
		 * Empty constructor
		 * @param len
		 */
		Vector();

		/**
		 * Empty constructor
		 * @param dimension the dimension of the vector
		 */
		Vector(unsigned int dimension);

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
		 * Copy constructor 
		 * @param rSide
		 * @return 
		 */
		Vector(const IVector<T>& orig);

		/**
		 * Overloaded assignment operator
		 * @param rSide right side of the assignment operator
		 * @return 
		 */
		virtual const Vector<T>& operator =(const Vector<T>& rSide);

		/**
		 * Override
		 */
		virtual const IVector<T>& operator =(const IVector<T>& rSide);

		/**
		 * Overloaded increment operator. Does component-wise
		 * addition.
		 * @pre rSide has the same dimension of the rSide
		 * @param rSide
		 * @return 
		 */
		virtual const IVector<T>& operator +=(const IVector<T>& rSide);

		/**
		 * Destructor
		 */
		virtual ~Vector();

		/**
		 * Scales the matrix
		 * scaleFactor multiplier for all of the components
		 * todo: Move this out of the class 
		 */
		virtual void scale(T scaleFactor);

		/**
		 * Clear entries and sets dimension to 0
		 * @param components
		 * @param len
		 */
		void clear();

		/**
		 * Sets the components of the vector
		 * @return 
		 */
		virtual void setComponents(const T* components, unsigned int len);

		/**
		 * Override
		 */
		virtual unsigned int getDimension() const;

		/**
		 * Override
		 */
		virtual void setDimension(unsigned int dimension);

		/**
		 * Override
		 */
		virtual const T& operator[] (unsigned int column) const;

		/**
		 * Override
		 */
		virtual T& operator[] (unsigned int column);

		/**
		 * Checks to see if two vectors are equal component wise;
		 */
		virtual bool operator ==(const IVector<T>& rSide);

		/**
		 * Checks to see if two vectors are in-equal component wise;
		 */
		virtual bool operator !=(const IVector<T>& rSide);

		/**
		 * Multiplies
		 */
		virtual const IVector<T>& operator*=(T scalar);

		/**
		 * Converts the vector to a float array
		 * @return 
		 */
		const T* getData() const;

		/**
		 * Returns a string representing the matrix row
		 * @return a string with the row's string representation
		 */
		virtual std::string toString() const;

	private:
		unsigned int _dimension; // length of the row
		T* _components; // the raw values

		/**
		 * Utility function for copying a generic vector
		 */
		void copy(const IVector<T>& rowToCopy);
	};

	//******************************************************************************
	// We must include the implementation in the same file to avoid compiler problems
	//******************************************************************************

	template<class T>
	Vector<T>::Vector():_components(NULL), _dimension(0)
	{

	}

	template<class T>
	Vector<T>::Vector(unsigned int dimension):_dimension(dimension)
	{
		_components = new T[dimension];
		for(int i = 0; i < dimension; i++)
			_components[i] = (T) 0; 
	}

	template<class T>
	Vector<T>::Vector(const T* source, unsigned int len):_dimension(len)
	{
		assert(source != NULL);
		_components = new float[len];
		for(int i = 0; i < len; i++)
			_components[i] = source[i];
	}
		
	template<class T>
	Vector<T>::Vector(const Vector<T>& orig):_components(NULL), _dimension(0)
	{
		copy(orig);
	}

	template<class T>
	Vector<T>::Vector(const IVector<T>& orig):_components(NULL), _dimension(0)
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
	const IVector<T>& Vector<T>::operator =(const IVector<T>& rSide)
	{
		if(&rSide == this)
			return *this;

		copy(rSide);

		return rSide;
	}

	template<class T>
	const IVector<T>& Vector<T>::operator += (const IVector<T>& rSide)
	{
		assert(_dimension == rSide.getDimension());
		
		for(int i = 0; i < _dimension; i++)
			_components[i] += rSide[i];
		
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
		for(int i = 0; i < _dimension; i++)
			_components[i] *= scaleFactor;
	}

	template<class T>
	void Vector<T>::clear()
	{
		if(_components != NULL)
		{
			delete [] _components;
			_components = NULL;
		}
		_dimension = 0;
	}

	template<class T>
	void Vector<T>::setComponents(const T* components, unsigned int len)
	{
		clear();

	}

	template<class T>
	T& Vector<T>::operator[] (unsigned int column) 
	{
		assert(column >= 0);
		assert(column < _dimension);
		return _components[column];
	}

	template<class T>
	const T& Vector<T>::operator[] (unsigned int column) const
	{
		assert(column >= 0);
		assert(column < _dimension);
		return _components[column];
	}

	template<class T>
	bool Vector<T>::operator == (const IVector<T>& rSide)
	{
		if(_dimension != rSide.getDimension())
			return false;
		
		for(int i = 0; i < _dimension; i++)
			if(_components[i] != rSide[i])
				return false;
		
		return true;
	}

	template<class T>
	bool Vector<T>::operator != (const IVector<T>& rSide)
	{
		return !(*this == rSide);
	}

	template<class T>
	const IVector<T>& Vector<T>::operator*=(T scalar)
	{
		scale(scalar);
		return *this;
	}

	template<class T>
	unsigned int Vector<T>::getDimension() const
	{
		return _dimension;
	}

	template<class T>
	void Vector<T>::setDimension(unsigned int dimension)
	{
		if(dimension == 0) 
		{
			clear();
		}
		else 
		{
			T* oldComps = _components;	
			unsigned int oldDimension = _dimension;	

			_dimension = dimension;

			_components = new T[dimension];
			for(int i = 0; i < _dimension; i++)
				_components[i] = (i < oldDimension ? oldComps[i] : 0);

			delete[] oldComps;
		}
	}

	template<class T>
	std::string Vector<T>::toString() const
	{
		std::stringstream rowString;
		rowString << "[";
		for(int i = 0; i < _dimension; i++)
		{
			rowString << _components[i];
			
			if(i < _dimension - 1)
				rowString << ", ";
		}
		rowString << "]";
			
		return rowString.str();
	}

	template <class T>
	void Vector<T>::copy(const IVector<T>& rowToCopy)
	{
		clear();		

		_dimension = rowToCopy.getDimension(); 

		if(_dimension != 0)
		{
			_components = new T[_dimension];
			for(int i = 0; i < rowToCopy.getDimension(); i++)
				_components[i] = rowToCopy[i];
		}
	}

	template<class T>
	const T* Vector<T>::getData() const
	{
		return _components;
	}
}
#endif