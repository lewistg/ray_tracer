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

#ifndef _VECTOR_INTERFACE_H_
#define _VECTOR_INTERFACE_H_

#include <string>

namespace mvl
{
	/**
	 * Vector interface
	 */
	template <class T>
	class IVector
	{
	public:
		virtual ~IVector() {}

		/**
		 * Overloaded assignment operator
		 * @param rSide right side of the assignment operator
		 * @return 
		 */
		virtual const IVector<T>& operator =(const IVector<T>& rSide) = 0;

		/**
		 * Overloaded increment operator. Does component-wise
		 * addition.
		 * @pre rSide has the same dimension of the rSide
		 * @param rSide
		 * @return 
		 */
		virtual const IVector<T>& operator +=(const IVector<T>& rSide) = 0;

		/**
		 * Scales the matrix
		 * scaleFactor multiplier for all of the components
		 * todo: Move this out of the class 
		 */
		virtual void scale(T scaleFactor) = 0;

		/**
		 * Clear entries and sets dimension to 0
		 * @param components
		 * @param len
		 */
		virtual void clear() = 0;

		/**
		 * Sets the components of the vector
		 * @return 
		 */
		virtual void setComponents(const T* components, unsigned int len) = 0;

		/**
		 * Gets the dimension of the vector
		 * @return a integer indicating the dimension of the Vector
		 */
		virtual unsigned int getDimension() const = 0;

		/**
		 * Resizes the dimension of the vector. If the vector
		 * has more dimensions than the the new dimension, the
		 * higher dimension values are sliced off while lower dimensions
		 * are preserved.
		 * @param column
		 * @return 
		 */
		virtual void setDimension(unsigned int dimension) = 0;

		/**
		 * Non-const getter for vector entry 
		 * @param column
		 * @return 
		 */
		virtual T& operator[] (unsigned int column) = 0;
		
		/**
		 * Const getter for vector entry 
		 * @param column
		 * @return 
		 */
		virtual const T& operator[] (unsigned int column) const = 0;

		/**
		 * Checks to see if two vectors are equal component wise;
		 */
		virtual bool operator ==(const IVector<T>& rSide) = 0;

		/**
		 * Checks to see if two vectors are in-equal component wise;
		 */
		virtual bool operator !=(const IVector<T>& rSide) = 0;

		/**
		 * Multiplies
		 */
		virtual const IVector<T>& operator*=(T scalar) = 0;

		/**
		 * Returns a string representing the matrix row
		 * @return a string with the row's string representation
		 */
		virtual std::string toString() const = 0;
	};
}
#endif