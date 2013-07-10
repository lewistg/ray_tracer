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

#include "vertex.h"

Vertex::Vertex(const Vector4f& vertex, const Vector4f& color):
	_vertex(vertex), _color(color)
{
}

Vertex::~Vertex()
	{}

Vector4f& Vertex::getVertex()
{
	return _vertex;
}

const Vector4f Vertex::getVertex() const
{
	return _vertex;
}

/*Vector4f* Vertex::getVertex()
{
    return &_vertex;
}*/

Vector4f& Vertex::getColor()
{
	return _color;
}

const Vector4f& Vertex::getColor() const
{
	return _color;
}