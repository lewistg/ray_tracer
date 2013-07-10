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

#ifndef _DRAW_BRESENHAM_LINE_H_
#define _DRAW_BRESENHAM_LINE_H_

#include <assert.h>
#include <cmath>
#include "draw_command.h"

/**
 * Draws a line according to the Bresenham algorithm
 */
class DrawBresenhamLine:public DrawCommand
{
	public:
		/**
		 * Constructor
		 */
		DrawBresenhamLine(Raster* raster);
		
		/**
		 * Destructor
		 */
		virtual ~DrawBresenhamLine();
		
		/**
		 * Overrides the draw command
		 */
		virtual void draw(Vertex* vertices, int numVertices);
		
	protected:
		/**
		 * Plots a point on the raster
         * @param x
         * @param y
         * @param color The color of the pixel.
         */
		//virtual void plotPoint(int x, int y, Vector4f color);
		
	private:
		/**
		 * Draws a line between two points using Bresenham by "walking
		 * along" the x axis.
		 * @pre p1, p2 have two integer components x,y
		 * @pre p1 is left of p2
         */
		void drawLine(Vertex& p0, Vertex& p1);
		
		/**
		 * "Walks along" the x axis filling in pixels.
		 * @pre epsilon is less than 1
		 * @pre x0 < x1
		 */
		void walkAlongX(Vector4f& color0, Vector4f& color1, int x0, int y0, float z0, int x1, float z1, float epsilon, 
						const int Y_INCREMENT, const int ERROR_RESET);
		
		/**
		 * "Walks along" the y axis filling in pixels.
		 * @pre epsilon is less than 1
		 * @pre y0 < y1
		 */
		void walkAlongY(Vector4f& color0, Vector4f& color1, int x0, int y0, float z0, int y1, float z1, float epsilon, 
						const int Y_INCREMENT, const int ERROR_RESET);
		
		
};


#endif