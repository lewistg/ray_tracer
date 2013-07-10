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

Screen::Screen(int w, int h, float unitsPerPix, const Vector4f& center, const Vector4f& negZ, 
	const Vector4f& posY):_width(w), _height(h), _unitsPerPix(unitsPerPix), _pixDim(unitsPerPix)
{
    // positive y in the image space points down
    _yBasis = scale(posY,-1);
    normalize(&_yBasis);
    
    _xBasis = cross(_yBasis, negZ);
    cout << _xBasis.toString() << endl;
    normalize(&_xBasis);
    
    float wWorldCoords = (w * unitsPerPix);
    float hWorldCoords = (h * unitsPerPix);
    
    Vector4f ulCornerYOffset = posY;
    normalize(&ulCornerYOffset);
    ulCornerYOffset.scale(hWorldCoords / 2);
    
    Vector4f ulCornerXOffset = _xBasis;
    normalize(&ulCornerXOffset);
    ulCornerXOffset.scale(-wWorldCoords / 2);
    
    _ulCornerPixCenter = add(center, ulCornerYOffset);
    _ulCornerPixCenter = add(_ulCornerPixCenter, ulCornerXOffset);
    x(_ulCornerPixCenter) += _pixDim / 2;
    y(_ulCornerPixCenter) += _pixDim / 2;
    
    cout << center.toString() << endl;
    cout << "Top left pixel center: " << _ulCornerPixCenter.toString() << endl;
}

void Screen::setPixel(int x, int y, const Vector4f& color)
{
    assert(x < _width);
    assert(y < _height);
    _raster.setPixel(x, _height - y - 1, color.getData());
}

const void* Screen::getRasterData() const
{
    return _raster.getData();
}

Vector4f Screen::getPointInPixel(float x, float y)
{
    assert(x >= 0 && x < _width);
    assert(y >= 0 && y < _height);
    
    Vector4f offsetToPoint = _ulCornerPixCenter;
    offsetToPoint = add(offsetToPoint, scale(_xBasis, x * _unitsPerPix));
    offsetToPoint = add(offsetToPoint, scale(_yBasis, y * _unitsPerPix));
    
    return offsetToPoint;
}

Vector4f Screen::getPointInPixel(int x, int y, float unitX, float unitY)
{
    assert(unitX >= 0 && unitX <= 1);
    assert(unitY >= 0 && unitY <= 1);
    
    // get the lower left corner of the pixel in world coordinates
    Vector4f llPixCornerWc = _ulCornerPixCenter;
    llPixCornerWc = add(llPixCornerWc, scale(_xBasis, x * _unitsPerPix));
    llPixCornerWc = add(llPixCornerWc, scale(_yBasis, y * _unitsPerPix));
    
    // get the scale factors to get the point from 
    float xWcScale = _unitsPerPix * unitX;
    Vector4f xOffset = scale(_xBasis, xWcScale);
    
    float yWcScale = -_unitsPerPix * unitY;
    Vector4f yOffset = scale(_yBasis, yWcScale);
    
    Vector4f point = add(llPixCornerWc, xOffset);
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