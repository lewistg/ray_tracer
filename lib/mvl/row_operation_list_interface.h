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

#ifndef _ROW_OPERATION_LIST_INTERFACE_H_
#define _ROW_OPERATION_LIST_INTERFACE_H_

#include "matrix_interface.h"
#include "row_operation_interface.h"

namespace mvl
{
	/**
	 * Interface for a list of row operations
	 */
	template <class T>
	class IRowOperationList
	{
	public:
		/**
		 * Destructor
		 */
		virtual ~IRowOperationList()
		{
		}

		/**
		 * Adds a new row operation to the list
		 * @param rowOp
		 */
		virtual void add(const IRowOperation<T>& rowOp) = 0;

		/**
		 * Applies the list of operations to a given matrix 
		 */
		virtual void applyOperations(IMatrix<T>& mat) = 0;
	};
}
#endif