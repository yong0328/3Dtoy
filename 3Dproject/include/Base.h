#pragma once
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include <stdio.h>
#include "glad/glad.h"
#include <iostream>
#include <vector>
#include "stb_image.h"
#include "../glm/gtc/type_ptr.hpp"
#include "shader.h"
#include <memory>
#include <string>
enum SHOWMODE
{
	SHOW2D = 0,
	SHOW3D
};
struct Point2D
{
public:
	Point2D(float x = 0.0f,float y = 0.0f) : m_x(x),m_y(y) {}
	float m_x;
	float m_y;
};
struct Point3D: public Point2D
{
public:
	Point3D(float x = 0.0f, float y = 0.0f,float z = 0.0f) :Point2D(x,y),m_z(z) {}
	float m_z;
};