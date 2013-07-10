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

#ifndef _DRAW_BRES_LINE_H_
#define _DRAW_BRES_LINE_H_

#include <assert.h>
#include <cmath>
#include "draw_command.h"
#include "line_depth_calculator.h"

class DrawBresLine: public DrawCommand
{
	public:
		/**
		 * Constructor
		 */
		DrawBresLine(Raster* raster);
		
		/**
		 * Destructor
		 */
		~DrawBresLine();
		
		/**
		 * Overrides the draw command
		 */
		virtual void draw(Vertex* vertices, int numVertices);
		
	protected:
		/**
		 * Plots a point on the raster
		 * @param x
		 * @param y
		 * @param color
		 */
		virtual void plotPoint(int x, int y, double pixelDepth, Vector4f color);	
		
	private:
	    LineDepthCalculator _lineDepthCalculator;
	    
		/**
		 * Draws a line using bresenham's line algorithm by walking 
		 * along the x axis
		 * @param v0
		 * @param v1
		 * @pre The slope |deltaY/deltaX| formed by v0 and v1 is < 1
		 * @pre y(v0.getVertex()) <= y(v0.getVertex())
		 */
		void drawLineByX(Vertex& v0, Vertex& v1);
		
		/**
		 * Draws a line using bresenham's line algorithm by walking
		 * along the y axis
		 * @param v0
		 * @param v1
		 * @pre The slope |deltaX/deltaY| formed by v0 and v1 is < 1
		 * @pre y(v0.getVertex()) <= y(v0.getVertex())
		 */
		void drawLineByY(Vertex& v0, Vertex& v1);
		
		/**
		 * Draws a vertical line from v0 to v1
		 * @param v0
		 * @param v1
		 */
		void drawVerticalLine(Vertex& v0, Vertex& v1);
		
		/**
		 * Draws a horizontal line from v0 to v1
		 * @param v0
		 * @param v1
		 */
		void drawHorizontalLine(Vertex& v0, Vertex& v1);
		
		/**
		 * Draws a diagonal line from v0 to v1
		 * @param v0
		 * @param v1
		 */
		void drawDiagonalLine(Vertex& v0, Vertex& v1);
		
		/**
		 * Utility function for sorting two vertices asscending
		 * by their x coordinate
		 * @param firstV
		 * @param secondV
		 * @param v0
		 * @param v1
		 * @post v0 points to the left most point
		 * @post v1 points to the right most point
		 * @return 
		 */
		Vertex* sortByX(Vertex& firstV, Vertex& secondV, 
				Vertex*& v0, Vertex*& v1);
		
		Vertex* sortByY(Vertex& firstV, Vertex& secondV, 
				Vertex*& v0, Vertex*& v1);		
		
		/**
		 * Utility function for sorting two vertices asscending
		 * by their y coordinate
         * @param firstV
         * @param secondV
         * @param v0
         * @param v1
		 * @post v0 points to the left most point
		 * @post v1 points to the right most point
         * @return 
         */
		Vector4f colorDelta(const Vertex& startV, const Vertex& endV, 
				int pixelsToDetermine);
		
		/**
		 * Gets the interpolated z-value
                 * @param v0
                 * @param v1
                 * @return 
                 */
		float getInterpolatedZ(const Vertex& v0,  const Vertex& v1);
};

#endif