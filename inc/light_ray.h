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

#ifndef _LIGHT_RAY_H_
#define _LIGHT_RAY_H_

#include <cmath>
#include <cstdlib>
#include "vector4f.h"
#include "ray.h"


/**
 * A ray that can be colored
 */
class LightRay: public Ray
{
    public:
	/**
	 * Constructor
         * @param pos
         * @param dir
         */
	LightRay(const Vector4f& pos, const Vector4f& dir, int recursiveDepth);
	
	/**
	 * Gets the color
	 */
	Vector4f getColor() const;
	
	/**
	 * Sets the the color of the light ray
	 */
	void setColor(const Vector4f& color);
	
	/**
	 * Gets the depth of the light ray
	 */
	int getDepth();
	
	/**
	 * Adds a perturbation to the light ray
	 */
	void addPertb();
	
    private:
	/**The color of the light ray*/
	Vector4f _color;
	/**The "recursive depth" of the ray*/
	int _recursiveDepth;
	
};

#endif