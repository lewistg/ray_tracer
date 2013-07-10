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

#define BOOST_TEST_MODULE matrixtest4f

#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include "matrix4f.h"
#include "vector4f.h"

using namespace std;
using namespace gmath;

BOOST_AUTO_TEST_SUITE (matrixtest4f)

BOOST_AUTO_TEST_CASE (read_write_from_array)
{
	//Read and write matrices and vectors to simple arrays of floats; 
	//do matrices in column major format.
	float m1Data[] = {8, -10, 3, 6, 2, 4, 8, 4, 4, -2, -9, 2, 4, 4, 5, -3};
	Matrix4f m1(m1Data);
	
	float m1DataRetrieved[16];
	m1.toArray(m1DataRetrieved);
	
	for(int i = 0; i < 16; i++)
	    BOOST_CHECK(m1Data[i] == m1DataRetrieved[i]);
	    
}

/*
 * Test to make sure that the cross product is working
 */
BOOST_AUTO_TEST_CASE (matrix_mult)
{
	// multiply two matrices
	float m1Data[] = {8, -10, 3, 6, 2, 4, 8, 4, 4, -2, -9, 2, 4, 4, 5, -3};
	Matrix4f m1(m1Data);
	
	float m2Data[] = {2, 6, -1, -5, 3, 7, -2, -6, 4, 8, -3, -7, 5, 9, -4, -8};
	Matrix4f m2(m2Data);
	
	float oracleData[] = {4, -14, 38, 49, 6, -22, 53, 60, 
							8, -30, 68, 71, 10, -38, 83, 82};
	Matrix4f oracle(oracleData);
	
	mult(m1, m2);
	
	BOOST_CHECK(oracle == mult(m1, m2));
	
	// multiply a matrix by a vector
	Vector4f v1(4, 5, -3, 5);
	Vector4f vOracle(50, 6, 104, 23);
	
	BOOST_CHECK(vOracle == mult(m1, v1));
}	

BOOST_AUTO_TEST_CASE (determinant)
{
	float m1Data[] = {8, -10, 3, 6, 2, 4, 8, 4, 4, -2, -9, 2, 4, 4, 5, -3};
	Matrix4f m1(m1Data);	
	
	float oracle = 6080;
	
	BOOST_CHECK(m1.det() == oracle);
}

BOOST_AUTO_TEST_CASE (inverse)
{
	float mData[] = {1, 0, 0, 0, 5, 1, 0, 0, 6, -8, 1, 0, 4, 3, 7, 1};
	Matrix4f m(mData);	

	float oracleData[] = {1, 0, 0, 0, -5, 1, 0, 0, -46, 8, 1, 0, 333, -59, -7, 1};
	Matrix4f oracle(oracleData);
	
	BOOST_CHECK(m.inverse() == oracle);
	
	float m2Data[] = {1, 4, -7, 2, 5, 1, 3, 4, 6, -8, 1, 6, 4, 3, 7, 1};
	m = Matrix4f(m2Data);
	Matrix4f shouldBeIdentity = mult(m.inverse(), m);
	
	BOOST_CHECK(practicallyIdentity(shouldBeIdentity));
}

BOOST_AUTO_TEST_SUITE_END()
