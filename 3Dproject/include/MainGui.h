#pragma once
#include "WindowBase.h"
enum ButtonType
{
	eNone,
	eCreateBox,
	eCreateSphere,

	eClear,
};
class MainGui : public WindowBase
{
public:
	MainGui(std::string name) : WindowBase(name),m_eBtnType(eNone)
	{
		
	}
	virtual void show() override;
	~MainGui()
	{
		
	}
	MainGui(const MainGui&) = delete;
	MainGui& operator=(const MainGui&) = delete;

public:
	ButtonType m_eBtnType;
};