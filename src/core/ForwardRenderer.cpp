#include "core/ForwardRenderer.h"

ForwardRenderer::ForwardRenderer(int pWidth, int pHeight)
	:	Renderer(pWidth, pHeight)
{
}

ForwardRenderer::~ForwardRenderer()
{
}

void ForwardRenderer::render(Scene* pScene)
{
	Light::shadow();
	RenderTextureMaterial::render(Camera::MAIN->getMatrix(), Camera::MAIN->getProjection());
	glViewport(0, 0, _width, _height);
	MAIN->bindDefaultFrameBuffer();
	_clear();
	Object::render();
	//Light::render(camera);
	
}
