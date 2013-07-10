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

#include "draw_bres_line.h"

DrawBresLine::DrawBresLine(Raster* raster):DrawCommand(raster)
{
	
}

DrawBresLine::~DrawBresLine()
{
	
}

void DrawBresLine::draw(Vertex* vertices, int numVertices)
{	
	for(int i = 0; i + 1 < numVertices; i += 2)
	{	
		Vertex* v0 = NULL;
		Vertex* v1 = NULL;
		
		int dx = x(vertices[i + 1].getVertex()) - x(vertices[i + 0].getVertex());
		int dy = y(vertices[i + 1].getVertex()) - y(vertices[i + 0].getVertex());
		if(dx == 0)
		{
			sortByY(vertices[i], vertices[i + 1], v0, v1);
			drawLineByY(*v0, *v1);
		}
		else if(dy == 0)
		{
			sortByX(vertices[i], vertices[i + 1], v0, v1);
			drawHorizontalLine(*v0, *v1);		
		}
		else if(dy == dx)
		{
			sortByX(vertices[i], vertices[i + 1], v0, v1);
			drawDiagonalLine(*v0, *v1);		
		}
		else if(fabs((float) dy / (float) dx) < 1)
		{
			sortByX(vertices[i], vertices[i + 1], v0, v1);
			drawLineByX(*v0, *v1);
		}
		else
		{
			sortByY(vertices[i], vertices[i + 1], v0, v1);
			drawLineByY(*v0, *v1);
		}
		
	}
		
}

void DrawBresLine::plotPoint(int x, int y, double pixelDepth, Vector4f color)
{
    Vector4f blendedColor = BlendingFunc::getInstance().blend(*getRaster(), x, y, color);
    DrawCommand::plotPoint(x, y, pixelDepth, blendedColor);
}

void DrawBresLine::drawVerticalLine(Vertex& v0, Vertex& v1)
{
	_lineDepthCalculator.calibrateForLine(v0.getVertex(), v1.getVertex());
	int dy = y(v1.getVertex()) - y(v1.getVertex());
	Vector4f colorD = colorDelta(v0, v1, dy);
	Vector4f color = v0.getColor();
	int xc = x(v0.getVertex());
	float pixelDelta = (z(v1.getVertex()) - z(v0.getVertex())) / 
		(y(v0.getVertex()) - y(v1.getVertex()));
	float pixelDepth = z(v0.getVertex());
	for(int yi = y(v0.getVertex()); yi <= y(v1.getVertex()); yi++)
	{
		plotPoint(xc, yi, _lineDepthCalculator.getDepthByY(yi), color);
		color += colorD;
		pixelDepth += pixelDelta;
	}
}

void DrawBresLine::drawHorizontalLine(Vertex& v0, Vertex& v1)
{
	_lineDepthCalculator.calibrateForLine(v0.getVertex(), v1.getVertex());
	int dx = x(v1.getVertex()) - x(v0.getVertex());
	Vector4f colorD = colorDelta(v0, v1,  dx);
	Vector4f color = v0.getColor();
	int yc = y(v0.getVertex());
	float pixelDelta = (z(v1.getVertex()) - z(v0.getVertex())) / 
		(x(v0.getVertex()) - x(v1.getVertex()));
	float pixelDepth = z(v0.getVertex());
	for(int xi = x(v0.getVertex()); xi <= x(v1.getVertex()); xi++)
	{
		plotPoint(xi, yc, _lineDepthCalculator.getDepthByX(xi), color);
		color += colorD;
		pixelDepth += pixelDelta;
	}	
}

void DrawBresLine::drawDiagonalLine(Vertex& v0, Vertex& v1)
{
	_lineDepthCalculator.calibrateForLine(v0.getVertex(), v1.getVertex());
	int dXAndY = x(v1.getVertex()) - x(v0.getVertex());
	Vector4f colorD = colorDelta(v0, v1,  dXAndY);
	Vector4f color = v0.getColor();
	float pixelDelta = (z(v1.getVertex()) - z(v0.getVertex())) / 
		(y(v0.getVertex()) - y(v1.getVertex()));
	float pixelDepth = z(v0.getVertex());	
	for(int i = 0; i + x(v0.getVertex()) <= x(v1.getVertex()); i++)
	{
		plotPoint(x(v0.getVertex()) + i, y(v0.getVertex()) + i, 
			_lineDepthCalculator.getDepthByX(x(v0.getVertex()) + i), 
			color);
		color += colorD;
		pixelDepth += pixelDelta;
	}
}

void DrawBresLine::drawLineByX(Vertex& v0, Vertex& v1)
{
	assert(x(v0.getVertex()) < x(v1.getVertex()));
	
	_lineDepthCalculator.calibrateForLine(v0.getVertex(), v1.getVertex());
	
	int xK = x(v0.getVertex());
	int yK = y(v0.getVertex());	
	plotPoint(xK, yK, z(v0.getVertex()), v0.getColor());
	
	int dx = x(v1.getVertex()) - x(v0.getVertex());
	int dy = y(v1.getVertex()) - y(v0.getVertex());
	int yInc = (dy < 0 && dx > 0 || dy > 0 && dx < 0) ? -1 : 1;
	
	int absDx = fabs(dx);
	int absDy = fabs(dy);
	int twoDy = 2 * absDy;
	int twoDyMinusTwoDx = twoDy - (2 * absDx);
	int pK = twoDy - absDx;
	
	Vector4f colorD = colorDelta(v0, v1, dx);
	Vector4f color = v0.getColor();
	
	float pixelDelta = (z(v1.getVertex()) - z(v0.getVertex())) / dx;
	float pixelDepth = z(v0.getVertex());	
	for(int k = 0; k <= absDx - 1; k++)
	{
		xK += 1;
		pixelDepth += pixelDelta;
		if(pK < 0)
		{
			pK = pK + twoDy;
		}
		else
		{
			yK += yInc;
			pK = pK + twoDyMinusTwoDx; 
		}
			
		plotPoint(xK, yK, _lineDepthCalculator.getDepthByX(xK), color);
		color += colorD;
	}
}

void DrawBresLine::drawLineByY(Vertex& v0, Vertex& v1)
{	
	assert(y(v0.getVertex()) <= y(v1.getVertex()));
	
	_lineDepthCalculator.calibrateForLine(v0.getVertex(), v1.getVertex());
	
	int xK = x(v0.getVertex());
	int yK = y(v0.getVertex());
	plotPoint(xK, yK, z(v0.getVertex()), v0.getColor());
	
	int dx = x(v1.getVertex()) - x(v0.getVertex());
	int dy = y(v1.getVertex()) - y(v0.getVertex());
	int xInc = (dy < 0 && dx > 0 || dy > 0 && dx < 0) ? -1 : 1;
	
	int absDx = fabs(dx);
	int absDy = fabs(dy);
	int twoDx = 2 * absDx;
	int twoDxMinusTwoDy = twoDx - (2 * absDy);
	int pK = twoDx - absDy;
	
	Vector4f colorD = colorDelta(v0, v1, dy);
	Vector4f color = v0.getColor();
	float pixelDelta = (z(v1.getVertex()) - z(v0.getVertex())) / dy;
	float pixelDepth = z(v0.getVertex());	
	
	for(int k = 0; k <= absDy - 1; k++)
	{
		yK += 1;
		pixelDepth += pixelDelta;
		if(pK < 0)
		{
			pK = pK + twoDx;
		}
		else
		{
			xK += xInc;
			pK = pK + twoDxMinusTwoDy; 
		}
			
		plotPoint(xK, yK, _lineDepthCalculator.getDepthByY(yK), color);
		color += colorD;
	}
	//cout << pixelDepth << endl;
	//cout << z(v1.getVertex()) << endl;
	//assert(pixelDepth == z(v1.getVertex()));
}

Vertex* DrawBresLine::sortByX(Vertex& firstV, Vertex& secondV, 
		Vertex*& v0, Vertex*& v1)
{
	if(x(firstV.getVertex()) < x(secondV.getVertex()))
	{
		v0 = &firstV;
		v1 = &secondV;
	}
	else
	{
		v0 = &secondV;
		v1 = &firstV;
	}	
}

Vertex* DrawBresLine::sortByY(Vertex& firstV, Vertex& secondV, 
		Vertex*& v0, Vertex*& v1)
{
	if(y(firstV.getVertex()) < y(secondV.getVertex()))
	{
		v0 = &firstV;
		v1 = &secondV;
	}
	else
	{
		v0 = &secondV;
		v1 = &firstV;
	}	
}

Vector4f DrawBresLine::colorDelta(const Vertex& startV, const Vertex& endV, 
		int pixelsToDetermine)
{
	Vector4f colorDelta = sub(endV.getColor(), startV.getColor());
	colorDelta.scale(1 / ((float) pixelsToDetermine));	
	//cout << colorDelta.toString() << endl;
	return colorDelta;
}

float DrawBresLine::getInterpolatedZ(const Vertex& v0,  const Vertex& v1)
{

}