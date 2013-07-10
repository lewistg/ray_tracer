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

#include "draw_triangle.h"

DrawTriangle::DrawTriangle(Raster* raster):DrawCommand(raster), _bresEdge(raster)
{
	
}
		
DrawTriangle::~DrawTriangle()
{
	
}

/**
 * Override
 */
void DrawTriangle::draw(Vertex* vertices, int numVertices)
{
	if(numVertices < 3)
		return;
	
	_triangleEdgePoints.clear();
	drawBorder(vertices[0], vertices[1], vertices[2]);
	_depthCalc.calibrateForPlane(vertices[0].getVertex(), 
					vertices[1].getVertex(), 
					vertices[2].getVertex());
	fillTriangle();
	
	/*for(int i = 0; i + 2 < numVertices; i += 3)
	{
		_triangleEdgePoints.clear();
		drawBorder(vertices[i + 0], vertices[i + 1], vertices[i + 2]);
		fillTriangle();
	}*/
}

void DrawTriangle::drawBorder(const Vertex& p0, const Vertex& p1, const Vertex& p2)
{
	//DrawBresenhamLine bresLine;
	Vertex edge0[] = {p0, p1};
	_bresEdge.draw(edge0, 2);
	storeEdgePoints(_bresEdge.getPlottedEdgePoints());
	
	Vertex edge1[] = {p0, p2};
	_bresEdge.draw(edge1, 2);
	storeEdgePoints(_bresEdge.getPlottedEdgePoints());
	
	Vertex edge2[] = {p1, p2};
	_bresEdge.draw(edge2, 2);
	storeEdgePoints(_bresEdge.getPlottedEdgePoints());
}

void DrawTriangle::fillTriangle()
{
	assert(!_triangleEdgePoints.empty());
	
	sort(_triangleEdgePoints.begin(), 
			_triangleEdgePoints.end(), 
			DrawTriangle::compareEdgePointsByY);
			
	Vertex* xMin = &(*_triangleEdgePoints.begin());
	Vertex* xMax = &(*_triangleEdgePoints.begin());
	int currentY = y(_triangleEdgePoints[0].getVertex());
	for(vector<Vertex>::iterator pixelItr = _triangleEdgePoints.begin();
			pixelItr != _triangleEdgePoints.end();
			pixelItr++)
	{
		if(x(pixelItr->getVertex()) < x(xMin->getVertex()))
		{
			xMin = &(*pixelItr);
		}
		else if(x(pixelItr->getVertex()) > x(xMax->getVertex()))
		{
			xMax = &(*pixelItr);
		}
		
		vector<Vertex>::iterator nextPixel = pixelItr + 1;
		
		// if we have gone through all the pixels, finish up the last line
		if(nextPixel == _triangleEdgePoints.end())
		{
			//if(xMin != xMax)
				fillScanLine(*xMin, *xMax);
			break;
		}
			
		// if we are done on this y scanline
		int nextY = y(nextPixel->getVertex());
		if(nextY > currentY)
		{
			//if(xMin != xMax)
				fillScanLine(*xMin, *xMax);
			
			currentY = nextY;
			xMin = &(*nextPixel);
			xMax = &(*nextPixel);
		}
		
		/*if(nextPixel != _triangleEdgePoints.end())
		{
			int nextY = y(nextPixel->getVertex());
			if(nextY > currentY && (xMin != xMax))
			{
				fillScanLine(*xMin, *xMax);
				currentY = nextY;
				xMin = &(*nextPixel);
				xMax = &(*nextPixel);
			}
		}
		else
		{
			if(xMin != xMax)
				fillScanLine(*xMin, *xMax);
		}*/
	}
}

void DrawTriangle::fillScanLine(const Vertex& xMin, const Vertex& xMax)
{
	//assert(&xMin != &xMax);
	assert(x(xMin.getVertex()) <= x(xMax.getVertex()));
	assert(y(xMin.getVertex()) == y(xMax.getVertex()));
	
	float x0 = x(xMin.getVertex());
	float x1 = x(xMax.getVertex());
	int y0 = y(xMin.getVertex());
	
	Vector4f colorDelta = sub(xMax.getColor(), xMin.getColor());
	colorDelta.scale(1 / ((float) (x1 - x0)));
	Vector4f color = xMin.getColor();
	double pixelDepth = z(xMin.getVertex());
	double depthDelta = (z(xMax.getVertex()) - z(xMin.getVertex())) / (x1 - x0);
	
	for(int x = x0; x <= x1; x++)
	{
	    Vector4f blendedColor = 
		    BlendingFunc::getInstance().blend(*DrawCommand::getRaster(), x, y0, color);
	    plotPoint(x, y0, _depthCalc.getDepth(x, y0), blendedColor);
	    //_raster->setPixel(x, y0, color.getData());
	    color += colorDelta;
	    pixelDepth += depthDelta;
	}
}

void DrawTriangle::storeEdgePoints(vector<Vertex>& edgePoints)
{
	for(vector<Vertex>::iterator vertexItr = edgePoints.begin();
		vertexItr != edgePoints.end(); 
		vertexItr++)
	{
		_triangleEdgePoints.push_back(*vertexItr);
	}
}

bool DrawTriangle::compareEdgePointsByY(const Vertex& p0, const Vertex& p1)
{
	return y(p0.getVertex()) < y(p1.getVertex());
}