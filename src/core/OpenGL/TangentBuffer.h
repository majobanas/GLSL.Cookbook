#pragma once

#include "core/OpenGL/core/AttributeBuffer.h"

class TangentBuffer : public AttributeBuffer {
private:
	std::vector<glm::vec4> _tangents;
public:
	TangentBuffer();
	~TangentBuffer() override;

	void add(glm::vec4 pTangent);
	void buffer(int pGL_DRAW_TYPE = GL_STATIC_DRAW) override;
	void bind() override;
	void enable(GLuint pAttributeHandle);
	void disable(GLuint pAttributeHandle);

	int size() override;
};