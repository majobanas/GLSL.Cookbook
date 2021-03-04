#include "core/Hierarchial/Drawable.h"

#include "core/Transform.h"
#include "core/Mesh.h"
#include "core/Material.h"

Drawable::Drawable(std::string pName, Transform* pTransform, std::string pModel, Material* pMaterial)
	: Collidable(pName, pTransform, pModel)
{
	//log("Drawable created");
	type = DRAWABLE;
	_material = pMaterial;
}

Drawable::~Drawable()
{
	//log("Drawable deleted");
	if (_material != NULL) {
		delete _material;
		_material = NULL;
	}
}

Material* Drawable::getMaterial()
{
	return _material;
}

void Drawable::render(glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection)
{
	// Children
	for (auto& child : children) {
		child->render(pModel, pView, pProjection);
	}
	// Self
	if (_material != NULL && _mesh != NULL && _transform != NULL) {
		_material->render(_mesh, _transform->getMatrix(), pModel, pView, pProjection);
	}
}
