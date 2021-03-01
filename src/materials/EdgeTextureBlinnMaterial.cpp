#include "materials/EdgeTextureBlinnMaterial.h"

#include "core/Renderer.h"

void EdgeTextureBlinnMaterial::_lazyInitializeShader()
{
	_aVertexHandle = _shader->getAttribLocation("vertex");
	_aNormalHandle = _shader->getAttribLocation("normal");
	_aUVHandle = _shader->getAttribLocation("uv");

	_uViewHandle = _shader->getUniformLocation("view");
	_uProjectionHandle = _shader->getUniformLocation("projection");
	_uMatrixHandle = _shader->getUniformLocation("matrix");

	_uPassHandle = _shader->getUniformLocation("pass");
	_uEdgeColorHandle = _shader->getUniformLocation("edgeColor");
	_uShinenessHandle = _shader->getUniformLocation("shineness");


	_uDiffuseTextureHandle = _shader->getUniformLocation("diffuseTexture");
	_uRenderTextureHandle = _shader->getUniformLocation("renderTexture");

	_initializeLightUniforms();
}

EdgeTextureBlinnMaterial::EdgeTextureBlinnMaterial(glm::vec3 pEdgeColor, float pShineness)
	:	Material("edgeTexBlin"),
		_edgeColor(pEdgeColor),
		_shineness(pShineness),
		_diffuseTexture(Texture::loadTexture2D("brick1.jpg"))
{
	_lazyInitializeShader();

	_frameBuffer = new FrameBuffer();
	_frameBuffer->bind();
	_renderTexture = Texture::createRenderTexture(_diffuseTexture->getWidth(), _diffuseTexture->getHeight());
	_frameBuffer->attachTexture2D(GL_COLOR_ATTACHMENT0, _renderTexture->getHandle());

	_depthBuffer = new DepthBuffer();
	_depthBuffer->bind();
	_depthBuffer->allocate(_diffuseTexture->getWidth(), _diffuseTexture->getHeight());

	_frameBuffer->attachDepthBuffer(_depthBuffer->getHandle());
	GLenum drawbuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawbuffers);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

EdgeTextureBlinnMaterial::~EdgeTextureBlinnMaterial()
{
	if (_renderTexture != NULL) {
		// dont delete, it belongs to other object
		_renderTexture = NULL;
	}
	if (_frameBuffer != NULL) {
		delete _frameBuffer;
		_frameBuffer = NULL;
	}
	if (_depthBuffer != NULL) {
		delete _depthBuffer;
		_depthBuffer = NULL;
	}
}

void EdgeTextureBlinnMaterial::render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection)
{
	int pass = 1;
	_shader->use();

	// Pass 1
	// Render to texture
	_frameBuffer->bind();
	_frameBuffer->clear();

	_shader->setUniform(_uViewHandle, pView);
	_shader->setUniform(_uProjectionHandle, pProjection);
	_shader->setUniform(_uMatrixHandle, pMatrix);

	_shader->setUniform(_uPassHandle, &pass);

	_diffuseTexture->activate(GL_TEXTURE0);
	_diffuseTexture->bind();
	int textureSlot = 0;
	_shader->setUniform(_uDiffuseTextureHandle, &textureSlot);

	pMesh->streamToOpenGL(_aVertexHandle, -1, _aUVHandle, -1);

	// Pass 2
	// Render object in scene
	Renderer::MAIN->bindDefaultFrameBuffer();

	_shader->setUniform(_uViewHandle, pView);
	_shader->setUniform(_uProjectionHandle, pProjection);
	_shader->setUniform(_uMatrixHandle, pMatrix);
	pass = 2;
	_shader->setUniform(_uPassHandle, &pass);

	_shader->setUniform(_uEdgeColorHandle, &_edgeColor);
	_shader->setUniform(_uShinenessHandle, &_shineness);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _renderTexture->getHandle());
	textureSlot = 0;
	_shader->setUniform(_uRenderTextureHandle, &textureSlot);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getHandle());
	textureSlot = 1;
	_shader->setUniform(_uDiffuseTextureHandle, &textureSlot);

	_setLightUniforms();

	pMesh->streamToOpenGL(_aVertexHandle, _aNormalHandle, _aUVHandle, -1);
}