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

#ifndef _DRAW_POINTS_H_
#define _DRAW_POINTS_H_

#include <assert.h>
#include <math.h>
#include "draw_command.h"

class DrawPoints:public DrawCommand
{
	public:
		/**
		 * Constructs a new DrawPoints
		 */
		DrawPoints(Raster* raster, float pointSize);
	
		/**
		 * Destructor
		 */
		virtual ~DrawPoints();
		
		/**
		 * Draws the points on the raster
		 */
		virtual void draw(Vertex* vertices, int numVertices);
		
	private:
		/**
		 * The size of the points
		 */
		float _pointSize;
		
		/**
		 * Plots a point on the grid
		 * @pre x, y are half-integers
                 */
		void plotPoint(float x, float y, double pixelDepth, Vector4f color);
		
		/**
		 * Utility rounding function
                 * @return 
                 */
		int roundPointSize(float pointSize);
};

#endif