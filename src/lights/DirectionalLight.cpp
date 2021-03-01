#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 pColor, float pIntensity, glm::vec3 pDirection, float pTotalAngle, float pEffectiveAngle, glm::vec3 pPosition, int pLightType)
	:	Light(pLightType, pPosition, pColor, pIntensity, pDirection, pTotalAngle, pEffectiveAngle)
{
}

DirectionalLight::~DirectionalLight()
{
}
