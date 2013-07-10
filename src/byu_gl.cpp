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

#include "byu_gl.h"

/**
 * Our drawing mode
 */
int drawMode = GL_MODE;

GeometryPipeline byuPipeline;

void byu_setDrawMode(int newDrawMode)
{
	assert(newDrawMode == GL_MODE || 
			newDrawMode == BYU_MODE);
	
	drawMode = newDrawMode;
}

int byu_getDrawMode()
{
	return drawMode;
}

void byu_glClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	if(drawMode == GL_MODE)
		glClearColor(r, g, b, a);
	else
	{
		float color[] = {r, g, b, a};
		Vector4f clearColor(color);
		GraphicsState::getInstance().setClearColor(clearColor);
	}
}

void byu_glClear(GLbitfield mask)
{
	if(drawMode == GL_MODE)
	{
		glClear(mask);
	}
	else
	{
		if((mask & GL_COLOR_BUFFER_BIT) != 0)
		    Raster::getInstance()->setAllPixels(GraphicsState::getInstance().getClearColor()->getData());
			//byuPipeline.clearWithColor();
		if((mask & GL_DEPTH_BUFFER_BIT) != 0)
		    Raster::getInstance()->clearDepthBuffer();
	}
}

void byu_glBegin(GLenum mode)
{
	if(drawMode == GL_MODE)
	{
		glBegin(mode);
	}
	else
	{
		byuPipeline.beginDrawing(mode);
	}
}

void byu_glEnd()
{
	if(drawMode == GL_MODE)
	{
		glEnd();
	}
	else
	{
		byuPipeline.endDrawing();
	}	
}

void byu_glColor3f(GLfloat r, GLfloat g, GLfloat b)
{
	if(drawMode == GL_MODE)
	{
		glColor3f(r, g, b);
	}
	else
	{
		float color[] = {g, r, b, 1.0f};
		GraphicsState::getInstance().setColor(Vector4f(color));
	}
}

void byu_glColor4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	if(drawMode == GL_MODE)
	{
		glColor4f(r, g, b, a);
	}
	else
	{
		float color[] = {r, g, b, a};
		GraphicsState::getInstance().setColor(Vector4f(color));
	}
}

void byu_glVertex2i(GLint x, GLint y)
{
	if(drawMode == GL_MODE)
	{
		glVertex2i(x, y);
	}
	else
	{
		//float point[] = {(float) x - 1, (float) y, 0, 1};
		float point[] = {(float) x, (float) y, 0, 1};
		byuPipeline.addVertex(Vertex(Vector4f(point), *GraphicsState::getInstance().getColor()));
	}	
}

void byu_glVertex2f(GLfloat x, GLfloat y)
{
	if(drawMode == GL_MODE)
	{
		glVertex2f(x, y);
	}
	else
	{
		//float point[] = {(float) x - 1, (float) y, 0, 1};
		float point[] = {x, y, 0, 1};
		byuPipeline.addVertex(Vertex(Vector4f(point), *GraphicsState::getInstance().getColor()));
	}    
}

void byu_glVertex3f(GLfloat x, GLfloat y, GLfloat z)
{
	if(drawMode == GL_MODE)
	{
		glVertex3f(x, y, z);
	}
	else
	{
		float point[] = {(float) x, (float) y, (float) z, 1};
		byuPipeline.addVertex(Vertex(Vector4f(point), *GraphicsState::getInstance().getColor()));
	}	  
}

void byu_glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	if(drawMode == GL_MODE)
	{
		glVertex4f(x, y, z, w);
	}
	else
	{
		float point[] = {(float) x, (float) y, (float) z, (float) w};
		byuPipeline.addVertex(Vertex(Vector4f(point), *GraphicsState::getInstance().getColor()));
	}    
}

void byu_glPointSize(float pointSize)
{
	if(drawMode == GL_MODE)
		glPointSize(pointSize);
	else
		GraphicsState::getInstance().setPointSize(pointSize);
}

void byu_glEnable(GLenum mode)
{
	glEnable(mode);
	switch(mode)
	{
		case GL_POINT_SMOOTH:
			GraphicsState::getInstance().enable(GraphicsState::POINT_SMOOTH);
		break;

		case GL_BLEND:
		    BlendingFunc::getInstance().enableBlending();
		break;

		case GL_DEPTH_TEST:
		    Raster::getInstance()->depthBuffOn();
		break;
	}
}

void byu_glDisable(GLenum mode)
{
	if(drawMode == GL_MODE)
		glDisable(mode);
	
	switch(mode)
	{
		case GL_POINT_SMOOTH:
			GraphicsState::getInstance().disable(GraphicsState::POINT_SMOOTH);
		break;

		case GL_BLEND:
		    BlendingFunc::getInstance().enableBlending();
		break;	

		case GL_DEPTH_TEST:
		    Raster::getInstance()->depthBuffOff();
		break;			
	}	
}

void byu_applyBWGradient()
{
    //DrawBlackWhiteGradient drawBWGrad;
    //byuPipeline.drawCommand(&drawBWGrad);
}

void byu_glLoadIdentity()
{
    glLoadIdentity();
    MatrixState::getInstance().loadIdentity();
    
    /*if(drawMode == GL_MODE)
	glLoadIdentity();
    else
	MatrixState::getInstance().loadIdentity();*/
}

void byu_glLoadMatrixd(double m[16])
{
    glLoadMatrixd(m);
    MatrixState::getInstance().loadMatrixd(m);
    
    /*if(drawMode == GL_MODE)
	glLoadMatrixd(m);
    else
	MatrixState::getInstance().loadMatrixd(m);*/
}

void byu_glMultMatrixd(double m[16])
{
    glMultMatrixd(m);
    MatrixState::getInstance().multMatrixd(m);
    
    /*if(drawMode == GL_MODE)
	glMultMatrixd(m);
    else
	MatrixState::getInstance().multMatrixd(m);*/
}

void byu_glGetDoublev(GLenum matrixMode, double data[16])
{
    if(drawMode == GL_MODE)
    {
	glGetDoublev(matrixMode, data);
    }
    else
    {
	assert(matrixMode == GL_MODELVIEW_MATRIX || 
		matrixMode == GL_PROJECTION_MATRIX);
	if(matrixMode == GL_MODELVIEW_MATRIX)
		MatrixState::getInstance().getModelViewMatrixDatad(data);
	else if(matrixMode == GL_PROJECTION_MATRIX)
	    	MatrixState::getInstance().getProjMatrixDatad(data);
    }
	
}

void byu_glRotatef(GLfloat angle, GLfloat rotAxisX, GLfloat rotAxisY, GLfloat rotAxisZ)
{
    glRotatef(angle, rotAxisX, rotAxisY, rotAxisZ);
    
    Vector4f rotAxis(rotAxisX, rotAxisY, rotAxisZ, 1);
    normalize(&rotAxis);
    
    const float PI = 3.14159265;
    float angleInRads = angle * PI / 180;
    float c = cos(angleInRads);
    float s = sin(angleInRads);
    float rotateMatData[16] = {
	x(rotAxis) * x(rotAxis) * (1 - c) + c,	 
	y(rotAxis) * x(rotAxis) * (1 - c) + z(rotAxis) * s, 
	z(rotAxis) * x(rotAxis) * (1 - c) - y(rotAxis) * s,
	0,
	x(rotAxis) * y(rotAxis) * (1 - c) - z(rotAxis) * s,
	y(rotAxis) * y(rotAxis) * (1 - c) + c,
	z(rotAxis) * y(rotAxis) * (1 - c) + x(rotAxis) * s,
	0,
	x(rotAxis) * z(rotAxis) * (1 - c) + y(rotAxis) * s,
	y(rotAxis) * z(rotAxis) * (1 - c) - x(rotAxis) * s,
	z(rotAxis) * z(rotAxis) * (1 - c) + c,
	0,
	0, 0, 0, 1};
    MatrixState::getInstance().multMatrixf(rotateMatData);
    
    /*Vector4f u(rotAxisX, rotAxisY, rotAxisZ, 1);
    normalize(&u);
    
    float a = x(u);
    float b = y(u);
    float c = z(u);
    float d = sqrt((b * b) + (c * c));
    
    float rotateToXZData[] = {1, 0, 0, 0,
				0, c / d, b / d, 0,
				0, -b / d, c / d, 0,
				0, 0, 0, 1};
    Matrix4f rotateToXZ(rotateToXZData);
    
    float rotateToZData[] = {d, 0, -a, 0,
				0, 1, 0, 0,
				a, 0, d, 0,
				0, 0, 0, 1};
    Matrix4f rotateToZ(rotateToZData);
    
    const float PI = 3.14159265;
    float angleInRads = angle * PI / 180;
    float rotateAboutZData[] = {cos(angleInRads), sin(angleInRads), 0, 0,
				-sin(angleInRads), cos(angleInRads), 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1};
    Matrix4f rotateAboutZ(rotateAboutZData);
    
    Matrix4f rotMatrix = mult(rotateToXZ.inverse(), rotateToZ.inverse());
    rotMatrix = mult(rotMatrix, rotateAboutZ);
    rotMatrix = mult(rotMatrix, rotateToZ);
    rotMatrix = mult(rotMatrix, rotateToXZ);
    
    float finalMatrixData[16];
    rotMatrix.toArray(finalMatrixData);
    MatrixState::getInstance().multMatrixf(finalMatrixData);*/
}

void byu_fullRotate(GLfloat angle, GLfloat p0X, GLfloat p0Y, GLfloat p0Z,
		GLfloat p1X, GLfloat p1Y, GLfloat p1Z)
{   
    Vector4f transAxis(p1X-p0X, p1Y-p0Y, p1Z-p0Z, 1);
    normalize(&transAxis);
    
    const float PI = 3.14159265;
    float angleInRads = angle * PI / 180;
    float c = cos(angleInRads);
    float s = sin(angleInRads);
    
    // partially fill in the matrix
    float rotateMatData[16] = {
	x(transAxis) * x(transAxis) * (1 - c) + c,	 
	y(transAxis) * x(transAxis) * (1 - c) + z(transAxis) * s, 
	z(transAxis) * x(transAxis) * (1 - c) - y(transAxis) * s,
	0,
	x(transAxis) * y(transAxis) * (1 - c) - z(transAxis) * s,
	y(transAxis) * y(transAxis) * (1 - c) + c,
	z(transAxis) * y(transAxis) * (1 - c) + x(transAxis) * s,
	0,
	x(transAxis) * z(transAxis) * (1 - c) + y(transAxis) * s,
	y(transAxis) * z(transAxis) * (1 - c) - x(transAxis) * s,
	z(transAxis) * z(transAxis) * (1 - c) + c,
	0,
	0, 0, 0, 1};
    
    // finish filling it in
    rotateMatData[12] = (-p0X * 
	    (rotateMatData[0] + rotateMatData[4] + rotateMatData[8])) + p0X;
    rotateMatData[13] = (-p0Y * 
	    (rotateMatData[1] + rotateMatData[5] + rotateMatData[9])) + p0Y;
    rotateMatData[14] = (-p0Z * 
	    (rotateMatData[2] + rotateMatData[6] + rotateMatData[10])) + p0Z;
    
    glMultMatrixf(rotateMatData);
    MatrixState::getInstance().multMatrixf(rotateMatData);    
}

void byu_glTranslatef(GLfloat transX, GLfloat transY, GLfloat transZ)
{
    glTranslatef(transX, transY, transZ);
    float transMatrixData[] = {1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				transX, transY, transZ, 1};
    MatrixState::getInstance().multMatrixf(transMatrixData);
}

void byu_glScalef(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ)
{
    glScalef(scaleX, scaleY, scaleZ);
    float scaleMatrixData[] = {scaleX, 0, 0, 0,
				0, scaleY, 0, 0,
				0, 0, scaleZ, 0,
				0, 0, 0, 1};
    MatrixState::getInstance().multMatrixf(scaleMatrixData);
}
    
void byu_fixedScale(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ, 
		    GLfloat centerX, GLfloat centerY, GLfloat centerZ)
{
    double centeredScaleData[] = {scaleX, 0, 0, 0,
					0, scaleY, 0, 0,
					0, 0, scaleZ, 0,
					(-scaleX * centerX) + centerX,
					(-scaleY * centerY) + centerY,
					(-scaleZ * centerZ) + centerZ, 
					1};
    byu_glMultMatrixd(centeredScaleData);
}

 void byu_shear(GLfloat shearXByY, GLfloat shearXByZ, 
		GLfloat shearYByX, GLfloat shearYByZ,
		GLfloat shearZByX, GLfloat shearZByY)
{
    double shearingMatrix[] = {1, shearYByX, shearZByX, 0,
				shearXByY, 1, shearZByY, 0,
				shearXByZ, shearYByZ, 1, 0,
				0, 0, 0, 1};
    float shearingMatrix2[] = {1, shearYByX, shearZByX, 0,
				shearXByY, 1, shearZByY, 0,
				shearXByZ, shearYByZ, 1, 0,
				0, 0, 0, 1};
    Matrix4f shearMat(shearingMatrix2);
    //cout << shearMat.toString() << endl;
    
    byu_glMultMatrixd(shearingMatrix);
}

void byu_glOrtho(GLdouble left, GLdouble right, 
			GLdouble bottom, GLdouble top,
			GLdouble nearVal, GLdouble farVal)
{
    glOrtho(left, right, bottom, top, nearVal, farVal);
    double orthoProjData[] = {2 / (right - left), 0, 0, 0,
				0, 2 / (top - bottom), 0, 0,
				0, 0, -2 / (nearVal - farVal), 0,
				-(right + left) / (right - left), 
				-(top + bottom) / (top - bottom),
				(nearVal + farVal) / (nearVal - farVal), 
				1};
    MatrixState::getInstance().multMatrixd(orthoProjData);
}

void byu_glPushMatrix()
{
    glPushMatrix();
    MatrixState::getInstance().pushMatrix();
}

void byu_glPopMatrix()
{
    glPopMatrix();
    MatrixState::getInstance().popMatrix();
}

void byu_glMatrixMode(GLenum matrixMode)
{
    glMatrixMode(matrixMode);
    if(matrixMode == GL_MODELVIEW)
	MatrixState::getInstance().setMatrixMode(MODELVIEW);
    else
	MatrixState::getInstance().setMatrixMode(PROJECTION);    
    
    
    /*if(drawMode == GL_MODE)
	glMatrixMode(matrixMode);
    else
    {
	if(matrixMode == GL_MODELVIEW)
	    MatrixState::getInstance().setMatrixMode(MODELVIEW);
	else
	    MatrixState::getInstance().setMatrixMode(PROJECTION);
    }*/
}

void byu_glViewport(int xMin, int yMin, int w, int h)
{
    glViewport(xMin, yMin, w, h);
    GraphicsState::getInstance().setViewport(xMin, yMin, w, h);
    /*if(drawMode == GL_MODE)
	glViewport(xMin, yMin, w, h);
    else
	GraphicsState::getInstance().setViewport(xMin, yMin, w, h);*/
}

void byu_glBlendFunc(GLenum sfactor, GLenum dfactor)
{
    if(drawMode == GL_MODE)
    {
	glBlendFunc(sfactor, dfactor);
    }
    else
    {
	switch(sfactor)
	{
	    case GL_ZERO:
		BlendingFunc::getInstance().setSrcBlendType(ZERO);
	    break;
	    case GL_ONE:
		BlendingFunc::getInstance().setSrcBlendType(ONE);
	    break;
	    case GL_SRC_ALPHA:
		BlendingFunc::getInstance().setSrcBlendType(SRC_ALPHA);
	    break;
	    case GL_ONE_MINUS_SRC_ALPHA:
		BlendingFunc::getInstance().setSrcBlendType(ONE_MINUS_SRC_ALPHA);
	    break;
	    default:
		assert(false);
	    break;
	}
	
	switch(dfactor)
	{
	    case GL_ZERO:
		BlendingFunc::getInstance().setDestBlendType(ZERO);
	    break;
	    case GL_ONE:
		BlendingFunc::getInstance().setDestBlendType(ONE);
	    break;
	    case GL_SRC_ALPHA:
		BlendingFunc::getInstance().setDestBlendType(SRC_ALPHA);
	    break;
	    case GL_ONE_MINUS_SRC_ALPHA:
		BlendingFunc::getInstance().setDestBlendType(ONE_MINUS_SRC_ALPHA);
	    break;
	    default:
		assert(false);
	    break;
	}	
    }
    
}