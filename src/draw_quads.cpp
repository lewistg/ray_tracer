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

#include "draw_quads.h"

DrawQuads::DrawQuads(Raster* raster):DrawCommand(raster), _drawTriangleStrip(raster)
{
	
}


DrawQuads::~DrawQuads()
{
	
}


void DrawQuads::draw(Vertex* vertices, int numVertices)
{
	for(int i = 3; i < numVertices; i += 4)
	{
		Vertex quad[] = {vertices[i - 3], vertices[i - 2], vertices[i - 0], vertices[i - 1]};
		/*cout << quad[0].getVertex().toString() << endl;
		cout << quad[1].getVertex().toString() << endl;
		cout << quad[2].getVertex().toString() << endl;
		cout << quad[3].getVertex().toString() << endl;*/
		_drawTriangleStrip.draw(quad, 4);
	}
}