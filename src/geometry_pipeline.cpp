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

#include <GL/glew.h>

#include "geometry_pipeline.h"

bool DEBUG = false;

GeometryPipeline::GeometryPipeline():
		_currentCommand(NULL), _raster(Raster::getInstance())
{

}

GeometryPipeline::~GeometryPipeline()
{
}

void GeometryPipeline::clearWithColor()
{
	_raster->setAllPixels(GraphicsState::getInstance().getClearColor()->getData());
}

void GeometryPipeline::beginDrawing(int glDrawCommand)
{
	_vertexBuffer.clear();
	
	DrawCommandFactory commandFactory;
	switch(glDrawCommand)
	{
		case GL_POINTS:
			_currentCommand = 
					auto_ptr<DrawCommand>(commandFactory.createDrawCommand(_raster, POINTS));
		break;
		
		case GL_LINES:
			_currentCommand = 
					auto_ptr<DrawCommand>(commandFactory.createDrawCommand(_raster, LINES));
		break;
		
		case GL_TRIANGLES:
			_currentCommand = 
					auto_ptr<DrawCommand>(commandFactory.createDrawCommand(_raster, TRIANGLES));
		break;
		
		case GL_TRIANGLE_STRIP:
			_currentCommand = 
					auto_ptr<DrawCommand>(commandFactory.createDrawCommand(_raster, TRIANGLE_STRIP));			
		break;
		
		case GL_POLYGON:
		case GL_TRIANGLE_FAN:
			_currentCommand = 
					auto_ptr<DrawCommand>(commandFactory.createDrawCommand(_raster, TRIANGLE_FAN));						
		break;
		
		case GL_LINE_STRIP:
			_currentCommand = 
					auto_ptr<DrawCommand>(commandFactory.createDrawCommand(_raster, LINE_STRIP));
		break;
		
		case GL_LINE_LOOP:
			_currentCommand = 
					auto_ptr<DrawCommand>(commandFactory.createDrawCommand(_raster, LINE_LOOP));
		break;
		
		case GL_QUADS:
			_currentCommand = 
					auto_ptr<DrawCommand>(commandFactory.createDrawCommand(_raster, QUADS));			
		break;
		
		case GL_QUAD_STRIP:
			_currentCommand = 
					auto_ptr<DrawCommand>(commandFactory.createDrawCommand(_raster, QUAD_STRIP));	
		break;
		
		default:
			assert(false);
		break;
	}
}

void GeometryPipeline::endDrawing()
{
	assert(_currentCommand.get() != NULL);
	projected3D();
	_currentCommand->draw(_vertexBuffer.getVertices(), _vertexBuffer.numVertices());
	//dumpRasterToPpm(_raster);
}

void GeometryPipeline::addVertex(Vertex vertex)
{
	_vertexBuffer.addVertex(vertex);
}

void GeometryPipeline::renderWithOpenGL()
{
    //dumpRasterToPpm(_raster);
    
    /*GLint oldMatrixMode;
    GLboolean depthWasEnabled = glIsEnabled(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glGetIntegerv(GL_MATRIX_MODE, &oldMatrixMode);
    glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();

    glRasterPos2f(-1, -1);
    glDrawPixels(640, 480, GL_RGBA, GL_FLOAT, _raster.getData());

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW); glPopMatrix();
    glMatrixMode(oldMatrixMode);
    if(depthWasEnabled)
	    glEnable(GL_DEPTH_TEST);*/
    
    GLboolean clippingWasOn[GL_MAX_CLIP_PLANES];
    for (int i=0; i<GL_MAX_CLIP_PLANES; ++i) {
	clippingWasOn[i] = glIsEnabled(GL_CLIP_PLANE0+i);
	glDisable(GL_CLIP_PLANE0+i);
    }

    GLboolean depthWasEnabled = glIsEnabled(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);

    GLint oldviewport[4];
    glGetIntegerv(GL_VIEWPORT, oldviewport);
    glViewport(0,0,640,480);

    GLint oldmatrixmode;
    glGetIntegerv(GL_MATRIX_MODE,&oldmatrixmode);

    glMatrixMode(GL_MODELVIEW);  glPushMatrix(); glLoadIdentity();
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
    glRasterPos2f(-1,-1);
    glDrawPixels(640,480,GL_RGBA,GL_FLOAT, _raster->getData());
    glMatrixMode(GL_PROJECTION); glPopMatrix();
    glMatrixMode(GL_MODELVIEW);  glPopMatrix();

    glMatrixMode(oldmatrixmode);

    glViewport(oldviewport[0],oldviewport[1],oldviewport[2],oldviewport[3]);

    if (depthWasEnabled)
	glEnable(GL_DEPTH_TEST);

    for (int i=0; i<GL_MAX_CLIP_PLANES; ++i) {
	if (clippingWasOn[i])
	    glEnable(GL_CLIP_PLANE0+i);
    }
}

void GeometryPipeline::drawCommand(DrawCommand* command)
{
	command->draw(_vertexBuffer.getVertices(), _vertexBuffer.numVertices());
}

void GeometryPipeline::projected3D()
{
    // multiply by the modelview and projection matrix
    for(int i = 0; i < _vertexBuffer.numVertices(); i++)
    {
	//cout << "Before translation: " << _vertexBuffer[i].getVertex().toString() << endl;
	if(DEBUG)
	{
	    cout << "Vertex: " << i << endl;
	    cout << "Before projection " << _vertexBuffer[i].getVertex().toString() << endl;
	}
	
	_vertexBuffer[i].getVertex() = mult(MatrixState::getInstance().getActiveModelViewMatrix(), 
				_vertexBuffer[i].getVertex());
	
	if(DEBUG)
	{
	    cout << "Current modelview matrix:" << endl;
	    cout << MatrixState::getInstance().getActiveModelViewMatrix().toString() << endl;
	    cout << "After modelview transform: " << _vertexBuffer[i].getVertex().toString() << endl;
	}
	
	_vertexBuffer[i].getVertex() = mult(MatrixState::getInstance().getActiveProjMatrix(), 
			_vertexBuffer[i].getVertex());
	
	if(DEBUG)
		cout << "After projection transform: " << _vertexBuffer[i].getVertex().toString() << endl;
	
	_vertexBuffer[i].getVertex().scale(1 / w(_vertexBuffer[i].getVertex()));
	
	if(DEBUG)
		cout << "After divide by w: " << _vertexBuffer[i].getVertex().toString() << endl;
	
	x(_vertexBuffer[i].getVertex()) = (x(_vertexBuffer[i].getVertex()) + 1) / 2;
	y(_vertexBuffer[i].getVertex()) = (y(_vertexBuffer[i].getVertex()) + 1) / 2;
	
	if(DEBUG)
		cout << "After divide by 2: " << _vertexBuffer[i].getVertex().toString() << endl;
	
	Viewport curViewport = GraphicsState::getInstance().getViewPort();
	x(_vertexBuffer[i].getVertex()) = 
		((float) curViewport.width - 1) * x(_vertexBuffer[i].getVertex()) + curViewport.xMin;
	y(_vertexBuffer[i].getVertex()) = 
		((float) curViewport.height - 1) * y(_vertexBuffer[i].getVertex()) + curViewport.yMin;
	
	if(DEBUG)
		cout << "After cur viewport transform: " << _vertexBuffer[i].getVertex().toString() << endl;
	
	roundCompsToInt(&_vertexBuffer[i].getVertex());
	
	if(DEBUG)
		cout << "Screen coords:" << _vertexBuffer[i].getVertex().toString() << endl;
    }
}