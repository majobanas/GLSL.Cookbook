#pragma once

#include "core/Material.h"

class BlinnMaterial : public Material {
private:
	void _lazyInitializeShader() override;

	float _shineness;
	glm::vec3 _diffuseColor;

	// Shader -----------------------
	GLuint _aVertexHandle;
	GLuint _aNormalHandle;

	GLuint _uViewHandle;
	GLuint _uProjectionHandle;
	GLuint _uMatrixHandle;

	GLuint _uShinenessHandle;
	GLuint _uDiffuseColorHandle;
	// ------------------------------

protected:

public:
	BlinnMaterial(glm::vec3 pDiffuseColor = glm::vec3(1.0f), float pShineness = 20.0f);
	~BlinnMaterial() override;

	void render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection) override;

};