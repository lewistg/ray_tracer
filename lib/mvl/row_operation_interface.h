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

#ifndef _ROW_OPERATION_INTERFACE_H_
#define _ROW_OPERATION_INTERFACE_H_

#include <memory>
#include "vector.h"

namespace mvl
{
	/**
	 * Interface for a row operation
	 * @param m
	 */
	template <class T>
	class IRowOperation
	{
	public:
		/**
		 * Destructor
		 */
		virtual ~IRowOperation() 
		{

		}

		/**
		 * Performs the basic row operation
		 * @param m
		 */
		virtual void operation(IMatrix<T>& m) = 0;

		/**
		 * Returns a copy of this row operation.
		 */
		virtual std::unique_ptr<IRowOperation> makeCopy() const = 0;
	};
}
#endif