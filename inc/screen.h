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

#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <vector>
#include "raster.h"
#include "screen_raster.h"
#include "graphics_vector.h"

/**
 * Represents the screen/image plane on which the image
 * is projected. It exists in the world space.
 */
class Screen
{
    public:
	/**
	 * Constructs a new screen
	 * @param w Width of the screen in pixels
	 * @param h Height of the screen in pixels
	 * @param unitsPerPix World coordinates per pixel
	 * @param center The center of screen in world coordinates
	 * @param negZ This vector should point towards the visible scene
	 * @param posY Essentially the up vector
	 */
	Screen(int w, int h, float unitsPerPix, const mvl::GVector3f& center, const mvl::GVector3f& negZ, 
		const mvl::GVector3f& posY);
	
	/**
	 * Sets the color intensity for a pixel
	 */
	void setPixel(int x, int y, const mvl::GVector4f& color);
	
	/**
	 * Gets the coordinates of a point in the pixel that contains
	 * the point x and y in screen coordinates. 
	 * @return 
	 */
	mvl::GVector3f getPointInPixel(float x, float y);
	
	/**
	 * Gets the coordinates of a point in the pixel, treating it like
	 * a unit square with the lower left corner of the pixel as (0,0)
	 * @pre 0 <= x <= 1, 0 <= y <= 1
	 * @return 
	 */
	mvl::GVector3f getPointInPixel(int x, int y, float unitX, float unitY);
	
	/**
	 * Gets a pointer to the color data
	 * @return a void pointer to the data
	 */	
	const void* getRasterData() const;
	
	/**
	 * Getter for the pixel width
	 */
	int getWidth() const;
	
	/**
	 * Getter for the pixel height
	 */
	int getHeight() const;
	
	/**
	 * Gets the indexed pixel's center in world coordinates
	 */
	mvl::GVector3f pixelCenter(int x, int y);
	
    private:
	/**Width in pixels*/
	int _width; 
	/**Height in pixels*/
	int _height;
	/**Width and height of a pixel in world coordinates (pixels are square)*/
	float _pixDim;
	/**Conversion factor from pixels to pixel coordinates in the screen space*/
	float _unitsPerPix;
	/**The actual pixel values*/
	ScreenRaster _raster;
	/**The center of the upper left corner of the screen in world coordinates*/
	mvl::GVector3f _ulCornerPixCenter;
	/**The "x" basis vector for the screen's space*/
	mvl::GVector3f _xBasis;
	/**The "y" basis vector for the screen's space*/
	mvl::GVector3f _yBasis;
	
};

#endif