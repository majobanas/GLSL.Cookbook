#pragma once

#include "core/Light.h"

class DirectionalLight : public Light {
private:

public:
	DirectionalLight(glm::vec3 pColor, float pIntensity, glm::vec3 pDirection, float pTotalAngle = 0.0f, float pEffectiveAngle = 0.0f, glm::vec3 pPosition = glm::vec3(0.0f), int pLightType = 0);
	~DirectionalLight() override;
};
