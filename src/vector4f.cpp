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

#include <vector>

#include "vector4f.h"

Vector4f::Vector4f()
{
	float initPoint[] = {0, 0, 0, 1};
	_vector = Vector(initPoint, 4);
}

Vector4f::Vector4f(float x, float y, float z, float w):_vector(4)
{
	_vector[0] = x;
	_vector[1] = y;
	_vector[2] = z;
	_vector[3] = w;
}

Vector4f::Vector4f(const float* source):_vector(source, 4)
	{}

Vector4f::Vector4f(const Vector4f& orig):_vector(orig._vector)
	{}

Vector4f::~Vector4f()
	{}

const Vector4f& Vector4f::operator = (const Vector4f& rSide)
{
	_vector = rSide._vector;
	return *this;
}

const Vector4f& Vector4f::operator += (const Vector4f& rSide)
{
	_vector += rSide._vector;
	return *this;
}

void Vector4f::scale(float scaleFactor)
{
	_vector.scale(scaleFactor);
}

float& Vector4f::operator[] (int column) const
{
	assert(column >= 0);
	assert(column <= 3);
	return _vector[column];
}

float Vector4f::getComp(int index) const
{
	return _vector.getComp(index);
}

bool Vector4f::operator == (const Vector4f& rSide)
{
	return _vector == rSide._vector;
}
	
bool Vector4f::operator != (const Vector4f& rSide)
{
	return _vector != rSide._vector;
}

const float* Vector4f::getData() const
{
	return _vector.getData();
}

string Vector4f::toString() const
{
	return _vector.toString();
}

void Vector4f::toArray(float* floatArray)
{
    for(int i = 0; i < 4; i++)
	floatArray[i] = _vector[i];
}

float& x(const Vector4f& v)
{
	return v[0];
}

float& y(const Vector4f& v)
{
	return v[1];
}	

float& z(const Vector4f& v)
{
	return v[2];
}	

float& w(const Vector4f& v)
{
	return v[3];
}		

float& r(const Vector4f& v)
{
	return v[0];
}

float& g(const Vector4f& v)
{
	return v[1];
}	

float& b(const Vector4f& v)
{
	return v[2];
}	

float& a(const Vector4f& v)
{
	return v[3];
}		

Vector4f add(const Vector4f& v1, const Vector4f& v2)
{
	Vector4f result;
	x(result) = x(v1) + x(v2);
	y(result) = y(v1) + y(v2);
	z(result) = z(v1) + z(v2);
	w(result) = w(v1) + w(v2);
	return result;
}

Vector4f sub(const Vector4f& v1, const Vector4f& v2)
{
	Vector4f result;
	x(result) = x(v1) - x(v2);
	y(result) = y(v1) - y(v2);
	z(result) = z(v1) - z(v2);
	w(result) = w(v1) - w(v2);	
	return result;
}

Vector4f scale(const Vector4f& v1, float scaleFactor)
{
    Vector4f v1Prime = v1;
    v1Prime.scale(scaleFactor);
    return v1Prime;
}

float dot(const Vector4f& v1, const Vector4f& v2)
{
	float product = 0;
	const int FOUR_DIMENSION = 4;
	for(int i = 0; i < FOUR_DIMENSION; i++)
	{	
		product += ((const float) v1[i]) * ((const float) v2[i]);
	}

	return product;
}	

float dot3f(const Vector4f& v1, const Vector4f& v2)
{
	float product = 0;
	const int THREE_DIMENSION = 3;
	for(int i = 0; i < THREE_DIMENSION; i++)
	{	
		product += ((const float) v1[i]) * ((const float) v2[i]);
	}

	return product;    
}

Vector4f cross(const Vector4f& v1, const Vector4f& v2)
{
	Vector4f result;

	const int X = 0;
	const int Y = 1;
	const int Z = 2;

	result[X] = y(v1) * z(v2) - z(v1) * y(v2);
	result[Y] = -(x(v1) * z(v2) - z(v1) * x(v2));
	result[Z] = x(v1) * y(v2) - y(v1) * x(v2);

	return result;
}	

Vector4f pwMult(const Vector4f& v1, const Vector4f& v2)
{
    return Vector4f(x(v1) * x(v2),
		y(v1) * y(v2),
		z(v1) * z(v2),
		w(v1) * w(v2));
}

float mag3f(const Vector4f& v)
{
    return sqrt((x(v) * x(v)) + (y(v) * y(v)) + (z(v) * z(v)));
}

void normalize(Vector4f* v)
{
    assert(v != 0);
    v->scale(1 / mag3f(*v));
}

void roundCompsToInt(Vector4f* v)
{
    x(*v) = floor(x(*v) + .5);
    y(*v) = floor(y(*v) + .5);
}