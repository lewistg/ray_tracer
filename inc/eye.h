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

#include "vector4f.h"
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
	Eye(const Vector4f& location, 
		const Vector4f& lookAt,
		const Vector4f& up);
	
	/**
	 * Gets the direction vector of the eye
	 */
	Vector4f getDir() const;
	
	/**
	 * Gets the location of the eye
	 */
	Vector4f getLocation() const;
	
	/**
	 * Gets the up vector the eye
	 */
	Vector4f getUp() const;
	
    private:
	/**The location of the eye*/
	Vector4f _location;
	/**Look at vector*/
	Vector4f _lookAt;
	/**Which way is udp*/
	Vector4f _up;
	/**Viewing direction*/
	Vector4f _dir;
};

#endif