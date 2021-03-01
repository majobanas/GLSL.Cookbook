#pragma once

#include "core/OpenGL/core/Buffer.h"

class AttributeBuffer : public Buffer {
private:

public:
	AttributeBuffer(int pBufferType);
	virtual ~AttributeBuffer() override;

	virtual void buffer(int pGL_DRAW_TYPE) = 0;
	virtual int size() = 0;
};
