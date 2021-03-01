#include "core/Cubemap.h"

Cubemap::Cubemap()
	:	Texture(GL_TEXTURE_CUBE_MAP)
{
}

Cubemap::~Cubemap()
{
}
bool Cubemap::exists(std::string pCubemap)
{
    return CUBEMAPS.find(pCubemap) != CUBEMAPS.end();
}

void Cubemap::buffer(int pIndex, GLubyte* pData)
{
    glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + pIndex, 0, 0, 0, _width, _height, GL_RGBA, GL_UNSIGNED_BYTE, pData);

}
