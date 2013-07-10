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

#include "matrix4f_stack.h"

Matrix4fStack::Matrix4fStack()
	{}

Matrix4fStack::~Matrix4fStack()
	{}

const Matrix4f& Matrix4fStack::top() const
{
	assert(!isEmpty());
	
	return _matrixStack.top();
}

Matrix4f Matrix4fStack::pop()
{
	assert(!isEmpty());
	
	Matrix4f top = _matrixStack.top();
	_matrixStack.pop();
	return top;
}

void Matrix4fStack::push(const Matrix4f& m)
{
	_matrixStack.push(m);
}

bool Matrix4fStack::isEmpty() const
{
	return _matrixStack.empty();
}

long Matrix4fStack::getSize()
{
    return _matrixStack.size();
}