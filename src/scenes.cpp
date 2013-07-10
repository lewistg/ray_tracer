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

#include "scenes.h"

int NUM_SCENES2;
vector<void (* )()> scenes2;

void initProj2Scenes()
{
    NUM_SCENES2 = 13;
    scenes2.push_back(drawGradient);
    scenes2.push_back(drawPoints);
    scenes2.push_back(drawBigPoints);
    scenes2.push_back(drawLines);
    scenes2.push_back(drawTriangles);
    scenes2.push_back(drawLineStrip);
    scenes2.push_back(drawLineLoop);
    scenes2.push_back(drawTriangleStrip);
    scenes2.push_back(drawTriangleFan);
    scenes2.push_back(drawQuads);
    scenes2.push_back(drawQuadStrip);
    scenes2.push_back(drawPolygon);
    scenes2.push_back(drawBlendedTriangles);
}

void drawGradient()
{
    	byu_glClearColor(1.0f, 0.0f, 0.0f, 1.0f);	
	byu_glClear(GL_COLOR_BUFFER_BIT);
	
	byu_applyBWGradient();	
	
	if(byu_getDrawMode() == BYU_MODE)
		byuPipeline.renderWithOpenGL();	
	
	glutSwapBuffers();	
}

void drawPoints()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT);    

    byu_glBegin(GL_POINTS);
    for(float theta=0, radius=60.0; radius>1.0; theta+=0.1, radius-=0.3)
    {
	byu_glColor3f(radius/60.0,0.3,1-(radius/60.0));
	byu_glVertex2i(200+radius*cos(theta),200+radius*sin(theta));
    }
    byu_glEnd();
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();	

    glutSwapBuffers();    
}

void drawLines()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT);

    // shows problem
    byu_glEnable(GL_BLEND);
    byu_glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
    byu_glBegin(GL_POINTS);	
	    byu_glColor3f(1, 1, 1);
	    byu_glVertex2i(0,0);
    for(int i=0; i <= 8; i++)
    {
	    byu_glVertex2i(200,200);
	    byu_glVertex2i(200 + 10*i, 280);
	    byu_glVertex2i(200,200);
	    byu_glVertex2i(200 - 10*i, 280);
	    byu_glVertex2i(200,200);
	    byu_glVertex2i(280, 200 + 10*i);
	    byu_glVertex2i(200,200);
	    byu_glVertex2i(280, 200 - 10*i);
    }
    byu_glEnd();	
	
    byu_glBegin(GL_LINES);
    for(int i=0; i<=8; i++)
    {
	byu_glColor3f(1,0,0);
	byu_glVertex2i(200,200);
	byu_glVertex2i(200 + 10*i, 280);
	byu_glColor3f(0,1,0);
	byu_glVertex2i(200,200);
	byu_glColor3f(0,1,1);
	byu_glVertex2i(200 - 10*i, 280);
	byu_glVertex2i(200,200);
	byu_glVertex2i(280, 200 + 10*i);
	byu_glVertex2i(200,200);
	byu_glVertex2i(280, 200 - 10*i);
    }
    byu_glEnd();
	
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();

    glutSwapBuffers();
}

void drawTriangles()
{
	byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
	byu_glClear(GL_COLOR_BUFFER_BIT);
    
	byu_glBegin(GL_POINTS);
		byu_glColor3f(1,1,1);
		byu_glVertex2i(300,300);
		byu_glVertex2i(600,300);
		byu_glVertex2i(450,410);
		byu_glVertex2i(100,400);
		byu_glVertex2i(70,60);
		byu_glVertex2i(350,100);
	byu_glEnd();	
	
	byu_glEnable(GL_BLEND);
	byu_glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(1,0,0);
	byu_glVertex2i(300,300);
	byu_glColor3f(0,1,0);
	byu_glVertex2i(600,300);
	byu_glColor3f(0,0,1);
	byu_glVertex2i(450,410);
	byu_glColor3f(1,1,0);
	byu_glVertex2i(100,400);
	byu_glColor3f(0,1,1);
	byu_glVertex2i(70,60);
	byu_glColor3f(1,0,1);
	byu_glVertex2i(350,100);
    byu_glEnd();
	
	if(byu_getDrawMode() == BYU_MODE)
		byuPipeline.renderWithOpenGL();	
	
	glutSwapBuffers();
}

void drawLineStrip()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT);    
    
    byu_glBegin(GL_POINTS);
	byu_glColor3f(1.0,1.0,1.0);
	byu_glVertex2i(250,30);
	byu_glVertex2i(270,60);
	byu_glVertex2i(270,210);
	byu_glVertex2i(230,230);
	byu_glVertex2i(220,270);
	byu_glVertex2i(220,310);
	byu_glVertex2i(250,340);
	byu_glVertex2i(275,360);
	byu_glVertex2i(325,360);
	byu_glVertex2i(350,340);
	byu_glVertex2i(380,310);
	byu_glVertex2i(380,270);
	byu_glVertex2i(370,230);
	byu_glVertex2i(330,210);
	byu_glVertex2i(330,60);
	byu_glVertex2i(350,30);
    byu_glEnd();     
    
    byu_glBegin(GL_LINE_STRIP);
	byu_glColor3f(0.42,0.27,0.11);
	byu_glVertex2i(250,30);
	byu_glVertex2i(270,60);
	byu_glVertex2i(270,210);
	byu_glColor3f(0.04,0.70,0.02);
	byu_glVertex2i(230,230);
	byu_glVertex2i(220,270);
	byu_glVertex2i(220,310);
	byu_glVertex2i(250,340);
	byu_glVertex2i(275,360);
	byu_glVertex2i(325,360);
	byu_glVertex2i(350,340);
	byu_glVertex2i(380,310);
	byu_glVertex2i(380,270);
	byu_glVertex2i(370,230);
	byu_glColor3f(0.42,0.27,0.11);
	byu_glVertex2i(330,210);
	byu_glVertex2i(330,60);
	byu_glVertex2i(350,30);
    byu_glEnd();    
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();	

    glutSwapBuffers();    
}

void drawLineLoop()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT);    
    
    byu_glBegin(GL_LINE_LOOP);
	byu_glColor3f(0.42,0.27,0.11);
	byu_glVertex2i(250,30);
	byu_glVertex2i(270,60);
	byu_glVertex2i(270,210);
	byu_glColor3f(0.04,0.70,0.02);
	byu_glVertex2i(230,230);
	byu_glVertex2i(220,270);
	byu_glVertex2i(220,310);
	byu_glVertex2i(250,340);
	byu_glVertex2i(275,360);
	byu_glVertex2i(325,360);
	byu_glVertex2i(350,340);
	byu_glVertex2i(380,310);
	byu_glVertex2i(380,270);
	byu_glVertex2i(370,230);
	byu_glColor3f(0.42,0.27,0.11);
	byu_glVertex2i(330,210);
	byu_glVertex2i(330,60);
	byu_glVertex2i(350,30);
    byu_glEnd();    
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();	

    glutSwapBuffers();     
}

void drawTriangleStrip()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT);    

    byu_glBegin(GL_TRIANGLE_STRIP);
	byu_glColor3f(1,0,0);
	byu_glVertex2i(40,70);
	byu_glColor3f(0,1,0);
	byu_glVertex2i(40,390);
	byu_glColor3f(1,1,0);
	byu_glVertex2i(130,30);
	byu_glColor3f(0,0,1);
	byu_glVertex2i(130,350);
	byu_glColor3f(1,0,1);
	byu_glVertex2i(330,80);
	byu_glColor3f(0,1,1);
	byu_glVertex2i(330,400);
	byu_glColor3f(1,0,0);
	byu_glVertex2i(480,40);
	byu_glColor3f(0,1,0);
	byu_glVertex2i(530,330);
    byu_glEnd();    
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();	

    glutSwapBuffers();     
}

void drawTriangleFan()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT);    
    
    byu_glBegin(GL_TRIANGLE_FAN);
	byu_glColor3f(1,0,0);
	byu_glVertex2i(250,170);
	byu_glColor3f(0,1,0);
	byu_glVertex2i(400,140);
	byu_glColor3f(1,1,0);
	byu_glVertex2i(300,50);
	byu_glColor3f(0,0,1);
	byu_glVertex2i(175,55);
	byu_glColor3f(1,0,1);
	byu_glVertex2i(100,170);
	byu_glColor3f(0,1,1);
	byu_glVertex2i(175,285);
	byu_glColor3f(1,0,0);
	byu_glVertex2i(300,290);
	byu_glColor3f(0,1,0);
	byu_glVertex2i(400,200);
    byu_glEnd();    
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();	

    glutSwapBuffers();     
}

void drawQuads()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT);    
    
    byu_glBegin(GL_QUADS);
	byu_glColor3f(1,0,0);
	byu_glVertex2i(40,70);
	byu_glColor3f(0,1,0);
	byu_glVertex2i(40,390);
	byu_glColor3f(0,0,1);
	byu_glVertex2i(130,350);
	byu_glColor3f(1,1,0);
	byu_glVertex2i(130,30);
	byu_glColor3f(1,0,1);
	byu_glVertex2i(330,80);
	byu_glColor3f(0,1,1);
	byu_glVertex2i(330,400);
	byu_glColor3f(0,1,0);
	byu_glVertex2i(530,330);
	byu_glColor3f(1,0,0);
	byu_glVertex2i(480,40);
    byu_glEnd();    
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();	

    glutSwapBuffers();     
}

void drawQuadStrip()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT);    
    
    byu_glBegin(GL_QUAD_STRIP);
	byu_glColor3f(1,0,0);
	byu_glVertex2i(40,70);
	byu_glColor3f(0,1,0);
	byu_glVertex2i(40,390);
	byu_glColor3f(1,1,0);
	byu_glVertex2i(130,30);
	byu_glColor3f(0,0,1);
	byu_glVertex2i(130,350);
	byu_glColor3f(1,0,1);
	byu_glVertex2i(330,80);
	byu_glColor3f(0,1,1);
	byu_glVertex2i(330,400);
	byu_glColor3f(1,0,0);
	byu_glVertex2i(480,40);
	byu_glColor3f(0,1,0);
	byu_glVertex2i(530,330);
    byu_glEnd();    
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();	

    glutSwapBuffers();     
}

void drawPolygon()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT);    
    
    byu_glBegin(GL_POLYGON);
	byu_glColor3f(1,0,0);
	byu_glVertex2i(250,170);
	byu_glColor3f(0,1,0);
	byu_glVertex2i(400,140);
	byu_glColor3f(1,1,0);
	byu_glVertex2i(300,50);
	byu_glColor3f(0,0,1);
	byu_glVertex2i(175,55);
	byu_glColor3f(1,0,1);
	byu_glVertex2i(100,170);
	byu_glColor3f(0,1,1);
	byu_glVertex2i(175,285);
	byu_glColor3f(1,0,0);
	byu_glVertex2i(300,290);
	byu_glColor3f(0,1,0);
	byu_glVertex2i(400,200);
    byu_glEnd();    
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();	

    glutSwapBuffers();     
}

void drawBlendedTriangles()
{
	byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
	byu_glClear(GL_COLOR_BUFFER_BIT);
    
	/*byu_glBegin(GL_POINTS);
		byu_glColor3f(1,1,1);
		byu_glVertex2i(300,300);
		byu_glVertex2i(600,300);
		byu_glVertex2i(450,410);
		byu_glVertex2i(100,400);
		byu_glVertex2i(70,60);
		byu_glVertex2i(350,100);
	byu_glEnd();	*/
	
    byu_glEnable(GL_BLEND);
    byu_glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
    byu_glBegin(GL_TRIANGLES);
	byu_glColor4f(1,0,0,.25);
	byu_glVertex2i(300,300);
	byu_glColor4f(0,1,0,0);
	byu_glVertex2i(600,300);
	byu_glColor4f(0,0,1,.5);
	byu_glVertex2i(450,400);
	
	byu_glColor4f(1,0,1,.5);
	byu_glVertex2i(100,300);
	byu_glColor4f(1,1,0,.5);
	byu_glVertex2i(400,300);
	byu_glColor4f(0,1,1,.5);
	byu_glVertex2i(200,400);
    byu_glEnd();
    
    byu_glBlendFunc(GL_ONE, GL_ZERO);
    byu_glBegin(GL_TRIANGLES);
	byu_glColor4f(1,0,0,.25);
	byu_glVertex2i(300,300 - 200);
	byu_glColor4f(0,1,0,0);
	byu_glVertex2i(600,300 - 200);
	byu_glColor4f(0,0,1,.5);
	byu_glVertex2i(450,400 - 200);
	
	byu_glColor4f(1,0,1,.5);
	byu_glVertex2i(100,300 - 200);
	byu_glColor4f(1,1,0,.5);
	byu_glVertex2i(400,300 - 200);
	byu_glColor4f(0,1,1,.5);
	byu_glVertex2i(200,400 - 200);
    byu_glEnd();    
	
	if(byu_getDrawMode() == BYU_MODE)
		byuPipeline.renderWithOpenGL();	
	
	glutSwapBuffers();    
}

void drawBigPoints()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT);    
    
    byu_glPointSize(5);
    byu_glBegin(GL_POINTS);
	byu_glColor3f(1,0,0);
	byu_glVertex2i(250,170);
    byu_glEnd();
    
    byu_glEnable(GL_BLEND);
    byu_glEnable(GL_POINT_SMOOTH);
    byu_glBegin(GL_POINTS);
	byu_glColor3f(1,1,0);
	byu_glVertex2i(300,170);
    byu_glEnd();
    byu_glPointSize(10);
    byu_glBegin(GL_POINTS);
	byu_glColor3f(0,0,1);
	byu_glVertex2i(300,140);
    byu_glEnd();
    byu_glDisable(GL_POINT_SMOOTH);
    byu_glBegin(GL_POINTS);
	byu_glColor3f(0,1,0);
	byu_glVertex2i(250,140);
    byu_glEnd();    
    
    byu_glPointSize(1);
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();	

    glutSwapBuffers();      
}

void initProj3Scenes()
{
    NUM_SCENES2 = 14;
    scenes2.push_back(viewPortTransform);
    scenes2.push_back(depthBufferTriangles);
    scenes2.push_back(divideByWCoord);
    scenes2.push_back(easyPointClipping);
    scenes2.push_back(matrixManipulation);
    scenes2.push_back(matrixStacks);
    scenes2.push_back(rotatedTriangle);
    scenes2.push_back(translatedTriangle);
    scenes2.push_back(scaledTrangle);
    scenes2.push_back(orthoTriangles);
    scenes2.push_back(fixedScaleTriangles);
    scenes2.push_back(shearedTriangles);
    scenes2.push_back(depthLines);
    scenes2.push_back(fullRotatedTriangles);
    //scenes2.push_back(fullRotatedTriangles);
}

void viewPortTransform()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        
    byu_glMatrixMode(GL_MODELVIEW);
    byu_glLoadIdentity();
    
    byu_glViewport(0,0,320,240);
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0,1,0);
	byu_glVertex3f(-1,0,0);
	byu_glVertex3f(0,-0.8,0);
	byu_glVertex3f(0.5,0.8,0);
    byu_glEnd();
    byu_glViewport(320,240,320,240);
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0,0,1);
	byu_glVertex3f(-1,0.8,0);
	byu_glVertex3f(0.1,-0.8,0);
	byu_glVertex3f(0.5,0.8,0);
    byu_glEnd();
    //Restore your viewport to the whole screen
    byu_glViewport(0,0,640,480);
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();    
    
    glutSwapBuffers();
}

void depthBufferTriangles()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
    byu_glMatrixMode(GL_MODELVIEW);
    byu_glLoadIdentity();    
    
    //byu_glEnable(GL_DEPTH_TEST);
    byu_glClear(GL_DEPTH_BUFFER_BIT);
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(1,1,0);
	byu_glVertex3f(-0.5,-0.2,-0.5);
	byu_glVertex3f(0,0.5,0);
	byu_glVertex3f(0.5,-0.2,0.5);    
    
	byu_glColor3f(0,1,1);
	byu_glVertex3f(-0.5,0.2,0.5);
	byu_glVertex3f(0,-0.5,0);
	byu_glVertex3f(0.5,0.2,-0.5);
    byu_glEnd();
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();      
    
    glutSwapBuffers();
}


void divideByWCoord()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);       
    byu_glMatrixMode(GL_MODELVIEW);
    byu_glLoadIdentity();   
    
    byu_glBegin(GL_POINTS);
	    byu_glColor3f(1,1,1);
	    byu_glVertex4f(-1,0.2,0,1);
	    byu_glVertex4f(0,0.8,0,1);
	    byu_glVertex4f(1,0.2,0,1);
    byu_glEnd();     
    
    byu_glBegin(GL_TRIANGLES);
	    byu_glColor3f(1,0,0);
	    byu_glVertex4f(-1,0.2,0,1);
	    byu_glVertex4f(0,0.8,0,1);
	    byu_glVertex4f(1,0.2,0,1);
	    byu_glColor3f(1,0,1);
	    byu_glVertex4f(-1,-0.8,0,2);
	    byu_glVertex4f(0,-0.2,0,2);
	    byu_glVertex4f(1,-0.8,0,2);
    byu_glEnd();   
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();      
    
    glutSwapBuffers();    
}


void easyPointClipping()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);      
    byu_glMatrixMode(GL_MODELVIEW);
    byu_glLoadIdentity();       
    
    //byu_glEnable(GL_DEPTH_TEST);
    byu_glBegin(GL_TRIANGLES);
	    byu_glColor3f(0.5,1,1);
	    byu_glVertex3f(0.5,0,0);
	    byu_glVertex3f(0,0.5,-2);
	    byu_glVertex3f(0,-0.5,2);
    byu_glEnd();
    byu_glViewport(50,50,200,400);
    byu_glBegin(GL_TRIANGLES);
	    byu_glColor3f(1,1,0.5);
	    byu_glVertex3f(-1.4,-1.2,-0.5);
	    byu_glVertex3f(0,1.2,0);
	    byu_glVertex3f(1.5,-0.2,0.5);
    byu_glEnd();
    //Restore your viewport to the whole screen
    byu_glViewport(0,0,640,480);    
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();      
    
    glutSwapBuffers();     
}

void matrixManipulation()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        
    byu_glMatrixMode(GL_MODELVIEW);
    byu_glLoadIdentity();       
    
    float PI = 3.14;
    double translate[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, -1.2,0.3,0,1};
    double rotate[16] = {cos(PI/2),sin(PI/2),0,0, -sin(PI/2),cos(PI/2),0,0, 0,0,1,0, 0,0,0,1};
    byu_glLoadIdentity();
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0.5,0.2,1);
	byu_glVertex3f(0.5,0.1,0);
	byu_glVertex3f(0.8,0.1,0);
	byu_glVertex3f(0.65,0.4,0);
    byu_glEnd();
    byu_glLoadMatrixd(translate); 
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0.5,0.8,0.2);
	byu_glVertex3f(0.5,0.1,0);
	byu_glVertex3f(0.8,0.1,0);
	byu_glVertex3f(0.65,0.4,0);
    byu_glEnd();
    byu_glLoadIdentity();
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0.2,0.6,1);
	byu_glVertex3f(0.5,-0.4,0);
	byu_glVertex3f(0.8,-0.4,0);
	byu_glVertex3f(0.65,-0.7,0);
    byu_glEnd();
    byu_glLoadMatrixd(rotate);
    byu_glMultMatrixd(translate);
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0.9,0.2,0.4);
	byu_glVertex3f(0.5,-0.4,0);
	byu_glVertex3f(0.8,-0.4,0);
	byu_glVertex3f(0.65,-0.7,0);
    byu_glEnd(); 
    byu_glLoadIdentity();
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();     
    
    glutSwapBuffers();
}

void tree(int depth)
{
    static const float r2 = 1/sqrt(2);
    static double mdown[16] = { 0,-r2,0,0, r2,0,0,0, 0,0,1,0, 0,-r2,0,1 };
    static double mup[16] = { 0,r2,0,0, -r2,0,0,0, 0,0,1,0, 0,r2,0,1 };
    if (depth <= 0) return;
    byu_glBegin(GL_LINES);
    byu_glVertex2f(0,-r2);
    byu_glVertex2f(0, r2);
    byu_glEnd();
    byu_glPushMatrix();
    byu_glMultMatrixd(mdown);
    tree(depth-1);
    byu_glPopMatrix();
    byu_glPushMatrix();
    byu_glMultMatrixd(mup);
    tree(depth-1);
    byu_glPopMatrix();
}

void matrixStacks()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    byu_glMatrixMode(GL_MODELVIEW);
    byu_glLoadIdentity();
    //tree(2);
    
    //byu_glLoadIdentity();
    tree(8);
    
    /*byu_glBegin(GL_LINES);
	byu_glVertex3f(0, 0.707107, 0.0);
	byu_glVertex3f(0, -0.707107, 0.0);
	byu_glVertex3f(0.5, 0.707107, 0.0);
	byu_glVertex3f(-0.5, 0.707107, 0.0);
	byu_glVertex3f(0.5, 0, 0);
	byu_glVertex3f(-0.5, 0, 0);
    byu_glEnd();*/
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();     
    
    glutSwapBuffers();    
}

void rotatedTriangle()
{
    static float angle = 0;
    static float angleDelta = 2;
    
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    byu_glMatrixMode(GL_MODELVIEW);    
  
    byu_glLoadIdentity();
    byu_glTranslatef(-.5, -.5, 0);
    byu_glRotatef(angle,0,0,1);
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0.5,0.2,1);
	byu_glVertex3f(-0.2,-0.2,0);
	byu_glVertex3f(0.2,-0.2,0);
	byu_glVertex3f(0.0,0.2,0);
    byu_glEnd();
    
    
    byu_glLoadIdentity();
    byu_glTranslatef(.5, -.5, 0);
    byu_glRotatef(angle,0,1,0);
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0.5,0.2,1);
	byu_glVertex3f(-0.2,-0.2,0);
	byu_glVertex3f(0.2,-0.2,0);
	byu_glVertex3f(0.0,0.2,0);
    byu_glEnd();
    
    byu_glLoadIdentity();
    byu_glTranslatef(0, .5, 0);
    byu_glRotatef(angle,1,0,0);
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0.5,0.2,1);
	byu_glVertex3f(-0.2,-0.2,0);
	byu_glVertex3f(0.2,-0.2,0);
	byu_glVertex3f(0.0,0.2,0);
    byu_glEnd();    
    
    /*byu_glRotatef(angle,0,0,1);
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0.1,0.2,1);
	byu_glVertex3f(0.5,0.1,0);
	byu_glVertex3f(0.8,0.1,0);
	byu_glVertex3f(0.65,0.4,0);
    byu_glEnd();*/
    
    angle += angleDelta;
    if(angle > 360)
	angle = 0;
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();     
    
    glutSwapBuffers();      
}

void translatedTriangle()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    byu_glMatrixMode(GL_MODELVIEW);        
    byu_glLoadIdentity();
    
    static float transX = 0;
    static float transY = 0;
    static float transXDelta = .02;
    static float transYDelta = .02;
    
    transX += transXDelta;
    if(abs(transX) > .5)
	transXDelta *= -1;
    
    transY += transXDelta;
    if(abs(transY) > .5)
	transYDelta *= -1;    
    
    byu_glTranslatef(transX,transY,0);
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0.77,0.2,0.3);
	byu_glVertex3f(-0.1,0.0,0);
	byu_glVertex3f(0.1,0.0,0);
	byu_glVertex3f(0.0,0.1,0);
    byu_glEnd();    
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();     
    
    glutSwapBuffers();          
}

void scaledTrangle()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    byu_glMatrixMode(GL_MODELVIEW);            

    byu_glLoadIdentity();
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0.9,0.5,1);
	byu_glVertex3f(0.5,0.4,0);
	byu_glVertex3f(0.8,0.4,0);
	byu_glVertex3f(0.65,0.9,0);
    byu_glEnd();
    /*byu_glScalef(0.8,0.7,1);
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0.8,0.7,0);
	byu_glVertex3f(0.5,0.1,0);
	byu_glVertex3f(0.8,0.1,0);
	byu_glVertex3f(0.65,0.4,0);
    byu_glEnd();*/
    
    static float scaleFactor = .3;
    static float scaleFactorDelta = .015;
    scaleFactor += scaleFactorDelta;
    if(scaleFactor > 1)
	scaleFactor = 0;
    
    byu_glLoadIdentity();
    byu_glScalef(scaleFactor,scaleFactor,1);
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0.8,0.7,0);
	byu_glVertex3f(0.5,0.4,0);
	byu_glVertex3f(0.8,0.4,0);
	byu_glVertex3f(0.65,0.9,0);
    byu_glEnd();  
    
    byu_glLoadIdentity();
    byu_glScalef(-scaleFactor,scaleFactor/3,1);
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0.8,0.7,0);
	byu_glVertex3f(0.5,0.4,0);
	byu_glVertex3f(0.8,0.4,0);
	byu_glVertex3f(0.65,0.9,0);
    byu_glEnd();      
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();     
    
    glutSwapBuffers();    
}

void orthoTriangles()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    byu_glMatrixMode(GL_MODELVIEW);                
    
    byu_glLoadIdentity();
    byu_glOrtho(0,640,0,480,-1,1);
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(1,0,0);
	byu_glVertex3f(300,300,0);
	byu_glColor3f(0,1,0);
	byu_glVertex3f(600,300,0);
	byu_glColor3f(0,0,1);
	byu_glVertex3f(450,410,0);
	byu_glColor3f(1,1,0);
	byu_glVertex3f(100,400,0);
	byu_glColor3f(0,1,1);
	byu_glVertex3f(70,60,0);
	byu_glColor3f(1,0,1);
	byu_glVertex3f(350,100,0);
    byu_glEnd();   
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();     
    
    glutSwapBuffers();        
}

void fixedScaleTriangles()
{
    static float scaleX = 0;
    static float scaleY = 0;
    static float scaleDelta = .02;
    
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    byu_glMatrixMode(GL_MODELVIEW);

    byu_glLoadIdentity();
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0.9,0.5,1);
	byu_glVertex3f(0.5,0.4,0);
	byu_glVertex3f(0.8,0.4,0);
	byu_glVertex3f(0.65,0.9,0);
    byu_glEnd();
    byu_fixedScale(scaleX, scaleY / 2 ,1, 
		    0.5,0.4,0);
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0.5,0.2,1);
	byu_glVertex3f(0.5,0.4,-.5);
	byu_glVertex3f(0.8,0.4,-.5);
	byu_glVertex3f(0.65,0.9,-.5);
    byu_glEnd();
    
    byu_glLoadIdentity();   
    byu_fixedScale(-scaleX, -scaleY / 5 ,1, 
		    0.5,0.4,0);
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0.5,0.6,1);
	byu_glVertex3f(0.5,0.4,-.5);
	byu_glVertex3f(0.8,0.4,-.5);
	byu_glVertex3f(0.65,0.9,-.5);
    byu_glEnd();     
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();     
    
    scaleX += scaleDelta;
    scaleY += scaleDelta;
    if(scaleX > 2 || scaleY > 2)
    {
	scaleX = 0;
	scaleY = 0;
    }
    
    glutSwapBuffers();        
}

void shearedTriangles()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    byu_glMatrixMode(GL_MODELVIEW);    

    byu_glLoadIdentity();
    /*byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0.9,0.5,1);
	byu_glVertex3f(0.5,0.4,0);
	byu_glVertex3f(0.8,0.4,0);
	byu_glVertex3f(0.65,0.9,0);
    byu_glEnd();*/
    
    byu_glBegin(GL_POINTS);
	byu_glVertex3f(0,0,0);
    byu_glEnd();    
    
    static float angle = 0;
    static float angleDelta = .5;   
    static float shearXByY = 0;
    
    byu_glTranslatef(.5, .5, 0);
    byu_shear(0, 0, shearXByY, 0, 0, 0);
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(1, 0, 0);
	byu_glVertex3f(0.0,0.0,0);
	byu_glVertex3f(0.5,0.0,0);
	byu_glVertex3f(0.25,0.2,0);
    byu_glEnd();
    
    byu_glLoadIdentity();
    byu_glTranslatef(-.5, .5, 0);
    byu_shear(shearXByY, 0, 0, 0, 0, 0);
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0, 1, 0);
	byu_glVertex3f(0.0,0.0,0);
	byu_glVertex3f(-0.5,0.0,0);
	byu_glVertex3f(-0.25,0.2,0);	
    byu_glEnd();
    
    byu_glLoadIdentity();
    byu_glTranslatef(.5, -.5, 0);
    byu_glRotatef(90, 0, 1, 0);
    byu_shear(0, 0, 0, 0, 0, -shearXByY);   
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0, 0, 1);
	byu_glVertex3f(0.0,0.0,0);
	byu_glVertex3f(0.0,0.0,0.5);
	byu_glVertex3f(0.0,0.2,0.25);
    byu_glEnd();

    /*byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0, .5, .4);
	byu_glVertex3f(0.0,0.0,0);
	byu_glVertex3f(0.0,0.0,-0.5);
	byu_glVertex3f(0.0,0.2,-0.25);		
    byu_glEnd();*/
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();     

    shearXByY += .03;
    if(shearXByY > 1.5)
	shearXByY = 0;
    
    angle += angleDelta;
    if(angle > 360)
	angle = 0;
	
    glutSwapBuffers();    
}

void fullRotatedTriangles()
{
    static float angle = 0;
    static float angleDelta = 2;
    
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    byu_glMatrixMode(GL_MODELVIEW);     
    
    byu_glLoadIdentity();
    
    byu_glBegin(GL_LINES);
	byu_glColor3f(.3, .6, .2);
	byu_glVertex3f(0, 0, 0);
	byu_glVertex3f(.2, .5, 0);
    byu_glEnd();
    
    byu_fullRotate(angle, 0, 0, 0, .2, .5, 0);
    //byu_fullRotate(angle, 0, 0, 0, .2, 0, 0);
    //byu_glRotatef(angle, .2, 0, 0);
    
    byu_glBegin(GL_TRIANGLES);
	byu_glColor3f(0.7,0.2,1);
	byu_glVertex3f(0.5,0.0,-.5);
	byu_glVertex3f(0.8,0.0,-.5);
	byu_glVertex3f(0.65,0.4,-.5);
    byu_glEnd();    
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();     
    
    angle += angleDelta;
    if(angle > 360)
	angle = 0;
	
    glutSwapBuffers();      
}

void depthLines()
{
    byu_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
    byu_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    byu_glMatrixMode(GL_MODELVIEW);     
    
    byu_glLoadIdentity();

    /*byu_glBegin(GL_LINES);
	byu_glColor3f(.9, .2, 0);
	byu_glVertex3f(-.5f, 0.0f, 0.5);
	byu_glVertex3f(.5f, 0.0f, -0.5);
	
	byu_glColor3f(.2, .9, 0);
	byu_glVertex3f(.5f, 0.0f, 0.5);
	byu_glVertex3f(-.5f, 0.0f, -0.5);	
    byu_glEnd();*/

    byu_glBegin(GL_LINES);
	byu_glColor3f(.9, .2, 0);
	byu_glVertex3f(0.0f, -0.5f, 0.5);
	byu_glVertex3f(0.0f, 0.5f, -0.5);
	
	byu_glColor3f(.2, .9, 0);
	byu_glVertex3f(0.0f, 0.5f, 0.5);
	byu_glVertex3f(0.0f, -0.5f, -0.5);	
    byu_glEnd();
    
    if(byu_getDrawMode() == BYU_MODE)
	    byuPipeline.renderWithOpenGL();     

    glutSwapBuffers();    
}