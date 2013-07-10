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

#include "graphics_state.h"

long GraphicsState::POINT_SMOOTH = 2;
//long GraphicsState::BLENDING = 4;

GraphicsState& GraphicsState::getInstance()
{
	static GraphicsState instance;
	
	return instance;
}

GraphicsState::GraphicsState():_pointSize(1.0f)
{
	float defaultColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	_currentVertexColor = Vector4f(defaultColor);	
}

GraphicsState::~GraphicsState()
{
	
}

void GraphicsState::setClearColor(const Vector4f& clearColor)
{
	_clearColor = clearColor;
}

const Vector4f* GraphicsState::getClearColor()
{
	return &_clearColor;
}

void GraphicsState::setColor(const Vector4f& color)
{
	_currentVertexColor = color;
}

const Vector4f* GraphicsState::getColor()
{
	return &_currentVertexColor;
}

void GraphicsState::setPointSize(float pointSize)
{
	assert(pointSize > 0);
	_pointSize = pointSize;
}

float GraphicsState::getPointSize()
{
	return _pointSize;
}

void GraphicsState::setViewport(int xMin, int yMin, int width, int height)
{
    _currentViewport.xMin = xMin;
    _currentViewport.yMin = yMin;
    _currentViewport.width = width;
    _currentViewport.height = height;
}

Viewport GraphicsState::getViewPort()
{
    return _currentViewport;
}

void GraphicsState::enable(long setting)
{
	_enabledSettings = _enabledSettings | setting; 
}
		
void GraphicsState::disable(long setting)
{
	_enabledSettings = _enabledSettings ^ setting; 
}

bool GraphicsState::isEnabled(long setting)
{
	return ((_enabledSettings & setting) > 0 ? true : false);
}