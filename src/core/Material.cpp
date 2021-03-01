#include "core/Material.h"

#include "core/Light.h"


void Material::_initializeLightUniforms()
{
	_uNumLightsHandle = _shader->getUniformLocation("numLights");
	_numLights = Light::LIGHTS.size();

	std::string index = "";
	Light* light = NULL;
	for (int i = 0; i < _numLights; i++) {
		index = std::to_string(i);
		light = Light::LIGHTS.at(i);
		_uLight[i][0] = _shader->getUniformLocation("light[" + index + "].type");
		_uLight[i][1] = _shader->getUniformLocation("light[" + index + "].position");
		_uLight[i][2] = _shader->getUniformLocation("light[" + index + "].color");
		_uLight[i][3] = _shader->getUniformLocation("light[" + index + "].intensity");
		_uLight[i][4] = _shader->getUniformLocation("light[" + index + "].direction");
		_uLight[i][5] = _shader->getUniformLocation("light[" + index + "].totalAngle");
		_uLight[i][6] = _shader->getUniformLocation("light[" + index + "].effectiveAngle");
	}
}

void Material::_setLightUniforms()
{

	_shader->setUniform(_uNumLightsHandle, &_numLights);
	Light* light = NULL;
	std::string index;
	for (int i = 0; i < _numLights; i++) {
		light = Light::LIGHTS.at(i);
		index = std::to_string(i);
		_shader->setUniform(_uLight[i][0], &light->getLightType());
		_shader->setUniform(_uLight[i][1], &light->getPosition());
		_shader->setUniform(_uLight[i][2], &light->getColor());
		_shader->setUniform(_uLight[i][3], &light->getIntensity());
		_shader->setUniform(_uLight[i][4], &light->getDirection());
		_shader->setUniform(_uLight[i][5], &light->getTotalAngle());
		_shader->setUniform(_uLight[i][6], &light->getEffectiveAngle());
	}
}

void Material::_initializeShadowUniform()
{
	_uShadowMapHandle = _shader->getUniformLocation("shadowMap");
}

void Material::_setShadowUniform(GLuint pLightViewProjectionHandle)
{
	glm::mat4 lightViewProjection = *Light::LIGHTS[0]->_projection * *Light::LIGHTS[0]->_view;
	_shader->setUniform(pLightViewProjectionHandle, glm::value_ptr(lightViewProjection));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Light::LIGHTS[0]->_depthMap);
	int textureSlot = 0;
	_shader->setUniform(_uShadowMapHandle, &textureSlot);
}

void Material::_bindShadowFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, Light::LIGHTS[0]->_depthMapFramebuffer);
}

void Material::_setShadowMap(int pSlot, GLuint pShadowMapHandle)
{
}

Material::Material(std::string pShader)
	:	_shader(Shader::create(pShader))
{
}

Material::~Material()
{
	if (_shader != NULL) {
		// do not delete, other object owns the shader
		_shader = NULL;
	}
}
