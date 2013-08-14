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

#ifndef _SWAP_ROWS_H_
#define _SWAP_ROWS_H_

#include <memory>
#include "row_operation_interface.h"

namespace mvl
{
	/**
	 * Represents a row swap
	 */
	template <class T>
	class SwapRows: public IRowOperation<T>
	{
	public:
		/**
		 * Constructor
		 * @param r0Index
		 * @param r1Index
		 */
		SwapRows(unsigned int r0Index, unsigned int r1Index);

		/**
		 * Override
		 */
		virtual void operation(IMatrix<T>& m);

		/**
		 * Override
		 */
		virtual std::unique_ptr<IRowOperation<T> > makeCopy() const;

	private:
		/**First row index*/
		unsigned int _r0Index;
		/**Second row index*/
		unsigned int _r1Index;
	};

	//******************************************************************************
	// We must include the implementation in the same file to avoid compiler problems
	//******************************************************************************

	template <class T>
	SwapRows<T>::SwapRows(unsigned int r0Index, unsigned int r1Index)
		: _r0Index(r0Index),
		_r1Index(r1Index)
	{

	}

	template <class T>
	void SwapRows<T>::operation(IMatrix<T>& m)
	{
		Vector<T> r0Copy = m[_r0Index];
		m[_r0Index] = m[_r1Index];
		m[_r1Index] = r0Copy; 
	}

	template <class T>
	std::unique_ptr<IRowOperation<T> > SwapRows<T>::makeCopy() const
	{
		return std::unique_ptr<IRowOperation<T> >(new SwapRows<T>(*this));
	}
}
#endif