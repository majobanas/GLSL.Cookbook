#include "lights/PointLight.h"

PointLight::PointLight(glm::vec3 pColor, float pIntensity, glm::vec3 pPosition, float pTotalAngle, float pEffectiveAngle, glm::vec3 pDirection, int pLightType)
	:	Light(pLightType, pPosition, pColor, pIntensity, pDirection, pTotalAngle, pEffectiveAngle)
{

}

PointLight::~PointLight()
{

}
