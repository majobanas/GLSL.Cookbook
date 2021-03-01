#pragma once

#include "core/OpenGL/core/AttributeBuffer.h"

class IndexBuffer : public AttributeBuffer {
private:
	std::vector<unsigned int> _indices;
public:
	IndexBuffer();
	~IndexBuffer() override;

	void add(unsigned int pIndex);
	void buffer(int pGL_DRAW_TYPE = GL_STATIC_DRAW) override;
	void bind() override;

	int size() override;
};