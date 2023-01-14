#pragma once
#include <string>
class WindowBase
{
public:
	WindowBase(std::string name = "") : m_strname(name)
	{
		
	}
	virtual ~WindowBase() {}
	virtual void show() = 0;
	WindowBase(const WindowBase&) = delete;
	WindowBase& operator=(const WindowBase&) = delete;
protected:
	std::string m_strname;
};