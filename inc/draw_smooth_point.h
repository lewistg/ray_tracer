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

#ifndef _DRAW_SMOOTH_POINT_H_
#define _DRAW_SMOOTH_POINT_H_

#include <assert.h>
#include <math.h>
#include "draw_command.h"

class DrawSmoothPoints:public DrawCommand
{
	public:
		/**
		 * Constructs a new DrawPoints
		 */
		DrawSmoothPoints(Raster* raster, float pointSize);
	
		/**
		 * Destructor
		 */
		virtual ~DrawSmoothPoints();
		
		/**
		 * Draws the points on the raster
		 */
		virtual void draw(Vertex* vertices, int numVertices);
		
	private:
		/**Point size*/
		float _radius;
		
		/**
		 * Draws a circle
         */
		void drawCircle(const Vertex& center);
		
		/**
		 * The circ function from page 105 times 4.
		 */
		int pKPlusOne(int x, int y);
		
		/**
		 * Plots the point symmetrically
		 * @pre x,y are points "on" the circle between 
		 * 45 degrees and 90 degrees
		 */
		void plotPointSymmetrically(int xC, int yC, int x, int y, float pixelDepth, const Vector4f& color);
};
#endif