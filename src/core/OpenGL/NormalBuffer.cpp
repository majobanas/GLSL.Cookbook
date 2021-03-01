#include "core/OpenGL/NormalBuffer.h"

NormalBuffer::NormalBuffer()
	: AttributeBuffer(GL_ARRAY_BUFFER)
{
	glGenBuffers(1, &_handle);
}

NormalBuffer::~NormalBuffer()
{
	glDeleteBuffers(1, &_handle);
}

void NormalBuffer::add(glm::vec3 pNormal)
{
	_normals.push_back(pNormal);
}

void NormalBuffer::buffer(int pGL_DRAW_TYPE)
{
	bind();
	glBufferData(_bufferType, _normals.size() * sizeof(glm::vec3), &_normals[0], pGL_DRAW_TYPE);

}

void NormalBuffer::bind()
{
	glBindBuffer(_bufferType, _handle);
}

void NormalBuffer::enable(GLuint pAttributeHandle)
{
	glEnableVertexAttribArray(pAttributeHandle);
	glVertexAttribPointer(pAttributeHandle, 3, GL_FLOAT, GL_TRUE, 0, 0);
}

void NormalBuffer::disable(GLuint pAttributeHandle)
{
	glDisableVertexAttribArray(pAttributeHandle);
}

int NormalBuffer::size()
{
	return _normals.size();
}
