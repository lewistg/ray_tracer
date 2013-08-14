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

#ifndef _GRAPHICS_MATRIX_H_
#define _GRAPHICS_MATRIX_H_

#include <string>
#include <assert.h>
#include "matrix.h"

namespace mvl 
{
	template <class S, unsigned int> class GraphicsVector;

	/**
	 * A matrix implementation geared towards graphics 
	 */
	template<class T, unsigned int N, unsigned int M>
	class GraphicsMatrix
	{
		public:	
			/**
			 * Constructor
			 */
			GraphicsMatrix();

			/**
			 * Destructor
			 */
			virtual ~GraphicsMatrix();
			
			/**
			 * Returns string representation of matrix
			 */
			std::string toString();

			/**
			 * Friend utility functions
			 */
			template <class S, unsigned int R, unsigned int C>
			friend GraphicsVector<S, C> mult(const GraphicsMatrix<S, R, C>& m, const GraphicsVector<S, C>& v);

		private:
			/**Matrix data*/
			Matrix<T> _matrix;
	};

	//******************************************************************************
	// We must include the implementation in the same file to avoid compiler problems
	//******************************************************************************

	template<class T, unsigned int N, unsigned int M>
	GraphicsMatrix<T, N, M>::GraphicsMatrix():_matrix(N, M)
	{

	}

	template<class T, unsigned int N, unsigned int M>
	GraphicsMatrix<T, N, M>::~GraphicsMatrix()
	{

	}

	template<class T, unsigned int N, unsigned int M>
	std::string GraphicsMatrix<T, N, M>::toString()
	{
		return _matrix.toString();
	}

	typedef GraphicsMatrix<float, 3, 3> GMatrix3f;
	typedef GraphicsMatrix<float, 4, 4> GMatrix4f;
	typedef GraphicsMatrix<double, 3, 3> GMatrix3d;
	typedef GraphicsMatrix<double, 4, 4> GMatrix4d;
}

#endif