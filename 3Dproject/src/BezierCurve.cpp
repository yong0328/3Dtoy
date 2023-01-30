#include "BezierCurve.h"
extern glm::mat4x4 _viewMatrix;
extern glm::mat4x4 _projectMatrix;
BezierCurve::BezierCurve() : Line()
{
	if (_vPt.size() != 0)
	{
		unsigned int _VAO = 0;
		unsigned int _VBO = 0;

		glGenVertexArrays(1, &_VAO);
		glBindVertexArray(_VAO);

		glGenBuffers(1, &_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, _vPt.size() * GL_FLOAT * 3, &_vPt.at(0), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		VAO = _VAO;
	}
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform mat4 _viewMatrix;\n"
		"uniform mat4 _projectMatrix;\n"
		"void main()\n"
		"{\n"
		"   gl_Position =_projectMatrix * _viewMatrix  * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* fragmentShader = "#version 330 core \n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
		"} \n";
	m_shader.CompileShader(vertexShaderSource, fragmentShader);
}

BezierCurve::~BezierCurve() {}

void BezierCurve::Render()
{
	//glUseProgram(m_shader.getProgram());
	glBindVertexArray(VAO);
	//glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgram(), "_viewMatrix"), 1, GL_FALSE, glm::value_ptr(_viewMatrix));
	//glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgram(), "_projectMatrix"), 1, GL_FALSE, glm::value_ptr(_projectMatrix));
	glPointSize(5.0f);
	glDrawArrays(GL_POINTS, 0, 3);
	glDrawArrays(GL_LINE_LOOP, 0, 3);
	glBindVertexArray(0);
	//glUseProgram(0);
}