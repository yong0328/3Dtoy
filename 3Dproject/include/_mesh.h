#pragma once
#include "Base.h"
struct Vertex
{
	glm::vec3 _pos;
	glm::vec3 _normal;
	glm::vec2 _textureCoord;
	Vertex(glm::vec3 pos = glm::vec3(0.0f,0.0f,0.0f),
		   glm::vec3 normal = glm::vec3(0.0f, 0.0f, 0.0f),
		   glm::vec2 coord = glm::vec2(0.0f, 0.0f))
	{
		_pos = pos;
		_normal = normal;
		_textureCoord = coord;
	}
};
#define TEXTURE_DIFFUSE "texture_diffuse"
#define TEXTURE_SPECULAR "texture_specular"
struct Texture
{
	unsigned int _id;
	std::string _type;   //diffuse texture or specular texture
	std::string _path;
};
class Mesh
{
public:
	Mesh(std::vector<Vertex> vVertex, std::vector<unsigned int> vIdx, std::vector<Texture> vTexture)
	{
		m_vVertex = vVertex;
		m_vIdx = vIdx;
		m_vTexture = vTexture;
		m_VAO = 0;
		m_VBO = 0;

		setupMesh();
	}
	void draw(shader _shader);
private:
	void setupMesh();
private:
	std::vector<Vertex> m_vVertex;
	std::vector<unsigned int> m_vIdx;
	std::vector<Texture> m_vTexture;

	unsigned int m_VAO;
	unsigned int m_VBO;

};