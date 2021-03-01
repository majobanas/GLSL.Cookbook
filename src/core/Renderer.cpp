#include "core/Renderer.h"

Renderer* Renderer::MAIN = NULL;

void Renderer::_clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

Renderer::Renderer(int pWidth, int pHeight)
	:	_width(pWidth),
		_height(pHeight)
{
	if (MAIN == NULL) {
		MAIN = this;
	}
}

Renderer::~Renderer()
{
	if (MAIN != NULL) {
		//do not delete, belongs to other object
		MAIN = NULL;
	}
}

void Renderer::setClearColor(float pRed, float pGreen, float pBlue)
{
	glClearColor(pRed, pGreen, pBlue, 1.0f);
}

void Renderer::bindDefaultFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

