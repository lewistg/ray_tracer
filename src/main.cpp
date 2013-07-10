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
#include "byu_gl.h"
#include "scenes.h"
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
	Vector4f(0.0f, 0.0f, 0.0f, 1.0f),
	Vector4f(0.0f, 0.0f, -1.0f, 1.0f),
	Vector4f(0.0f, 1.0f, 0.0f, 1.0f));

Eye eye(Vector4f(0.0f, 0.0f, 50.0f, 1.0f), 
	Vector4f(0.0f, 0.0f, -20.0f, 1.0f), 
	Vector4f(0.0f, 1.0f, 0.0f, 1.0f));
/*Eye eye(Vector4f(0.0f, 100.0f, 0.0f, 1.0f), 
	Vector4f(0.0f, 0.0f, -20.0f, 1.0f), 
	Vector4f(-1.0f, 0.0f, 0.0f, 1.0f));*/
Camera camera(eye);

Scene scene;

//RayTracer rayTracer(Vector4f(0.0f, 0.0f, 50.0f, 1.0f), &screen);
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
 * Callback for keyboard interaction
 */
void keyPressed(unsigned char key, int x, int y);

/**
 * Checks for a special key press
 */
void specialKeyPressed(int key, int x, int y);

/**
 * Draws the scene.
 */
void drawScene();

extern int NUM_SCENES2;
extern vector<void (* )()> scenes2;

void* rayThread(void* argument)
{
    //IlluminatedObject object;
    float r = 10.0f;
    Vector4f center(0.0f, 0.0f, -15.0f, 1.0f);
    Sphere sphereA(center, r);
    sphereA.setColor(Vector4f(1.0f, 0.85f, 0.73f, 1.0f));
    sphereA.setDiffAmbCoeff(1.0);
    sphereA.setReflCoeff(0.0);
    //sphereA.setDiffAmbCoeff(.8);
    //sphereA.setReflCoeff(0.4);
    
    r = 7.0f;
    center = Vector4f(-15.0f, -3.0f, -3.0f, 1.0f);
    Sphere sphereB(center, r);
    sphereB.setColor(Vector4f(1.0f, 1.0f, 0.6f, 1.0f));
    sphereB.setDiffAmbCoeff(0.8f);
    sphereB.setReflCoeff(0.1f);
    
    r = 14.0f;
    center = Vector4f(20.0f, 4.0f, 0.0f, 1.0f);
    Sphere sphereL(center, r);
    sphereL.setColor(Vector4f(1.0f, 0.079f, 0.57f, 1.0f));
    sphereL.setReflCoeff(0.0f);
    
    Vector4f p0(-30.0f, 10.0f, -15.0f, 1.0f);
    Vector4f p1(-7.0f, 10.0f, -20.0f, 1.0f);
    Vector4f p2(-20.0f, 25.0f, -8.5f, 1.0f);
    RTriangle triangle(p0, p1, p2);
    triangle.setDiffAmbCoeff(0.2f);
    triangle.setReflCoeff(1.0f);
    
    //Plane plane(Vector4f(0.0f, 0.0f, -100.0f, 1.0f), Vector4f(0.0f, 0.707f, 0.707f, 1.0f));
    Plane table(Vector4f(0.0f, -10.0f, 0.0f, 1.0f), Vector4f(0.0f, 1.0f, 0.1f, 1.0f));
    table.setColor(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
    table.setReflCoeff(.2);
    
    Plane backWall(Vector4f(0.0f, -10.0f, -50.0f, 1.0f), Vector4f(0.0f, 0.0f, 1.0f, 1.0f));
    backWall.setColor(Vector4f(0.67f, 0.84f, 0.90f, 1.0f));
    backWall.setReflCoeff(.2);    
    
    Plane frontWall(Vector4f(0.0f, -10.0f, 100.0f, 1.0f), Vector4f(0.0f, 0.0f, -1.0f, 1.0f));
    frontWall.setColor(Vector4f(0.5f, 1.0f, 0.5f, 1.0f));
    frontWall.setReflCoeff(.2);    
    
    Plane ceilingWall(Vector4f(0.0f, 40.0f, 100.0f, 1.0f), Vector4f(0.0f, -1.0f, 0.0f, 1.0f));
    ceilingWall.setColor(Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
    ceilingWall.setReflCoeff(.2);     
    
    LambertLight light;
    //light.setPos(Vector4f(0.0f, 0.0f, 10.0f, 1.0f));
    light.setPos(Vector4f(-20.0f, 20.0f, 100.0f, 1.0f));
    light.setDiffuse(Vector4f(0.75f, 0.75f, 0.6f, 1.0f));
    light.setAmbient(Vector4f(0.01f, 0.01f, 0.01f, 1.0f));
    
    LambertLight light2;
    light2.setPos(Vector4f(20.0f, 20.0f, 100.0f, 1.0f));
    //light2.setPos(Vector4f(0.0f, 0.0f, -500.0f, 1.0f));
    light2.setDiffuse(Vector4f(0.5f, 0.5f, 0.4f, 1.0f));
    light2.setAmbient(Vector4f(0.01f, 0.01f, 0.01f, 1.0f));
    
    Scene scene;
    scene.addObject(&sphereA);
    scene.addObject(&sphereB);
    scene.addObject(&sphereL);
    scene.addObject(&table);
    scene.addObject(&triangle);
    scene.addObject(&backWall);
    //scene.addObject(&frontWall);
    //scene.addObject(&ceilingWall);
    scene.addLight(&light);
    scene.addLight(&light2);    
    
    
    //cout << "hello there\n" << endl;
    rayTracer.trace(scene);
    return NULL;
}

int main(int argc, char* argv[])
{	
    pthread_t rayTraceThread;
    int threadArgs;
    pthread_create(&rayTraceThread, NULL, rayThread, (void*) &threadArgs);
    
    //rayTracer.trace();

    initProj3Scenes();
    //initProj2Scenes();
    //applyBlackToWhiteGradient(&raster);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Base Code");
    glewInit();

    setupRC();

    glutKeyboardFunc(keyPressed);
    glutSpecialFunc(specialKeyPressed);
    glutReshapeFunc(reshapeWindow);
    glutDisplayFunc(drawScene);
    glutTimerFunc(33, timerFunc, 1);

    glutMainLoop();
}

void setupRC()
{
	// set white background
	byu_glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	float clearColor[] = {.5, 0, .5, 1};
	Raster::getInstance()->setAllPixels(clearColor);
}

void reshapeWindow(int w, int h)
{
	// set viewport to the window dimensions
	byu_glViewport(0, 0, w, h);
	
	// reset the coordinate system
	byu_glMatrixMode(GL_PROJECTION);
	byu_glLoadIdentity();
	
	byu_glMatrixMode(GL_MODELVIEW);
	byu_glLoadIdentity();
	//glOrtho(0, 640, 0, 480, -1, 1); // only for project 2; delete thereafter!
}

void drawScene()
{   
    GLint oldMatrixMode;
    GLboolean depthWasEnabled = glIsEnabled(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glGetIntegerv(GL_MATRIX_MODE, &oldMatrixMode);
    glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();

    glRasterPos2f(-1, -1);
    //glDrawPixels(640, 480, GL_RGBA, GL_FLOAT, Raster::getInstance()->getData());
    //glDrawPixels(640, 480, GL_RGBA, GL_FLOAT, screen.getRasterData());
    glDrawPixels(640, 480, GL_RGBA, GL_FLOAT, camera.getScreen().getRasterData());

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW); glPopMatrix();
    glMatrixMode(oldMatrixMode);
    if(depthWasEnabled)
	    glEnable(GL_DEPTH_TEST);	

    glutSwapBuffers();
}

void timerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(33, timerFunc, 1);		
}

void keyPressed(unsigned char key, int x, int y)
{   
	if(key == '1')
	    byu_setDrawMode(GL_MODE);
	else if(key == '2')
	    byu_setDrawMode(BYU_MODE);
	else if(key == 'q')
	    glutDisplayFunc(drawTriangles);
	else if(key == 'w')
	    glutDisplayFunc(drawLines);
	else if(key == 'd')
	    byu_glEnable(GL_DEPTH_TEST);
	
	glutPostRedisplay();
}

void specialKeyPressed(int key, int x, int y)
{
    /*static const int RIGHT_ARROW_KEY = 102;
    static const int LEFT_ARROW_KEY = 100;
    
    static int currentScene = 0;
    if(key == RIGHT_ARROW_KEY)
	currentScene += 1;
    else if(key == LEFT_ARROW_KEY)
	currentScene -= 1;
    
    if(currentScene == NUM_SCENES2)
	currentScene = 0;
    else if(currentScene < 0)
	currentScene = NUM_SCENES2 - 1;
    
    cout << currentScene << endl;
    
    glutDisplayFunc(scenes2[currentScene]);*/
}