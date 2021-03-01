#pragma once

#include "core/Shader.h"
#include "core/Mesh.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"


class Material {
private:

protected:
	Shader* _shader = NULL;

	virtual void _lazyInitializeShader() = 0;

	// Lights
	GLuint _uNumLightsHandle;
	int _numLights;
	std::map<int, std::map<int, GLuint>> _uLight;
	void _initializeLightUniforms();
	void _setLightUniforms();

	GLuint _uShadowMapHandle;
	void _initializeShadowUniform();
	void _setShadowUniform(GLuint pLightViewProjectionHandle);

	void _bindShadowFrameBuffer();
	void _setShadowMap(int pSlot, GLuint pShadowMapHandle);
	/*// Render pass
	GLuint _uPassHandle;
	// Model
	GLuint _aVertexHandle;
	GLuint _aNormalHandle;
	GLuint _aUVHandle;
	GLuint _aTangentHandle;
	// Camera & Model (_uMatrixHandle)
	GLuint _uModelHandle;
	GLuint _uViewHandle;
	GLuint _uProjectionHandle;
	GLuint _uMatrixHandle;
	// Diffuse
	GLuint _uDiffuseColorHandle;
	GLuint _uDiffuseTextureHandle;
	// Specular
	GLuint _uShinenessHandle;
	// Cartoon
	GLuint _uLevelsHandle; // Cartoon shader
	// Edge
	GLuint _uEdgeColorHandle;
	GLuint _uRenderTextureHandle;
	// Cubemap
	GLuint _uCubemapTextureHandle;
	GLuint _uReflectionFactorHandle;
	// Physical
	GLuint _uRoughnessHandle;
	GLuint _uMetalHandle;*/

public:
	Material(std::string pShader);
	virtual ~Material() = 0;


	virtual void render(Mesh* pMesh, glm::mat4* pMatrix, glm::mat4* pModel, glm::mat4* pView, glm::mat4* pProjection) = 0;
};
