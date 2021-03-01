#include "core/Mesh.h"


void Mesh::_buffer()
{
	if (_vertexBuffer != NULL) _vertexBuffer->buffer();
	if (_normalBuffer != NULL) _normalBuffer->buffer();
	if (_uvBuffer != NULL) _uvBuffer->buffer();
	if (_tangentBuffer != NULL) _tangentBuffer->buffer();
	if (_indexBuffer != NULL) _indexBuffer->buffer();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//std::cout << std::to_string(_vertexBufferHandle) + " " + std::to_string(_normalBufferHandle) + " " +  std::to_string(_uvBufferHandle) << std::endl;
}

Mesh::Mesh()
{
	_vertexBuffer = new VertexBuffer();
	_normalBuffer = new NormalBuffer();
	_uvBuffer = new UVBuffer();
	//_tangentBuffer = new TangentBuffer();
	_indexBuffer = new IndexBuffer();
}

Mesh::~Mesh()
{
	if (_vertexBuffer != NULL) {
		delete _vertexBuffer;
		_vertexBuffer = NULL;
	}
	if (_normalBuffer != NULL) {
		delete _normalBuffer;
		_normalBuffer = NULL;
	}
	if (_uvBuffer != NULL) {
		delete _uvBuffer;
		_uvBuffer = NULL;
	}
	if (_tangentBuffer != NULL) {
		delete _tangentBuffer;
		_tangentBuffer = NULL;
	}
	if (_indexBuffer != NULL) {
		delete _indexBuffer;
		_indexBuffer = NULL;
	}
}

Mesh* Mesh::load(std::string pModel)
{
	if (MESHES.find(pModel) != MESHES.end()) {
		return MESHES[pModel];
	} else {
		//std::cout << "Creating new mesh: " + pModel << std::endl;

		Mesh* mesh = new Mesh();

		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uvs;

		std::map <FaceIndexTriplet, unsigned int> mappedTriplets;

		std::ifstream model("../assets/models/" + pModel);
		if (model) {
			std::string line;
			while (getline(model, line))
			{
				// Cmd read from obj file (v, vt, vn, f)
				char cmd[10];
				cmd[0] = 0;

				// Get the first string in the line of max 10 chars (c-style)
				sscanf(line.c_str(), "%10s", cmd);

				// "v" lines first, then "vt" lines, then "vn" lines, then "f" lines last
				if (strcmp(cmd, "v") == 0) {
					glm::vec3 vertex;
					sscanf(line.c_str(), "%10s %f %f %f ", cmd, &vertex.x, &vertex.y, &vertex.z);
					vertices.push_back(vertex);
				}
				else if (strcmp(cmd, "vn") == 0) {
					glm::vec3 normal;
					sscanf(line.c_str(), "%10s %f %f %f ", cmd, &normal.x, &normal.y, &normal.z);
					normals.push_back(normal);
				}
				else if (strcmp(cmd, "vt") == 0) {
					glm::vec2 uv;
					sscanf(line.c_str(), "%10s %f %f ", cmd, &uv.x, &uv.y);
					uvs.push_back(uv);
				}
				else if (strcmp(cmd, "f") == 0) {
					// "f" lines looks like: f 2/1/1 1/2/1 3/3/1
					// or: f v1/u1/n1 v2/u2/n2 v3/u3/n3
					// we need to check whether we already encountered it
					// and update our administration based on that
					glm::ivec3 vertexIndex;
					glm::ivec3 normalIndex;
					glm::ivec3 uvIndex;
					int count = sscanf(line.c_str(), "%10s %d/%d/%d %d/%d/%d %d/%d/%d", cmd, &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

					// Have we read exactly 10 elements?
					if (count == 10) {
						// Process 3 triplets
						for (int i = 0; i < 3; ++i) {
							// Create key out of the triplet and check if we already encountered this before
							FaceIndexTriplet triplet(vertexIndex[i], uvIndex[i], normalIndex[i]);
							std::map<FaceIndexTriplet, unsigned int>::iterator found = mappedTriplets.find(triplet);
							// If not found
							if (found == mappedTriplets.end())
							{
								// Create a new index value, and map our triplet to it
								unsigned int index = mappedTriplets.size();
								mappedTriplets[triplet] = index;
								mesh->_indexBuffer->add(index);
								// All values in the f triplets in the .obj file
								// are 1 based, but our vectors are 0 based
								mesh->_vertexBuffer->add(vertices[vertexIndex[i] - 1]);
								mesh->_normalBuffer->add(normals[normalIndex[i] - 1]);
								mesh->_uvBuffer->add(uvs[uvIndex[i] - 1]);
							}
							else
							{
								// If the key was already present, get the index value for it
								unsigned int index = found->second;
								mesh->_indexBuffer->add(index);
							}
						}
					}
					else {
						// If we read a different amount, something is wrong
						std::cout << "Error reading obj, needing v,vn,vt" << std::endl;
						delete mesh;
						return NULL;
					}
				}
			}
		}
		mesh->_buffer();
		MESHES[pModel] = mesh;
		return mesh;
	}
}

void Mesh::clear()
{
	for (auto& pair : MESHES) {
		delete pair.second;
		pair.second = NULL;
	}
	MESHES.clear();
}

std::map<std::string, Mesh*> Mesh::MESHES = std::map<std::string, Mesh*>();

void Mesh::streamToOpenGL(GLint pVerticesAttrib, GLint pNormalsAttrib, GLint pUVsAttrib, GLint pTangentsAttrib) {
	if (pVerticesAttrib != -1) {
		_vertexBuffer->bind();
		_vertexBuffer->enable(pVerticesAttrib);
	}

	if (pNormalsAttrib != -1) {
		_normalBuffer->bind();
		_normalBuffer->enable(pNormalsAttrib);
	}

	if (pUVsAttrib != -1) {
		_uvBuffer->bind();
		_uvBuffer->enable(pUVsAttrib);
	}

	if (pTangentsAttrib != -1) {
		_tangentBuffer->bind();
		_tangentBuffer->enable(pTangentsAttrib);
	}

	_indexBuffer->bind();

	glDrawElements(GL_TRIANGLES, _indexBuffer->size(), GL_UNSIGNED_INT, (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	if (pVerticesAttrib != -1) _vertexBuffer->disable(pVerticesAttrib);
	if (pNormalsAttrib != -1) _normalBuffer->disable(pNormalsAttrib);
	if (pUVsAttrib != -1) _uvBuffer->disable(pUVsAttrib);
	if (pTangentsAttrib != -1) _tangentBuffer->disable(pTangentsAttrib);
}