#include "materials/SkyboxMaterial.h"

void SkyboxMaterial::_lazyInitializeShader()
{
	_aVertexHandle = _shader->getAttribLocation("vertex");

	_uViewHandle = _shader->getUniformLocation("view");
	_uProjectionHandle = _shader->getUniformLocation("projection");
	_uMatrixHandle = _shader->getUniformLocation("matrix");

	_uCubemapTextureHandle = _shader->getUniformLocation("cubemapTexture");
}

SkyboxMaterial::SkyboxMaterial(std::string pCubemap, std::string pExtension)
	:	Material("skybox"),
		_cubemapTexture(Texture::loadCubemap(pCubemap, pExtension))
{
	_lazyInitializeShader();
}

SkyboxMaterial::~SkyboxMaterial()
{
	if (_cubemapTexture != NULL) {
		// dont delete, it belongs to other object
		_cubemapTexture = NULL;
	}
}

Texture* SkyboxMaterial::getTexture()
{
	return _cubemapTexture;
}

void SkyboxMaterial::render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection)
{
	_shader->use();

	_shader->setUniform(_uViewHandle, pView);
	_shader->setUniform(_uProjectionHandle, pProjection);
	_shader->setUniform(_uMatrixHandle, pMatrix);

	_cubemapTexture->activate(GL_TEXTURE0);
	_cubemapTexture->bind();
	int textureSlot = 0;
	_shader->setUniform(_uCubemapTextureHandle, &textureSlot);

	glFrontFace(GL_CW);
	pMesh->streamToOpenGL(_aVertexHandle, -1, -1, -1);
	glFrontFace(GL_CCW);
}