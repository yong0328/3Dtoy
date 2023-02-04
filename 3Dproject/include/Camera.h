#pragma once
#include "Base.h"
enum MOVE_DIR
{
	MOVE_RIGHT = 0,
	MOVE_LEFT,
	MOVE_FRONT,
	MOVE_BACK
};
enum SCROLL_DIR
{
	SCROLL_FRONT = 0,
	SCROLL_BACK
};
class Camera
{
public:
	Camera();
	~Camera();

	void update();
	void lookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 up);
	void Move(MOVE_DIR);
	void MouseMidScroll(SCROLL_DIR);

	glm::mat4 getMatrix();
private:
	glm::mat4 m_viewMtx;
	glm::vec3 m_pos;

	glm::vec3 m_target;
	glm::vec3 m_up;
	glm::vec3 m_right;   //actually,camera coordinate X axis
	glm::vec3 m_lookDir;

	float m_fMoveDis;
};

