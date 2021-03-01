#include "core/Camera.h"

#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/rotate_vector.hpp"

#include "input/Mouse.h"
#include "input/Keyboard.h"

float Camera::_setAspectRatio(int pWidth, int pHeight)
{
	return (float)pWidth / (float) pHeight;
}

glm::mat4 Camera::_setProjection(float pFov, float pAspectRatio)
{
	return glm::perspective(glm::radians(pFov), pAspectRatio, 0.001f, 1000.0f);
}

Camera::Camera(int pWidth, int pHeight, float pFov, glm::vec3 pPosition, glm::vec3 pRotation)
	:	_width(pWidth),
		_height(pHeight),
		_aspectRatio(_setAspectRatio(_width, _height)),
		_fov(pFov),
		_matrix(new glm::mat4(
			glm::translate(glm::mat4(1.0f), pPosition) *
			glm::rotate(glm::radians(pRotation.z), glm::vec3(0.0f, 0.0f, 1.0f))*
			glm::rotate(glm::radians(pRotation.y), glm::vec3(0.0f, 1.0f, 0.0f))*
			glm::rotate(glm::radians(pRotation.x), glm::vec3(1.0f, 0.0f, 0.0f)))),
		_view(new glm::mat4(1.0f)),
		_projection(new glm::mat4(
			_setProjection(_fov, _aspectRatio))),
		_viewProjection(new glm::mat4(1.0f))

{
	if (MAIN == NULL) {
		MAIN = this;
	}
}

Camera::~Camera()
{
	if (_matrix != NULL) {
		delete _matrix;
		_matrix = NULL;
	}
	if (_view != NULL) {
		delete _view;
		_view = NULL;
	}
	if (_projection != NULL) {
		delete _projection;
		_projection = NULL;
	}
	if (_viewProjection != NULL) {
		delete _viewProjection;
		_viewProjection = NULL;
	}
}

Camera* Camera::MAIN = NULL;

void Camera::clear()
{
	delete MAIN;
	MAIN = NULL;
}

glm::mat4* Camera::getMatrix()
{
	return _matrix;
}

glm::mat4* Camera::getView()
{
	*_view = glm::inverse(*_matrix);
	return _view;
}

glm::mat4* Camera::getProjection()
{
	return _projection;
}

glm::mat4* Camera::getViewProjection()
{
	*_viewProjection = *_projection * *getView();
	return _viewProjection;
}

int Camera::getWidth()
{
	return _width;
}

int Camera::getHeight()
{
	return _height;
}

float Camera::getFov()
{
	return _fov;
}

float Camera::getAspectRatio()
{
	return _aspectRatio;
}

void Camera::setFov(float pFov)
{
	_fov = pFov;
	_setProjection(_fov, _aspectRatio);
}

void Camera::setAspectRatio(int pWidth, int pHeight)
{
	_aspectRatio = _setAspectRatio(pWidth, pHeight);
	_setProjection(_fov, _aspectRatio);
}

void Camera::update(float pElapsedTime)
{
	pElapsedTime *= 10;

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
		*_matrix =
			glm::translate(glm::vec3(glm::vec3((*_matrix)[3]) + _movementDirection * pElapsedTime)) *
			glm::rotate(glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::rotate(glm::radians(_movementRotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::rotate(glm::radians(_movementRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

		*_viewProjection = *_projection * *getView();
		_movementDirection = glm::vec3(0.0f);
	}
}
