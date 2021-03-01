#pragma once

#include "core/Material.h"
#include "core/Texture.h"
#include "core/Transform.h"
#include "core/Object.h"

#include"core/OpenGL/FrameBuffer.h"
#include"core/OpenGL/DepthBuffer.h"


class EdgeTextureBlinnMaterial : public Material {
private:
	void _lazyInitializeShader() override;

	glm::vec3 _edgeColor;
	float _shineness;

	Texture* _renderTexture = NULL;
	Texture* _diffuseTexture = NULL;

	// Shader

	GLuint _aVertexHandle;
	GLuint _aNormalHandle;
	GLuint _aUVHandle;

	GLuint _uViewHandle;
	GLuint _uProjectionHandle;
	GLuint _uMatrixHandle;

	GLuint _uPassHandle;
	GLuint _uEdgeColorHandle;
	GLuint _uShinenessHandle;


	GLuint _uDiffuseTextureHandle;
	GLuint _uRenderTextureHandle;
	//

	FrameBuffer* _frameBuffer = NULL;
	DepthBuffer* _depthBuffer = NULL;

protected:

public:
	EdgeTextureBlinnMaterial(glm::vec3 pEdgeColor = glm::vec3(1.0f), float pShineness = 20.0f);
	~EdgeTextureBlinnMaterial() override;

	void render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection) override;

};
