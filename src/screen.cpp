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

#include "screen.h"
#include "graphics_vector_utils.h"

Screen::Screen(int w, int h, float unitsPerPix, const mvl::GVector3f& center, const mvl::GVector3f& negZ, 
	const mvl::GVector3f& posY)
	:_width(w), 
	_height(h), 
	_unitsPerPix(unitsPerPix), 
	_pixDim(unitsPerPix),
	_ulCornerPixCenter(),
	_xBasis(),
	_yBasis()
{
    // positive y in the image space points down
    _yBasis = mvl::scaledCopy(posY,-1.0f);
	_yBasis.normalize();
    
    _xBasis = mvl::cross(_yBasis, negZ);
    cout << _xBasis.toString() << endl;
	_xBasis.normalize();
    
    float wWorldCoords = (w * unitsPerPix);
    float hWorldCoords = (h * unitsPerPix);
    
    mvl::GVector3f ulCornerYOffset = posY;
	ulCornerYOffset.normalize();
    ulCornerYOffset.scale(hWorldCoords / 2.0f);
    
    mvl::GVector3f ulCornerXOffset = _xBasis;
	ulCornerXOffset.normalize();
    ulCornerXOffset.scale(-wWorldCoords / 2.0f);
    
    _ulCornerPixCenter = add(center, ulCornerYOffset);
    _ulCornerPixCenter = add(_ulCornerPixCenter, ulCornerXOffset);
    x(_ulCornerPixCenter) += _pixDim / 2.0f;
    y(_ulCornerPixCenter) += _pixDim / 2.0f;
    
    cout << center.toString() << endl;
    cout << "Top left pixel center: " << _ulCornerPixCenter.toString() << endl;
}

void Screen::setPixel(int x, int y, const mvl::GVector4f& color)
{
    assert(x < _width);
    assert(y < _height);
	float colorData[4];
	color.getData(colorData);
    _raster.setPixel(x, _height - y - 1, colorData);
}

const void* Screen::getRasterData() const
{
    return _raster.getData();
}

mvl::GVector3f Screen::getPointInPixel(float x, float y)
{
    assert(x >= 0 && x < _width);
    assert(y >= 0 && y < _height);
    
    mvl::GVector3f offsetToPoint = _ulCornerPixCenter;
    offsetToPoint = add(offsetToPoint, mvl::scaledCopy(_xBasis, x * _unitsPerPix));
    offsetToPoint = add(offsetToPoint, mvl::scaledCopy(_yBasis, y * _unitsPerPix));
    
    return offsetToPoint;
}

mvl::GVector3f Screen::getPointInPixel(int x, int y, float unitX, float unitY)
{
    assert(unitX >= 0 && unitX <= 1);
    assert(unitY >= 0 && unitY <= 1);
    
    // get the lower left corner of the pixel in world coordinates
    mvl::GVector3f llPixCornerWc = _ulCornerPixCenter;
    llPixCornerWc = add(llPixCornerWc, scaledCopy(_xBasis, x * _unitsPerPix));
    llPixCornerWc = add(llPixCornerWc, scaledCopy(_yBasis, y * _unitsPerPix));
    
    // get the scale factors to get the point from 
    float xWcScale = _unitsPerPix * unitX;
    mvl::GVector3f xOffset = scaledCopy(_xBasis, xWcScale);
    
    float yWcScale = -_unitsPerPix * unitY;
    mvl::GVector3f yOffset = scaledCopy(_yBasis, yWcScale);
    
    mvl::GVector3f point = add(llPixCornerWc, xOffset);
    point = add(point, yOffset);
    
    return point;
}

int Screen::getWidth() const
{
    return _width;
}
	
int Screen::getHeight() const
{
    return _height;
}