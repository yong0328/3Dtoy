#include "shader.h"
void shader::CompileShader(const char* vertexShader, const char* fragmentShader)
{
	if (vertexShader == nullptr || fragmentShader == nullptr)
		return;
	unsigned int _vertexID = 0, _fragID = 0;
	//存储错误信息
	char _infolog[512];
	int _successFlag = 0;

	//在opengl上下文中分配一个shader ID；
	//编译vertex shader
	_vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vertexID, 1, &vertexShader, NULL);
	glCompileShader(_vertexID);

	glGetShaderiv(_vertexID, GL_COMPILE_STATUS, &_successFlag);
	if (!_successFlag)
	{
		glGetShaderInfoLog(_vertexID, 512, NULL, _infolog);
		std::string errstr(_infolog);
		std::cout << _infolog << std::endl;
	}
	//编译fragment shader
	_fragID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fragID, 1, &fragmentShader, NULL);
	glCompileShader(_fragID);

	glGetShaderiv(_fragID, GL_COMPILE_STATUS, &_successFlag);
	if (!_successFlag)
	{
		glGetShaderInfoLog(_fragID, 512, NULL, _infolog);
		std::string errstr(_infolog);
		std::cout << _infolog << std::endl;
	}

	//链接
	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, _vertexID);
	glAttachShader(m_shaderProgram, _fragID);
	glLinkProgram(m_shaderProgram);

	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &_successFlag);
	if (!_successFlag)
	{
		glGetProgramInfoLog(m_shaderProgram, 512, NULL, _infolog);
		std::string errstr(_infolog);
		std::cout << _infolog << std::endl;
	}
	//删除中间文件
	glDeleteShader(_vertexID);
	glDeleteShader(_fragID);
}