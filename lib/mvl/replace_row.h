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

#ifndef _REPLACE_ROW_H_
#define _REPLACE_ROW_H_

#include <memory>
#include "row_operation_interface.h"

namespace mvl
{
	/**
	 * Represents a multiply-and-add row operation
	 */
	template <class T>
	class ReplaceRow: public IRowOperation<T>
	{
	public:
		/**
		 * Constructor.  
		 * @param r0Index
		 * @param r1Index
		 * @param scaleFactor
		 */
		ReplaceRow(unsigned int r0Index, unsigned int r1Index, T scaleFactor);

		/**
		 * Copy constructor
		 * @param copy
		 */
		ReplaceRow(const ReplaceRow& copy)
		{
			*this = copy;
		}

		/**
		 * Override
		 */
		virtual void operation(IMatrix<T>& m);

		/**
		 * Override
		 */
		virtual std::unique_ptr<IRowOperation<T> > makeCopy() const;

	private:
		/**Index of the row to be replaced*/
		unsigned int _r0Index;
		/**Index of the row to be multiplied and added to the replaced row*/
		unsigned int _r1Index;
		/**The scale factor*/
		T _scaleFactor;
	};

	//******************************************************************************
	// We must include the implementation in the same file to avoid compiler problems
	//******************************************************************************

	template <class T>
	ReplaceRow<T>::ReplaceRow(unsigned int r0Index, unsigned int r1Index, T scaleFactor)
		: _r0Index(r0Index),
		_r1Index(r1Index),
		_scaleFactor(scaleFactor)
	{

	}


	template <class T>
	void ReplaceRow<T>::operation(IMatrix<T>& m)
	{
		m[_r0Index] += scaledCopy(m[_r1Index], _scaleFactor);
	}

	template <class T>
	std::unique_ptr<IRowOperation<T> > ReplaceRow<T>::makeCopy() const
	{
		return std::unique_ptr<IRowOperation<T> >(new ReplaceRow<T>(*this));
	}

}
#endif