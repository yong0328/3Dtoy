#pragma once
#include "Base.h"
#include <vector>

class Line
{
public:
	Line() : nodeVAO(0),controlVAO(0) {}
	virtual~Line() {}
	virtual void Render() = 0;
protected:
	unsigned int nodeVAO;
	unsigned int controlVAO;

	unsigned int nodeVBO;
	unsigned int controlVBO;
	shader m_shader;
};