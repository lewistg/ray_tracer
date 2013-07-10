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

#include "screen_raster.h"

ScreenRaster::ScreenRaster(): _pixelWidth(640), _pixelHeight(480)
{    
	_floatsPerPixel = 4;
	_pixels.resize(_pixelWidth * _pixelHeight * _floatsPerPixel);
}


ScreenRaster::~ScreenRaster()
	{}

void ScreenRaster::getPixel(int x, int y, float pixel[]) const
{
	assert(x >= 0);
	assert(y >= 0);
	assert(x < _pixelWidth);
	assert(y < _pixelHeight);    
	
	pixel[ScreenRaster::R] = _pixels[pixelIndex(x, y) + ScreenRaster::R];
	pixel[ScreenRaster::G] = _pixels[pixelIndex(x, y) + ScreenRaster::G];
	pixel[ScreenRaster::B] = _pixels[pixelIndex(x, y) + ScreenRaster::B];
	pixel[ScreenRaster::A] = _pixels[pixelIndex(x, y) + ScreenRaster::A];
}

void ScreenRaster::setAllPixels(const float pixelData[])
{   
	for(int w = 0; w < _pixelWidth; w++)
		for(int h = 0; h < _pixelHeight; h++)
			setPixel(w, h, pixelData);
}

int ScreenRaster::getWidth() const
{
	return _pixelWidth;
}

int ScreenRaster::getHeight() const
{
	return _pixelHeight;
}


const void* ScreenRaster::getData()
{
	return _pixels.data();
}

const void* ScreenRaster::getData() const
{
	return _pixels.data();
}

int ScreenRaster::pixelIndex(int w, int h) const
{
	return _floatsPerPixel * ((h * _pixelWidth) + w);
}

void ScreenRaster::setPixel(int x, int y, const float pixelData[])
{
    assert(x >= 0);
    assert(y >= 0);
    assert(x < _pixelWidth);
    if(y >= _pixelHeight)
    {
	cout << "y: " << y << endl;
	cout << "pixle height: " << _pixelHeight << endl;
    }
	
    assert(y < _pixelHeight);

    const int R = 0;
    const int G = 1;
    const int B = 2;
    const int A = 3;

    _pixels[pixelIndex(x, y) + R] = pixelData[R];
    _pixels[pixelIndex(x, y) + G] = pixelData[G];
    _pixels[pixelIndex(x, y) + B] = pixelData[B];
    _pixels[pixelIndex(x, y) + A] = pixelData[A];    
}