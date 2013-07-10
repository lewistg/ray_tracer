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

#ifndef _DRAW_COMMAND_H_
#define _DRAW_COMMAND_H_

#include <assert.h>
#include <vector>
#include "vertex.h"
#include "raster.h"
#include "blending_func.h"

using namespace gmath;

/**
 * Abstract class for a drawing command
 */
class DrawCommand
{
	public:
	    /**
	     * Constructs a draw command.
	     * @param raster The "screen" to be drawn on.
	     * @param vertices The vertices that define the geometry.
	     */
	    DrawCommand(Raster* raster);
		
	    /**
	     * Destructor
	     */
	    virtual ~DrawCommand();

	    /**
	     * Executes the drawing command.
	     */
	    virtual void draw(Vertex* vertices, int numVertices) = 0;
	    
	protected:
	    /**
	     * Plots a point 
             * @param x
             * @param y
             * @param color
             */
	    virtual void plotPoint(int x, int y, double pixelDepth, Vector4f color);
	    
	    /**
	     * Getter for the raster
             * @return 
             */
	    const Raster* getRaster() const;
	
	private:
	    /**The raster that is drawn on.*/
	    Raster* _raster;
};

#endif