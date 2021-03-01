#include "materials/TextureBlinnMaterial.h"

void TextureBlinnMaterial::_lazyInitializeShader()
{
	_aVertexHandle = _shader->getAttribLocation("vertex");
	_aNormalHandle = _shader->getAttribLocation("normal");
	_aUVHandle = _shader->getAttribLocation("uv");

	_uViewHandle = _shader->getUniformLocation("view");
	_uProjectionHandle = _shader->getUniformLocation("projection");
	_uMatrixHandle = _shader->getUniformLocation("matrix");

	_uShinenessHandle = _shader->getUniformLocation("shineness");
	_uDiffuseTextureHandle = _shader->getUniformLocation("diffuseTexture");

	_initializeLightUniforms();
}

TextureBlinnMaterial::TextureBlinnMaterial(std::string pTexture, float pShineness)
	:	Material("texBlin"),
		_shineness(pShineness),
		_diffuseTexture(Texture::loadTexture2D(pTexture))
{
	_lazyInitializeShader();
}

TextureBlinnMaterial::~TextureBlinnMaterial()
{
	if (_diffuseTexture != NULL) {
		// dont delete, it belongs to other object
		_diffuseTexture = NULL;
	}
}

void TextureBlinnMaterial::render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection)
{
	_shader->use();

	_shader->setUniform(_uViewHandle, pView);
	_shader->setUniform(_uProjectionHandle, pProjection);
	_shader->setUniform(_uMatrixHandle, pMatrix);

	_shader->setUniform(_uShinenessHandle, &_shineness);

	_diffuseTexture->activate(GL_TEXTURE0);
	_diffuseTexture->bind();
	int textureSlot = 0;
	_shader->setUniform(_uDiffuseTextureHandle, &textureSlot);

	_setLightUniforms();

	pMesh->streamToOpenGL(_aVertexHandle, _aNormalHandle, _aUVHandle, -1);
}