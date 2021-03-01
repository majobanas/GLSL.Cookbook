#pragma once

#include "core/Material.h"
#include "core/Texture.h"

class LightsourceCubemapTextureMaterial : public Material {
private:
	void _lazyInitializeShader() override;

	Texture* _diffuseTexture = NULL;
	Texture* _cubemapTexture = NULL;

	// Shader -----------------------
	GLuint _aVertexHandle;
	GLuint _aNormalHandle;
	GLuint _aUVHandle;

	GLuint _uModelHandle;
	GLuint _uViewHandle;
	GLuint _uProjectionHandle;
	GLuint _uMatrixHandle;

	GLuint _uDiffuseTextureHandle;
	GLuint _uCubemapTextureHandle;
	// ------------------------------

protected:

public:
	LightsourceCubemapTextureMaterial(std::string pTexture, Texture* pSkybox);
	~LightsourceCubemapTextureMaterial() override;

	void render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection) override;

};