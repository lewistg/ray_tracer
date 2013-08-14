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

#ifndef _MATRIX_VECTOR_H_
#define _MATRIX_VECTOR_H_

#include <assert.h>
#include "vector_interface.h"

namespace mvl
{
	/**
	 * This vector can be used as either a row or column of a matrix 
	 */
	template <class T>
	class MatrixVector: public IVector<T>
	{
	public:
		/**
		 * Constructor 
		 * @param compPtrs Pointers to the vector components
		 */
		MatrixVector(const std::vector<T*> compPtrs);

		/**
		 * No-arg constructor
		 */
		MatrixVector();

		/**
		 * No-arg constructor
		 */
		virtual ~MatrixVector();

		/**
		 * Override
		 */
		virtual const IVector<T>& operator =(const IVector<T>& rSide);

		/**
		 * Override
		 */
		virtual const IVector<T>& operator +=(const IVector<T>& rSide);

		/**
		 * Override
		 */
		virtual void scale(T scaleFactor);

		/**
		 * Override
		 */
		virtual void clear(); 

		/**
		 * Override
		 */
		virtual void setComponents(const T* components, unsigned int len);

		/**
		 * Override
		 */
		virtual unsigned int getDimension() const;

		/**
		 * Override
		 */
		void setDimension(unsigned int dimension);

		/**
		 * Override
		 */
		virtual const T& operator[] (unsigned int column) const;

		/**
		 * Override
		 */
		virtual T& operator[] (unsigned int column);

		/**
		 * Override
		 */
		virtual bool operator ==(const IVector<T>& rSide);

		/**
		 * Override
		 */
		virtual bool operator !=(const IVector<T>& rSide);

		/**
		 * Override
		 */
		virtual const IVector<T>& operator*=(T scalar);

		/**
		 * Override
		 */
		virtual std::string toString() const;

		/**
		 * The indexed component will point the given matrix entry.
		 */
		void setEntryPtr(unsigned int comp, T& ptrToMatEntry);

	private:	
		/*Pointers to the actual vector components from the matrix*/
		std::vector<T*> _compPtrs;
	};

	template <class T>
	MatrixVector<T>::MatrixVector(const std::vector<T*> compPtrs): _compPtrs(compPtrs)
	{

	}

	template <class T>
	MatrixVector<T>::MatrixVector()
	{

	}

	template <class T>
	MatrixVector<T>::~MatrixVector()
	{

	}

	template <class T>
	const IVector<T>& MatrixVector<T>::operator =(const IVector<T>& rSide)
	{
		assert(getDimension() == rSide.getDimension());

		for(int i = 0; i < getDimension(); i++)
			(*this)[i] = rSide[i];
	}

	template <class T>
	const IVector<T>& MatrixVector<T>::operator +=(const IVector<T>& rSide)
	{
		assert(getDimension() == rSide.getDimension());

		for(int i = 0; i < getDimension(); i++)
			(*this)[i] += rSide[i];
	}

	template <class T>
	void MatrixVector<T>::scale(T scaleFactor)
	{
		*this *= scaleFactor;
	}

	template <class T>
	void MatrixVector<T>::clear()
	{
		_compPtrs.clear();
	}

	template <class T>
	void MatrixVector<T>::setComponents(const T* components, unsigned int len)
	{
		assert(len == _compPtrs.size());
		for(int i = 0; i < len; i++) {
			*(_compPtrs[i]) = components[i]; 
		}
	}

	template <class T>
	unsigned int MatrixVector<T>::getDimension() const
	{
		return _compPtrs.size();
	}

	template <class T>
	void MatrixVector<T>::setDimension(unsigned int dimension)
	{
		_compPtrs.resize(dimension);
	}

	template <class T>
	T& MatrixVector<T>::operator[] (unsigned int column) 
	{
		assert(_compPtrs.size());
		return *(_compPtrs[column]);
	}

	template <class T>
	const T& MatrixVector<T>::operator[] (unsigned int column) const
	{
		assert(_compPtrs.size());
		return *(_compPtrs[column]);
	}

	template <class T>
	bool MatrixVector<T>::operator ==(const IVector<T>& rSide)
	{
		if(getDimension() != rSide.getDimension())
			return false;

		for(int i = 0; i < getDimension(); i++)
			if(*(_compPtrs[i]) != rSide[i])
				return false;

		return true;
	}

	template <class T>
	bool MatrixVector<T>::operator !=(const IVector<T>& rSide)
	{
		return !(*this == rSide);
	}

	template <class T>
	const IVector<T>& MatrixVector<T>::operator*=(T scalar)
	{
		for(int i = 0; i < getDimension(); i++)
			(*this)[i] *= scalar;
	}

	template <class T>
	std::string MatrixVector<T>::toString() const
	{
		std::stringstream rowString;
		rowString << "[";
		for(int i = 0; i < getDimension(); i++)
		{
			rowString << (*this)[i];
			
			if(i < getDimension() - 1)
				rowString << ", ";
		}
		rowString << "]";
			
		return rowString.str();
	}

	template <class T>
	void MatrixVector<T>::setEntryPtr(unsigned int comp, T& ptrToMatEntry)
	{
		assert(comp < getDimension());
		_compPtrs[comp] = &ptrToMatEntry;
	}
}
#endif