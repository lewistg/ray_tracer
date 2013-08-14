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

#include "ray.h"
#include "graphics_vector_utils.h"

Ray::Ray()
	:_originPos(), 
	_dir(),
	_t(0)
{

}

Ray::Ray(const mvl::GVector3f& origin, const mvl::GVector3f& dir)
	:_originPos(origin), 
	_dir(dir), 
	_t(0)
{
	_dir.normalize();
}

void Ray::setParam(float t)
{
    _t = t;
}

void Ray::setOriginPos(const mvl::GVector3f& originPos)
{
	_originPos = originPos;	
}

void Ray::setDir(const mvl::GVector3f& dir)
{
    _dir = dir;
	_dir.normalize();
}

mvl::GVector3f Ray::getPoint() const
{
    return getPoint(_t);
}

mvl::GVector3f Ray::getPoint(float t) const 
{
    mvl::GVector3f point = _originPos;
    mvl::GVector3f offset = mvl::scaledCopy(_dir, t);
    return add(point, offset);
}

mvl::GVector3f Ray::getOrigin() const
{
    return _originPos;
}

mvl::GVector3f Ray::getDir() const
{
    return _dir;
}

string Ray::toString()
{
    string rayString = "(origin: " + _originPos.toString();
    rayString += ", direction: " + _dir.toString() + ")";
    return rayString;
}

float Ray::getParam()
{
    return _t;
}