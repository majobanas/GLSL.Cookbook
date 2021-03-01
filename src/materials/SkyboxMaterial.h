#pragma once

#include "core/Material.h"
#include "core/Texture.h"

class SkyboxMaterial : public Material {
private:
	void _lazyInitializeShader() override;

	Texture* _cubemapTexture = NULL;

	// Shader -----------------------
	GLuint _aVertexHandle;

	GLuint _uViewHandle;
	GLuint _uProjectionHandle;
	GLuint _uMatrixHandle;

	GLuint _uCubemapTextureHandle;
	// ------------------------------

protected:

public:
	SkyboxMaterial(std::string pCubemap, std::string pExtension);
	~SkyboxMaterial() override;

	Texture* getTexture();

	void render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection) override;

};