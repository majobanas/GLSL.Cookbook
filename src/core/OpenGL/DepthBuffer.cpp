#include "core/OpenGL/DepthBuffer.h"

DepthBuffer::DepthBuffer()
	:	Buffer(GL_RENDERBUFFER)
{
	glGenRenderbuffers(1, &_handle);
}

DepthBuffer::~DepthBuffer()
{
	glDeleteRenderbuffers(1, &_handle);
}

void DepthBuffer::bind()
{
	glBindRenderbuffer(_bufferType, _handle);
}

void DepthBuffer::allocate(int pWidth, int pHeight)
{
	glRenderbufferStorage(_bufferType, GL_DEPTH_COMPONENT, pWidth, pHeight);
}
