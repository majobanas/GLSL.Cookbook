#include "colliders/SphereCollider.h"

#include "core/Hierarchial/Entity.h"

SphereCollider::SphereCollider(Entity* pOwner, int pRadius) 
	/*: Collider(pOwner)*/
{
	_radius = pRadius;
}

SphereCollider::~SphereCollider()
{
}
