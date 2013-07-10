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

#include "draw_smooth_point.h"

DrawSmoothPoints::DrawSmoothPoints(Raster* raster, float pointSize):DrawCommand(raster), _radius(ceil(pointSize / 2))
	{}

DrawSmoothPoints::~DrawSmoothPoints()
	{}

void DrawSmoothPoints::draw(Vertex* vertices, int numVertices)
{
	assert(vertices != NULL);
	
	for(int i = 0; i < numVertices; i++)
		drawCircle(vertices[i]);
}

void DrawSmoothPoints::drawCircle(const Vertex& center)
{	
	int xC = x(center.getVertex());
	int yC = y(center.getVertex());
	
	int xK = 0;
	int yK = _radius;
	plotPointSymmetrically(xC, yC, xK, yK, z(center.getVertex()), center.getColor());		
	
	float pK = 5/4 - _radius;
	while(xK < yK)
	{
		float twoXKPlusOne = 2 * xK + 2;
		float twoYKPlusOne = 2 * yK - 2;
		xK += 1;
		if(pK < 0 )
		{
			plotPointSymmetrically(xC, yC, xK, yK, z(center.getVertex()), center.getColor());	
			pK = pK + twoXKPlusOne + 1;
		}
		else
		{
			yK -= 1;
			plotPointSymmetrically(xC, yC, xK, yK, z(center.getVertex()), center.getColor());
			pK = pK + twoXKPlusOne + 1 - twoYKPlusOne;
		}
	}
	
	/*while(xK < yK)
	//for(int i = 0; i < 30; i++)
	{
		int xKPlusOne = xK + 1;
		int yKPlusOne;
		int _pKPlusOne = pKPlusOne(xK, yK);
		if(_pKPlusOne < 0)
			yKPlusOne = yK;
		else if(_pKPlusOne == 0)
			yKPlusOne = yK - 1;
		else // _pKPlusOne > 0
			yKPlusOne = yK - 1;
		
		plotPointSymmetrically(xC, yC, xKPlusOne, yKPlusOne, center.getColor());		
		
		xK = xKPlusOne;
		yK = yKPlusOne;
	}*/
	
	
}

int DrawSmoothPoints::pKPlusOne(int x, int y)
{
	return (4 * pow(x, 2)) + (8 * x) + 
			(4 * pow(y, 2)) - (4 * y) - (4 * pow(_radius, 2)) + 5;
}

void DrawSmoothPoints::plotPointSymmetrically(int xC, int yC, int x, int y, float pixelDepth, const Vector4f& color)
{
	DrawCommand::plotPoint(xC + x, yC + y, (double) pixelDepth, color);
	DrawCommand::plotPoint(xC - x, yC + y, (double) pixelDepth, color);
	int xi = xC - x;
	int yi = yC + y;
	for(; xi < xC + x; xi++)
		DrawCommand::plotPoint(xi, yi, (double) pixelDepth, color);
	
	DrawCommand::plotPoint(xC + x, yC - y, (double) pixelDepth, color);
	DrawCommand::plotPoint(xC - x, yC - y, (double) pixelDepth, color);
	xi = xC - x;
	yi = yC - y;	
	for(; xi < xC + x; xi++)
		DrawCommand::plotPoint(xi, yi, pixelDepth, color);	

	DrawCommand::plotPoint(xC + y, yC + x, pixelDepth, color);
	DrawCommand::plotPoint(xC - y, yC + x, pixelDepth, color);
	xi = xC - y;
	yi = yC + x;	
	for(; xi < xC + y; xi++)
		DrawCommand::plotPoint(xi, yi, pixelDepth, color);		
	
	DrawCommand::plotPoint(xC + y, yC - x, pixelDepth, color);
	DrawCommand::plotPoint(xC - y, yC - x, pixelDepth, color);
	xi = xC - y;
	yi = yC - x;	
	for(; xi < xC + y; xi++)
		DrawCommand::plotPoint(xi, yi, pixelDepth, color);			
}