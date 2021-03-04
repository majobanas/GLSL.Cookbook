#include "core/Light.h"

#include "core/Camera.h"
#include "core/Scene.h"

Light::Light(int pLightType, glm::vec3 pPosition, glm::vec3 pColor, float pIntensity, glm::vec3 pDirection, float pTotalAngle, float pEffectiveAngle)
	:	Object("Light" + std::to_string(pLightType), "cube_flat.obj", new BasicMaterial(pColor), pPosition),
		_lightType(pLightType),
		_position(pPosition),
		_color(pColor),
		_intensity(pIntensity),
		_direction(pDirection),
		_totalAngle(glm::cos(glm::radians(pTotalAngle))),
		_effectiveAngle(glm::cos(glm::radians(pEffectiveAngle))),
		_projection(new glm::mat4(glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, 0.001f, 1000.0f)))
{
	_view = new glm::mat4(
		glm::lookAt(glm::vec3(0.0f, 1.0f, 1.0f),
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(0.0f, 1.0f, 0.0f)));

	glGenFramebuffers(1, &_depthMapFramebuffer);

	glGenTextures(1, &_depthMap);
	glBindTexture(GL_TEXTURE_2D, _depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, _depthMapFramebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	_shader = Shader::create("shadow");
	_aVertexHandle = _shader->getAttribLocation("vertex");
	_uViewHandle = _shader->getUniformLocation("view");
	_uProjectionHandle = _shader->getUniformLocation("projection");
	_uMatrixHandle = _shader->getUniformLocation("matrix");

}

Light::~Light()
{
	if (_shader != NULL) {
		// do not delete, belongs to other object
		_shader = NULL;
	}
}

void Light::shadow(Scene* pScene)
{
	for (auto& light : LIGHTS) {
		glViewport(0, 0, light->SHADOW_WIDTH, light->SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, light->_depthMapFramebuffer);
		glClear(GL_DEPTH_BUFFER_BIT);
		light->_shader->use();

		light->_shader->setUniform(light->_uViewHandle, light->_view);
		light->_shader->setUniform(light->_uProjectionHandle, light->_projection);
		
		for (auto& child : pScene->children) {
			if (child->type == COLLIDABLE) {
				light->_shader->setUniform(light->_uMatrixHandle, child->getTransform()->getMatrix());
				child->getMesh()->streamToOpenGL(light->_aVertexHandle, -1, -1, -1);
			}
		}
	}
	
}

void Light::render(Camera* pCamera)
{
	for (auto& light : LIGHTS) {
		light->_material->render(
			light->_mesh,
			light->_transform->getMatrix(),
			pCamera->getTransform()->getMatrix(),
			pCamera->getView(),
			pCamera->getProjection());
	}
}

std::vector<Light*> Light::LIGHTS = std::vector<Light*>();

void Light::clear()
{
	for (auto& light : LIGHTS) {
		// do not delete, owned by Scene
		light = NULL;
	}
	LIGHTS.clear();
}


int& Light::getLightType()
{
	return _lightType;
}

glm::vec3& Light::getPosition()
{
	return _position;
}

glm::vec3& Light::getColor()
{
	return _color;
}

float& Light::getIntensity()
{
	return _intensity;
}

glm::vec3& Light::getDirection()
{
	return _direction;
}

float& Light::getTotalAngle()
{
	return _totalAngle;
}

float& Light::getEffectiveAngle()
{
	return _effectiveAngle;
}
