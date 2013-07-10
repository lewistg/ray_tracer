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

#include "eye.h"

Eye::Eye()
{
    
}

Eye::Eye(const Vector4f& location, 
		const Vector4f& lookAt,
		const Vector4f& up): _location(location), _lookAt(lookAt), 
		_dir(sub(lookAt, location))
{
    normalize(&_dir);
    Vector4f viewDir = sub(lookAt, location);
    
    // if the look at and  up vector are not already perpendicular
    if(!closeTo(dot(viewDir, up), 0, .000001))
    {
	Vector4f sideVector = cross(lookAt, up);
	_up = cross(sideVector, viewDir);
    }
    else
    {
	_up = up;
    }
	
}

Vector4f Eye::getDir() const
{
    return _dir;
}

Vector4f Eye::getLocation() const
{
    return _location;
}

Vector4f Eye::getUp() const
{
    return _up;
}