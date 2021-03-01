#pragma once
#include "glad/glad.h"

class OpenGLObject {
protected:
	GLuint _handle = -1;

public:
	OpenGLObject();
	virtual ~OpenGLObject() = 0;

	GLuint getHandle();
};
