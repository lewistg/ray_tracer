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

#include "raster.h"
#include "graphics_state.h"

/*int Raster::R = 0;
int Raster::G = 1;
int Raster::B = 2;
int Raster::A = 3;*/

Raster* Raster::getInstance()
{
    static Raster instance;
    
    return &instance;
}

Raster::Raster():_pixelFormat(RGBA), 
	_pixelWidth(640), 
	_pixelHeight(480), 
	_DEPTH_BUFFER_ON(false)
{
	/*switch(_pixelFormat)
	{
		case RGB:
			_floatsPerPixel = 3;
		break;
		
		case RGBA:
			_floatsPerPixel = 4;
		break;
		
		default:
			assert(false);
	}*/
    
	_floatsPerPixel = 4;
	_pixels.resize(_pixelWidth * _pixelHeight * _floatsPerPixel);
	_depthBuffer.resize(_pixelWidth * _pixelHeight);
}


Raster::~Raster()
	{}

void Raster::setPixel(int x, int y, double pixelDepth, const float pixelData[])
{
    // clip pixels that fall outside the current view port
    Viewport currentViewPort = GraphicsState::getInstance().getViewPort();
    if(x < currentViewPort.xMin					|| 
	    x >= currentViewPort.xMin + currentViewPort.width	|| 
	    y < currentViewPort.yMin				|| 
	    y >= currentViewPort.yMin + currentViewPort.height	||
	    pixelDepth > 1					|| 
	    pixelDepth < -1)
    {
	return;
    }
	
    if(_DEPTH_BUFFER_ON && _depthBuffer[depthIndex(x, y)] <= pixelDepth)
    {
	return;
    }
    else
    {
	setPixel(x, y, pixelData);
	_depthBuffer[depthIndex(x, y)] = pixelDepth;
    }
    
    /*if(_depthBuffer[depthIndex(x, y)] > pixelDepth)
    {
	setPixel(x, y, pixelData);
	_depthBuffer[depthIndex(x, y)] = pixelDepth;
    }*/
}

void Raster::getPixel(int x, int y, float pixel[]) const
{
	assert(x >= 0);
	assert(y >= 0);
	assert(x < _pixelWidth);
	assert(y < _pixelHeight);    
	
	pixel[Raster::R] = _pixels[pixelIndex(x, y) + Raster::R];
	pixel[Raster::G] = _pixels[pixelIndex(x, y) + Raster::G];
	pixel[Raster::B] = _pixels[pixelIndex(x, y) + Raster::B];
	pixel[Raster::A] = _pixels[pixelIndex(x, y) + Raster::A];
}

void Raster::setAllPixels(const float pixelData[])
{   
	for(int w = 0; w < _pixelWidth; w++)
		for(int h = 0; h < _pixelHeight; h++)
			setPixel(w, h, pixelData);
}

void Raster::depthBuffOn()
{
    _DEPTH_BUFFER_ON = true;
}

void Raster::depthBuffOff()
{
    _DEPTH_BUFFER_ON = false;
}

void Raster::clearDepthBuffer()
{
    for(int i = 0; i < _pixelWidth * _pixelHeight; i++)
	_depthBuffer[i] = 1;
}

int Raster::getWidth() const
{
	return _pixelWidth;
}

int Raster::getHeight() const
{
	return _pixelHeight;
}

/*PixelFormat Raster::getPixelFormat()
{
	return _pixelFormat;
}*/

const void* Raster::getData()
{
	return _pixels.data();
}

const void* Raster::getData() const
{
	return _pixels.data();
}

int Raster::pixelIndex(int w, int h) const
{
	return _floatsPerPixel * ((h * _pixelWidth) + w);
}

int Raster::depthIndex(int x, int y) const
{
    return (y * _pixelWidth) + x;
}

void Raster::setPixel(int x, int y, const float pixelData[])
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
    /*if(_pixelFormat == RGBA)
	    _pixels[pixelIndex(w, h) + A] = pixelData[A];*/
    _pixels[pixelIndex(x, y) + A] = pixelData[A];    
}

void dumpRasterToPpm(const Raster& raster)
{
    ofstream rasterFile;
    rasterFile.open("raster.ppm", ios::out | ios::trunc);
    rasterFile << "P3" << endl;
    rasterFile << raster.getWidth() << " " << raster.getHeight() << endl;
    rasterFile << "256" << endl;
    const float* pixelData = (float*) raster.getData();
    for(int i = 0; i < (raster.getWidth() * raster.getHeight() * 4); i += 4)
    {
	rasterFile << (int) (256 * pixelData[i + 0]) << endl;
	rasterFile << (int) (256 * pixelData[i + 1]) << endl;
	rasterFile << (int) (256 * pixelData[i + 2]) << endl;
    }
}