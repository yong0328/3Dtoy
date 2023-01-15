#pragma once
#include "shader.h"
class BaseObj
{
public:
	BaseObj() {
		uuid = generatoruuid();
	}
	BaseObj(const BaseObj&)
	{
		uuid = generatoruuid();
	}
	BaseObj& operator=(const BaseObj&)
	{
		uuid = generatoruuid();
	}
public:
	virtual void Render() = 0;
private:
	long long generatoruuid() { return 0; }

protected:
	long long uuid = 0;
	unsigned int VAO;
	shader m_shader;
};