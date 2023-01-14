#pragma once
#include "WindowBase.h"
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
};