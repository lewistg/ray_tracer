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

#define BOOST_TEST_MODULE matrix_stack_test

#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <time.h>
#include "matrix4f_stack.h"
#include "matrix4f.h"

using namespace std;

BOOST_AUTO_TEST_SUITE (matrix_stack_test)
        
BOOST_AUTO_TEST_CASE (push_test)
{
    Matrix4fStack mStack;
    BOOST_CHECK(mStack.isEmpty());
    
    srand(time(NULL));
    
    const int NUM_MATS = 32;
    
    // generate random matrices
    Matrix4f mats[32];
    for(int i = 0; i < NUM_MATS; i++)
    {
        for(int row = 0; row < 4; row++)
            for(int col = 0; col < 4; col++)
                mats[i][row][col] = (float) rand();
	
	mStack.push(mats[i]);
    }
    
    BOOST_CHECK(mStack.getSize() == NUM_MATS);
    BOOST_CHECK(mStack.top() == mats[NUM_MATS - 1]);
    
    for(int i = NUM_MATS - 1; i >= 0; i--)
	BOOST_CHECK(mStack.pop() == mats[i]);
	

    BOOST_CHECK(mStack.isEmpty());
}        


BOOST_AUTO_TEST_SUITE_END()