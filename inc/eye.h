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

#ifndef _EYE_H_
#define _EYE_H_

#include "graphics_vector.h"
#include "math_utils.h"


/**
 * Represents the eye of the viewer.
 */
class Eye
{
    public:
	/**
	 * Default constructor
         */
	Eye();
	
	/**
	 * Constructs a new eye
	 */
	Eye(const mvl::GVector3f& location, 
		const mvl::GVector3f& lookAt,
		const mvl::GVector3f& up);
	
	/**
	 * Gets the direction vector of the eye
	 */
	mvl::GVector3f getDir() const;
	
	/**
	 * Gets the location of the eye
	 */
	mvl::GVector3f getLocation() const;
	
	/**
	 * Gets the up vector the eye
	 */
	mvl::GVector3f getUp() const;
	
    private:
	/**The location of the eye*/
	mvl::GVector3f _location;
	/**Look at vector*/
	mvl::GVector3f _lookAt;
	/**Which way is up*/
	mvl::GVector3f _up;
	/**Viewing direction*/
	mvl::GVector3f _dir;
};

#endif