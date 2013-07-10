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

#ifndef _VERTEX_BUFFER_H_
#define _VERTEX_BUFFER_H_

#include "vertex.h"

using namespace std;

/**
 * Holds the verticies in the order they are
 * defined 
 */
class VertexBuffer
{
	public:
		/**
		 * Constructor
		 */
		VertexBuffer();
		
		/**
		 * Destructor
		 */
		~VertexBuffer();
		
		/**
		 * Allows for access like an array
                 * @param i
                 * @return 
                 */
		Vertex& operator[] (int i);
		
		/**
		 * Returns the number of vertices that have
		 * been buffered
		 */
		int numVertices();
		
		/**
		 * Returns a pointer to the vertices
		 * @return 
		 */
		Vertex* getVertices();
		
		/**
		 * Adds the vertex to the buffer
		 */
		void addVertex(const Vertex& vertex);
		
		/**
		 * Clears the buffer
		 */
		void clear();
		
	private:
		/**The buffered vertices for drawing*/
		vector<Vertex> _bufferedVertices;
		
};

#endif