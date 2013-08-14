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

#ifndef _ROW_OPERATION_LIST_H_
#define _ROW_OPERATION_LIST_H_

#include <vector>
#include <memory>
#include "row_operation_list_interface.h"

namespace mvl
{
	template <class T>
	class RowOperationList: public IRowOperationList<T>
	{
	public:
		/**
		 * Destructor
		 * @param rowOp
		 */
		virtual ~RowOperationList() 
		{
		}

		/**
		 * Override
		 */
		void add(const IRowOperation<T>& rowOp);

		/**
		 * Override
		 */
		void applyOperations(IMatrix<T>& mat);

	private:
		std::vector<std::unique_ptr<IRowOperation<T> > > _rowOperations;
	};

	//******************************************************************************
	// We must include the implementation in the same file to avoid compiler problems
	//******************************************************************************

	template <class T>
	void RowOperationList<T>::add(const IRowOperation<T>& rowOp)
	{
		_rowOperations.push_back(rowOp.makeCopy());
	}

	template <class T>
	void RowOperationList<T>::applyOperations(IMatrix<T>& mat)
	{
		for(int i = 0; i < _rowOperations.size(); i++)
		{
			_rowOperations[i]->operation(mat);
		}
	}
}
#endif