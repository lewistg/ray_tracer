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

#include "draw_dda_line.h"

DrawDdaLine::DrawDdaLine(Raster* raster): DrawCommand(raster)
	{}

DrawDdaLine::~DrawDdaLine()
	{}

void DrawDdaLine::draw(Vertex* vertices, int numVertices)
{
	for(int i = 0; i + 1 < numVertices; i += 2)
	{
	    int dx = x(vertices[i+1].getVertex()) - x(vertices[i].getVertex());
	    int dy = y(vertices[i+1].getVertex()) - y(vertices[i].getVertex());
	    
	    int steps = (fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy));
	    float xIncrement = float (dx) / float (steps);
	    float yIncrement = float (dy) / float (steps);
	    
	    float xi = x(vertices[i].getVertex());
	    float yi = y(vertices[i].getVertex());
	    DrawCommand::plotPoint(round(xi), round(yi), 0, vertices[i].getColor());
	    for(int k = 0; k < steps; k++)
	    {
		xi += xIncrement;
		yi += yIncrement;
		DrawCommand::plotPoint(round(xi), round(yi), 0, vertices[i].getColor());
	    }
	}
}


int DrawDdaLine::round(const float x)
{
    return (int) (x + 0.5);
}