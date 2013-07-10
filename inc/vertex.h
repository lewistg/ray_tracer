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

#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <assert.h>
#include "vector4f.h"

using namespace gmath;

/**
 * A vertex that defines geometry.
 */
class Vertex
{
	public:
		/**
		 * Constructs a Vertex from a vector and color
		 * @pre vertex, color have 4 dimensions
		 */
		Vertex(const Vector4f& vertex, const Vector4f& color);
		
		/**
		 * Destructor.
		 */
		virtual ~Vertex();
		
		/**
		 * Gets the vertex Vector
		 * @return A reference to the vertex.
		*/
		Vector4f& getVertex();
		
		/**
		 * Gets the vertex Vector
		 * @return A const reference to the vertex.
		 */		
		const Vector4f getVertex() const;
		
		/**
		 * Gets a pointer to the internal Vector stored in this Vertex
                 * @return A pointer to the internal vertex
                 */
		//Vector4f* getVertex();
		
		/**
		 * Gets the color associated with this vertex
		 * @return A reference to the color.
		 */
		Vector4f& getColor();
		
		/**
		 * Gets the color associated with this vertex
		 * @return A const reference to the color.
		 */		
		const Vector4f& getColor() const;
		
	private:
		/**The actual vertex*/
		Vector4f _vertex;
		/**The color of the vertex*/
		Vector4f _color;
};

#endif