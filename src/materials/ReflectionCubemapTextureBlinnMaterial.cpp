#include "materials/ReflectionCubemapTextureBlinnMaterial.h"

void ReflectionCubemapTextureBlinnMaterial::_lazyInitializeShader()
{
	_aVertexHandle = _shader->getAttribLocation("vertex");
	_aNormalHandle = _shader->getAttribLocation("normal");
	_aUVHandle = _shader->getAttribLocation("uv");

	_uModelHandle = _shader->getUniformLocation("model");
	_uViewHandle = _shader->getUniformLocation("view");
	_uProjectionHandle = _shader->getUniformLocation("projection");
	_uMatrixHandle = _shader->getUniformLocation("matrix");

	_uShinenessHandle = _shader->getUniformLocation("shineness");
	_uDiffuseTextureHandle = _shader->getUniformLocation("diffuseTexture");
	_uReflectionFactorHandle = _shader->getUniformLocation("reflectionFactor");
	_uCubemapTextureHandle = _shader->getUniformLocation("cubemapTexture");

	_initializeLightUniforms();
}

ReflectionCubemapTextureBlinnMaterial::ReflectionCubemapTextureBlinnMaterial(float pReflectionFactor, std::string pTexture, Texture* pSkybox, float pShineness)
	 :	Material("refleCubeTexBlin"),
		_shineness(pShineness),
		_diffuseTexture(Texture::loadTexture2D(pTexture)),
	  	_reflectionFactor(pReflectionFactor),
		_cubemapTexture(pSkybox)
{
	_lazyInitializeShader();
}

ReflectionCubemapTextureBlinnMaterial::~ReflectionCubemapTextureBlinnMaterial()
{
	if (_diffuseTexture != NULL) {
		// dont delete, it belongs to other object
		_diffuseTexture = NULL;
	}
	if (_cubemapTexture != NULL) {
		// dont delete, it belongs to other object
		_cubemapTexture = NULL;
	}
}

void ReflectionCubemapTextureBlinnMaterial::render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection)
{
	_shader->use();

	_shader->setUniform(_uModelHandle, pModel);
	_shader->setUniform(_uViewHandle, pView);
	_shader->setUniform(_uProjectionHandle, pProjection);
	_shader->setUniform(_uMatrixHandle, pMatrix);

	_shader->setUniform(_uShinenessHandle, &_shineness);

	_diffuseTexture->activate(GL_TEXTURE0);
	_diffuseTexture->bind();
	int textureSlot = 0;
	_shader->setUniform(_uDiffuseTextureHandle, &textureSlot);

	_shader->setUniform(_uReflectionFactorHandle, &_reflectionFactor);

	_cubemapTexture->activate(GL_TEXTURE1);
	_cubemapTexture->bind();
	textureSlot = 1;
	_shader->setUniform(_uCubemapTextureHandle, &textureSlot);

	_setLightUniforms();

	pMesh->streamToOpenGL(_aVertexHandle, _aNormalHandle, _aUVHandle, -1);
}