#include "Shader.h"

std::map<std::string, GLuint> Shader::TYPE = 
{ 
	{"vertex.glsl", GL_VERTEX_SHADER},
	{"fragment.glsl", GL_FRAGMENT_SHADER},
	{"geometry.glsl", GL_GEOMETRY_SHADER},
	{"tessellationevaluation.glsl", GL_TESS_EVALUATION_SHADER},
	{"tessellationcontrol.glsl", GL_TESS_CONTROL_SHADER},
	{"compute.glsl", GL_COMPUTE_SHADER}
};

std::string Shader::_readShaderSource(std::string pShaderSourcePath)
{
	std::ifstream file(pShaderSourcePath);
	if (!file) {
		std::cerr << "Failed to open " + pShaderSourcePath << std::endl;
		//exit(EXIT_FAILURE);
	}
	std::stringstream code;
	code << file.rdbuf();
	file.close();
	return code.str();
}

GLuint Shader::_createShader(GLuint pShaderType, std::string pShaderSourcePath)
{
	GLuint shader = glCreateShader(pShaderType);
	if (shader == 0) {
		std::cerr << "Failed to create shader object " + pShaderSourcePath << std::endl;
		//exit(EXIT_FAILURE);
	}
	std::string shaderSource = _readShaderSource(pShaderSourcePath);
	const GLchar* shaderCode[] = { shaderSource.c_str() };
	glShaderSource(shader, 1, shaderCode, NULL);
	//delete[] shaderCode;

	glCompileShader(shader);

	GLint result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		std::cerr << "Failed to compile " + pShaderSourcePath << std::endl;
		GLint logLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0) {
			std::string log(logLength, ' ');
			GLsizei written;
			glGetShaderInfoLog(shader, logLength, &written, &log[0]);
			std::cerr << "Shader log: " << std::endl << log;
		}
	}
	return shader;
}

void Shader::_linkShader(std::vector<GLuint>& pShaders)
{
	for (const GLuint& shader : pShaders) {
		glAttachShader(_handle, shader);
	}

	glLinkProgram(_handle);

	GLint result;
	glGetProgramiv(_handle, GL_LINK_STATUS, &result);
	if (result == GL_FALSE) {
		std::cerr << "Failed to link program" << std::endl;
		GLint logLength;
		glGetProgramiv(_handle, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0) {
			std::string log(logLength, ' ');
			GLsizei written;
			glGetProgramInfoLog(_handle, logLength, &written, &log[0]);
			std::cerr << "Program log: " << std::endl << log;
		}
	}
	else {
		//std::cout << "Link successful" << std::endl;
		glUseProgram(_handle);
	}

	for (const GLuint& shader : pShaders) {
		glDetachShader(_handle, shader);
	}
	for (const GLuint& shader : pShaders) {
		glDeleteShader(shader);
	}
}

void Shader::_saveShaderToBinary(std::string pShader)
{
	GLint formats = 0;
	glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &formats);
	if (formats < 1) {
		std::cerr << "Driver does not support any binary formats" << std::endl;
	}
	else {
		GLint length = 0;
		glGetProgramiv(_handle, GL_PROGRAM_BINARY_LENGTH, &length);

		std::vector<GLubyte> buffer(length);
		GLenum format = 0;
		glGetProgramBinary(_handle, length, NULL, &format, buffer.data());
		std::string binaryFile(pShader + ".bin");
		std::cout << "Writing to " << binaryFile << ", binary format = " << format << std::endl;
		std::ofstream out(binaryFile.c_str(), std::ios::binary);
		out.write(reinterpret_cast<char*>(buffer.data()), length);
		out.close();
	}
}

void Shader::_loadShaderFromBinary(std::string pShader, GLenum pFormat)
{
	std::ifstream inputStream(pShader, std::ios::binary);
	std::istreambuf_iterator<char> startIt(inputStream), endIt;
	std::vector<char> buffer(startIt, endIt);
	inputStream.close();

	glProgramBinary(_handle, pFormat, buffer.data(), buffer.size());

	GLint result;
	glGetProgramiv(_handle, GL_LINK_STATUS, &result);
	if (result == GL_FALSE) {
		std::cerr << "Failed to load " + pShader + " from binary" << std::endl;
	}
}

void Shader::_getActiveAttribs()
{
	GLint numAttributes;
	glGetProgramInterfaceiv(_handle, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numAttributes);
	GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION };
	//std::cout << "Active attributes" << std::endl;
	for (int i = 0; i < numAttributes; i++) {
		GLint results[3];
		glGetProgramResourceiv(_handle, GL_PROGRAM_INPUT, i, 3, properties, 3, NULL, results);
		GLint nameBufSize = results[0] + 1;
		char* name = new char[nameBufSize];
		glGetProgramResourceName(_handle, GL_PROGRAM_INPUT, i, nameBufSize, NULL, name);
		printf("%-5d %s (%s)\n", results[2], name, _getTypeString(results[1]));
		delete[] name;
	}
}

void Shader::_getActiveUniforms()
{
	GLint numUniforms = 0;
	glGetProgramInterfaceiv(_handle, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);
	GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX };
	//std::cout << "Active Uniforms" << std::endl;
	for (int i = 0; i < numUniforms; i++) {
		GLint results[4];
		glGetProgramResourceiv(_handle, GL_UNIFORM, i, 4, properties, 4, NULL, results);
		if (results[3] != -1)
			continue; // Skip uniforms in blocks
		GLint nameBufSize = results[0] + 1;
		char* name = new char[nameBufSize];
		glGetProgramResourceName(_handle, GL_UNIFORM, i, nameBufSize, NULL, name);
		printf("%-5d %s (%s)\n", results[2], name, _getTypeString(results[1]));
		delete[] name;
	}
}

const char* Shader::_getTypeString(GLenum pType)
{
	switch (pType) {
	case GL_FLOAT:
		return "float";
	case GL_FLOAT_VEC2:
		return "vec2";
	case GL_FLOAT_VEC3:
		return "vec3";
	case GL_FLOAT_VEC4:
		return "vec4";
	case GL_DOUBLE:
		return "double";
	case GL_INT:
		return "int";
	case GL_UNSIGNED_INT:
		return "unsigned int";
	case GL_BOOL:
		return "bool";
	case GL_FLOAT_MAT2:
		return "mat2";
	case GL_FLOAT_MAT3:
		return "mat3";
	case GL_FLOAT_MAT4:
		return "mat4";
	default:
		return "?";
	}
}

Shader::Shader(std::string pShader)
	: _name(pShader)
{
	_handle = glCreateProgram();
	if (_handle == 0) {
		std::cerr << "Shader::Failed to create program" << std::endl;
		//exit(EXIT_FAILURE);
	}
}

Shader::~Shader()
{
	glDeleteProgram(_handle);
}

Shader* Shader::create(std::string pShader)
{
	if (SHADERS.find(pShader) != SHADERS.end()) {
		return SHADERS[pShader];
	} else {
		//std::cout << "Creating new shader: " + pShader << std::endl;

		Shader* shader = new Shader(pShader);

		std::vector<GLuint> shaders;
		std::string directory = "../src/shaders/";
		std::string shaderPath;
		std::string shaderType;

		for (const auto& entry : std::filesystem::directory_iterator(directory)) {
			shaderPath = entry.path().string();
			if (shaderPath.find(pShader) != std::string::npos) {
				shaderType = shaderPath.substr(directory.size() + pShader.size() + 1, shaderPath.size());
				shaders.push_back(shader->_createShader(TYPE[shaderType], shaderPath));
			}
		}
		shader->_linkShader(shaders);
		//shader->_getActiveAttribs();
		//shader->_getActiveUniforms();

		//_saveShaderToBinary(directory + "binary/" + pShader);
		//_loadShaderFromBinary(directory + "binary/" + pShader, 36385);

		//_getActiveAttribs();
		//_getActiveUniforms();
		SHADERS[pShader] = shader;
		return shader;
	}
}

std::map<std::string, Shader*> Shader::SHADERS = std::map<std::string, Shader*>();

void Shader::clear()
{
	for (auto& pair : SHADERS) {
		delete pair.second;
		pair.second = NULL;
	}
	SHADERS.clear();
}

std::string Shader::getName()
{
	return _name;
}

void Shader::use()
{
	GLint currentProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
	if (currentProgram != _handle) {
		glUseProgram(_handle);
	}
}

GLuint Shader::getAttribLocation(std::string pAttrib)
{
	return glGetAttribLocation(_handle, pAttrib.c_str());
}

GLuint Shader::getUniformLocation(std::string pUniform)
{
	return glGetUniformLocation(_handle, pUniform.c_str());
}

void Shader::setUniform(GLuint pHandle, glm::mat4* pMatrix)
{
	glUniformMatrix4fv(pHandle, 1, GL_FALSE, glm::value_ptr(*pMatrix));
}

void Shader::setUniform(GLuint pHandle, glm::vec3* pVector)
{
	glUniform3fv(pHandle, 1, glm::value_ptr(*pVector));
}

void Shader::setUniform(GLuint pHandle, float* pFloat)
{
	glUniform1f(pHandle, *pFloat);
}

void Shader::setUniform(GLuint pHandle, int* pInt)
{
	glUniform1i(pHandle, *pInt);
}

void Shader::setUniform(GLuint pHandle, bool* pBool)
{
	glUniform1i(pHandle, *pBool);
}
