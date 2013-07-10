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

#include "draw_points.h"

DrawPoints::DrawPoints(Raster* raster, float pointSize):DrawCommand(raster), 
	_pointSize(roundPointSize(pointSize))
	{}

DrawPoints::~DrawPoints()
	{}

void DrawPoints::draw(Vertex* vertices, int numVertices)
{
	assert(vertices != NULL);
	
	for(int i = 0; i < numVertices; i++)
	{
	    float xc;
	    float yc;
	    float offsetToCorner;
	    if((int) _pointSize % 2 != 0)
	    {
		xc = floor(x(vertices[i].getVertex())) + .5;
		yc = floor(y(vertices[i].getVertex())) + .5;
		offsetToCorner = floor(_pointSize / 2.0f);
	    }
	    else
	    {
		xc = floor(x(vertices[i].getVertex()) + .5);
		yc = floor(y(vertices[i].getVertex()) + .5);
		offsetToCorner = (_pointSize / 2.0f) - .5;
	    }
	    
	    for(float x = xc - offsetToCorner; x <= xc + offsetToCorner; x += 1)
	    {
		for(float y = yc - offsetToCorner; y <= yc + offsetToCorner; y += 1)
		{
		    plotPoint(x, y, z(vertices[i].getVertex()), vertices[i].getColor());
		}
	    }
	}
	
	// lower left point
	/*int lDelta = (int) (_pointSize / 2);
	int rDelta = (lDelta % 2 == 0 ? lDelta : lDelta - 1);
	
	for(int i = 0; i < numVertices; i++)
	{
		int x0 = x(vertices[i].getVertex()) - lDelta;
		int y0 = y(vertices[i].getVertex()) - lDelta;
		int x1 = x(vertices[i].getVertex()) + rDelta;
		int y1 = y(vertices[i].getVertex()) + rDelta;
		
		for(int x = x0; x <= x1; x++)
		{
			for(int y = y0; y <= y1; y++)
			{
				const float* color = vertices[i].getColor().getData();
				raster->setPixel(x, y, color);
			}
		}
			
		
		/*int w = x(vertices[i].getVertex());
		int h = y(vertices[i].getVertex());
		const float* color = vertices[i].getColor().getData();
		raster->setPixel(w, h, color);*/
	//}
}

void DrawPoints::plotPoint(float x, float y, double pixelDepth, Vector4f color)
{
    assert(x - floor(x) == .5);
    assert(y - floor(y) == .5);
    DrawCommand::plotPoint((int) x, (int) y, pixelDepth, color);
}

int DrawPoints::roundPointSize(float pointSize)
{
    if(pointSize < 1.0f)
	return 1;
    else
	return (int) floor(pointSize + .5);
}