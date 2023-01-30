#pragma once
#include "Base.h"
#include <vector>

class Line
{
public:
	Line() {}
	virtual~Line() {}
	virtual void Render() = 0;
protected:
	unsigned int VAO;
	shader m_shader;
};