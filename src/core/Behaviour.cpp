#include "core/Behaviour.h"

#include "core/Hierarchial/Entity.h"

Behaviour::Behaviour(Entity* pOwner)
{
	owner = pOwner;
}

Behaviour::~Behaviour()
{
	if (owner != NULL) {
		// do not delete, owned by other object
		owner = NULL;
	}
}
