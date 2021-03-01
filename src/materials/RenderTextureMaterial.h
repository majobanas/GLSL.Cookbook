#pragma once

#include "core/Material.h"
#include "core/Texture.h"
#include "core/Transform.h"
#include "core/Object.h"

#include"core/OpenGL/FrameBuffer.h"
#include"core/OpenGL/DepthBuffer.h"


class RenderTextureMaterial : public Material {
private:
	void _lazyInitializeShader() override;

	glm::mat4* _eyeModel = NULL;
	int _textureHeight;
	int _textureWidth;
	Texture* _renderTexture = NULL;

	// Shader -----------------------
	GLuint _aVertexHandle;
	GLuint _aUVHandle;

	GLuint _uViewHandle;
	GLuint _uProjectionHandle;
	GLuint _uMatrixHandle;

	GLuint _uDiffuseTextureHandle;
	// ------------------------------

	FrameBuffer* _frameBuffer = NULL;
	DepthBuffer* _depthBuffer = NULL;

protected:

public:
	RenderTextureMaterial(int pWidth, int pHeight, glm::mat4* pModel);
	~RenderTextureMaterial() override;

	void render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection) override;

	static void render(glm::mat4* pModel, glm::mat4* pProjection);
	static std::vector<RenderTextureMaterial*> RENDERTEXTUREMATERIAL;

};
