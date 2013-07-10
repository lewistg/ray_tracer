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
#include "vector4f.h"

using namespace std;

BOOST_AUTO_TEST_SUITE (vector4ftest)

BOOST_AUTO_TEST_CASE (read_write_from_array)
{
	//Read and write matrices and vectors to simple arrays of floats; 
	//do matrices in column major format.
	float v1Data[] = {8, -10, 3, 6};
	Vector4f v1(v1Data);
	
	float v1DataRetrieved[4];
	v1.toArray(v1DataRetrieved);
	
	for(int i = 0; i < 4; i++)
	    BOOST_CHECK(v1Data[i] == v1DataRetrieved[i]);
}

BOOST_AUTO_TEST_CASE (vector_arith)
{
    // Multiply vectors by single numbers
    Vector4f v1(4, 5, -3, 5);
    v1.scale(4);
    
    Vector4f oracle;
    x(oracle) = 16;
    y(oracle) = 20;
    z(oracle) = -12;
    w(oracle) = 20;
    
    BOOST_CHECK(v1 == oracle);
    
    // add vectors
    Vector4f v2(3, 2, -3, 5);
    Vector4f v3(5, -4, 3, 5);
    
    Vector4f sum = add(v2, v3);
    x(oracle) = 8;
    y(oracle) = -2;
    z(oracle) = 0;
    w(oracle) = 10;
    
    BOOST_CHECK(sum == oracle);
    
    // subtract vectors
    Vector4f diff = sub(v2, v3);
    x(oracle) = -2;
    y(oracle) = 6;
    z(oracle) = -6;
    w(oracle) = 0;
    
    BOOST_CHECK(diff == oracle);
       
}

/*
 * Test to make sure that the cross product is working
 */
BOOST_AUTO_TEST_CASE (cross_product)
{
	// simple cross product
	Vector4f v1;
	x(v1) = 1.0f;
	y(v1) = 0.0f;
	z(v1) = 0.0f;
	
	Vector4f v2;
	x(v2) = 0.0f;
	y(v2) = 1.0f;
	z(v2) = 0.0f;
	
	Vector4f oracle;
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
	Vector4f v1;
	x(v1) = 2.0f;
	y(v1) = 3.0f;
	z(v1) = 4.0f;
	w(v1) = 0.0f;
	
	Vector4f v2;
	x(v2) = 5.0f;
	y(v2) = 6.0f;
	z(v2) = 7.0f;	
	w(v2) = 0.0f;
	
	float oracle = 56;
	
	cout << "dot(v1, v2)" << dot(v1, v2) << endl;
	
	BOOST_CHECK(oracle == dot(v1, v2));
	
	// some negative numbers
	x(v1) = 2.0f;
	y(v1) = -3.0f;
	z(v1) = 4.0f;
	w(v1) = 0.0f;
	
	x(v2) = 2.0f;
	y(v2) = 3.0f;
	z(v2) = -4.0f;
	w(v2) = 0.0f;
	
	oracle = -21;
	
	BOOST_CHECK(oracle == dot(v1, v2));
}

BOOST_AUTO_TEST_SUITE_END()
