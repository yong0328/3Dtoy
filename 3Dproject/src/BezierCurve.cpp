#include "BezierCurve.h"
extern glm::mat4x4 _viewMatrix;
extern glm::mat4x4 _projectMatrix;
BezierCurve::BezierCurve() : Line(),m_iPtNum(0)
{
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform mat4 _viewMatrix;\n"
		"uniform mat4 _projectMatrix;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = _projectMatrix * _viewMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* fragmentShader = "#version 330 core \n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
		"} \n";
	m_shader.CompileShader(vertexShaderSource, fragmentShader);
	drawpt.reserve(100);
}

BezierCurve::~BezierCurve() {}

void BezierCurve::Render()
{
	if (_vPt.size() == 0)
		return;
	//only if _vpt.size change,calculate VAO again
	if (_vPt.size() != m_iPtNum)
	{
		m_iPtNum = _vPt.size();
		drawpt.clear();
		if (_vPt.size() >= 3)
		{
			std::vector<Point3D> node;
			float t = 0.0f;
			for (; t < 1.0f; t += 0.02f)
			{
				node = _vPt;
				std::vector<Point3D> tmp;
				while (node.size() != 1)
				{
					tmp.clear();
					for (int i = 0; i < node.size() - 1; ++i)
					{
						float x = node[i].m_x * (1.0f - t) + node[i + 1].m_x * t;
						float y = node[i].m_y * (1.0f - t) + node[i + 1].m_y * t;
						tmp.push_back(Point3D(x, y, node[i].m_z));
					}
					node = tmp;
				}
				drawpt.push_back(node[0]);
			}
			//drawpt.push_back(_vPt[_vPt.size() - 1]);
		}
		else
			drawpt = _vPt;
		if (nodeVAO != 0 || controlVAO != 0)
		{
			//glDeleteVertexArrays(1,&nodeVAO);
			//glDeleteVertexArrays(1, &controlVAO);

			glDeleteBuffers(1, &nodeVBO);
			glDeleteBuffers(1, &controlVBO);
		}
		unsigned int _VAO = 0;
		unsigned int _VBO = 0;

		glGenVertexArrays(1, &_VAO);
		glBindVertexArray(_VAO);

		glGenBuffers(1, &_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, drawpt.size() * GL_FLOAT * 3, &drawpt[0], GL_STATIC_DRAW);
		std::cout << glGetError() << std::endl;
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		nodeVAO = _VAO;
		nodeVBO = _VBO;
		unsigned int _VAO2 = 0;
		unsigned int _VBO2 = 0;

		glGenVertexArrays(1, &_VAO2);
		glBindVertexArray(_VAO2);

		glGenBuffers(1, &_VBO2);
		glBindBuffer(GL_ARRAY_BUFFER, _VBO2);
		glBufferData(GL_ARRAY_BUFFER, _vPt.size() * GL_FLOAT * 3, &_vPt.at(0), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		controlVAO = _VAO2;
		controlVBO = _VBO2;
	}
	glUseProgram(m_shader.getProgram());
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgram(), "_viewMatrix"), 1, GL_FALSE, glm::value_ptr(_viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgram(), "_projectMatrix"), 1, GL_FALSE, glm::value_ptr(_projectMatrix));
	glPointSize(5.0f);
	glBindVertexArray(nodeVAO);
	glDrawArrays(GL_POINTS, 0, drawpt.size());
	glDrawArrays(GL_LINE_STRIP, 0, drawpt.size());
	glBindVertexArray(0);
	glBindVertexArray(controlVAO);
	glDrawArrays(GL_POINTS, 0, _vPt.size());
	glDrawArrays(GL_LINE_STRIP, 0, _vPt.size());
	glBindVertexArray(0);
	glUseProgram(0);
}