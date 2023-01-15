#pragma once
#include "glad/glad.h"
#include <string>
#include <iostream>
class shader
{
public:
	shader() : m_shaderProgram(0)
	{}
	~shader()
	{}

	void CompileShader(const char* vertexShader, const char* fragmentShader);
	unsigned int getProgram() { return m_shaderProgram; }
private:
	unsigned int m_shaderProgram;
};

