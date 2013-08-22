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

#ifndef _GRAPHICS_VECTOR_UTILS_H_
#define _GRAPHICS_VECTOR_UTILS_H_

#include "graphics_vector.h"
#include "vector_math.h"

namespace mvl 
{
	template <class T, unsigned int N> class GraphicsVector;

	/**
	 * Handy indices
	 */
	const int X = 0;
	const int Y = 1;
	const int Z = 2;
	const int W = 3;

	/**
	 * Returns reference to x component of graphical vector
	 */
	template <class T, unsigned int N>
	T& x(GraphicsVector<T, N>& gVector)
	{
		return gVector[X];
	}

	/**
	 * Returns const reference to x component of graphical vector
	 */
	template <class T, unsigned int N>
	const T& x(const GraphicsVector<T, N>& gVector)
	{
		return gVector[X];
	}

	/**
	 * Returns reference to y component of graphical vector
	 */
	template <class T, unsigned int N>
	T& y(GraphicsVector<T, N>& gVector)
	{
		return gVector[Y];
	}

	/**
	 * Returns cosnt reference to y component of graphical vector
	 */
	template <class T, unsigned int N>
	const T& y(const GraphicsVector<T, N>& gVector)
	{
		return gVector[Y];
	}

	/**
	 * Returns reference to z component of graphical vector
	 */
	template <class T, unsigned int N>
	T& z(GraphicsVector<T, N>& gVector)
	{
		return gVector[Z];
	}

	/**
	 * Returns const reference to z component of graphical vector
	 */
	template <class T, unsigned int N>
	const T& z(const GraphicsVector<T, N>& gVector)
	{
		return gVector[Z];
	}

	/**
	 * Returns reference to w component of graphical vector
	 */
	template <class T, unsigned int N>
	T& w(GraphicsVector<T, N>& gVector)
	{
		return gVector[W];
	}

	/**
	 * Cross product
	 */
	template<class S, unsigned int M>
	GraphicsVector<S, M> cross(const GraphicsVector<S, M>& v0, const GraphicsVector<S, M>& v1)
	{
		GraphicsVector<S, M> crossProd;
		x(crossProd) = y(v0) * z(v1) - z(v0) * y(v1);
		y(crossProd) = z(v0) * x(v1) - x(v0) * z(v1);
		z(crossProd) = x(v0) * y(v1) - y(v0) * x(v1);

		return crossProd;
	}

	/**
	 * Makes a copy of the given vector an normalizes it.
	 */
	template<class T, unsigned int N>
	GraphicsVector<T, N> normalizedCopy(const GraphicsVector<T, N>& v)
	{
		GraphicsVector<T,N> copy(v);
		copy.normalize();

		return copy;
	}

	/**
	 * Makes a scaled copy of the given vector.
	 */
	template<class T, unsigned int N>
	GraphicsVector<T,N> scaledCopy(const GraphicsVector<T, N>& v, T scaleFactor)
	{
		GraphicsVector<T,N> copy(v);
		copy.scale(scaleFactor);

		return copy;
	}

	/**
	 * Point-wise multiplication
	 */
	template<class T, unsigned int N>
	GraphicsVector<T,N> pointwiseMult(const GraphicsVector<T,N>& v0, const GraphicsVector<T,N>& v1)
	{
		GraphicsVector<T,N> product;
		for(int i = 0; i < N; i++)
			product[i] = v0[i] * v1[i];

		return product;
	}
}

#endif