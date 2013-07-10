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

#define BOOST_TEST_MODULE matrixtest

#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include "matrix.h"
#include "vector.h"

using namespace std;
using namespace gmath;

BOOST_AUTO_TEST_SUITE (matrixtest)

/*
 * Test to make sure that the cross product is working
 */
BOOST_AUTO_TEST_CASE (matrix_mult)
{
	float m1Data[] = {8, -10, 3, 4, 6, 2, 4, 5, 6};
	SquareMatrix m1(m1Data, 3);
	
	float m2Data[] = {8, 8, -30, 4, 6, 6, -20, 5, 6};
	SquareMatrix m2(m2Data, 3);
	
	float oracleData[] = {-24, -182, -140, 80, 26, 60, -116, 260, -14};
	SquareMatrix oracle(oracleData, 3);
	
	mult(m1, m2);
	
	BOOST_CHECK(oracle == mult(m1, m2));
}	

BOOST_AUTO_TEST_CASE (determinant)
{
	float m1Data[] = {8, -10, 3, 4, 6, 2, 4, 5, 6};
	SquareMatrix m1(m1Data, 3);	
	
	float oracle = 356;
	
	BOOST_CHECK(m1.det() == oracle);
}

BOOST_AUTO_TEST_CASE (inverse)
{
	float mData[] = {1, 0, 0, 2, 1, 0, 4, 5, 1};
	SquareMatrix m(mData, 3);	

	float oracleData[] = {1, 0, 0, -2, 1, 0, 6, -5, 1};
	SquareMatrix oracle(oracleData, 3);
	
	BOOST_CHECK(m.inverse() == oracle);
}

BOOST_AUTO_TEST_SUITE_END()
