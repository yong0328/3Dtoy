#pragma once
#include "DrawObject.h"
class BoxObject : public BaseObj 
{
public:
	BoxObject(float d, float w,float h)
		:BaseObj()
	{
		m_fd = d;
		m_fw = w;
		m_fh = h;
	}
	virtual void Draw() override;

private:
	float m_fd;
	float m_fw;
	float m_fh;
};
