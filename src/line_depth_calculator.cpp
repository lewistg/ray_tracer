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

#include "line_depth_calculator.h"


LineDepthCalculator::LineDepthCalculator()
{
    
}

void LineDepthCalculator::calibrateForLine(const Vector4f& v0, const Vector4f& v1)
{
    double deltaZ = z(v1) - z(v0);
    
    _xSlope = deltaZ / (x(v1) - x(v0));
    _zInterceptX = z(v0) - _xSlope * x(v0);
    
    _ySlope = deltaZ / (y(v1) - y(v0));
    _zInterceptY = z(v0) - _ySlope * y(v0);
}

double LineDepthCalculator::getDepthByX(int x)
{
    return x * _xSlope + _zInterceptX;
}


double LineDepthCalculator::getDepthByY(int y)
{
    return y * _ySlope + _zInterceptY;
}