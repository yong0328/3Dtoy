#pragma once
#include "Line.h"
extern std::vector<Point3D> _vPt;
class BezierCurve : public Line
{
public:
	BezierCurve();
	~BezierCurve();
	virtual void Render() override;
private:
	std::vector<Point3D> drawpt;
	int m_iPtNum;
};