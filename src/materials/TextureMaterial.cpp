#include "materials/TextureMaterial.h"

void TextureMaterial::_lazyInitializeShader()
{
	_aVertexHandle = _shader->getAttribLocation("vertex");
	_aUVHandle = _shader->getAttribLocation("uv");

	_uViewHandle = _shader->getUniformLocation("view");
	_uProjectionHandle = _shader->getUniformLocation("projection");
	_uMatrixHandle = _shader->getUniformLocation("matrix");

	_uDiffuseTextureHandle = _shader->getUniformLocation("diffuseTexture");
}

TextureMaterial::TextureMaterial(std::string pTexture)
	:	Material("texture"),
		_diffuseTexture(Texture::loadTexture2D(pTexture))
{
	_lazyInitializeShader();
}

TextureMaterial::~TextureMaterial()
{
	if (_diffuseTexture != NULL) {
		// dont delete, it belongs to other object
		_diffuseTexture = NULL;
	}
}

void TextureMaterial::render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection)
{
	_shader->use();

	_shader->setUniform(_uViewHandle, pView);
	_shader->setUniform(_uProjectionHandle, pProjection);
	_shader->setUniform(_uMatrixHandle, pMatrix);

	_diffuseTexture->activate(GL_TEXTURE0);
	_diffuseTexture->bind();
	int textureSlot = 0;
	_shader->setUniform(_uDiffuseTextureHandle, &textureSlot);

	pMesh->streamToOpenGL(_aVertexHandle, -1, _aUVHandle, -1);
}
