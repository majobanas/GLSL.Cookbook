#pragma once

#include "core/Texture.h"

class Cubemap : public Texture {
private:

public:
	Cubemap();
	~Cubemap() override;

	static bool exists(std::string pCubemap);

	void buffer(int pIndex, GLubyte* pData);
};
