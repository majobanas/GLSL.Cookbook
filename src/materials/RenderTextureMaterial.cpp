#include "materials/RenderTextureMaterial.h"

void RenderTextureMaterial::_lazyInitializeShader()
{
	_aVertexHandle = _shader->getAttribLocation("vertex");
	_aUVHandle = _shader->getAttribLocation("uv");

	_uViewHandle = _shader->getUniformLocation("view");
	_uProjectionHandle = _shader->getUniformLocation("projection");
	_uMatrixHandle = _shader->getUniformLocation("matrix");

	_uDiffuseTextureHandle = _shader->getUniformLocation("diffuseTexture");
}

RenderTextureMaterial::RenderTextureMaterial(int pWidth, int pHeight, glm::mat4* pModel)
	:	Material("texture"),
		_textureWidth(pWidth),
		_textureHeight(pHeight),
		_eyeModel(pModel)
{
	_lazyInitializeShader();

	// gen frame buff
	_frameBuffer = new FrameBuffer();
	_frameBuffer->bind();

	glActiveTexture(GL_TEXTURE0);
	_renderTexture = Texture::createRenderTexture(_textureWidth, _textureHeight);
	// bind
	_frameBuffer->attachTexture2D(GL_COLOR_ATTACHMENT0, _renderTexture->getHandle());

	// gen depth buff
	_depthBuffer = new DepthBuffer();
	_depthBuffer->bind();
	_depthBuffer->allocate(_textureWidth, _textureHeight);

	// bind
	_frameBuffer->attachDepthBuffer(_depthBuffer->getHandle());
	GLenum drawbuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawbuffers);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	RENDERTEXTUREMATERIAL.push_back(this);
}

RenderTextureMaterial::~RenderTextureMaterial()
{
	if (_eyeModel != NULL) {
		// dont delete, belongs to other object
		_eyeModel = NULL;
	}
	if (_renderTexture != NULL) {
		// dont delete, belongs to other object
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

void RenderTextureMaterial::render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection)
{
	_shader->use();

	_renderTexture->activate(GL_TEXTURE0);
	_renderTexture->bind();
	int textureSlot = 0;
	_shader->setUniform(_uDiffuseTextureHandle, &textureSlot);

	_shader->setUniform(_uViewHandle, pView);
	_shader->setUniform(_uProjectionHandle, pProjection);
	_shader->setUniform(_uMatrixHandle, pMatrix);

	pMesh->streamToOpenGL(_aVertexHandle, -1, _aUVHandle, -1);
}

void RenderTextureMaterial::render(glm::mat4* pModel, glm::mat4* pProjection)
{
	for (auto& renderTextureMaterial : RENDERTEXTUREMATERIAL) {
		// Render to texture
		renderTextureMaterial->_frameBuffer->bind();
		renderTextureMaterial->_frameBuffer->clear();
		//glViewport(0, 0, renderTexture->_textureWidth, renderTexture->_textureHeight);
		//pCamera->setAspectRatio(renderTexture->_textureWidth, renderTexture->_textureHeight);

		for (auto& object : Object::OBJECTS) {
			glm::mat4 view = glm::inverse(*renderTextureMaterial->_eyeModel);

			object->getMaterial()->render(
				object->getMesh(),
				object->getTransform()->getMatrix(),
				pModel,
				&view,
				pProjection);
		}
		renderTextureMaterial->_frameBuffer->unbind();
	}
	//int cameraWidth = Camera::MAIN->getWidth();
	//int cameraHeight = Camera::MAIN->getHeight();

	//glViewport(0, 0, cameraWidth, cameraHeight);
	//pCamera->setAspectRatio(cameraWidth, cameraHeight);
}

std::vector<RenderTextureMaterial*> RenderTextureMaterial::RENDERTEXTUREMATERIAL = std::vector<RenderTextureMaterial*>();
