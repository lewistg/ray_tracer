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

#include "sphere.h"

Sphere::Sphere(const Vector4f& center, float radius): _center(center), _radius(radius)
	{}

float Sphere::rayStrikesObject(const Ray& ray)
{
//    float r = 5.0f;
//    Vector4f center(0.0f, 0.0f, -6.0f, 1.0f);
    
    Vector4f deltaP = sub(_center, ray.getOrigin());
    
    float discrim = pow(dot3f(deltaP, ray.getDir()), 2) - pow(mag3f(deltaP), 2) + pow(_radius, 2);
    if(discrim < 0)
	return -1;
    
    
    float a = dot3f(ray.getDir(), deltaP);
    float b = sqrt(discrim);
    
    float t1 = a + b;
    float t2 = a - b;
    
    //return min(t1, t2);
    return minAndSig(t1, t2);
}

Vector4f Sphere::getNormal(const Vector4f& pointOnObj) const
{
    Vector4f normal = sub(pointOnObj, _center);
    normalize(&normal);
    return normal;
}