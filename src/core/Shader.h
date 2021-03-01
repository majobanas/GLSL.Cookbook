#pragma once

#include "core/OpenGL/core/OpenGLObject.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>
#include <vector>
#include <map>

class Shader : public OpenGLObject {
private:
	std::string _name;

	std::string _readShaderSource(std::string pShaderSourcePath);
	GLuint _createShader(GLuint pShaderType, std::string pShaderSourcePath);
	void _linkShader(std::vector<GLuint>& pShaders);

	static std::map<std::string, GLuint> TYPE;

	void _saveShaderToBinary(std::string pShader);
	void _loadShaderFromBinary(std::string pShader, GLenum pFormat);

	void _getActiveAttribs();
	void _getActiveUniforms();

	const char* _getTypeString(GLenum pType);

public:
	Shader(std::string pShader);
	~Shader();

	static Shader* create(std::string pShader);
	static std::map<std::string, Shader*> SHADERS;
	static void clear();

	std::string getName();

	void use();

	GLuint getAttribLocation(std::string pAttrib);
	GLuint getUniformLocation(std::string pUniform);

	void setUniform(GLuint pHandle, glm::mat4* pMatrix);
	void setUniform(GLuint pHandle, glm::vec3* pVector);
	void setUniform(GLuint pHandle, float* pFloat);
	void setUniform(GLuint pHandle, int* pInt);
	void setUniform(GLuint pHandle, bool* pBool);
};
