#include "core/OpenGL/IndexBuffer.h"
#include <iostream>
IndexBuffer::IndexBuffer()
	: AttributeBuffer(GL_ELEMENT_ARRAY_BUFFER)
{
	glGenBuffers(1, &_handle);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &_handle);
}

void IndexBuffer::add(unsigned int pIndex)
{
	_indices.push_back(pIndex);
}

void IndexBuffer::buffer(int pGL_DRAW_TYPE)
{
	bind();
	glBufferData(_bufferType, _indices.size() * sizeof(glm::vec3), &_indices[0], pGL_DRAW_TYPE);

}

void IndexBuffer::bind()
{
	glBindBuffer(_bufferType, _handle);
}

int IndexBuffer::size()
{
	return _indices.size();
}
