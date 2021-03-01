#pragma once

#include "core/OpenGL/core/Buffer.h"

class FrameBuffer : public Buffer {
private:

public:
	FrameBuffer();
	~FrameBuffer() override;

	void setClearColor(float pRed, float pGreen, float pBlue);
	void clear();

	void bind() override;
	void unbind();
	void attachDepthBuffer(GLuint pDepthBufferHandle);
	void attachTexture2D(int pGL_COLOR_ATTACHMENT, GLuint pTextureHandle, int pLevel = 0);
};
