#pragma once
#include "Base.h"
#include <vector>
class Line
{
public:
	Line() {}
	virtual~Line() {}
protected:
	std::vector<Point3D> m_vPt;
	unsigned int VAO;
	shader m_shader;
};