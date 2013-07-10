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

#ifndef _BYU_GL_H_
#define _BYU_GL_H_

#include <GL/freeglut.h>
#include <assert.h>
#include "vector.h"
#include "raster.h"
#include "geometry_pipeline.h"
#include "draw_black_white_gradient.h"
#include "matrix_state.h"
#include "scenes.h"

const int GL_MODE = 1;
const int BYU_MODE = 2;

/**
 * Software implementation of the pipeline
 */
extern GeometryPipeline byuPipeline;

/**
 * Toggles the draw mode from OpenGL to the mode
 * the software implementation for CS 455.
 */
void byu_setDrawMode(int newDrawMode);

/**
 * Gets the draw mode.
 */
int byu_getDrawMode();

/**
 * Implements glClearColor
 * @param r
 * @param g
 * @param b
 * @param a
 */
void byu_glClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

/**
 * Implements glClear
 * @param mask
 */
void byu_glClear(GLbitfield mask);

/**
 * Implements glBegin
 */
void byu_glBegin(GLenum mode);

/**
 * Implements glEnd
 */
void byu_glEnd();

/**
 * Implements glColor3f
 */
void byu_glColor3f(GLfloat r, GLfloat g, GLfloat b);

/**
 * Implements glColor4f
 */
void byu_glColor4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

/**
 * Implements glVertex2i
 */
void byu_glVertex2i(GLint x, GLint y);

/**
 * Implements glVertex2f
 */
void byu_glVertex2f(GLfloat x, GLfloat y);

/**
 * Implements glVertex3f
 */
void byu_glVertex3f(GLfloat x, GLfloat y, GLfloat z);

/**
 * Implements glVertex4f
 */
void byu_glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

/**
 * Sets the point size
 * @param pointSize
 */
void byu_glPointSize(float pointSize);

/**
 * Enables drawing functionality
 */
void byu_glEnable(GLenum mode);

/**
 * Disables drawing functionality
 */
void byu_glDisable(GLenum mode);

/**
 * Applies a black to white gradient that is only visible
 * in BYU mode
 */
void byu_applyBWGradient();

/**
 * Implements glMatrixMode
 */
void byu_glMatrixMode(GLenum matrixMode);

/**
 * Implements glLoadIdentity
 */
void byu_glLoadIdentity();

/**
 * Implements glLoadMatrixd
 */
void byu_glLoadMatrixd(double m[16]);

/**
 * Implements glMultMatrixd
 */
void byu_glMultMatrixd(double m[16]);

/**
 * Implements glGetDoublev
 */
void byu_glGetDoublev(GLenum matrixMode, double data[16]);

/**
 * Implements glRotatef
 */
void byu_glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

/**
 * Non-standard rotate function
 * @param transX
 * @param transY
 * @param transZ
 */
void byu_fullRotate(GLfloat angle, GLfloat p0X, GLfloat p0Y, GLfloat p0Z,
		GLfloat p1X, GLfloat p1Y, GLfloat p1Z);

/**
 * Implements glTranslatef
 */
void byu_glTranslatef(GLfloat transX, GLfloat transY, GLfloat transZ);

/**
 * Implements glScalef
 */
void byu_glScalef(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ);

/**
 * Non-standard scaling function that scales keeping a given
 * "center point" fixed.
 * @param scaleX
 * @param scaleY
 * @param scaleZ
 * @param centerX
 * @param centerY
 * @param centerZ
 */
void byu_fixedScale(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ, 
			GLfloat centerX, GLfloat centerY, GLfloat centerZ);

/**
 * Non-standard shearing function
 * @param shearXByY
 * @param shearXByZ
 * @param shearYByX
 * @param shearYByZ
 * @param shearZByX
 * @param shearZByY
 */
void byu_shear(GLfloat shearXByY, GLfloat shearXByZ, 
		GLfloat shearYByX, GLfloat shearYByZ,
		GLfloat shearZByX, GLfloat shearZByY);

/**
 * Implements glOrtho
 */
void byu_glOrtho(GLdouble left, GLdouble right, 
			GLdouble bottom, GLdouble top,
			GLdouble nearVal, GLdouble farVal);

/**
 * Implements glPopMatrix
 */
void byu_glPopMatrix();

/**
 * Implements glPushMatrix
 */
void byu_glPushMatrix();

/**
 * Implements glViewport
 */
void byu_glViewport(int xMin, int yMin, int w, int h);

/**
 * Implements the glBlendFunc
 */
void byu_glBlendFunc(GLenum sfactor, GLenum dfactor);

#endif