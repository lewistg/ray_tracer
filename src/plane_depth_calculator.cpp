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

#include "plane_depth_calculator.h"

PlaneDepthCalculator::PlaneDepthCalculator(const Vector4f& v0, 
						const Vector4f& v1, 
						const Vector4f& v2)
{
    calibrateForPlane(v0, v1, v2);
} 

PlaneDepthCalculator::PlaneDepthCalculator(): _A(0), _B(1), _C(0), _D(0)
	{}

double PlaneDepthCalculator::getDepth(int x, int y)
{
    return (-(_A * x) - (_B * y) - _D) / _C;
}

void PlaneDepthCalculator::calibrateForPlane(const Vector4f& v0, 
			    const Vector4f& v1, 
			    const Vector4f& v2)
{
    Vector4f normal = cross(sub(v1, v0), sub(v2, v0));
    _A = (double) x(normal);
    _B = (double) y(normal);
    _C = (double) z(normal);
    _D = (_A * -x(v0)) + (_B * -y(v0)) + (_C * -z(v0));    
}