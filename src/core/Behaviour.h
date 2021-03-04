#pragma once

#include "glm/gtx/rotate_vector.hpp"

/*#include "input/Mouse.h"
#include "input/Keyboard.h"*/

//#include "core/Hierarchial/Entity.h"
class Entity;

class Behaviour {

private:

protected:
	Entity* owner = NULL;

public:

	Behaviour(Entity* pOwner);
	virtual ~Behaviour() = 0;

	virtual void update(float pElapsedTIme) = 0;
};