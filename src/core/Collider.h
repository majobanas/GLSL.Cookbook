#pragma once

class Entity;

class Collider {

private:

protected:

	Entity* _owner = nullptr;

public:

	Collider(Entity* pOwner);
	virtual ~Collider() = 0;

};
