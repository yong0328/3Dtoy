#include "Camera.h"

void Camera::update()
{
	//m_target = m_pos + m_front;
	m_viewMtx = glm::lookAt(m_pos, m_target, m_up);
}
glm::mat4 Camera::getMatrix()
{
	return m_viewMtx;
}
void Camera::lookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 up)
{
	m_pos = pos;
	m_target = target;
	m_up = glm::normalize(up);

	m_lookDir = glm::normalize(target - pos);
	m_right = glm::normalize(glm::cross(m_lookDir, m_up));
}
void Camera::MouseMidScroll(SCROLL_DIR dir)
{
	m_right = glm::normalize(glm::cross(m_lookDir, m_up));
	switch (dir)
	{
	case SCROLL_FRONT:
	{
		m_pos += m_lookDir * m_fMoveDis;
		m_lookDir = m_target - m_target;
		break;
	}
	case SCROLL_BACK:
	{
		m_pos -= m_lookDir * m_fMoveDis;
		m_lookDir = m_target - m_target;
		break;
	}
	default:
		break;
	}
}
void Camera::Move(MOVE_DIR dir)
{
	//adjust camera position
	//m_lookdir not change,so m_target change
	m_right = glm::normalize(glm::cross(m_lookDir, m_up));
	switch (dir)
	{
	case MOVE_RIGHT:
	{
		//adjust camera position
		//m_lookdir not change,so m_target change
		m_pos -= m_right * m_fMoveDis;
		m_target = m_pos + m_lookDir;
		break;
	}
	case MOVE_LEFT:
	{
		//adjust camera position
		//m_lookdir not change,so m_target change
		m_pos += m_right * m_fMoveDis;
		m_target = m_pos + m_lookDir;
		break;
	}
	case MOVE_FRONT:
	{
		//adjust camera position
		m_pos += m_up * m_fMoveDis;
		m_lookDir = m_target - m_pos;
		//m_target can be changed or not;
		//depends on your needs;
		//m_target = m_pos + m_lookDir;
		break;
	}
	case MOVE_BACK:
	{
		//adjust camera position
		m_pos -= m_up * m_fMoveDis;
		m_lookDir = m_target - m_pos;
		//m_target can be changed or not;
		//depends on your needs;
		//m_target = m_pos + m_lookDir;
		break;
	}
	default:
		break;
	}
	
}
Camera::Camera()
{
	m_viewMtx = glm::mat4(1.0f);
	m_pos = glm::vec3(1.0f);

	m_target = glm::vec3(1.0f);
	m_up = glm::vec3(1.0f);
	m_lookDir = glm::vec3(1.0f);

	m_fMoveDis = 0.01f;
}

Camera::~Camera()
{
}