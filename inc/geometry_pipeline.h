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

#ifndef _GRAPHICS_PIPELINE_H_
#define _GRAPHICS_PIPELINE_H_

#include <vector>
#include <assert.h>
#include <memory>
#include "matrix4f.h"
#include "vector4f.h"
#include "draw_command_factory.h"
#include "draw_command.h"
#include "vertex.h"
#include "graphics_state.h"
#include "vertex_buffer.h"
#include "matrix_state.h"

using namespace gmath;

/**
 * A software implementation of a graphics 
 * implementation. A method class that renders
 * to the raster
 */
class GeometryPipeline
{
	public:
		/**
		 * Constructor
		 */
		GeometryPipeline();
		
		/**
		 * Destructor
		 */
		virtual ~GeometryPipeline();
		
		/**
		 * Clears the screen with the color 
		 */
		void clearWithColor();
		
		/**
		 * Starts drawing a particular object
		 */
		void beginDrawing(int glDrawCommand);
		
		/**
		 * Executes the command that is passed in.
		 * @pre command != NULL
		 */
		void drawCommand(DrawCommand* command);
		
		/**
		 * Ends drawing the particular object and performs
		 * actual rendering.
		 */
		void endDrawing();
		
		/**
		 * Adds a vector to the current. This is called between
		 * the beginDrawing and endDrawing commands.
		 * @pre vertex is a 4 dimensional Vector
		 */
		void addVertex(Vertex vertex);
		
		/**
		 * Draws the scene using OpenGL 
		 */
		void renderWithOpenGL();
		
	private:
		/**The buffered vertices for drawing*/
		VertexBuffer _vertexBuffer;
		/**The "screen" to be drawn on*/
		Raster* _raster;
		/**The current drawing command*/
		auto_ptr<DrawCommand> _currentCommand;
		
		/**
		 * Performs the 3D projection process
                 */
		void projected3D();
};

#endif
