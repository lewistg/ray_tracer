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

#ifndef _MATRIX_STATE_H_
#define _MATRIX_STATE_H_

#include <assert.h>
#include <iostream>
#include "matrix4f.h"
#include "matrix4f_stack.h"

using namespace std;

/**
 * Type for matrix mode state
 */
enum MatrixMode
{
    MODELVIEW,
    PROJECTION
};

/**
 * A singleton class that holds the matrix
 * state information.
 */
class MatrixState
{
    public:
	/**
	 * Returns the singleton instance.
         */
	static MatrixState& getInstance();
	
       /**
	* Sets the current matrix mode. In other words
	* it sets the current matrix stack that is used
	* either the Modelview or the Projection matrix
	* @param mode The mode that should be activated
	*/
       void setMatrixMode(MatrixMode mode);

       /**
	* Pushes the active matrix onto the currently active
	* matrix stack.
	* @post top(currentMatrixStack) = active matrix
	*/
       void pushMatrix();

       /**
	* Replaces the active matrix with the top matrix 
	* from the currently active stack
	*/
       void popMatrix();

       /**
	* Loads the identity into the currently active matrix
	* @post active matrix = identity matrix
	*/
       void loadIdentity();

       /**
	* Loads a new matrix into the current matrix
	* @param m An array that defines the new matrix
	* @post current matrix = matrix defined by m
	*/
       void loadMatrixd(double m[]);

       /**
	* Multiplies the current matrix by the matrix defined by m.
	* @param m An array that defines the multiplier
	* @post current matrix = (current matrix) * (matrix defined by m)
	*/
       void multMatrixd(double m[]);
       void multMatrixf(float m[]);

       /**
	* Gets the active projection matrix
	* @return 
	*/
       Matrix4f getActiveProjMatrix();
       
       /**
	* Gets the active model view matrix
	*/
       Matrix4f getActiveModelViewMatrix();       
       
       /**
	* Loads the matrix data into the given array
	* @pre The array is 4x4
	*/
       void getProjMatrixDatad(double data[]);

       /**
	* Loads the matrix data into the given array
        * @pre The array is 4x4
        */
       void getModelViewMatrixDatad(double data[]);
       
    private:
	/**Active model view matrix*/
	Matrix4f _activeModelViewMatrix;
	/**Active projection matrix*/
	Matrix4f _activeProjMatrix;
	/**Currently active matrix*/
	Matrix4f* _currentActiveMatrix;
	/**Current matrix stack*/
	Matrix4fStack* _currentMatStack;
	/**Model view matrix stack*/
	Matrix4fStack _modelViewMatStack;
	/**Projection matrix stack*/
	Matrix4fStack _projMatStack;	
	
	/**
	 * No-arg constructor
         */
	MatrixState();
	
	/**
	 * Private and unimplemented copy constructor.
	 */
	MatrixState(const MatrixState& copy);
	
	/**
	 * Private and unimplemented assignment operator
	 */
	const MatrixState& operator=(const MatrixState& rSide);
	
	
};

#endif