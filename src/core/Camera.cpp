#include "core/Camera.h"

#include "glm/gtx/string_cast.hpp"
//#include "glm/gtx/rotate_vector.hpp"

//#include "input/Mouse.h"
//#include "input/Keyboard.h"
#include "core/Transform.h"

float Camera::_setAspectRatio(int pWidth, int pHeight)
{
	return (float)pWidth / (float) pHeight;
}

glm::mat4 Camera::_setProjection(float pFov, float pAspectRatio)
{
	return glm::perspective(glm::radians(pFov), pAspectRatio, 0.001f, 1000.0f);
}

Camera::Camera(int pWidth, int pHeight, float pFov, glm::vec3 pPosition, glm::vec3 pRotation)
	: Transformable("camera", new Transform(pPosition, glm::vec3(1.0f), pRotation))
{
	_width = pWidth;
	_height = pHeight;
	_aspectRatio = _setAspectRatio(_width, _height);
	_fov = pFov;
	
	_view = new glm::mat4(1.0f);
	_projection = new glm::mat4(_setProjection(_fov, _aspectRatio));
	_viewProjection = new glm::mat4(1.0f);


	if (MAIN == NULL) {
		MAIN = this;
	}
}

Camera::~Camera()
{
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
	if (MAIN != NULL) {
		// do not delete, owned by Scene
		MAIN = NULL;
	}
}

glm::mat4* Camera::getView()
{
	*_view = glm::inverse(*getTransform()->getMatrix());
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
