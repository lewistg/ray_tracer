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

#include "matrix_state.h"

MatrixState& MatrixState::getInstance()
{
    static MatrixState instance;
    
    return instance;
}

MatrixState::MatrixState():_currentMatStack(NULL)
	{}

void MatrixState::setMatrixMode(MatrixMode mode)
{
    switch(mode)
    {
	case MODELVIEW:
	    _currentMatStack = &_modelViewMatStack;
	    _currentActiveMatrix = &_activeModelViewMatrix;
	break;
	    
	case PROJECTION:
	    _currentMatStack = &_projMatStack;
	    _currentActiveMatrix = &_activeProjMatrix;
	break;
	    
	default:
	    assert(false);
	break;
    }
}

void MatrixState::pushMatrix()
{
    assert(_currentMatStack != NULL);
    _currentMatStack->push(*_currentActiveMatrix);
}

void MatrixState::popMatrix()
{
    assert(_currentMatStack != NULL);
    assert(!_currentMatStack->isEmpty());
    *_currentActiveMatrix = _currentMatStack->pop();
}

void MatrixState::loadIdentity()
{
    assert(_currentActiveMatrix != NULL);
    float identityMat[] = {1, 0, 0, 0, 
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1};
    *_currentActiveMatrix = Matrix4f(identityMat);
}

void MatrixState::loadMatrixd(double m[])
{
    float castedM[16];
    for(int i = 0; i < 16; i++)
	castedM[i] = (float) m[i];
    
    *_currentActiveMatrix = Matrix4f(castedM);
}

void MatrixState::multMatrixd(double m[])
{
    float castedM[16];
    for(int i = 0; i < 16; i++)
	castedM[i] = (float) m[i];

    Matrix4f multiplier(castedM);
    *_currentActiveMatrix = mult((*_currentActiveMatrix), multiplier);
}

void MatrixState::multMatrixf(float m[])
{
	Matrix4f multiplier(m);
	*_currentActiveMatrix = mult((*_currentActiveMatrix), multiplier);    
}

Matrix4f MatrixState::getActiveProjMatrix()
{
    return _activeProjMatrix;
}

Matrix4f MatrixState::getActiveModelViewMatrix()
{
    return _activeModelViewMatrix;
}

void MatrixState::getProjMatrixDatad(double data[])
{
    float dataf[16];
    _activeProjMatrix.toArray(dataf);
    for(int i = 0; i < 16; i++)
	data[i] = (double) dataf[i];
}

void MatrixState::getModelViewMatrixDatad(double data[])
{
    float dataf[16];
    _activeModelViewMatrix.toArray(dataf);
    for(int i = 0; i < 16; i++)
	data[i] = (double) dataf[i];    
}