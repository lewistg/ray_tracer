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
#include "graphics_vector_utils.h"

Sphere::Sphere(const mvl::GVector3f& center, float radius): _center(center), _radius(radius)
	{}

float Sphere::rayStrikesObject(const Ray& ray)
{
	//    float r = 5.0f;
	//    mvl::GVector4f center(0.0f, 0.0f, -6.0f, 1.0f);

	mvl::GVector3f deltaP = sub(_center, ray.getOrigin());

	float discrim = pow(mvl::dot(deltaP, ray.getDir()), 2) - pow(deltaP.getMagnitude(), 2) + pow(_radius, 2);
	if (discrim < 0)
		return -1;


	float a = mvl::dot(ray.getDir(), deltaP);
	float b = sqrt(discrim);

	float t1 = a + b;
	float t2 = a - b;

	//return min(t1, t2);
	return minAndSig(t1, t2);
}

mvl::GVector3f Sphere::getNormal(const mvl::GVector3f& pointOnObj) const
{
    mvl::GVector3f normal = sub(pointOnObj, _center);
	normal.normalize();
    return normal;
}