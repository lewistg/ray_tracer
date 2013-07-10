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

#ifndef _BLENDING_FUNC_H_
#define _BLENDING_FUNC_H_

#include <assert.h>
#include "vector4f.h"
#include "raster.h"

enum BlendType
{
    ZERO,
    ONE,
    SRC_ALPHA,
    ONE_MINUS_SRC_ALPHA
};

/**
 * A blending function used by drawing commands.
 * A method object that blends 
 */
class BlendingFunc
{
	public:
	    /**Gets the singleton instance of this class*/
	    static BlendingFunc& getInstance();
	    
	    /**
	     * Takes an input color and blends it with 
	     * the existing colors that exist on the raster
             * @param raster The raster that will be drawn on
	     * @param x
	     * @param y
             * @param colorIn The color that will be plotted
             * @return 
             */
	    Vector4f blend(const Raster& raster, int x, int y,
		    const Vector4f& colorIn);

	    /**
	     * Sets the source's blend type
	     * @pre The blend type is valid
	     */
	    void setSrcBlendType(BlendType blendType);
	    
	    /**
	     * Sets the destination's blend type
	     */
	    void setDestBlendType(BlendType blendType);
	    
	    /**
	     * Disables blending
	     */
	    void disableBlending();
	    
	    /**
	     * Enable blending
	     */
	    void enableBlending();
	    
	private:
	    /**
	     * No-arg constructor
             */
	    BlendingFunc();

	    /**Should never be called*/
	    ~BlendingFunc();
	    
	    /**Blending type for source scale factors*/
	    BlendType _srcBlendType;
	    /**Blending type for destination scale factors*/
	    BlendType _destBlendType;
	    /**Blending flag*/
	    bool BLENDING_ON;
	    /**The source color*/
	    Vector4f _src;
	    /**The destination color*/
	    Vector4f _dest;
	    /**
	     * Rs, Gs, Bs are source color scale factors and
	     * Rd, Gd, Bd are the destination scale factors
	     */
	    float _Rs;
	    float _Gs;
	    float _Bs;
	    float _Rd;
	    float _Gd;
	    float _Bd;
	    
	    /**
	     * Sets the blending scale factors
	     */
	    void setScaleFactors(float* R, float* G, float* B, BlendType blendType);
};

#endif