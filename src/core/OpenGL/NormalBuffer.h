#pragma once

#include "core/OpenGL/core/AttributeBuffer.h"

class NormalBuffer : public AttributeBuffer {
private:
	std::vector<glm::vec3> _normals;
public:
	NormalBuffer();
	~NormalBuffer() override;

	void add(glm::vec3 pNormal);
	void buffer(int pGL_DRAW_TYPE = GL_STATIC_DRAW) override;
	void bind() override;
	void enable(GLuint pAttributeHandle);
	void disable(GLuint pAttributeHandle);

	int size() override;
};