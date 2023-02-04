#pragma once
#include "Line.h"
extern std::vector<Point3D> _vPt;
class Bspline : public Line
{
public:
	Bspline() {  }
private:
	std::vector<Point3D> drawpt;
	int m_iPtNum = 0;
};