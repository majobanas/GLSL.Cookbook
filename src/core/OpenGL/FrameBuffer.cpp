#include "core/OpenGL/FrameBuffer.h"



FrameBuffer::FrameBuffer()
	:	Buffer(GL_FRAMEBUFFER)
{
	glGenFramebuffers(1, &_handle);
	setClearColor(0.0f, 0.0f, 0.0f);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &_handle);
}

void FrameBuffer::setClearColor(float pRed, float pGreen, float pBlue)
{
	glClearColor(pRed, pGreen, pBlue, 1.0f);
}

void FrameBuffer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void FrameBuffer::bind()
{
	glBindFramebuffer(_bufferType, _handle);
}

void FrameBuffer::unbind()
{
	glBindFramebuffer(_bufferType, 0);
}

void FrameBuffer::attachDepthBuffer(GLuint pDepthBufferHandle)
{
	glFramebufferRenderbuffer(_bufferType, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, pDepthBufferHandle);
}

void FrameBuffer::attachTexture2D(int pGL_COLOR_ATTACHMENT, GLuint pTextureHandle, int pLevel)
{
	glFramebufferTexture2D(_bufferType, pGL_COLOR_ATTACHMENT, GL_TEXTURE_2D, pTextureHandle, pLevel);
}
