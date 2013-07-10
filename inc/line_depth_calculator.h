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

#ifndef _LINE_DEPTH_CALCULATOR_H_
#define _LINE_DEPTH_CALCULATOR_H_

#include <assert.h>
#include "vector4f.h"

class LineDepthCalculator
{
	public:
	    /**
	     * Constructor 
	     */
	    LineDepthCalculator();
	    
	    /**
	     * Calibrates the calculator according to the line defined by
	     * two points.
	     */
	    void calibrateForLine(const Vector4f& v0, const Vector4f& v1);
	    
	    /**
	     * Gets the depth according to the x component
             * @return 
             */
	    double getDepthByX(int x);
	    
	    /**
	     * Gets the depth according to the y component
	     */
	    double getDepthByY(int y);
	    
	private:
	    /**The slope in the xz plane*/
	    double _xSlope;
	    /**The x intercept in the xz plane*/
	    double _zInterceptX;
	    /**The slope in the yz plane*/
	    double _ySlope;
	    /**The x intercept in the yz plane*/
	    double _zInterceptY;	    
};

#endif