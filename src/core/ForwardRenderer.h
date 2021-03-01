#pragma once
#include "core/Renderer.h"


class ForwardRenderer : public Renderer {
private:

public:
	ForwardRenderer(int pWidth, int pHeight);
	~ForwardRenderer() override;

	void render(Scene* pScene) override;
};