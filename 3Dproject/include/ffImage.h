#pragma once
#include "Base.h"
class ffImage
{
private:
	int m_width;
	int m_height;
	int m_picType;
	ffRGBA* m_data;
public:
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	int getPicType() const { return m_picType; }
	ffRGBA* getData()const { return m_data; }

	ffRGBA getColor(int x, int y) const 
	{
		if (x < 0 || x > m_width - 1 || y < 0 || y > m_height - 1)
			return ffRGBA(0,0,0,0);
		return m_data[y * m_width + x];
	}
	ffImage(int width = 0, int height = 0, int picType = 0, ffRGBA* data = nullptr)
		:m_width(width),m_height(height),m_picType(picType),m_data(data)
	{
		int size = m_width * m_height;
		if (m_data && size)
		{
			m_data = new ffRGBA[size];
			memcpy(m_data,data,sizeof(ffRGBA) * size);
		}
	}
	~ffImage()
	{
		if (m_data != nullptr)
		{
			delete[] m_data;
			m_data = nullptr;
		}
	}
public:
	static ffImage* readFromFile(const char* filename);
};

