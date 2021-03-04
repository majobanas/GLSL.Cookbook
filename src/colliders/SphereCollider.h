#pragma once

//#include "core/Collider.h"

class Entity;

class SphereCollider /*: public Collider*/ {

private:
	int _radius;

protected:

public:

	SphereCollider(Entity* pOwner, int pRadius);
	~SphereCollider() /*override*/;
};