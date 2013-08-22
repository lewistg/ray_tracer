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

#include "vector_math.h"
#include "plane.h"

Plane::Plane(const mvl::GVector3f& pointOnPlane, const mvl::GVector3f& normal):
	_D(mvl::dot(pointOnPlane, normal)),  
	_normal(normal)
{
	_normal.normalize();
    _D = mvl::dot(pointOnPlane, _normal);
}

mvl::GVector3f Plane::getNormal() const
{
    return _normal;
}

float Plane::rayStrikesObject(const Ray& ray)
{
    // if they are parallel
    float normalRayDirDot = mvl::dot(ray.getDir(), _normal);
    if(verySmall(normalRayDirDot))
	return -1;
    
    // otherwise calculate the parameter
    float t = -(mvl::dot(ray.getOrigin(), _normal) - _D) / normalRayDirDot;
    
    // if the plane is behind the ray
    if(verySmall(t) || t < 0)
    {
	/*cout << "t: " << t << endl;
	cout << _normal.toString() << endl;
	cout << ray.getDir().toString() << endl;
	cout << ray.getOrigin().toString() << endl;*/
	return -1.0;
    }
    
    return t;
}

mvl::GVector3f Plane::getNormal(const mvl::GVector3f& pointOnObj) const
{
    return _normal;
}