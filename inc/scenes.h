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

#ifndef _SCENES_H_
#define _SCENES_H_

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include "raster.h"
#include "byu_gl.h"

using namespace std;

/**
 * Loads the scenes array with project two scenes
 */
void initProj2Scenes();


/**
 * Scenes from project 2
 */
void drawGradient();
void drawPoints();
void drawLines();
void drawTriangles();
void drawLineStrip();
void drawLineLoop();
void drawTriangleStrip();
void drawTriangleFan();
void drawQuads();
void drawQuadStrip();
void drawPolygon();
void drawGradient();
void drawBlendedTriangles();
void drawBigPoints();

/**
 * Scenes from project 3
 */
void initProj3Scenes();
void viewPortTransform();
void depthBufferTriangles();
void divideByWCoord();
void easyPointClipping();
void matrixManipulation();
void tree(int depth);
void matrixStacks();
void rotatedTriangle();
void translatedTriangle();
void scaledTrangle();
void orthoTriangles();
void fixedScaleTriangles();
void shearedTriangles();
void fullRotatedTriangles();
void depthLines();

#endif