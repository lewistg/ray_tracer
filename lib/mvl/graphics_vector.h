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

#ifndef _GRAPHICS_VECTOR_H_
#define _GRAPHICS_VECTOR_H_

#include <string>
#include <cmath>
#include <assert.h>
#include "vector.h"
#include "vector_interface.h" 

namespace mvl 
{
	template<class T, unsigned int N, unsigned int M> class GraphicsMatrix;

	/**
	 * A vector implementation geared towards graphics
	 */
	template <class T, unsigned int N> 
	class GraphicsVector
	{
		public:
			/**
			 * Constructor
			 */
			GraphicsVector();	

			/**
			 * Copy constructor
             */
			GraphicsVector(const GraphicsVector<T,N>& cpy);

			/**
			 * Assignment operator
             */
			const GraphicsVector<T, N>& operator=(const GraphicsVector<T,N>& rhs);

			/**
			 * Constructor
			 * @pre  len(source) == N
			 */
			GraphicsVector(const T source[]);

			/**
			 * Constructs GraphicsVector with two predetermined 
			 * components.
			 * @param x
			 * @param y
             */
			GraphicsVector(const T& xComp, const T& yComp);

			/**
			 * Constructs GraphicsVector with three predetermined 
			 * components.
             * @param x
             * @param y
             * @param z
             */
			GraphicsVector(const T& xComp, const T& yComp, const T& zComp);

			/**
			 * Constructs GraphicsVector with four predetermined 
			 * components.
			 * @param x
			 * @param y 
			 * @param z
			 * @param w
             */
			GraphicsVector(const T& xComp, const T& yComp, const T& zComp, const T& wComp);


			/**
			 * Constructor 
			 */
			GraphicsVector(const IVector<T>& vector);

			/**
			 * Destructor
			 */
			~GraphicsVector();

			/**
			 * Gets the indexed vector component
			 */		
			const T& operator[](unsigned int componentIndex) const; 

			/**
			 * Gets the indexed vector component
			 */
			T& operator[](unsigned int componentIndex);

			/**
			 * Gets the magnitude of the vector
             */
			T getMagnitude() const;

			/**
			 * Normalizes the vector so its magnitude is one unit
             */
			void normalize();

			/**
			 * Scales the vector by the given amount
			 */
			void scale(T scaleFactor);

			/**
			 * Gets a pointer to the raw vector data
			 * @pre len(rawData) == N
             * @return 
             */
			void getData(T rawData[]) const;

			/**
			 * Returns a string representation of the graphical vector. 
			 */
			std::string toString() const;

			/**
			 * Friend utility functions
			 */
			template <class S, unsigned int M>
			friend S dot(const GraphicsVector<S, M>& v0, const GraphicsVector<S, M>& v1);

			template <class S, unsigned int R, unsigned int C>
			friend GraphicsVector<S, C> mult(const GraphicsMatrix<S, R, C>& m, const GraphicsVector<S, C>& v);

		private:
			Vector<T> _vector;
	};

	//******************************************************************************
	// We must include the implementation in the same file to avoid compiler problems
	//******************************************************************************

	template<class T, unsigned int N>
	GraphicsVector<T,N>::GraphicsVector()
		:_vector(N)
	{

	}

	template<class T, unsigned int N>
	GraphicsVector<T,N>::GraphicsVector(const GraphicsVector<T,N>& cpy)
		:_vector(cpy._vector)
	{
	}

	template<class T, unsigned int N>
	const GraphicsVector<T,N>& GraphicsVector<T,N>::operator=(const GraphicsVector<T,N>& rhs)
	{
		if(this != &rhs)
			_vector = rhs._vector;

		return *this;
	}

	template<class T, unsigned int N>
	GraphicsVector<T,N>::GraphicsVector(const T source[]): _vector(source, N)
	{
	}

	template<class T, unsigned int N>
	GraphicsVector<T, N>::GraphicsVector(const IVector<T>& vector): _vector(vector)
	{
		assert(_vector.getDimension() == N);
	}

	template<class T, unsigned int N>
	GraphicsVector<T, N>::~GraphicsVector()
	{
	}

	template<class T, unsigned int N>
	const T& GraphicsVector<T, N>::operator[](unsigned int componentIndex) const
	{
		assert(componentIndex < N);
		return _vector[componentIndex];
	}

	template <class T, unsigned int N>
	T& GraphicsVector<T, N>::operator[](unsigned int componentIndex) 
	{
		assert(componentIndex < N);
		return _vector[componentIndex];
	}

	template <class T, unsigned int N>
	std::string GraphicsVector<T, N>::toString() const
	{
		return _vector.toString();
	}

	template <class T, unsigned int N>
	T GraphicsVector<T, N>::getMagnitude() const
	{
		T squaredSum = 0;
		for(int i = 0; i < N; i++)
			squaredSum += (_vector[i] * _vector[i]);

		T magnitude = sqrt(squaredSum);

		return magnitude;
	}

	template <class T, unsigned int N>
	void GraphicsVector<T, N>::normalize()
	{
		T magnitude = getMagnitude();
		for(int i = 0; i < N; i++)
			_vector[i] /= magnitude;
	}

	template <class T, unsigned int N>
	void GraphicsVector<T, N>::scale(T scaleFactor)
	{
		for(int i = 0; i < N; i++)
			_vector[i] *= scaleFactor;
	}

	template <class T, unsigned int N>
	void GraphicsVector<T,N>::getData(T rawData[]) const
	{
		for(int i = 0; i < N; i++)
			rawData[i] = _vector[i];
	}

	template<class T, unsigned int N>
	GraphicsVector<T, N>::GraphicsVector(const T& xComp, const T& yComp): _vector(N)
	{
		_vector[0] = xComp;
		_vector[1] = yComp;
	}

	template<class T, unsigned int N>
	GraphicsVector<T, N>::GraphicsVector(const T& xComp, const T& yComp, const T& zComp): _vector(N)
	{
		_vector[0] = xComp;
		_vector[1] = yComp;
		_vector[2] = zComp;
	}

	template<class T, unsigned int N>
	GraphicsVector<T,N>::GraphicsVector(const T& xComp, const T& yComp, const T& zComp, const T& wComp): _vector(N)
	{
		_vector[0] = xComp;
		_vector[1] = yComp;
		_vector[2] = zComp;
		_vector[3] = wComp;
	}

	/**
	 * Common vectors 
	 */
	typedef GraphicsVector<float, 3> GVector3f;
	typedef GraphicsVector<float, 4> GVector4f;
	typedef GraphicsVector<double, 3> GVector3d;
	typedef GraphicsVector<double, 4> GVector4d;
}
#endif