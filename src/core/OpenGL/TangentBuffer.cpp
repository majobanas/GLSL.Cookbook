#include "core/OpenGL/TangentBuffer.h"

TangentBuffer::TangentBuffer()
	: AttributeBuffer(GL_ARRAY_BUFFER)
{
	glGenBuffers(1, &_handle);
}

TangentBuffer::~TangentBuffer()
{
	glDeleteBuffers(1, &_handle);
}

void TangentBuffer::add(glm::vec4 pTangent)
{
	_tangents.push_back(pTangent);
}

void TangentBuffer::buffer(int pGL_DRAW_TYPE)
{
	bind();
	glBufferData(_bufferType, _tangents.size() * sizeof(glm::vec3), &_tangents[0], pGL_DRAW_TYPE);

}

void TangentBuffer::bind()
{
	glBindBuffer(_bufferType, _handle);
}

void TangentBuffer::enable(GLuint pAttributeHandle)
{
	glEnableVertexAttribArray(pAttributeHandle);
	glVertexAttribPointer(pAttributeHandle, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void TangentBuffer::disable(GLuint pAttributeHandle)
{
	glDisableVertexAttribArray(pAttributeHandle);
}

int TangentBuffer::size()
{
	return _tangents.size();
}
