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

#ifndef _DRAW_TRIANGLE_H_
#define _DRAW_TRIANGLE_H_

#include <assert.h>
#include <vector>
#include <algorithm>
#include "draw_command.h"
//#include "draw_bresenham_line.h"
#include "draw_bres_edge.h"
#include "plane_depth_calculator.h"

using namespace std;

/**
 * Draws a single triangle
 */
class DrawTriangle: public DrawCommand
{
	public:
		/**
		 * Constructor
		 */
		DrawTriangle(Raster* raster);
		
		/**
		 * Destructor
		 */
		virtual ~DrawTriangle();
		
		/**
		 * Override
		 */
		void draw(Vertex* vertices, int numVertices);
		
	private:
		/**Draws Bresenham edge*/
		DrawBresenhamEdge _bresEdge;	
	    
		/**The points along the edge of the triangle*/
		vector<Vertex> _triangleEdgePoints;
		
		/**Used to calculate our depth for scan lines*/
		PlaneDepthCalculator _depthCalc;
		
		/**
		 * Draws the border of the triangle
		 * @param p0, p1, p2 The points defining the corners of the triangle.
		 */
		void drawBorder(const Vertex& p0, const Vertex& p1, const Vertex& p2);
		
		/**
		 * Store edge points
		 */
		void storeEdgePoints(vector<Vertex>& edgePoints);
		
		/**
		 * Fills in the triangle
		 * @param p0
		 * @param p1
		 * @return 
		 */
		void fillTriangle();
		
		/**
		 * Fills a line of pixels
		 * @pre xMin != xMax
		 * @pre x(xMin) < x(xMax)
		 * @pre y(xMin) == y(xMax)s
		 * @param xMin
		 * @param xMax
		 */
		void fillScanLine(const Vertex& xMin, const Vertex& xMax);
		
		/**
		 * Compares two edge points
		 * @param p0
		 * @param p1
		 * @return 
		 */
		static bool compareEdgePointsByY(const Vertex& p0, const Vertex& p1);
};

#endif