#include "core/Scene.h"

Scene::Scene(std::string pName, Transform* pTransform)
	: Transformable(pName, pTransform)
{
	
}

Scene::~Scene()
{
}

void Scene::update(float pElapsedTime)
{
	// Update behaviours
	//std::cout << "scene update" << std::endl;
	updateBehaviours(pElapsedTime);

	// Update physics
}
