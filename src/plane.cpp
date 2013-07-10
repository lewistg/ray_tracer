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

#include "plane.h"

Plane::Plane(const Vector4f& pointOnPlane, const Vector4f& normal):
	_D(dot3f(pointOnPlane, normal)),  
	_normal(normal)
{
    normalize(&_normal);
    _D = dot3f(pointOnPlane, _normal);
}

Vector4f Plane::getNormal() const
{
    return _normal;
}

float Plane::rayStrikesObject(const Ray& ray)
{
    // if they are parallel
    float normalRayDirDot = dot3f(ray.getDir(), _normal);
    if(verySmall(normalRayDirDot))
	return -1;
    
    // otherwise calculate the parameter
    float t = -(dot3f(ray.getOrigin(), _normal) - _D) / normalRayDirDot;
    
    // if the plane is behind the ray
    if(verySmall(t) || t < 0)
    {
	/*cout << "t: " << t << endl;
	cout << _normal.toString() << endl;
	cout << ray.getDir().toString() << endl;
	cout << ray.getOrigin().toString() << endl;*/
	return -1;
    }
    
    return t;
}

Vector4f Plane::getNormal(const Vector4f& pointOnObj) const
{
    return _normal;
}