#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "core/Camera.h"
#include "core/Scene.h"

class Renderer {
private:

protected:
	int _width;
	int _height;

	void _clear();

public:
	Renderer(int pWidth, int pHeight);
	virtual ~Renderer() = 0;

	static Renderer* MAIN;

	virtual void render(Scene* pScene) = 0;

	void setClearColor(float pRed, float pGreen, float pBlue);
	void bindDefaultFrameBuffer();
};
