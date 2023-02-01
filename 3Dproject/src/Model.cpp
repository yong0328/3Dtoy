#include "Model.h"
Model::Model(const std::string& path)
{
	loadModel(path);
}
void Model::loadModel(const std::string& path)
{
	Assimp::Importer _importer;
	const aiScene* _scene = _importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (_scene == nullptr || _scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || _scene->mRootNode == nullptr)
		return;
	m_dir = path.substr(0, path.find_last_of('/'));
	ParseNode(_scene->mRootNode, _scene);
}
void Model::draw(shader& _shader)
{
	
}
void Model::ParseNode(aiNode* node, const aiScene* scene)
{
	for (int i = 0;i < node->mNumMeshes;++i)
	{
		aiMesh* pMesh = scene->mMeshes[node->mMeshes[i]];   //scene->mMeshes's context is data,node->mMeshes's context is index
		m_vMesh.push_back(ParseMesh(pMesh, scene));
	}
	for (int i = 0;i < node->mNumChildren;++i)
		ParseNode(node->mChildren[i], scene);
}
Mesh Model::ParseMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> _vVertex;
	std::vector<unsigned int> _vIdx;
	std::vector<Texture> _vTexture;
	for (int i = 0;i < mesh->mNumVertices;++i)
	{
		Vertex _vertex;
		//read pos
		aiVector3D pos = mesh->mVertices[i];
		_vertex._pos = glm::vec3(pos.x, pos.y, pos.z);
		//read normal
		aiVector3D normal = mesh->mNormals[i];
		_vertex._normal = glm::vec3(normal.x, normal.y, normal.z);
		//read textureCoord
		if (mesh->HasTextureCoords(0))
		{
			aiVector3D textureCoord = mesh->mTextureCoords[0][i];
			_vertex._textureCoord = glm::vec2(textureCoord.x, textureCoord.y);
		}
		_vVertex.push_back(_vertex);
	}
	for (int i = 0; i < mesh->mNumFaces;++i)
	{
		aiFace pFace = mesh->mFaces[i];
		for (int j = 0; j < pFace.mNumIndices; ++j)
			_vIdx.push_back(pFace.mIndices[j]);
	}
}
std::vector<Texture> Model::loadMaterial(aiMaterial* material, aiTextureType type,std::string strName)
{
	std::vector<Texture> _vTex;
	for (int i = 0;i < material->GetTextureCount(type);++i)
	{
		Texture _texture;
		aiString _path;
		material->GetTexture(type, i, &_path);
	}
}

unsigned int TextureMng::createTexture(const std::string& path)
{
	auto it = m_mTexture.find(path);
	if (it != m_mTexture.end())
		return it->second;
}