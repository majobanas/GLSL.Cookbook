#pragma once

#include "core/OpenGL/core/OpenGLObject.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

class Texture2D;
class Cubemap;
class RenderTexture;

class Texture : public OpenGLObject {
private:

	static GLubyte* _loadPixels(std::string pFileName, int& pWidth, int& pHeight, bool pFlip = true);
protected:
	int _textureType;

	int _width;
	int _height;

public:
	Texture(int pGL_TEXTURE_TYPE);
	virtual ~Texture() = 0;

	static std::map<std::string, Texture*> TEXTURES;
	static Texture* loadTexture2D(std::string pTexture);

	static std::map<std::string, Texture*> CUBEMAPS;
	static Texture* loadCubemap(std::string pBaseName, std::string pExtension);

	static std::vector<Texture*> RENDERTEXTURES;
	static Texture* createRenderTexture(int pWidth, int pHeight, int pGL_INTERNAL_FORMAT = GL_RGBA8, int pGL_FORMAT = GL_RGBA, int pGL_TYPE = GL_UNSIGNED_BYTE);

	static void clear();

	void bind();
	void activate(int pGL_TEXTURE_SLOT);
	void allocate(int pLevels = 1, int pGL_INTERNAL_FORMAT = GL_RGBA8);
	void setMinMagFiler(int pGL_MIN_FILTER, int pGL_MAG_FILTER);

	int getWidth();
	int getHeight();
};
