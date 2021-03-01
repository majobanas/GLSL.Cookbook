#pragma once

#include "glm/glm.hpp"

#include "core/Transform.h"
#include "core/Mesh.h"
#include "core/Material.h"

class Camera;

class Object {
private:

protected:
	Transform* _transform = NULL;
	Mesh* _mesh = NULL;
	Material* _material = NULL;

public:
	Object(std::string pModel, Material* pMaterial, glm::vec3 pPosition = glm::vec3(0.0f), glm::vec3 pScale = glm::vec3(1.0f), glm::vec3 pRotation = glm::vec3(0.0f));
	~Object();

	static void create(Object* pObject);
	static void render();
	static std::vector<Object*> OBJECTS;
	static void clear();

	Transform* getTransform();
	Mesh* getMesh();
	Material* getMaterial();
};