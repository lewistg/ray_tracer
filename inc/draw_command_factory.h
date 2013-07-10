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

#ifndef _DRAW_COMMAND_FACTORY_H_
#define _DRAW_COMMAND_FACTORY_H_

#include <assert.h>
#include "draw_command.h"
#include "draw_points.h"
#include "draw_bresenham_line.h"
#include "draw_triangles.h"
#include "draw_line_strip.h"
#include "draw_line_loop.h"
#include "draw_triangle_strip.h"
#include "draw_triangle_fan.h"
#include "draw_quad_strip.h"
#include "draw_quads.h"
#include "draw_smooth_point.h"
#include "graphics_state.h"
#include "draw_bres_line.h"

enum DrawCommandType
{
	POINTS,
	LINES,
	TRIANGLES,
	LINE_STRIP,
	LINE_LOOP,
	TRIANGLE_STRIP,
	TRIANGLE_FAN,
	QUADS,
	QUAD_STRIP,
	POLYGON
};

/**
 * Creates a particular command according to the 
 * state of the pipeline. 
 */
class DrawCommandFactory
{
	public:
		/**
		 * Constructs a new draw command factory.
         * @param pipelineQuery Pointer to the pipeline query object.
         */
		DrawCommandFactory();
		
		/**
		 * Deconstructor
         */
		virtual ~DrawCommandFactory();
		
		/**
		 * Creates a draw command according to the pipeline state and
		 * the command type.
         * @param commandType The type of the command to be created.
         * @return A pointer to a DrawCommand allocated on the heap.
         */
		DrawCommand* createDrawCommand(Raster* raster, DrawCommandType commandType);
		
	private:
		/**Vertex data*/
		Vertex* _vertices;
		
		/**Number of vertices*/
		int _numVertices;
};

#endif