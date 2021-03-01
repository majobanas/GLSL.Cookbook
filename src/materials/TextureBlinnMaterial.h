#pragma once

#include "core/Material.h"
#include "core/Texture.h"

class TextureBlinnMaterial : public Material {
private:
	void _lazyInitializeShader() override;

	float _shineness;
	Texture* _diffuseTexture = NULL;

	// Shader -----------------------
	GLuint _aVertexHandle;
	GLuint _aNormalHandle;
	GLuint _aUVHandle;

	GLuint _uViewHandle;
	GLuint _uProjectionHandle;
	GLuint _uMatrixHandle;

	GLuint _uShinenessHandle;
	GLuint _uDiffuseTextureHandle;
	// ------------------------------

protected:

public:
	TextureBlinnMaterial(std::string pTexture, float pShineness = 20.0f);
	~TextureBlinnMaterial() override;

	void render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection) override;

};