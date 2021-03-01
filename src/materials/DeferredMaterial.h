#pragma once
#include "core/Material.h"
#include "core/Texture.h"

class DeferredMaterial : public Material {
private:
	void _lazyInitializeShader() override;

	Texture* _diffuseTexture = NULL;

	// Shader

	GLuint _aVertexHandle;
	GLuint _aNormalHandle;
	GLuint _aUVHandle;

	GLuint _uViewHandle;
	GLuint _uProjectionHandle;
	GLuint _uMatrixHandle;

	GLuint _uDiffuseTextureHandle;
	//

protected:

public:
	DeferredMaterial(std::string pTexture);
	~DeferredMaterial() override;

	void render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection) override;

};