#pragma once

#include "core/Hierarchial/Transformable.h"

class Transform;

class Camera : public Transformable {
private:
	int _width;
	int _height;
	float _aspectRatio;
	float _fov;

	glm::mat4* _view = NULL;
	glm::mat4* _projection = NULL;
	glm::mat4* _viewProjection = NULL;


	float _setAspectRatio(int pWidth, int pHeight);
	glm::mat4 _setProjection(float pFov, float pAspectRatio);

public:
	Camera(int pWidth, int pHeight, float pFov, glm::vec3 pPosition, glm::vec3 pRotation = glm::vec3(0.0f));
	~Camera() override;

	static Camera* MAIN;
	static void clear();

	glm::mat4* getView();
	glm::mat4* getProjection();
	glm::mat4* getViewProjection();

	int getWidth();
	int getHeight();
	float getFov();
	float getAspectRatio();

	void setFov(float pFov);
	void setAspectRatio(int pWidth, int pHeight);
};