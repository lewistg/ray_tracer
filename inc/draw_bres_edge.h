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

#ifndef _DRAW_BRES_EDGE_H_
#define _DRAW_BRES_EDGE_H_

#include <vector>
#include <assert.h>
#include "draw_bres_line.h"

using namespace std;

/**
 * An method class that plots an edge. Note that this 
 * only traces and the edge and doesn't actually plot the points
 * on the raster. It only *captures* the points
 */
class DrawBresenhamEdge: public DrawBresLine
{
	public:
		/**
		 * Constructor
		 */
		DrawBresenhamEdge(Raster* raster);
		
		/**
		 * Destructor
		 */
		~DrawBresenhamEdge();
		
		/**
		 * Override
		 * @post Only the edge points that were plotted during this draw command
		 * are stored. Previous points that were stored are discarded.
		 */
		virtual void draw(Vertex* vertices, int numVertices);
		
		/**
		 * Gets the points that were plotted.
		 */
		vector<Vertex>& getPlottedEdgePoints();
		
	protected:
		/**
		 * Override
		 */
		void plotPoint(int x, int y, double pixelDepth, Vector4f color);
		
	private:
		vector<Vertex> _plottedEdgePoints;
};

#endif