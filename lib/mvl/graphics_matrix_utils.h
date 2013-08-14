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

#ifndef _GRAPHICS_MATRIX_UTILS_H_
#define _GRAPHICS_MATRIX_UTILS_H_

#include <string>
#include <assert.h>
#include "graphics_matrix.h"
#include "graphics_vector.h"
#include "matrix_math.h"
#include "matrix.h"

namespace mvl
{
	template <class S, unsigned int R, unsigned int C>
	GraphicsVector<S, C> mult(const GraphicsMatrix<S, R, C>& m, const GraphicsVector<S, C>& v)
	{
		Vector<S> vectorResult = mult(m._matrix, v._vector);
		GraphicsVector<S, C> graphicsVectorResult(vectorResult);

		return graphicsVectorResult;
	}
}

#endif