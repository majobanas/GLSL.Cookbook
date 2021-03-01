#pragma once

#include <vector>

#include "core/Object.h"
#include "core/Camera.h"
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


class Scene {
private:

protected:

public:
	Scene();
	virtual ~Scene();
};