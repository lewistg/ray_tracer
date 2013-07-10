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

#include "draw_triangle_strip.h"
#include "draw_command_factory.h"

DrawTriangleStrip::DrawTriangleStrip(Raster* raster):DrawCommand(raster), _drawTriangle(raster)
	{}
		
DrawTriangleStrip::~DrawTriangleStrip()
	{}

void DrawTriangleStrip::draw(Vertex* vertices, int numVertices)
{
	
	for(int i = 0; i + 2 < numVertices; i++)
	{	
		// if it is odd
		if(i % 2 == 1)
		{
			Vertex triangle[] = {vertices[i + 0], vertices[i + 1], vertices[i + 2]};
			_drawTriangle.draw(triangle, 3);
		}
		else // else if it is even
		{
			Vertex triangle[] = {vertices[i + 1], vertices[i + 0], vertices[i + 2]};
			_drawTriangle.draw(triangle, 3);
		}
	}
}