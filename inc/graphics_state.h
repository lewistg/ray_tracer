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

#ifndef _GRAPHICS_STATE_H_
#define _GRAPHICS_STATE_H_

#include <assert.h>
#include "vector4f.h"
#include "matrix4f_stack.h"
#include "blending_func.h"

using namespace std;

struct Viewport
{
    int xMin;
    int yMin;
    int width;
    int height;
};

/**
 * A singleton class that holds miscellaneous information about
 * drawing. TODO: Decompose further
 */
class GraphicsState
{
	public:		
		/**Settings masks*/
		static long POINT_SMOOTH;	

		/**
		 * Gets the instance
		 */
		static GraphicsState& getInstance();
		
		/**
		 * Sets the clear color.
		 * @param clearColor The new clear color.
		 * @pre clearColor is of the format RGBA
		 */
		void setClearColor(const Vector4f& clearColor);

		/**
		 * Getter for the clear color
		 * @return A reference to the clear color
		 */
		const Vector4f* getClearColor();
		
		/**	
		 * Sets the color. This colors a particular vertex. It is called
		 * between the beginDrawing and endDrawing.
		 * @pre color is a 4 dimensional Vector
		 */
		void setColor(const Vector4f& color);

		/**
		 * Getter for the draw color
		 * @return A reference to the color
		 */
		const Vector4f* getColor();	
		
		/**
		 * Sets the point size
		 * @param pointSize The new point size
		 * @pre pointSize > 0
		 */
		void setPointSize(float pointSize);
		
		/**
		 * Getter for the point size
		 */
		float getPointSize();
		
		
		/**
		 * Sets the viewport
                 * @param setting
                 */
		void setViewport(int xMin, int yMin, int width, int height);
		
		/**
		 * Gets the current view port
                 * @param setting
                 */
		Viewport getViewPort();
		
		/**
		 * Enable a drawing functionality 
		 */
		void enable(long setting);
		
		/**
		 * Disables a drawing functionality
		 */
		void disable(long setting);
		
		/**
		 * Checks to see if a graphics setting is set
		 */
		bool isEnabled(long setting);
		
	private:
		/**Setting variables*/
		long _enabledSettings;
		/**Width of the points*/
		float _pointSize;
		/**Clear color*/
		Vector4f _clearColor;
		/**Current drawing color*/
		Vector4f _currentVertexColor;
		/**Current viewport*/
		Viewport _currentViewport;
		
		/**
		 * Constructor
		 */
		GraphicsState();
		
		/**
		 * Destructor
		 */
		virtual ~GraphicsState();
		
		/**
		 * Copy constructor *should never be called*
		 * and is not implemented
		 */
		GraphicsState(const GraphicsState& copy);
		
		/**
		 * Overloaded assignment operator *should not be called*
		 * and is not implemented
		 */
		const GraphicsState& operator=(const GraphicsState& rSide);
};

#endif