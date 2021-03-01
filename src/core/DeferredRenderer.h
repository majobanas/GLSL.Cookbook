#pragma once
#include "core/Renderer.h"

#include "core/OpenGL/VertexBuffer.h"
#include "core/OpenGL/NormalBuffer.h"
#include "core/OpenGL/UVBuffer.h"
#include "core/OpenGL/IndexBuffer.h"

#include "core/Shader.h"

#include "core/OpenGL/FrameBuffer.h"
#include "core/OpenGL/DepthBuffer.h"
#include "core/RenderTexture.h"

class DeferredRenderer : public Renderer {
private:
	VertexBuffer* _vertexBuffer = NULL;
	UVBuffer* _uvBuffer = NULL;
	IndexBuffer* _indexBuffer = NULL;

	Shader* _shader = NULL;

	GLuint _aVertexHandle;
	GLuint _aUVHandle;

	GLuint _uPositionTexture;
	GLuint _uNormalTexture;
	GLuint _uColorTexture;
	
	FrameBuffer* _frameBuffer = NULL;
	DepthBuffer* _depthBuffer = NULL;

	Texture* _positionTexture = NULL;
	Texture* _normalTexture = NULL;
	Texture* _colorTexture = NULL;

	void _initializeQuad();
	void _initializeShader();
	void _streamQuadToOpenGL();

public:
	DeferredRenderer(int pWidth, int pHeight);
	~DeferredRenderer() override;

	void render(Scene* pScene) override;
};