#pragma once

#include "core/Material.h"

class LitMaterial : public Material {
private:
	void _lazyInitializeShader() override;

	glm::vec3 _diffuseColor;

	// Shader -----------------------
	GLuint _aVertexHandle;
	GLuint _aNormalHandle;

	GLuint _uViewHandle;
	GLuint _uProjectionHandle;
	GLuint _uMatrixHandle;

	GLuint _uDiffuseColorHandle;
	// ------------------------------

protected:

public:
	LitMaterial(glm::vec3 pDiffuseColor = glm::vec3(1.0f));
	~LitMaterial() override;

	void render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection) override;

};
