#include "core/DeferredRenderer.h"

void DeferredRenderer::_initializeQuad()
{
	_vertexBuffer = new VertexBuffer();
	_uvBuffer = new UVBuffer();
	_indexBuffer = new IndexBuffer();

	std::vector<glm::vec3> vertices = {
		{ -1.0f, 1.0f, 0.0f },
		{ -1.0f, -1.0f, 0.0f },
		{ 1.0f, -1.0f, 0.0f },
		{ 1.0f, 1.0f, 0.0f }
	};
	for (auto& vertex : vertices)
		_vertexBuffer->add(vertex);

	std::vector<glm::vec2> uvs = {
		{ 0.0f, 1.0f },
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f }
	};
	for (auto& uv : uvs)
		_uvBuffer->add(uv);

	std::vector<unsigned int> indices = {
		0, 1, 2, 0, 2, 3
	};
	for (auto& index : indices)
		_indexBuffer->add(index);

	_vertexBuffer->buffer();
	_uvBuffer->buffer();
	_indexBuffer->buffer();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DeferredRenderer::_initializeShader()
{
	_aVertexHandle = _shader->getAttribLocation("vertex");
	_aUVHandle = _shader->getAttribLocation("uv");

	_uPositionTexture = _shader->getUniformLocation("positionTexture");
	_uNormalTexture = _shader->getUniformLocation("normalTexture");
	_uColorTexture = _shader->getUniformLocation("colorTexture");
}

void DeferredRenderer::_streamQuadToOpenGL() {




	_vertexBuffer->bind();
	_vertexBuffer->enable(_aVertexHandle);

	_uvBuffer->bind();
	_uvBuffer->enable(_aUVHandle);

	_indexBuffer->bind();

	glDrawElements(GL_TRIANGLES, _indexBuffer->size(), GL_UNSIGNED_INT, (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	_vertexBuffer->disable(_aVertexHandle);
	_uvBuffer->disable(_aUVHandle);
}

DeferredRenderer::DeferredRenderer(int pWidth, int pHeight)
	:	Renderer(pWidth, pHeight)
{
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	_initializeQuad();

	_shader = Shader::create("renderer");
	_initializeShader();

	_frameBuffer = new FrameBuffer();
	_frameBuffer->bind();

	_depthBuffer = new DepthBuffer();
	_depthBuffer->bind();
	_depthBuffer->allocate(pWidth, pHeight);

	glActiveTexture(GL_TEXTURE0);
	_positionTexture = Texture::createRenderTexture(pWidth, pHeight, GL_RGB32F, GL_RGB, GL_FLOAT);
	glActiveTexture(GL_TEXTURE1);
	_normalTexture = Texture::createRenderTexture(pWidth, pHeight, GL_RGB32F, GL_RGB, GL_FLOAT);
	glActiveTexture(GL_TEXTURE2);
	_colorTexture = Texture::createRenderTexture(pWidth, pHeight, GL_RGB8, GL_RGBA, GL_UNSIGNED_BYTE);

	_frameBuffer->attachDepthBuffer(_depthBuffer->getHandle());
	_frameBuffer->attachTexture2D(GL_COLOR_ATTACHMENT0, _positionTexture->getHandle());
	_frameBuffer->attachTexture2D(GL_COLOR_ATTACHMENT1, _normalTexture->getHandle());
	_frameBuffer->attachTexture2D(GL_COLOR_ATTACHMENT2, _colorTexture->getHandle());

	GLenum drawBuffers[] = { GL_NONE, GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(4, drawBuffers);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	else std::cout << "FRAMEBUFFER complete!" << std::endl;

	bindDefaultFrameBuffer();
}

DeferredRenderer::~DeferredRenderer()
{
	if (_vertexBuffer != NULL) {
		delete _vertexBuffer;
		_vertexBuffer = NULL;
	}
	if (_uvBuffer != NULL) {
		delete _uvBuffer;
		_uvBuffer = NULL;
	}
	if (_indexBuffer != NULL) {
		delete _indexBuffer;
		_indexBuffer = NULL;
	}
	if (_shader != NULL) {
		// do not delete, belongs to other object
		_shader = NULL;
	}
	if (_frameBuffer != NULL) {
		delete _frameBuffer;
		_frameBuffer = NULL;
	}
	if (_depthBuffer != NULL) {
		delete _depthBuffer;
		_depthBuffer = NULL;
	}
	if (_positionTexture != NULL) {
		// dont delete, belongs to other objects
		_positionTexture = NULL;
	}
	if (_normalTexture != NULL) {
		// dont delete, belongs to other objects
		_normalTexture = NULL;
	}
	if (_colorTexture != NULL) {
		// dont delete, belongs to other objects
		_colorTexture = NULL;
	}
}

void DeferredRenderer::render(Scene* pScene)
{
	_frameBuffer->bind();
	_clear();
	glEnable(GL_DEPTH_TEST);


	for (auto& child : pScene->children) {
		child->render(Camera::MAIN->getTransform()->getMatrix(), Camera::MAIN->getView(), Camera::MAIN->getProjection());
	}


	MAIN->bindDefaultFrameBuffer();
	_clear();
	glDisable(GL_DEPTH_TEST);

	_shader->use();

	_positionTexture->activate(GL_TEXTURE0);
	_positionTexture->bind();
	int textureSlot = 0;
	//_shader->setUniform(_uPositionTexture, &textureSlot);

	_normalTexture->activate(GL_TEXTURE1);
	_normalTexture->bind();
	textureSlot = 1;
	//_shader->setUniform(_uNormalTexture, &textureSlot);

	_colorTexture->activate(GL_TEXTURE2);
	_colorTexture->bind();
	textureSlot = 2;
	//_shader->setUniform(_uColorTexture, &textureSlot);

	_streamQuadToOpenGL();
}
