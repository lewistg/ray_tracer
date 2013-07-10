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

#include "draw_bres_edge.h"

DrawBresenhamEdge::DrawBresenhamEdge(Raster* raster):DrawBresLine(raster)
{
	
}

DrawBresenhamEdge::~DrawBresenhamEdge()
{
	
}

void DrawBresenhamEdge::draw(Vertex* vertices, int numVertices)
{
	_plottedEdgePoints.clear();
	DrawBresLine::draw(vertices, numVertices);
}

vector<Vertex>& DrawBresenhamEdge::getPlottedEdgePoints()
{
	return _plottedEdgePoints;
}

void DrawBresenhamEdge::plotPoint(int x, int y, double pixelDepth, Vector4f color)
{	
	//DrawBresLine::plotPoint(x, y, color);
	_plottedEdgePoints.push_back(Vertex(Vector4f(x, y, pixelDepth, 0), color));
}