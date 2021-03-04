#pragma once

#include "core/Hierarchial/Collidable.h"

class Transform;
class Mesh;
class Material;

class Drawable : public Collidable {

private:

protected:
	Material* _material = NULL;

public:

	Drawable(std::string pName, Transform* pTransform, std::string pModel, Material* pMaterial);
	virtual ~Drawable() override;

	Material* getMaterial();

	void render(glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection);
};