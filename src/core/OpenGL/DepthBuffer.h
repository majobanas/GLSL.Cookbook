#pragma once

#include "core/OpenGL/core/Buffer.h"

class DepthBuffer : public Buffer {
private:

public:
	DepthBuffer();
	~DepthBuffer() override;

	void bind() override;
	void allocate(int pWidth, int pHeight);
};
