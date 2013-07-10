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

#include "draw_command_factory.h"
#include "draw_dda_line.h"

DrawCommandFactory::DrawCommandFactory()
{
}

DrawCommandFactory::~DrawCommandFactory()
{
}

DrawCommand* DrawCommandFactory::createDrawCommand(Raster* raster, DrawCommandType commandType)
{
	DrawCommand* drawCommand = NULL;
	switch(commandType)
	{
		case POINTS:
			if(GraphicsState::getInstance().isEnabled(GraphicsState::POINT_SMOOTH))
				drawCommand = new DrawSmoothPoints(raster, GraphicsState::getInstance().getPointSize());
			else
				drawCommand = new DrawPoints(raster, GraphicsState::getInstance().getPointSize());
		break;
		
		case LINES:
			//drawCommand = new DrawBresenhamLine();
			drawCommand = new DrawBresLine(raster);
			//drawCommand = new DrawDdaLine();
		break;
		
		case TRIANGLES:
			drawCommand = new DrawTriangles(raster);
		break;
		
		case LINE_STRIP:
			drawCommand = new DrawLineStrip(raster);
		break;
		
		case LINE_LOOP:
			drawCommand = new DrawLineLoop(raster);
		break;
		
		case TRIANGLE_STRIP:
			drawCommand = new DrawTriangleStrip(raster);
		break;
		
		case TRIANGLE_FAN:
			drawCommand = new DrawTriangleFan(raster);
		break;
		
		case QUADS:
			drawCommand = new DrawQuads(raster);
		break;		
		
		case QUAD_STRIP:
			drawCommand = new DrawQuadStrip(raster);
		break;		
		
		default:
			assert(false);
		break;
	}
	
	assert(drawCommand != NULL);
	return drawCommand;
}