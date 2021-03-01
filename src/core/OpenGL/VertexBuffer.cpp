#include "core/OpenGL/VertexBuffer.h"

VertexBuffer::VertexBuffer()
	:	AttributeBuffer(GL_ARRAY_BUFFER)
{
	glGenBuffers(1, &_handle);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &_handle);
}

void VertexBuffer::add(glm::vec3 pVertex)
{
	_vertices.push_back(pVertex);
}

void VertexBuffer::buffer(int pGL_DRAW_TYPE)
{
	bind();
	glBufferData(_bufferType, _vertices.size() * sizeof(glm::vec3), &_vertices[0], pGL_DRAW_TYPE);

}

void VertexBuffer::bind()
{
	glBindBuffer(_bufferType, _handle);
}

void VertexBuffer::enable(GLuint pAttributeHandle)
{
	glEnableVertexAttribArray(pAttributeHandle);
	glVertexAttribPointer(pAttributeHandle, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void VertexBuffer::disable(GLuint pAttributeHandle)
{
	glDisableVertexAttribArray(pAttributeHandle);
}

int VertexBuffer::size()
{
	return _vertices.size();
}
