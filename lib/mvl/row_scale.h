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

#ifndef _ROW_SCALE_H_
#define _ROW_SCALE_H_

#include <memory>
#include "row_operation_interface.h"

namespace mvl
{
	/**
	 * Represents a row scale operation
	 */
	template <class T>
	class RowScale: public IRowOperation<T>
	{
	public:
		/**
		 * Constructor.
		 * @param r0Index
		 * @param scalar
		 */
		RowScale(unsigned int r0Index, T scaleFactor);

		/**
		 * Override
		 */
		virtual void operation(IMatrix<T>& m);

		/**
		 * Override
		 */
		virtual std::unique_ptr<IRowOperation<T> > makeCopy() const;

	private:
		/**Index of the row to scale*/
		unsigned int _r0Index;
		/**The scale factor*/
		T _scaleFactor;
	};

	//******************************************************************************
	// We must include the implementation in the same file to avoid compiler problems
	//******************************************************************************

	template <class T>
	RowScale<T>::RowScale(unsigned int r0Index, T scaleFactor)
		: _r0Index(r0Index),
		_scaleFactor(scaleFactor)
	{
		assert(_scaleFactor != 0);
	}

	template <class T>
	void RowScale<T>::operation(IMatrix<T>& m)
	{
		m[_r0Index] *= _scaleFactor;
	}

	template <class T>
	std::unique_ptr<IRowOperation<T> > RowScale<T>::makeCopy() const
	{
		return std::unique_ptr<IRowOperation<T> >(new RowScale<T>(*this));
	}
}
#endif