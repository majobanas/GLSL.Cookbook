#include "core/Object.h"

#include "core/Transform.h"

#include "core/Camera.h"

Object::Object(std::string pName, std::string pModel, Material* pMaterial, glm::vec3 pPosition, glm::vec3 pScale, glm::vec3 pRotation)
	: Drawable(pName, new Transform(pPosition, pScale, pRotation), pModel, pMaterial)
{

}

Object::~Object()
{

}