#include "core/Collider.h"

#include "core/Hierarchial/Entity.h"

Collider::Collider(Entity* pOwner)
{
	_owner = pOwner;
}
