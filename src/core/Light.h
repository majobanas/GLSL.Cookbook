#pragma once

#include "core/Object.h"
#include "materials/BasicMaterial.h"

#include <map>
#include <vector>

#include "glm/glm.hpp"

class Camera;

class Light : public Object {
private:

protected:
	int _lightType;
	glm::vec3 _position;
	glm::vec3 _color;
	float _intensity;
	glm::vec3 _direction;
	float _totalAngle;
	float _effectiveAngle;

public:
	Light(int pLightType, glm::vec3 pPosition, glm::vec3 pColor, float pIntensity, glm::vec3 pDirection, float pTotalAngle, float pEffectiveAngle);
	virtual ~Light() = 0;

	static void create(Light* pLight);
	static void shadow();
	static void render(Camera* pCamera);
	static std::vector<Light*> LIGHTS;
	static void clear();

	int& getLightType();
	glm::vec3& getPosition();
	glm::vec3& getColor();
	float& getIntensity();
	glm::vec3& getDirection();
	float& getTotalAngle();
	float& getEffectiveAngle();

	GLuint _depthMap;
	GLuint _depthMapFramebuffer;
	const unsigned int SHADOW_WIDTH = 640;
	const unsigned int SHADOW_HEIGHT = 480;
	glm::mat4* _view;
	glm::mat4* _projection;

	Shader* _shader = NULL;

	GLuint _aVertexHandle;
	GLuint _uViewHandle;
	GLuint _uProjectionHandle;
	GLuint _uMatrixHandle;

};