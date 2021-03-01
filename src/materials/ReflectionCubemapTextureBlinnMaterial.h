#pragma once

#include "core/Material.h"
#include "core/Texture.h"

class ReflectionCubemapTextureBlinnMaterial : public Material {
private:
	void _lazyInitializeShader() override;

	float _shineness;
	Texture* _diffuseTexture = NULL;
	float _reflectionFactor;
	Texture* _cubemapTexture = NULL;

	// Shader -----------------------
	GLuint _aVertexHandle;
	GLuint _aNormalHandle;
	GLuint _aUVHandle;

	GLuint _uModelHandle;
	GLuint _uViewHandle;
	GLuint _uProjectionHandle;
	GLuint _uMatrixHandle;

	GLuint _uShinenessHandle;
	GLuint _uDiffuseTextureHandle;
	GLuint _uReflectionFactorHandle;
	GLuint _uCubemapTextureHandle;
	// ------------------------------

protected:

public:
	ReflectionCubemapTextureBlinnMaterial(float pReflectionFactor, std::string pTexture, Texture* pSkybox, float pShineness = 20.0f);
	~ReflectionCubemapTextureBlinnMaterial() override;

	void render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection) override;

};