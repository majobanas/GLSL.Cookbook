#include "core/Texture2D.h"

Texture2D::Texture2D()
	:	Texture(GL_TEXTURE_2D)
{
}

Texture2D::~Texture2D()
{
}

bool Texture2D::exists(std::string pTexture)
{
    return TEXTURES.find(pTexture) != TEXTURES.end();
}

void Texture2D::buffer(GLubyte* pData)
{
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _width, _height, GL_RGBA, GL_UNSIGNED_BYTE, pData);
}
