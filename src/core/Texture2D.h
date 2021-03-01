#pragma once

#include "core/Texture.h"

class Texture2D : public Texture {
private:

public:
	Texture2D();
	~Texture2D() override;

	static bool exists(std::string pTexture);

	void buffer(GLubyte* pData);

};
