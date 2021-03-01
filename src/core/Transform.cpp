#include "core/Transform.h"

Transform::Transform(glm::vec3 pPosition, glm::vec3 pScale, glm::vec3 pRotation)
	: _matrix(new glm::mat4(
		glm::translate(pPosition) *
		glm::rotate(glm::radians(pRotation.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::rotate(glm::radians(pRotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::radians(pRotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::scale(pScale)))
{
}

Transform::~Transform()
{
	delete _matrix;
	_matrix = NULL;
}

glm::mat4* Transform::getMatrix()
{
	return _matrix;
}
