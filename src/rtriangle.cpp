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

#include "rtriangle.h"
#include "math_utils.h"
#include "plane_depth_calculator.h"
#include "graphics_vector_utils.h"

RTriangle::RTriangle(const mvl::GVector3f& p0, const mvl::GVector3f& p1, const mvl::GVector3f& p2) 
	: _p0(p0), 
	_p1(p1), 
	_p2(p2), 
	_plane(p0, mvl::cross(sub(p1, p0), sub(p2, p0)))
{
}

float RTriangle::rayStrikesObject(const Ray& ray)
{
	float t = _plane.rayStrikesObject(ray);

	// if didn't strike the plane containing the 
	if (t == -1)
		return -1;

	// find the plane of fattest projection
	float nDotX = abs(mvl::dot(_plane.getNormal(), mvl::GVector3f(1.0f, 0.0f, 0.0f)));
	float nDotY = abs(mvl::dot(_plane.getNormal(), mvl::GVector3f(0.0f, 1.0f, 0.0f)));
	float nDotZ = abs(mvl::dot(_plane.getNormal(), mvl::GVector3f(0.0f, 0.0f, 1.0f)));

	mvl::GVector3f pointOnPlane = ray.getPoint(t);

	float detT = 0;
	float lambda1 = 0;
	float lambda2 = 0;
	float lambda3 = 0;

	// if the normal is most parallel to the x axis
	if (nDotX >= nDotY && nDotX >= nDotZ)
	{
		// calculate, projecting the triangle onto the y,z plane
		detT = (z(_p1) - z(_p2)) * (y(_p0) - y(_p2));
		detT += (y(_p2) - y(_p1)) * (z(_p0) - z(_p2));
		lambda1 = ((z(_p1) - z(_p2)) * (y(pointOnPlane) - y(_p2)) + (y(_p2) - y(_p1)) * (z(pointOnPlane) - z(_p2)))
				/ detT;
		lambda2 = ((z(_p2) - z(_p0)) * (y(pointOnPlane) - y(_p2)) + (y(_p0) - y(_p2)) * (z(pointOnPlane) - z(_p2)))
				/ detT;
		lambda3 = 1 - lambda1 - lambda2;
	} else if (nDotY >= nDotX && nDotY >= nDotZ) // if is most parallel to the y axis
	{
		// calculate, projecting it onto the x,z plane
		detT = (z(_p1) - z(_p2)) * (x(_p0) - x(_p2));
		detT += (x(_p2) - x(_p1)) * (z(_p0) - z(_p2));
		lambda1 = ((z(_p1) - z(_p2)) * (x(pointOnPlane) - x(_p2)) + (x(_p2) - x(_p1)) * (z(pointOnPlane) - z(_p2)))
				/ detT;
		lambda2 = ((z(_p2) - z(_p0)) * (x(pointOnPlane) - x(_p2)) + (x(_p0) - x(_p2)) * (z(pointOnPlane) - z(_p2)))
				/ detT;
		lambda3 = 1 - lambda1 - lambda2;
	} else // else it is most parallel to the z axis
	{
		detT = (y(_p1) - y(_p2)) * (x(_p0) - x(_p2));
		detT += (x(_p2) - x(_p1)) * (y(_p0) - y(_p2));
		lambda1 = ((y(_p1) - y(_p2)) * (x(pointOnPlane) - x(_p2)) + (x(_p2) - x(_p1)) * (y(pointOnPlane) - y(_p2)))
				/ detT;
		lambda2 = ((y(_p2) - y(_p0)) * (x(pointOnPlane) - x(_p2)) + (x(_p0) - x(_p2)) * (y(pointOnPlane) - y(_p2)))
				/ detT;
		lambda3 = 1 - lambda1 - lambda2;
	}


	if (withinTri(lambda1) && withinTri(lambda2) && withinTri(lambda3))
		return t;
	else
		return -1;
}

mvl::GVector3f RTriangle::getNormal(const mvl::GVector3f& pointOnObj) const
{
	return _plane.getNormal();
}

bool RTriangle::withinTri(float lambda)
{
	if ((closeTo(lambda, 0, .0001) || lambda > 0) && (lambda < 1 || closeTo(lambda, 1, .0001)))
		return true;
	else
		return false;
}