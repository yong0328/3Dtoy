#pragma once
#include "WindowBase.h"
#include "Base.h"
extern SHOWMODE curShowMode;
extern std::vector<Point3D> _vPt;

enum ButtonType3D
{
	eNone,
	eCreateBox,
	eCreateSphere,

	eClear,
};
enum ButtonType2D
{
	eNone2D,
	eBizierCurve,
	eBspline,
	eNurbs,
};
extern ButtonType2D m_eBtnType2D;
extern ButtonType3D m_eBtnType3D;
class MainGui : public WindowBase
{
public:
	MainGui(std::string name) : WindowBase(name)
	{
		
	}
	virtual void show() override;
	~MainGui()
	{
		
	}
	MainGui(const MainGui&) = delete;
	MainGui& operator=(const MainGui&) = delete;

public:
};