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

#include "draw_bresenham_line.h"

DrawBresenhamLine::DrawBresenhamLine(Raster* raster):DrawCommand(raster)
	{}
		
DrawBresenhamLine::~DrawBresenhamLine()
	{}
		
void DrawBresenhamLine::draw(Vertex* vertices, int numVertices)
{	
	for(int i = 0; i + 1 < numVertices; i += 2)
		drawLine(vertices[i], vertices[i + 1]);
}

void DrawBresenhamLine::drawLine(Vertex& p0, Vertex& p1)
{
	/*if(p0 == p1)
		return;*/
	
	/*assert(x(p0.getVertex()) <= x(p1.getVertex()));*/
	int xDelta = x(p0.getVertex()) - x(p1.getVertex());
	int yDelta = y(p0.getVertex()) - y(p1.getVertex());
	
	float epsilon = (float) yDelta / (float) xDelta;
	const int Y_INCREMENT = epsilon < 0 ? -1 : 1;
	const float ERROR_RESET = epsilon < 0 ? 1.0 : -1.0;
	
	if(abs(epsilon) < 1)
	{
		int startX; 
		int endX;
		float startZ;
		float endZ;
		int startY;
		Vector4f* startColor = NULL; 
		Vector4f* endColor = NULL;		
		if(x(p0.getVertex()) < x(p1.getVertex()))
		{
			startX = x(p0.getVertex());
			endX = x(p1.getVertex());
			startY = y(p0.getVertex());
			startZ = z(p0.getVertex());
			endZ = z(p1.getVertex());
			startColor = &p0.getColor();
			endColor = &p1.getColor();			
		}
		else
		{
			startX = x(p1.getVertex());
			endX = x(p0.getVertex());
			startY = y(p1.getVertex());
			startZ = z(p1.getVertex());
			endZ = z(p0.getVertex());
			startColor = &p1.getColor();
			endColor = &p0.getColor();				
		}
				
		walkAlongX(*startColor, *endColor,
				startX, startY, startZ, endX, endZ,
				epsilon, Y_INCREMENT, ERROR_RESET);
	}
	else
	{
		int startY; 
		int endY;
		float startZ;
		float endZ;
		int startX;
		Vector4f* startColor = NULL; 
		Vector4f* endColor = NULL;
		if(y(p0.getVertex()) < y(p1.getVertex()))
		{
			startY = y(p0.getVertex());
			endY = y(p1.getVertex());
			startX = x(p0.getVertex());
			startZ = z(p0.getVertex());
			endZ = z(p1.getVertex());
			startColor = &p0.getColor();
			endColor = &p1.getColor();
		}
		else
		{
			startY = y(p1.getVertex());
			endY = y(p0.getVertex());
			startX = x(p1.getVertex());
			startZ = z(p1.getVertex());
			endZ = z(p0.getVertex());
			startColor = &p1.getColor();
			endColor = &p0.getColor();			
		}		
		
		walkAlongY(*startColor, *endColor,
			startX, startY, startZ, endY, endZ,
			1 / epsilon, Y_INCREMENT, ERROR_RESET);
	}
}

void DrawBresenhamLine::walkAlongX(Vector4f& color0, Vector4f& color1, 
						int x0, int y0, float z0, 
						int x1, float z1, float epsilon, 
						const int Y_INCREMENT, const int ERROR_RESET)
{
	float error = 0;
	Vector4f colorDelta = sub(color1, color0);
	colorDelta.scale(1 / ((float) (x1 - x0)));
	Vector4f color = color0;
	float depthDelta = (z1 - z0) / (x1 - x0);
	float pixelDepth = z0;
	for(int x = x0, y = y0; x <= x1; x++)
	{
		plotPoint(x, y, pixelDepth, color);
		//_raster->setPixel(x, y, color.getData());
		error += epsilon;
		if(abs(error) >= 0.5f)
		{
			y += Y_INCREMENT;
			error += ERROR_RESET;
		}
		color += colorDelta;
		pixelDepth += depthDelta;
	}	
}

void DrawBresenhamLine::walkAlongY(Vector4f& color0, Vector4f& color1, 
						int x0, int y0, float z0, 
						int y1, float z1, float epsilon, 
						const int Y_INCREMENT, const int ERROR_RESET)
{
	float error = 0;
	Vector4f colorDelta = sub(color1, color0);
	colorDelta.scale(1 / ((float) (y1 - y0)));
	Vector4f color = color0;
	float depthDelta = (z1 - z0) / (y1 - y0);
	float pixelDepth = z0;
	for(int y = y0, x = x0; y <= y1; y++)
	{
		plotPoint(x, y, pixelDepth, color);
		//_raster->setPixel(x, y, color.getData());
		error += epsilon;
		if(abs(error) >= 0.5f)
		{
			x += Y_INCREMENT;
			error += ERROR_RESET;
		}
		color += colorDelta;
		pixelDepth += depthDelta;
	}	
}