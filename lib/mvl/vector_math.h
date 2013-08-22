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

/**
 * Created by: Ty Lewis
 * All rights reserved
 */
#ifndef _VECTOR_MATH_H_
#define _VECTOR_MATH_H_

#include "vector.h"
#include <iostream>

namespace mvl
{
	/**
	 * Adds two vectors.
	 * 
	 * @param v0
	 * @param v1
	 * 
	 * @pre The vectors must be of the same dimension
	 * 
	 * @return The vector sum
	 */
	template <class T>
	Vector<T> add(const IVector<T>& v0, const IVector<T>& v1)
	{
		assert(v0.getDimension() == v1.getDimension());

		Vector<T> sum(v0.getDimension());
		for(int i = 0; i < v0.getDimension(); i++)
		sum[i] = v0[i] + v1[i];

		return sum;
	}

	/**
	 * Overloaded addition operator.
	 */
	template <class T>
	Vector<T> operator+(const IVector<T>& v0, const IVector<T>& v1)
	{
		return add(v0, v1);
	}

	/**
	 * Subtracts two vectors v0 - v1.
	 * 
	 * @param v0
	 * @param v1
	 * 
	 * @return The vector difference
	 */
	template <class T>
	Vector<T> sub(const IVector<T>& v0, const IVector<T>& v1)
	{
		assert(v0.getDimension() == v1.getDimension());

		Vector<T> diff(v0.getDimension());
		for(int i = 0; i < v0.getDimension(); i++)
		diff[i] = v0[i] - v1[i];

		return diff;
	}

	/**
	 * Overloaded subtraction operator.
	 */
	template <class T>
	Vector<T> operator-(const IVector<T>& v0, const IVector<T>& v1)
	{
		return sub(v0, v1);
	}

	/**
	 * Scales the vector by the given scale factor 
	 */
	template <class T, class S>
	void scale(IVector<T>& v, S scaleFactor)
	{
		for(int i = 0; i < v.getDimension(); i++)
		{
			v[i] = (v[i] * scaleFactor);
		}
	}

	/**
	 * Scales the vector and returns a copy
	 */
	template <class T, class S>
	Vector<T> scaledCopy(const IVector<T>& v, S scaleFactor)
	{
		Vector<T> scaledCopy(v);
		scale(scaledCopy, scaleFactor);
		return scaledCopy;
	}

	/**
	 * Returns the dot product of the two vectors 
	 * @param v0
	 * @param v1
	 */
	template <class T>
	T dot(const IVector<T>& v0, const IVector<T>& v1)
	{
		assert(v0.getDimension() == v1.getDimension());

		T product = 0;
		for(int i = 0; i < v0.getDimension(); i++)
			product += (v0[i] * v1[i]);

		return product;
	}
}
#endif