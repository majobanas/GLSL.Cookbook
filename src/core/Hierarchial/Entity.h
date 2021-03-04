#pragma once

#include <iostream>
#include <vector>

#include "glm/glm.hpp"

#include "core/Constants.h"

class Behaviour;
class Transform;
class Mesh;
class Collider;
class Material;

class Light;

class Entity {

private:

protected:


	void log(std::string pMessage);

public:
	int type;

	std::string name;

	Entity(std::string pName);
	virtual ~Entity() = 0;

	std::vector<Behaviour*> behaviours;
	void add(Behaviour* pBehaviour);

	std::vector<Entity*> children;
	void add(Entity* pChild);
	void add(Light* pLight);

	virtual void updateBehaviours(float pElapsedTime);
	virtual void resolveCollisions();
	virtual void render(glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection);

	virtual Transform* getTransform();
	virtual Mesh* getMesh();
	virtual Collider* getCollider();
	virtual Material* getMaterial();

};