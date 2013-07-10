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

#include "draw_triangle_fan.h"

DrawTriangleFan::DrawTriangleFan(Raster* raster):DrawCommand(raster), _drawTriangle(raster)
{
	
}

DrawTriangleFan::~DrawTriangleFan()
{
	
}

void DrawTriangleFan::draw(Vertex* vertices, int numVertices)
{
	if(numVertices < 3)
		return;
	
	int numTriangles = numVertices - 2;
	const int CENTER = 0;
	for(int n = 0; n < numTriangles; n++)
	{
		Vertex triangle[] = {vertices[CENTER], vertices[n + 1], vertices[n + 2]};
		_drawTriangle.draw(triangle, 3);
	}
}