#include "core/Object.h"

#include "core/Camera.h"

Object::Object(std::string pModel, Material* pMaterial, glm::vec3 pPosition, glm::vec3 pScale, glm::vec3 pRotation)
	:	_transform(new Transform(pPosition, pScale, pRotation))
{
	_mesh = Mesh::load(pModel);
	_material = pMaterial;
}

Object::~Object()
{
	if (_transform != NULL){
		delete _transform;
		_transform = NULL;
	}
	if (_mesh != NULL) {
		// do not delete, other objects owns the mesh
		_mesh = NULL;
	}
	if (_material != NULL) {
		delete _material;
		_material = NULL;
	}
}

void Object::create(Object* pObject)
{
	OBJECTS.push_back(pObject);
}

void Object::render()
{
	int i = 0;
	for (auto& object : OBJECTS) {
		object->_material->render(
			object->_mesh,
			object->_transform->getMatrix(),
			Camera::MAIN->getMatrix(),
			Camera::MAIN->getView(),
			Camera::MAIN->getProjection());
	}
}

std::vector<Object*> Object::OBJECTS = std::vector<Object*>();

void Object::clear()
{
	for (auto& object : OBJECTS) {
		delete object;
		object = NULL;
	}
	OBJECTS.clear();
}

Transform* Object::getTransform()
{
	return _transform;
}

Mesh* Object::getMesh()
{
	return _mesh;
}

Material* Object::getMaterial()
{
	return _material;
}
