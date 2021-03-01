#include "materials/DeferredMaterial.h"

void DeferredMaterial::_lazyInitializeShader()
{
	_aVertexHandle = _shader->getAttribLocation("vertex");
	_aNormalHandle = _shader->getAttribLocation("normal");
	_aUVHandle = _shader->getAttribLocation("uv");

	_uViewHandle = _shader->getUniformLocation("view");
	_uProjectionHandle = _shader->getUniformLocation("projection");
	_uMatrixHandle = _shader->getUniformLocation("matrix");

	_uDiffuseTextureHandle = _shader->getUniformLocation("diffuseTexture");
}

DeferredMaterial::DeferredMaterial(std::string pTexture)
	: Material("deferred"),
	_diffuseTexture(Texture::loadTexture2D(pTexture))
{
	_lazyInitializeShader();
}

DeferredMaterial::~DeferredMaterial()
{
	if (_diffuseTexture != NULL) {
		// dont delete, it belongs to other object
		_diffuseTexture = NULL;
	}
}

void DeferredMaterial::render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection)
{
	_shader->use();

	_shader->setUniform(_uViewHandle, pView);
	_shader->setUniform(_uProjectionHandle, pProjection);
	_shader->setUniform(_uMatrixHandle, pMatrix);

	_diffuseTexture->activate(GL_TEXTURE0);
	_diffuseTexture->bind();
	int textureSlot = 0;
	_shader->setUniform(_uDiffuseTextureHandle, &textureSlot);

	pMesh->streamToOpenGL(_aVertexHandle, _aNormalHandle, _aUVHandle, -1);
}
