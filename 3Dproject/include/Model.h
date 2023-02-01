#pragma once
//one model can has several parts
//one part is one mesh
#include <map>
#include "_mesh.h"
#include "Base.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
class Model
{
public:
	Model(const std::string& path);
	void draw(shader& _shader);
private:
	void loadModel(const std::string& path);
	void ParseNode(aiNode* node, const aiScene* scene);
	Mesh ParseMesh(aiMesh* node, const aiScene* scene);
	std::vector<Texture> loadMaterial(aiMaterial* material,aiTextureType type,std::string strName);
private:
	std::vector<Mesh> m_vMesh;
	std::string m_dir;   //model file location

};

class TextureMng
{
public:
	TextureMng() {}
	unsigned int createTexture(const std::string& path);  //full path
private:
	std::map<std::string, unsigned int> m_mTexture;   //texture path,id
};