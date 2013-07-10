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

Ray::Ray(const Vector4f& origin, const Vector4f& dir):_origin(origin), _dir(dir)
{
    normalize(&_dir);
}

void Ray::setParam(float t)
{
    _t = t;
}

void Ray::setDir(const Vector4f dir)
{
    _dir = dir;
    normalize(&_dir);
}

Vector4f Ray::getPoint()
{
    return getPoint(_t);
}

Vector4f Ray::getPoint(float t) const 
{
    Vector4f point = _origin;
    Vector4f offset = scale(_dir, t);
    return add(point, offset);
}

Vector4f Ray::getOrigin() const
{
    return _origin;
}

Vector4f Ray::getDir() const
{
    return _dir;
}

string Ray::toString()
{
    string rayString = "(origin: " + _origin.toString();
    rayString += ", direction: " + _dir.toString() + ")";
    return rayString;
}

float Ray::getParam()
{
    return _t;
}