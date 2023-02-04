#include "_mesh.h"
void Mesh::setupMesh()
{
	unsigned int EBO = 0;
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glGenBuffers(1,&m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER,m_VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex) * m_vVertex.size(),&m_vVertex[0],GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int) * m_vIdx.size(),&m_vIdx[0],GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, _normal)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, _textureCoord)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}
void Mesh::draw(shader _shader)
{
	unsigned int _diffuseTextureN = 1;
	unsigned int _specularTextureN = 1;
	for (int i = 0;i < m_vTexture.size();++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D,m_vTexture[i]._id);
		std::string strType= m_vTexture[i]._type;
		std::string strNum;
		if (strType == TEXTURE_DIFFUSE)
			strNum = std::to_string(_diffuseTextureN++);
		else if(strType == TEXTURE_SPECULAR)
			strNum = std::to_string(_specularTextureN++);
		glUniform1iv(glGetUniformLocation(_shader.getProgram(), "myMaterial." + strType + strNum), 1, &i);
	}
	glActiveTexture(GL_TEXTURE0);
	glUseProgram(_shader.getProgram());
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES,m_vIdx.size(),GL_UNSIGNED_INT,0);
	glBindVertexArray(0); 
	glUseProgram(0);
}