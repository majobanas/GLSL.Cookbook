#pragma once

#include "core/Hierarchial/Transformable.h"

class Mesh;
class Collider;

class Collidable : public Transformable {

private:

protected:
	Mesh* _mesh = NULL;
	Collider* _collider = NULL;

public:

	Collidable(std::string pName, Transform* pTransform, std::string pModel);
	virtual ~Collidable() override;

	Mesh* getMesh();
	Collider* getCollider();

};
