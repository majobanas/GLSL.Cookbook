#pragma once

#include "core/OpenGL/core/OpenGLObject.h"

#include <vector>

#include "glm/glm.hpp"

class Buffer : public OpenGLObject {
private:

protected:
	int _bufferType;

public:
	Buffer(int pBufferType);
	virtual ~Buffer() override;

	virtual void bind() = 0;
};
