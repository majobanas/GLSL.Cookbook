#pragma once

#include "core/Material.h"

class CartoonMaterial : public Material {
private:
	void _lazyInitializeShader() override;

	glm::vec3 _diffuseColor;
	int _levels;

	// Shader

	GLuint _aVertexHandle;
	GLuint _aNormalHandle;

	GLuint _uViewHandle;
	GLuint _uProjectionHandle;
	GLuint _uMatrixHandle;

	GLuint _uDiffuseColorHandle;
	GLuint _uLevelsHandle;
	//

protected:

public:
	CartoonMaterial(glm::vec3 pDiffuseColor = glm::vec3(1.0f), int pLevels = 10);
	~CartoonMaterial() override;

	void render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection) override;

};
