#include "core/ForwardRenderer.h"

ForwardRenderer::ForwardRenderer(int pWidth, int pHeight)
	:	Renderer(pWidth, pHeight)
{
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

ForwardRenderer::~ForwardRenderer()
{
}

void ForwardRenderer::render(Scene* pScene)
{
	Light::shadow(pScene);
	RenderTextureMaterial::render(pScene, Camera::MAIN->getTransform()->getMatrix(), Camera::MAIN->getProjection());
	glViewport(0, 0, _width, _height);
	MAIN->bindDefaultFrameBuffer();
	_clear();

	for (auto& child : pScene->children) {
		child->render(Camera::MAIN->getTransform()->getMatrix(), Camera::MAIN->getView(), Camera::MAIN->getProjection());
	}

	Light::render(Camera::MAIN);
	
}
