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

#ifndef _PLANE_DEPTH_CALCULATOR_H_
#define _PLANE_DEPTH_CALCULATOR_H_

#include <assert.h>
#include "vector4f.h"

/**
 * Calculates the depth (i.e. z value) of a given point
 */
class PlaneDepthCalculator
{
	public:
	    /**
	     * Constructor
	     */
	    PlaneDepthCalculator(const Vector4f& v0, 
					const Vector4f& v1, 
					const Vector4f& v2);
	    
	    /**
	     * No arg constructor
             */
	    PlaneDepthCalculator();
	    
	    /**
	     * Calibrates the calculator to the given plane
             * @param v0
             * @param v1
             * @param v2
             */
	    void calibrateForPlane(const Vector4f& v0, 
					const Vector4f& v1, 
					const Vector4f& v2);
	    
	    /**
	     * Gets the depth value for a particular x, y coordinate
             * @param x 
             * @param y
             * @return 
             */
	    double getDepth(int x, int y);
	    
	private:
	    /**Plane equation constants*/
	    double _A;
	    double _B;
	    double _C;
	    double _D;
};

#endif