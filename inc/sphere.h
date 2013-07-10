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

#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <math.h>
#include "illuminated_object.h"
#include "vector4f.h"

/**
 * Represents a sphere
 */
class Sphere:public IlluminatedObject
{
    public:
	/**
	 * Constructs a new sphere with a center point and
	 * radius
         * @param center
         * @param radius
         */
	Sphere(const Vector4f& center, float radius);
	
	/**
	 * Override
	 */
	virtual float rayStrikesObject(const Ray& ray);
	
    protected:
	/**
	 * Override
	 */
	virtual Vector4f getNormal(const Vector4f& pointOnObj) const;
	
    private:
	/**Center of the sphere*/
	Vector4f _center;
	/**Radius of the sphere*/
	float _radius;
};

#endif