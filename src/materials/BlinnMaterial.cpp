#include "materials/BlinnMaterial.h"

void BlinnMaterial::_lazyInitializeShader()
{
	_aVertexHandle = _shader->getAttribLocation("vertex");
	_aNormalHandle = _shader->getAttribLocation("normal");

	_uViewHandle = _shader->getUniformLocation("view");
	_uProjectionHandle = _shader->getUniformLocation("projection");
	_uMatrixHandle = _shader->getUniformLocation("matrix");

	_uShinenessHandle = _shader->getUniformLocation("shineness");
	_uDiffuseColorHandle = _shader->getUniformLocation("diffuseColor");

	_initializeLightUniforms();
}

BlinnMaterial::BlinnMaterial(glm::vec3 pDiffuseColor, float pShineness)
	:	Material("blinn"),
		_shineness(pShineness),
		_diffuseColor(pDiffuseColor)
{
	_lazyInitializeShader();
}

BlinnMaterial::~BlinnMaterial()
{
}

void BlinnMaterial::render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection)
{
	_shader->use();

	_shader->setUniform(_uViewHandle, pView);
	_shader->setUniform(_uProjectionHandle, pProjection);
	_shader->setUniform(_uMatrixHandle, pMatrix);

	_shader->setUniform(_uShinenessHandle, &_shineness);
	_shader->setUniform(_uDiffuseColorHandle, &_diffuseColor);

	_setLightUniforms();

	pMesh->streamToOpenGL(_aVertexHandle, _aNormalHandle, -1, -1);
}