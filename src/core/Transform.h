#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
//#include "glm/gtc/matrix_transform.hpp"

class Transform {
private:
	glm::mat4* _matrix = NULL;

public:
	Transform(glm::vec3 pPosition = glm::vec3(0.0f), glm::vec3 pScale = glm::vec3(1.0f), glm::vec3 pRotation = glm::vec3(0.0f));
	~Transform();

	glm::mat4* getMatrix();
};
