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

#ifndef _RAY_TRACER_H_
#define _RAY_TRACER_H_

#include <boost/shared_ptr.hpp>
#include "eye.h"
#include "screen.h"
#include "ray.h"
#include "vector4f.h"
#include "sphere.h"
#include "scene.h"

using namespace std;

/**
 * Represents the ray tracing algorithm. Contains
 * all of the essential components.
 */
class RayTracer
{
	public:
	    /**
	     * Constructor
             */
	    RayTracer(const Vector4f& eye, Screen& screen);
	    
	    /**
	     * Performs the ray tracing algorithm
	     */
	    void trace(const Scene& scene);
	    
	private:
	    /**The eye of the viewer*/
	    Vector4f _eye;
	    /**The screen we project on*/
	    Screen& _screen;
	    /**The seen we will trace*/
	    Scene _scene;
	    /**Stochastic antialiasing*/
	    static const int STOCHASTIC_ANTIALIASING = 4;
};

#endif