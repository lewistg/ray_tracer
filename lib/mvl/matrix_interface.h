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

#ifndef _MATRIX_INTERFACE_H_
#define _MATRIX_INTERFACE_H_

#include <string>

namespace mvl 
{
	/**
	 * Common interface for all matrices
	 */
	template <class T>
	class IMatrix
	{
	public:

		virtual ~IMatrix() {}

		/**
		 * Assignment operator, copies over the values from a generic
		 * matrix.
		 * 
		 * @param rhs The right hand side of the = operator
		 */
		virtual const IMatrix& operator=(const IMatrix<T>& rhs) = 0;

		/**
		 * Gets the indexed row.
		 * 
		 * @param _rowIndex
		 */
		virtual const IVector<T>& operator[](unsigned int rowIndex) const = 0;

		/**
		 * Gets the indexed row.
		 * 
		 * @param _rowIndex
		 */
		virtual IVector<T>& operator[](unsigned int rowIndex) = 0;

		/**
		 * Gets the indexed column vector.
		 * @return 
		 */
		virtual const IVector<T>& getCol(unsigned int colIndex) const = 0;

		/**
		 * Gets a reference to the indexed column vector.
		 * @return 
		 */
		virtual IVector<T>& getCol(unsigned int colIndex) = 0;

		/**
		 * Returns the number of rows
		 */
		virtual unsigned int getNumRows() const = 0;

		/**
		 * Returns the number of columns
		 */
		virtual unsigned int getNumCols() const = 0;

		/**
		 * Returns from a string representation of the matrix. 
		 */
		virtual std::string toString() = 0;
	};
}
#endif