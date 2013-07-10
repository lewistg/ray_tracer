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

#ifndef _SCREEN_RASTER_H_
#define _SCREEN_RASTER_H_

#include <vector>
#include <assert.h>
#include <iostream>

using namespace std;

class ScreenRaster
{
	public:
	    /**
	     * Constructs a new raster
	     * @param w
	     * @param h
	     * @param format
	     */
	    ScreenRaster();
		
	    /**
	     * Destructor
	     */
	    ~ScreenRaster();

	    /**
	     * Sets a pixel in the raster to a certain color
             * @param x
             * @param y
             * @return 
             */
	    void setPixel(int x, int y, const float pixelData[]);

	    /**
	     * Gets a particular pixel's data
	     * @param x
	     * @param y
	     * @param pixel
	     */
	    void getPixel(int x, int y, float pixel[]) const;

	    /**
	     * Sets all the pixels in the raster to the particular color.
	     * @pre pixelData matches the format of the Raster's pixel format
	     * @param pixelData The color to be applied to all of the pixels.
	     * @post All of the pixels in the raster match the color in pixelData
	     */
	    void setAllPixels(const float pixelData[]);

	    /**
	     * Getter for the width
	     * @return 
	     */
	    int getWidth() const;

	    /**
	     * Getter for the height
	     * @return int of the pixel 
	     */
	    int getHeight() const;

	    /**
	     * Gets a pointer to the raw data
	     * @return a void pointer to the data
	     */
	    const void* getData();
	    const void* getData() const;
		
	private:
	    static const int R = 0;
	    static const int G = 1;
	    static const int B = 2;
	    static const int A = 3;
	    
	    //PixelFormat _pixelFormat;
	    /**The width of the raster in pixels*/
	    int _pixelWidth;
	    /**The height of the raster in pixels*/
	    int _pixelHeight;
	    /**The number of floats per pixel*/
	    int _floatsPerPixel;
	    /**The actual pixel values*/
	    vector<float> _pixels;
	    
	    /**
	     * Utility function for manually indexing the pixels
	     * @param w
	     * @param h
	     * @return 
	     */
	    int pixelIndex(int w, int h) const;
};

#endif