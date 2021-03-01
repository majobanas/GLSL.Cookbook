#include "materials/LitMaterial.h"

void LitMaterial::_lazyInitializeShader()
{
	_aVertexHandle = _shader->getAttribLocation("vertex");
	_aNormalHandle = _shader->getAttribLocation("normal");

	_uViewHandle = _shader->getUniformLocation("view");
	_uProjectionHandle = _shader->getUniformLocation("projection");
	_uMatrixHandle = _shader->getUniformLocation("matrix");

	_uDiffuseColorHandle = _shader->getUniformLocation("diffuseColor");

	_initializeLightUniforms();
	_initializeShadowUniform();
}

LitMaterial::LitMaterial(glm::vec3 pDiffuseColor)
	:	Material("lit"),
		_diffuseColor(pDiffuseColor)
{
	_lazyInitializeShader();
}

LitMaterial::~LitMaterial()
{
}

void LitMaterial::render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection)
{
	_shader->use();

	_shader->setUniform(_uViewHandle, pView);
	_shader->setUniform(_uProjectionHandle, pProjection);
	_shader->setUniform(_uMatrixHandle, pMatrix);

	_shader->setUniform(_uDiffuseColorHandle, &_diffuseColor);

	_setLightUniforms();
	_setShadowUniform(_shader->getUniformLocation("lightViewProjection"));

	pMesh->streamToOpenGL(_aVertexHandle, _aNormalHandle, -1, -1);
}
