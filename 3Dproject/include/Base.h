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
enum SHOWMODE
{
	SHOW2D = 0,
	SHOW3D
};
struct Point2D
{
	float x;
	float y;
};
struct Point3D: public Point2D
{
	float z;
};