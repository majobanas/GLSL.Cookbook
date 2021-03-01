#include "materials/PhysicalMaterial.h"

void PhysicalMaterial::_lazyInitializeShader()
{
	_aVertexHandle = _shader->getAttribLocation("vertex");
	_aNormalHandle = _shader->getAttribLocation("normal");

	_uViewHandle = _shader->getUniformLocation("view");
	_uProjectionHandle = _shader->getUniformLocation("projection");
	_uMatrixHandle = _shader->getUniformLocation("matrix");

	_uDiffuseColorHandle = _shader->getUniformLocation("diffuseColor");
	_uRoughnessHandle = _shader->getUniformLocation("roughness");
	_uMetalHandle = _shader->getUniformLocation("metal");

	_initializeLightUniforms();
}

PhysicalMaterial::PhysicalMaterial(glm::vec3 pDiffuseColor, float pRoughness, bool pMetal)
	:	Material("physical"),
		_diffuseColor(pDiffuseColor),
		_roughness(pRoughness),
		_metal(pMetal)
{
	_lazyInitializeShader();
}

PhysicalMaterial::~PhysicalMaterial()
{
}

void PhysicalMaterial::render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection)
{
	_shader->use();

	_shader->setUniform(_uViewHandle, pView);
	_shader->setUniform(_uProjectionHandle, pProjection);
	_shader->setUniform(_uMatrixHandle, pMatrix);

	_shader->setUniform(_uDiffuseColorHandle, &_diffuseColor);
	_shader->setUniform(_uRoughnessHandle, &_roughness);
	_shader->setUniform(_uMetalHandle, &_metal);

	_setLightUniforms();

	pMesh->streamToOpenGL(_aVertexHandle, _aNormalHandle, -1, -1);
}