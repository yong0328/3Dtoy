#pragma once
#include "DrawObject.h"
#include "shader.h"
class BoxObject : public BaseObj 
{
public:
	BoxObject(float d, float w, float h);
	virtual void Draw() override;
private:
	unsigned int CreateVAO();
private:
	float m_fd;
	float m_fw;
	float m_fh;

	unsigned int VAO;
	unsigned int VBO;

	shader m_shader;
};
