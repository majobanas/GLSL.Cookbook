#pragma once

#include "core/Hierarchial/Entity.h"

class Transform;

class Transformable : public Entity {

private:

protected:
	Transform* _transform = NULL;

public:

	Transformable(std::string pName, Transform* pTransform);
	virtual ~Transformable() override;

	Transform* getTransform() override;
};