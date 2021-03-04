#include "behaviours/CameraControls.h"

#include "input/Mouse.h"
#include "input/Keyboard.h"

#include "core/Transform.h"

#include "core/Hierarchial/Entity.h"
#include "core/Camera.h"

CameraControls::CameraControls(Entity* pOwner) 
	: Behaviour(pOwner)
{
	cameraOwner = reinterpret_cast<Camera*>(owner);
}

CameraControls::~CameraControls()
{
	if (cameraOwner != NULL) {
		// do not delete, owned by other object
		cameraOwner = NULL;
	}
}

void CameraControls::update(float pElapsedTime)
{
	pElapsedTime *= 100;

	if (Mouse::buttonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
		Mouse::setLockPosition(Mouse::getPosition());
		Mouse::hide();
	}
	if (Mouse::buttonReleased(GLFW_MOUSE_BUTTON_RIGHT)) {
		Mouse::show();
	}

	if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_RIGHT)) {
		_mousePositionDifference = Mouse::getPositionDifference();
		if (_mousePositionDifference.x != 0 || _mousePositionDifference.y != 0) {
			_movementRotation.x -= _mousePositionDifference.y * pElapsedTime;
			_movementRotation.y -= _mousePositionDifference.x * pElapsedTime;
			Mouse::setPosition(Mouse::getLockPosition());
		}
	}

	// Move camera if keys are held
	if (Keyboard::keyDown(GLFW_KEY_W) ||
		Keyboard::keyDown(GLFW_KEY_S) ||
		Keyboard::keyDown(GLFW_KEY_A) ||
		Keyboard::keyDown(GLFW_KEY_D) ||
		Keyboard::keyDown(GLFW_KEY_Q) ||
		Keyboard::keyDown(GLFW_KEY_E)) {
		_movementDirection = glm::normalize(glm::vec3(
			Keyboard::keyDown(GLFW_KEY_A) ? -1.0f : (Keyboard::keyDown(GLFW_KEY_D) ? 1.0f : 0.0f),
			Keyboard::keyDown(GLFW_KEY_Q) ? -1.0f : (Keyboard::keyDown(GLFW_KEY_E) ? 1.0f : 0.0f),
			Keyboard::keyDown(GLFW_KEY_W) ? -1.0f : (Keyboard::keyDown(GLFW_KEY_S) ? 1.0f : 0.0f)));
		_movementDirection = glm::rotateX(_movementDirection, glm::radians(_movementRotation.x));
		_movementDirection = glm::rotateY(_movementDirection, glm::radians(_movementRotation.y));
		_movementDirection = glm::normalize(_movementDirection);

	}
	if (_movementDirection != glm::vec3(0.0f) ||
		_mousePositionDifference != glm::vec2(0.0f)) {


		*cameraOwner->getTransform()->getMatrix() =
			glm::translate(glm::vec3(glm::vec3((*cameraOwner->getTransform()->getMatrix())[3]) + _movementDirection * pElapsedTime)) *
			glm::rotate(glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::rotate(glm::radians(_movementRotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::rotate(glm::radians(_movementRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

		*cameraOwner->getViewProjection() = *cameraOwner->getProjection() * *cameraOwner->getView();
		_movementDirection = glm::vec3(0.0f);
	}
}
