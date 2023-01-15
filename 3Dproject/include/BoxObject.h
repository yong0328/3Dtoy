#pragma once
#include "DrawObject.h"
class BoxObject : public BaseObj 
{
public:
	BoxObject(float d, float w, float h);
	virtual void Render() override;
private:
	unsigned int CreateVAO();
private:
	float m_fd;
	float m_fw;
	float m_fh;


};
