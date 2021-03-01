#pragma once

#include "core/Object.h"

#include "glm/gtx/transform.hpp"

class Camera {
private:
	int _width;
	int _height;
	float _aspectRatio;
	float _fov;

	glm::mat4* _matrix = NULL;
	glm::mat4* _view = NULL;
	glm::mat4* _projection = NULL;
	glm::mat4* _viewProjection = NULL;

	glm::vec3 _movementDirection = glm::vec3(0.0f);
	glm::vec2 _movementRotation = glm::vec3(0.0f);
	glm::vec2 _previousMousePosition = glm::vec3(0.0f);
	glm::vec2 _mousePositionDifference = glm::vec3(0.0f);


	float _setAspectRatio(int pWidth, int pHeight);
	glm::mat4 _setProjection(float pFov, float pAspectRatio);

public:
	Camera(int pWidth, int pHeight, float pFov, glm::vec3 pPosition, glm::vec3 pRotation = glm::vec3(0.0f));
	~Camera();

	static Camera* MAIN;
	static void clear();

	glm::mat4* getMatrix();
	glm::mat4* getView();
	glm::mat4* getProjection();
	glm::mat4* getViewProjection();

	int getWidth();
	int getHeight();
	float getFov();
	float getAspectRatio();

	void setFov(float pFov);
	void setAspectRatio(int pWidth, int pHeight);

	void update(float pElapsedTime);
};