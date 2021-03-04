#include "core/Hierarchial/Entity.h"

#include "core/Behaviour.h"

#include "core/Light.h"

Entity::Entity(std::string pName) {
	//log("Entity created");
	type = ENTITY;
	name = pName;

	behaviours = std::vector<Behaviour*>();
	children = std::vector<Entity*>();
}

Entity::~Entity() {
	//log("Entity deleted");
	for (auto& behaviour : behaviours) {
		delete behaviour;
		behaviour = NULL;
	}
	children.clear();

	for (auto& child : children) {
		delete child;
		child = NULL;
	}
	children.clear();
}

void Entity::log(std::string pMessage)
{
	std::cout << pMessage << std::endl;
}

void Entity::add(Behaviour* pBehaviour)
{
	
	if (pBehaviour != NULL) {
		behaviours.push_back(pBehaviour);
	}
}

void Entity::add(Entity* pChild)
{
	if (pChild != NULL) {
		children.push_back(pChild);
	}
}

void Entity::add(Light* pLight) {
	if (pLight != NULL) {
		children.push_back(pLight);
		Light::LIGHTS.push_back(pLight);
	}
}

void Entity::updateBehaviours(float pElapsedTime)
{
	for (auto& child : children) {
		child->updateBehaviours(pElapsedTime);
	}

	for (auto& behaviour : behaviours) {
		behaviour->update(pElapsedTime);
	}
}

void Entity::resolveCollisions() {

}

void Entity::render(glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection) {

}

Transform* Entity::getTransform() {
	return NULL;
}

Mesh* Entity::getMesh() {
	return NULL;
}

Collider* Entity::getCollider() {
	return NULL;
}

Material* Entity::getMaterial() {
	return NULL;
}