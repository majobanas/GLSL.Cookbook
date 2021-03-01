#pragma once

#include "core/Light.h"

class PointLight : public Light {
private:

public:
	PointLight(glm::vec3 pColor, float pIntensity, glm::vec3 pPosition, float pTotalAngle = 0.0f, float pEffectiveAngle = 0.0f, glm::vec3 pDirection = glm::vec3(0.0f), int pLightType = 1);
	~PointLight();
};