#pragma once

#include "core/OpenGL/VertexBuffer.h"
#include "core/OpenGL/NormalBuffer.h"
#include "core/OpenGL/UVBuffer.h"
#include "core/OpenGL/TangentBuffer.h"
#include "core/OpenGL/IndexBuffer.h"

#include <iostream>
#include <fstream>
#include <string>

#include <map>

#include "glad/glad.h"
#include "glm/glm.hpp"

class Mesh {
private:
	class FaceIndexTriplet {
	public:
		unsigned v; //vertex
		unsigned uv;//uv
		unsigned n; //normal
		FaceIndexTriplet(unsigned pV, unsigned pUV, unsigned pN)
			: v(pV), uv(pUV), n(pN) {
		}
		//needed for use as key in map
		bool operator<(const FaceIndexTriplet other) const {
			return memcmp((void*)this, (void*)&other, sizeof(FaceIndexTriplet)) > 0;
		}
	};

	VertexBuffer* _vertexBuffer = NULL;
	NormalBuffer* _normalBuffer = NULL;
	UVBuffer* _uvBuffer = NULL;
	TangentBuffer* _tangentBuffer = NULL;
	IndexBuffer* _indexBuffer = NULL;


	void _buffer();

public:
	Mesh();
	~Mesh();

	static Mesh* load(std::string pModel);
	static std::map<std::string, Mesh*> MESHES;
	static void clear();

	void streamToOpenGL(GLint pVerticesAttrib, GLint pNormalsAttrib, GLint pUVsAttrib, GLint pTangentsAttrib);
};
