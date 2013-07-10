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

#include "blending_func.h"

BlendingFunc& BlendingFunc::getInstance()
{
    static BlendingFunc instance;
    
    return instance;
}

BlendingFunc::BlendingFunc():BLENDING_ON(false), 
	_srcBlendType(ONE), _destBlendType(ZERO)
	{}   

BlendingFunc::~BlendingFunc()
	{}

Vector4f BlendingFunc::blend(const Raster& raster, int x, int y,
	const Vector4f& source)
{
    if(!BLENDING_ON)
	return source;
    
    _src = source;	
    float destData[4];
    raster.getPixel(x, y, destData);    
    _dest = Vector4f(destData);
    
    setScaleFactors(&_Rs, &_Gs, &_Bs, _srcBlendType);
    setScaleFactors(&_Rd, &_Gd, &_Bd, _destBlendType);
    
    Vector4f blended;
    r(blended) = r(_src) * _Rs + r(_dest) * _Rd;
    g(blended) = g(_src) * _Gs + g(_dest) * _Gd;
    b(blended) = b(_src) * _Bs + b(_dest) * _Bd;
    
    return blended;
}

void BlendingFunc::setSrcBlendType(BlendType blendType)
{
    _srcBlendType = blendType;
}

void BlendingFunc::setDestBlendType(BlendType blendType)
{
    _destBlendType = blendType;
}

void BlendingFunc::disableBlending()
{
    BLENDING_ON = false;
}

void BlendingFunc::enableBlending()
{	
    BLENDING_ON = true;
}

void BlendingFunc::setScaleFactors(float* R, float* G, float* B, BlendType blendType)
{
    switch(blendType)
    {
	case ZERO:
	    *R = 0;
	    *G = 0;
	    *B = 0;
	break;
	
	case ONE:
	    *R = 1;
	    *G = 1;
	    *B = 1;	    
	break;
	
	case SRC_ALPHA:
	    *R = a(_src);
	    *G = a(_src);
	    *B = a(_src);
	break;
	
	case ONE_MINUS_SRC_ALPHA:
	    *R = 1 - a(_src);
	    *G = 1 - a(_src);
	    *B = 1 - a(_src);	    
	break;	
	
	default:
	    assert(false);
	break;
    }
}