#include "core/Texture.h"

#include "core/Texture2D.h"
#include "core/Cubemap.h"
#include "core/RenderTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

GLubyte* Texture::_loadPixels(std::string pFileName, int& pWidth, int& pHeight, bool pFlip)
{
    int bytesPerPixel;
    stbi_set_flip_vertically_on_load(pFlip);
    return stbi_load(("../assets/textures/" + pFileName).c_str(), &pWidth, &pHeight, &bytesPerPixel, 4);
}

Texture::Texture(int pGL_TEXTURE_TYPE)
    :   _textureType(pGL_TEXTURE_TYPE)
{
    glGenTextures(1, &_handle);
}

Texture::~Texture()
{
    glDeleteTextures(1, &_handle);
}

std::map<std::string, Texture*> Texture::TEXTURES = std::map<std::string, Texture*>();


Texture* Texture::loadTexture2D(std::string pTexture)
{
    if (Texture2D::exists(pTexture)) {
        return TEXTURES[pTexture];
    }
    else {
        Texture2D* texture = new Texture2D();

        GLubyte* data = Texture::_loadPixels(pTexture, texture->_width, texture->_height);
        if (data != NULL) {
            texture->bind();
            texture->allocate();
            texture->buffer(data);
            texture->setMinMagFiler(GL_LINEAR, GL_LINEAR);
            stbi_image_free(data);
        }
        TEXTURES[pTexture] = texture;
        return texture;
    }
}

std::map<std::string, Texture*> Texture::CUBEMAPS = std::map<std::string, Texture*>();

Texture* Texture::loadCubemap(std::string pBaseName, std::string pExtension)
{
    if (Cubemap::exists(pBaseName + pExtension)) {
        return CUBEMAPS[pBaseName + pExtension];
    }
    else {
        Cubemap* texture = new Cubemap();

        texture->bind();

        const char* suffix[] = { "posx", "negx", "posy", "negy", "posz", "negz" };

        // Load the first one to get width/height
        std::string fullName = pBaseName + "_" + suffix[0] + pExtension;
        GLubyte* data = Texture::_loadPixels(fullName, texture->_width, texture->_height, false);

        // Allocate immutable storage for the whole cube map texture
        texture->allocate(); 
        texture->buffer(0, data);
        stbi_image_free(data);

        // Load the other 5 cube-map faces
        for (int i = 1; i < 6; i++) {
            fullName = pBaseName + "_" + suffix[i] + pExtension;
            data = Texture::_loadPixels(fullName, texture->_width, texture->_height, false);
            texture->buffer(i, data);
            stbi_image_free(data);
        }

        texture->setMinMagFiler(GL_LINEAR, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        CUBEMAPS[pBaseName + pExtension] = texture;
        return texture;
    }
}

std::vector<Texture*> Texture::RENDERTEXTURES = std::vector<Texture*>();

Texture* Texture::createRenderTexture(int pWidth, int pHeight, int pGL_INTERNAL_FORMAT, int pGL_FORMAT, int pGL_TYPE)
{
    RenderTexture* texture = new RenderTexture();
    texture->_width = pWidth;
    texture->_height = pHeight;

    texture->bind();
    glTexImage2D(GL_TEXTURE_2D, 0, pGL_INTERNAL_FORMAT, pWidth, pHeight, 0, pGL_FORMAT, pGL_TYPE, NULL);
    //texture->allocate(1, pGL_INTERNAL_FORMAT);

    texture->setMinMagFiler(GL_LINEAR, GL_LINEAR);

    RENDERTEXTURES.push_back(texture);
    return texture;
}

void Texture::clear()
{
    for (auto& texture : TEXTURES) {
        delete texture.second;
        texture.second = NULL;
    }
    TEXTURES.clear();
    for (auto& cubemap : CUBEMAPS) {
        delete cubemap.second;
        cubemap.second = NULL;
    }
    CUBEMAPS.clear();
    for (auto& renderTexture : RENDERTEXTURES) {
        delete renderTexture;
        renderTexture = NULL;
    }
    RENDERTEXTURES.clear();
}

void Texture::bind()
{
    glBindTexture(_textureType, _handle);
}

void Texture::activate(int pGL_TEXTURE_SLOT)
{
    glActiveTexture(pGL_TEXTURE_SLOT);
}

void Texture::allocate(int pLevels, int pGL_INTERNAL_FORMAT)
{
    glTexStorage2D(_textureType, pLevels, pGL_INTERNAL_FORMAT, _width, _height);
}

void Texture::setMinMagFiler(int pGL_MIN_FILTER, int pGL_MAG_FILTER)
{
    glTexParameteri(_textureType, GL_TEXTURE_MIN_FILTER, pGL_MIN_FILTER);
    glTexParameteri(_textureType, GL_TEXTURE_MAG_FILTER, pGL_MAG_FILTER);
}

int Texture::getWidth()
{
    return _width;
}

int Texture::getHeight()
{
    return _height;
}