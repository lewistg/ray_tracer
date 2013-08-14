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

#include <memory>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <assert.h>
#include <vector>
#include <fstream>
#include <math.h>
#include <pthread.h>
#include "matrix.h"
#include "vector.h"
#include "raster.h"
#include "screen.h"
#include "ray_tracer.h"
#include "rtriangle.h"
#include "sphere.h"
#include "camera.h"

using namespace std;
using namespace gmath;

/*
 * My ratracer
 */
Screen screen(640, 480, .1, 
	mvl::GVector3f(0.0f, 0.0f, 0.0f),
	mvl::GVector3f(0.0f, 0.0f, -1.0f),
	mvl::GVector3f(0.0f, 1.0f, 0.0f));

Eye eye(mvl::GVector3f(0.0f, 0.0f, 50.0f), 
	mvl::GVector3f(0.0f, 0.0f, -20.0f), 
	mvl::GVector3f(0.0f, 1.0f, 0.0f));
/*Eye eye(mvl::GVector4f(0.0f, 100.0f, 0.0f, 1.0f), 
	mvl::GVector4f(0.0f, 0.0f, -20.0f, 1.0f), 
	mvl::GVector4f(-1.0f, 0.0f, 0.0f, 1.0f));*/
Camera camera(eye);

Scene scene;

//RayTracer rayTracer(mvl::GVector4f(0.0f, 0.0f, 50.0f, 1.0f), &screen);
RayTracer rayTracer(camera.getEye().getLocation(), camera.getScreen());

/**
 * Intialize OpenGL context for rendering.
 */
void setupRC();

/**
 * This function is the callback function for when the window is reshaped.  
 * It re-establishes the viewport and clipping area.
 */
void reshapeWindow(int, int);

/**
 * This function is the callback for establishing the timer for redrawing the scene.
 */
void timerFunc(int);

/**
 * Draws the scene.
 */
void drawRaster();

void* rayThread(void* argument)
{
    float r = 10.0f;
    mvl::GVector3f center(0.0f, 0.0f, -15.0f);
	std::shared_ptr<IlluminatedObject> sphereA(new Sphere (center, r));
    sphereA->setColor(mvl::GVector4f(1.0f, 0.85f, 0.73f, 1.0f));
    sphereA->setDiffAmbCoeff(1.0);
    sphereA->setReflCoeff(0.0);
    //sphereA.setDiffAmbCoeff(.8);
    //sphereA.setReflCoeff(0.4);
    
    r = 7.0f;
    center = mvl::GVector3f(-15.0f, -3.0f, -3.0f);
    std::shared_ptr<IlluminatedObject> sphereB(new Sphere(center, r));
    sphereB->setColor(mvl::GVector4f(1.0f, 1.0f, 0.6f, 1.0f));
    sphereB->setDiffAmbCoeff(0.8f);
    sphereB->setReflCoeff(0.1f);
    
    r = 14.0f;
    center = mvl::GVector3f(20.0f, 4.0f, 0.0f);
    std::shared_ptr<IlluminatedObject> sphereL(new Sphere(center, r));
    sphereL->setColor(mvl::GVector4f(1.0f, 0.079f, 0.57f, 1.0f));
    sphereL->setReflCoeff(0.0f);
    
    mvl::GVector3f p0(-30.0f, 10.0f, -15.0f);
    mvl::GVector3f p1(-7.0f, 10.0f, -20.0f);
    mvl::GVector3f p2(-20.0f, 25.0f, -8.5f);
    std::shared_ptr<IlluminatedObject>triangle(new RTriangle (p0, p1, p2));
    triangle->setDiffAmbCoeff(0.2f);
    triangle->setReflCoeff(1.0f);
    
    //Plane plane(mvl::GVector4f(0.0f, 0.0f, -100.0f, 1.0f), mvl::GVector4f(0.0f, 0.707f, 0.707f, 1.0f));
    std::shared_ptr<IlluminatedObject>table(new Plane(mvl::GVector3f(0.0f, -10.0f, 0.0f), mvl::GVector3f(0.0f, 1.0f, 0.1f)));
    table->setColor(mvl::GVector4f(1.0f, 1.0f, 1.0f, 1.0f));
    table->setReflCoeff(.2);
    
    std::shared_ptr<IlluminatedObject>backWall(new Plane(mvl::GVector3f(0.0f, -10.0f, -50.0f), mvl::GVector3f(0.0f, 0.0f, 1.0f)));
    backWall->setColor(mvl::GVector4f(0.67f, 0.84f, 0.90f, 1.0f));
    backWall->setReflCoeff(.2);    
    
    Plane frontWall(mvl::GVector3f(0.0f, -10.0f, 100.0f), mvl::GVector3f(0.0f, 0.0f, -1.0f));
    frontWall.setColor(mvl::GVector4f(0.5f, 1.0f, 0.5f, 1.0f));
    frontWall.setReflCoeff(.2);    
    
    Plane ceilingWall(mvl::GVector3f(0.0f, 40.0f, 100.0f), mvl::GVector3f(0.0f, -1.0f, 0.0f));
    ceilingWall.setColor(mvl::GVector4f(1.0f, 0.0f, 0.0f, 1.0f));
    ceilingWall.setReflCoeff(.2);     
    
    LambertLight light0;
    //light.setPos(mvl::GVector4f(0.0f, 0.0f, 10.0f, 1.0f));
    light0.setPos(mvl::GVector3f(-20.0f, 20.0f, 100.0f));
    light0.setDiffuse(mvl::GVector4f(0.75f, 0.75f, 0.6f, 1.0f));
    light0.setAmbient(mvl::GVector4f(0.01f, 0.01f, 0.01f, 1.0f));
    
    LambertLight light1;
    light1.setPos(mvl::GVector3f(20.0f, 20.0f, 100.0f));
    //light2.setPos(mvl::GVector4f(0.0f, 0.0f, -500.0f, 1.0f));
    light1.setDiffuse(mvl::GVector4f(0.5f, 0.5f, 0.4f, 1.0f));
    light1.setAmbient(mvl::GVector4f(0.01f, 0.01f, 0.01f, 1.0f));
    
    Scene scene;
    scene.addObject(sphereA);
    scene.addObject(sphereB);
    scene.addObject(sphereL);
    scene.addObject(table);
    scene.addObject(triangle);
    scene.addObject(backWall);
    //scene.addObject(&frontWall);
    //scene.addObject(&ceilingWall);
    scene.addLight(&light0);
    scene.addLight(&light1);    
    
    rayTracer.trace(scene);
    return NULL;
}

int main(int argc, char* argv[])
{	
    pthread_t rayTraceThread;
    int threadArgs;
    pthread_create(&rayTraceThread, NULL, rayThread, (void*) &threadArgs);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Ray tracer");
    glewInit();

    setupRC();

    glutReshapeFunc(reshapeWindow);
    glutDisplayFunc(drawRaster);
    glutTimerFunc(33, timerFunc, 1);

    glutMainLoop();
}

void setupRC()
{
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
}

void reshapeWindow(int w, int h)
{
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawRaster()
{   
    GLint oldMatrixMode;
    GLboolean depthWasEnabled = glIsEnabled(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glGetIntegerv(GL_MATRIX_MODE, &oldMatrixMode);
    glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();

    glRasterPos2f(-1, -1);
    glDrawPixels(640, 480, GL_RGBA, GL_FLOAT, camera.getScreen().getRasterData());

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW); glPopMatrix();
    glMatrixMode(oldMatrixMode);
    if(depthWasEnabled)
	    glEnable(GL_DEPTH_TEST);	

    glutSwapBuffers();
}

void timerFunc(int /*value*/)
{
	glutPostRedisplay();
	glutTimerFunc(33, timerFunc, 1);		
}