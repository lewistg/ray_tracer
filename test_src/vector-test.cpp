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

#define BOOST_TEST_MODULE vectortest

#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include "vector.h"

using namespace std;
using namespace gmath;

BOOST_AUTO_TEST_SUITE (vectortest)

/*
 * Test to make sure that the cross product is working
 */
BOOST_AUTO_TEST_CASE (cross_product)
{
	// simple cross product
	Vector v1(3);
	x(v1) = 1.0f;
	y(v1) = 0.0f;
	z(v1) = 0.0f;
	
	Vector v2(3);
	x(v2) = 0.0f;
	y(v2) = 1.0f;
	z(v2) = 0.0f;
	
	Vector oracle(3);
	x(oracle) = 0.0f;
	y(oracle) = 0.0f;
	z(oracle) = 1.0f;
	BOOST_CHECK(oracle == cross(v1, v2));
	
	// a more complicated cross product
	x(v1) = 1.0f;
	y(v1) = 2.0f;
	z(v1) = 3.0f;
	
	x(v2) = 3.0f;
	y(v2) = 4.0f;
	z(v2) = 5.0f;

	x(oracle) = -2.0f;
	y(oracle) = 4.0f;
	z(oracle) = -2.0f;
	
	BOOST_CHECK(oracle == cross(v1, v2));
}	

BOOST_AUTO_TEST_CASE (dot_product)
{
	// all positive numbers
	Vector v1(3);
	x(v1) = 2.0f;
	y(v1) = 3.0f;
	z(v1) = 4.0f;
	
	Vector v2(3);
	x(v2) = 5.0f;
	y(v2) = 6.0f;
	z(v2) = 7.0f;	
	
	float oracle = 56;
	
	BOOST_CHECK(oracle == dot(v1, v2));
	
	// some negative numbers
	x(v1) = 2.0f;
	y(v1) = -3.0f;
	z(v1) = 4.0f;
	
	x(v2) = 2.0f;
	y(v2) = 3.0f;
	z(v2) = -4.0f;
	
	oracle = -21;
	
	BOOST_CHECK(oracle == dot(v1, v2));
}

BOOST_AUTO_TEST_SUITE_END()
