#include "core/Hierarchial/Transformable.h"

#include "core/Transform.h"

Transformable::Transformable(std::string pName, Transform* pTransform) 
	: Entity(pName)
{
	type = TRANSFORMABLE;
	//log("Transformable created");
	_transform = pTransform;
}

Transformable::~Transformable()
{
	//log("Transformable deleted");
	if (_transform != NULL) {
		delete _transform;
		_transform = NULL;
	}
}

Transform* Transformable::getTransform()
{
	return _transform;
}