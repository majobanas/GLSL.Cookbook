#pragma once

#include <vector>

#include "core/Hierarchial/Drawable.h"

//#include "core/Object.h"
//#include "core/Camera.h"
#include "core/Texture.h"

#include "materials/BasicMaterial.h"
#include "materials/LitMaterial.h"
#include "materials/PhongMaterial.h"
#include "materials/BlinnMaterial.h"
#include "materials/CartoonMaterial.h"
#include "materials/PhysicalMaterial.h"
#include "materials/TextureMaterial.h"
#include "materials/TextureBlinnMaterial.h"
#include "materials/SkyboxMaterial.h"
#include "materials/ReflectionCubemapTextureBlinnMaterial.h"
#include "materials/RefractionCubemapTextureBlinnMaterial.h"
#include "materials/LightsourceCubemapTextureMaterial.h"
#include "materials/RenderTextureMaterial.h"
#include "materials/EdgeTextureBlinnMaterial.h"

#include "materials/DeferredMaterial.h"

#include "core/Light.h"
#include "lights/DirectionalLight.h"
#include "lights/PointLight.h"
#include "lights/SpotLight.h"


class Scene : public Transformable {
private:

protected:

public:
	Scene(std::string pName, Transform* pTransform);
	virtual ~Scene() = 0;

	virtual void populate() = 0;

	void update(float pElapsedTime);
};