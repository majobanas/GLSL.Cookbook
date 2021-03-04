#pragma once

#include "core/Scene.h"

class Camera;

class MyScene : public Scene {

private:

protected:

public:

	MyScene(std::string pName, Transform* pTransform);
	~MyScene() override;

	void populate() override;
};