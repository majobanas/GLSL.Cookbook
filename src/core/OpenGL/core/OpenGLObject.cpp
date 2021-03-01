#include "core/OpenGL/core/OpenGLObject.h"

OpenGLObject::OpenGLObject()
{
}

OpenGLObject::~OpenGLObject()
{
}

GLuint OpenGLObject::getHandle()
{
	return _handle;
}
