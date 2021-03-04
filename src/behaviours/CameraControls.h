#pragma once

#include "core/Behaviour.h"

class Transform;

class Entity;
class Camera;

class CameraControls : public Behaviour {

private:
	Camera* cameraOwner = NULL;

	glm::vec3 _movementDirection = glm::vec3(0.0f);
	glm::vec2 _movementRotation = glm::vec3(0.0f);
	glm::vec2 _previousMousePosition = glm::vec3(0.0f);
	glm::vec2 _mousePositionDifference = glm::vec3(0.0f);

protected:

public:

	CameraControls(Entity* pEntity);
	virtual ~CameraControls() override;

	void update(float pElapsedTime) override;
};