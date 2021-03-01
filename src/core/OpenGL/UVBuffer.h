#pragma once

#include "core/OpenGL/core/AttributeBuffer.h"

class UVBuffer : public AttributeBuffer {
private:
	std::vector<glm::vec2> _uvs;
public:
	UVBuffer();
	~UVBuffer() override;

	void add(glm::vec2 pUV);
	void buffer(int pGL_DRAW_TYPE = GL_STATIC_DRAW) override;
	void bind() override;
	void enable(GLuint pAttributeHandle);
	void disable(GLuint pAttributeHandle);

	int size() override;
};