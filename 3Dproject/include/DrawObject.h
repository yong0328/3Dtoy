#pragma once
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
	virtual void Draw() = 0;
private:
	long long generatoruuid() { return 0; }
private:
	long long uuid = 0;
};