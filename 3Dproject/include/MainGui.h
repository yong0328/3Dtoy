#pragma once
#include "WindowBase.h"
#include "Base.h"
extern SHOWMODE curShowMode;
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
class MainGui : public WindowBase
{
public:
	MainGui(std::string name) : WindowBase(name), m_eBtnType3D(eNone),m_eBtnType2D(eNone2D)
	{
		
	}
	virtual void show() override;
	~MainGui()
	{
		
	}
	MainGui(const MainGui&) = delete;
	MainGui& operator=(const MainGui&) = delete;

public:
	ButtonType2D m_eBtnType2D;
	ButtonType3D m_eBtnType3D;
};