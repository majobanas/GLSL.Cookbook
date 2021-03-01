#pragma once

#include "core/Material.h"

class PhysicalMaterial : public Material {
private:
	void _lazyInitializeShader() override;

	glm::vec3 _diffuseColor;
	float _roughness;
	bool _metal;

	// Shader -----------------------
	GLuint _aVertexHandle;
	GLuint _aNormalHandle;

	GLuint _uViewHandle;
	GLuint _uProjectionHandle;
	GLuint _uMatrixHandle;

	GLuint _uDiffuseColorHandle;
	GLuint _uRoughnessHandle;
	GLuint _uMetalHandle;
	// ------------------------------

protected:

public:
	PhysicalMaterial(glm::vec3 pDiffuseColor = glm::vec3(1.0f), float pRoughness = 0.0f, bool pMetal = false);
	~PhysicalMaterial() override;

	void render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection) override;

};