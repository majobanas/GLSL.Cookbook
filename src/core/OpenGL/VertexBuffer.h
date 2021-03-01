#pragma once

#include "core/OpenGL/core/AttributeBuffer.h"

class VertexBuffer : public AttributeBuffer {
private:
	std::vector<glm::vec3> _vertices;
public:
	VertexBuffer();
	~VertexBuffer() override;

	void add(glm::vec3 pVertex);
	void buffer(int pGL_DRAW_TYPE = GL_STATIC_DRAW) override;
	void bind() override;
	void enable(GLuint pAttributeHandle);
	void disable(GLuint pAttributeHandle);

	int size() override;
};