#include "core/Hierarchial/Collidable.h"

#include "core/Mesh.h"
#include "core/Collider.h"

Collidable::Collidable(std::string pName, Transform* pTransform, std::string pModel)
	: Transformable(pName, pTransform)
{
	//log("Collidable created");

	type = COLLIDABLE;
	_mesh = Mesh::load(pModel);
	//_collider = new Collider();
}

Collidable::~Collidable()
{
	//log("Collidable deleted");
	if (_mesh != NULL) {
		// do not delete, Mesh class owns it
		_mesh = NULL;
	}
}

Mesh* Collidable::getMesh()
{
	return _mesh;
}

Collider* Collidable::getCollider() {
	return _collider;
}