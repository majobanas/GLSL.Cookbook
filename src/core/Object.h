#pragma once

#include "glm/glm.hpp"

#include "core/Hierarchial/Drawable.h"

class Transform;

class Camera;

class Object : public Drawable {
private:

protected:

public:
	Object(std::string pName, std::string pModel, Material* pMaterial, glm::vec3 pPosition = glm::vec3(0.0f), glm::vec3 pScale = glm::vec3(1.0f), glm::vec3 pRotation = glm::vec3(0.0f));
	~Object() override;

};