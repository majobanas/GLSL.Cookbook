#pragma once

#include "core/Light.h"

class SpotLight : public Light {
private:

public:
	SpotLight(glm::vec3 pColor, float pIntensity, glm::vec3 pPosition, float pTotalAngle = 0.0f, float pEffectiveAngle = 0.0f, glm::vec3 pDirection = glm::vec3(0.0f), int pLightType = 2);
	~SpotLight();

};
