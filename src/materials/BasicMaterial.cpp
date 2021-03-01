#include "materials/BasicMaterial.h"

void BasicMaterial::_lazyInitializeShader()
{
	_aVertexHandle = _shader->getAttribLocation("vertex");

	_uViewHandle = _shader->getUniformLocation("view");
	_uProjectionHandle = _shader->getUniformLocation("projection");
	_uMatrixHandle = _shader->getUniformLocation("matrix");

	_uDiffuseColorHandle = _shader->getUniformLocation("diffuseColor");
}

BasicMaterial::BasicMaterial(glm::vec3 pDiffuseColor)
	:	Material("basic"),
		_diffuseColor(pDiffuseColor)
{
	_lazyInitializeShader();
}

BasicMaterial::~BasicMaterial()
{
}

void BasicMaterial::render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection)
{
	_shader->use();

	_shader->setUniform(_uViewHandle, pView);
	_shader->setUniform(_uProjectionHandle, pProjection);
	_shader->setUniform(_uMatrixHandle, pMatrix);

	_shader->setUniform(_uDiffuseColorHandle, &_diffuseColor);

	pMesh->streamToOpenGL(_aVertexHandle, -1, -1, -1);
}
