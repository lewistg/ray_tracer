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
#include "vector_math.h"
#include "graphics_vector_utils.h"

Eye::Eye()
	:_location(),
	_lookAt(),
	_up(),
	_dir()
{
    
}

Eye::Eye(const mvl::GVector3f& location, 
		const mvl::GVector3f& lookAt,
		const mvl::GVector3f& up)
	: _location(location), 
	_lookAt(lookAt), 
	_up(up),
	_dir(sub(lookAt, location))
{
	_dir.normalize();
    mvl::GVector3f viewDir = sub(lookAt, location);
    
    // if the look at and  up vector are not already perpendicular
    if(!closeTo(mvl::dot(viewDir, up), 0, .000001))
    {
		mvl::GVector3f sideVector = mvl::cross(lookAt, up);
		_up = cross(sideVector, viewDir);
    }
    else
    {
		_up = up;
    }
	
}

mvl::GVector3f Eye::getDir() const
{
    return _dir;
}

mvl::GVector3f Eye::getLocation() const
{
    return _location;
}

mvl::GVector3f Eye::getUp() const
{
    return _up;
}