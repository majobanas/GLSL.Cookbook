#include "core/OpenGL/UVBuffer.h"

UVBuffer::UVBuffer()
	: AttributeBuffer(GL_ARRAY_BUFFER)
{
	glGenBuffers(1, &_handle);
}

UVBuffer::~UVBuffer()
{
	glDeleteBuffers(1, &_handle);
}

void UVBuffer::add(glm::vec2 pUV)
{
	_uvs.push_back(pUV);
}

void UVBuffer::buffer(int pGL_DRAW_TYPE)
{
	bind();
	glBufferData(_bufferType, _uvs.size() * sizeof(glm::vec3), &_uvs[0], pGL_DRAW_TYPE);

}

void UVBuffer::bind()
{
	glBindBuffer(_bufferType, _handle);
}

void UVBuffer::enable(GLuint pAttributeHandle)
{
	glEnableVertexAttribArray(pAttributeHandle);
	glVertexAttribPointer(pAttributeHandle, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void UVBuffer::disable(GLuint pAttributeHandle)
{
	glDisableVertexAttribArray(pAttributeHandle);
}

int UVBuffer::size()
{
	return _uvs.size();
}
