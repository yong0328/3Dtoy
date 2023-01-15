#define STB_IMAGE_IMPLEMENTATION
#include "CubeMap.h"

extern glm::mat4x4 _viewMatrix;
extern glm::mat4x4 _projectMatrix;
CubeMap::CubeMap()
{
}
void CubeMap::initCubeMap()
{
	VAO = CreateCubemapModel();
	m_uCubeMapTexID = loadCubeMap();
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform mat4 _viewMatrix;\n"
		"uniform mat4 _projectMatrix;\n"
		"out vec3 TexCoords;\n"
		"void main()\n"
		"{\n"
		"TexCoords = aPos;\n"
		"   vec4 pos =_projectMatrix * _viewMatrix  * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		" gl_Position = pos.xyww;\n"
		"}\0";
	const char* fragmentShader = "#version 330 core \n"
		"out vec4 FragColor;\n"
		"in vec3 TexCoords;\n"
		"uniform samplerCube CubeMap;\n"
		"void main()\n"
		"{\n"
		"	FragColor = texture(CubeMap,TexCoords);\n"
		"} \n";
	m_shader.CompileShader(vertexShaderSource, fragmentShader);
}
CubeMap::~CubeMap()
{
}
unsigned int CubeMap::CreateCubemapModel()
{
	unsigned int VAO;
	unsigned int VB0;
	float boxVertices[] = {    
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VB0);
	glBindBuffer(GL_ARRAY_BUFFER, VB0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return VAO;
}
unsigned int CubeMap::loadCubeMap()
{
	unsigned int cubemapId;
	glGenTextures(1, &cubemapId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapId);

	int width;
	int height;
	int channels;
	for (int i = 0; i < m_vCubemapPath.size(); ++i)
	{
		unsigned char* data = stbi_load(m_vCubemapPath[i].c_str(), &width, &height, &channels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "cubemap load failed" << std::endl;
			stbi_image_free(data);
		}

	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	return cubemapId;
}

void CubeMap::Render()
{
	glDepthFunc(GL_LEQUAL);
	glUseProgram(m_shader.getProgram());
	glBindVertexArray(VAO);
	glm::mat4 viewMtx = glm::mat4(glm::mat3(_viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgram(), "_viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMtx));
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgram(), "_projectMatrix"), 1, GL_FALSE, glm::value_ptr(_projectMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glUseProgram(0);
	glDepthFunc(GL_LESS);
}