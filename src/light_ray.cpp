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

#include "light_ray.h"

LightRay::LightRay(const Vector4f& pos, const Vector4f& dir, int recursiveDepth)
	:Ray(pos, dir), 
	_color(0.0f, 0.0f, 0.0f, 1.0f),
	_recursiveDepth(recursiveDepth)
{
}

Vector4f LightRay::getColor() const
{
    return _color;
}

void LightRay::setColor(const Vector4f& color)	
{
    _color = color;
}

int LightRay::getDepth() const
{
    return _recursiveDepth;
}

void LightRay::addPertb()
{
    Vector4f dir = getDir();
   
    float xPert = (2 * (float)rand()/(float) RAND_MAX - 1) / 500;
    float yPert = (2 * (float)rand()/(float) RAND_MAX - 1) / 500;
    float zPert = (2 * (float)rand()/(float) RAND_MAX - 1) / 500;

	if (abs(x(dir)) >= abs(y(dir)) && abs(x(dir)) >= abs(z(dir)))
		xPert = 0;
	else if (abs(y(dir)) >= abs(x(dir)) && abs(y(dir)) >= abs(z(dir)))
		yPert = 0;
	else
		zPert = 0;
    
    
    Vector4f pertb(xPert, yPert, zPert, 1.0f);    
    
    dir = add(dir, pertb);
    setDir(dir);
}