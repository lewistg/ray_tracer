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

#ifndef _MATRIX4F_STACK_H_
#define _MATRIX4F_STACK_H_

#include <stack>
#include <assert.h>
#include "matrix4f.h"

using namespace std;

/**
 * A stack for SquareMatrix's
 */
class Matrix4fStack
{
        public:
                /**
                 * Default constructor
                 */
                Matrix4fStack();

                /**
                 * Destructor
                 */
                virtual ~Matrix4fStack();

                /**
                 * Access the top element of the stack.
                 * @pre The stack is not empty
		* @return A reference to the top element.
		 */
                const Matrix4f& top() const;

                /**
                 * Pops the top SquareMatrix off the stack.
                 * @pre The stack is not empty
		 * @return The matrix that was on top of the stack
		 */
                Matrix4f pop();

                /**
                 * Pushes a new SquareMatrix onto the stack.
		 * @param m the matrix that will be pushed on to the top of the stack
		 */
                void push(const Matrix4f& m);

		/**
		 * Returns the number of elements on the stack
                 * @return 
                 */
		long getSize();
		
                /**
                 * Indicates whether or not the stack is empty or not.
                 */
                bool isEmpty() const;

        private:
                stack<Matrix4f> _matrixStack;
};

#endif