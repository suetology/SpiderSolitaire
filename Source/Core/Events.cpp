#include "Events.h"

#include <GLFW/glfw3.h>
#include <string.h>

bool* Events::m_Keys;
unsigned int* Events::m_Frames;
unsigned int Events::m_CurrentFrame;
glm::vec2 Events::m_MousePos;
glm::vec2 Events::m_MouseDelta;

void Events::Init(GLFWwindow* window)
{
	m_CurrentFrame = 0;
	m_Keys = new bool[KEYS_NUM + BUTTONS_NUM];
	m_Frames = new unsigned int[KEYS_NUM + BUTTONS_NUM];

	memset(m_Keys, false, (KEYS_NUM + BUTTONS_NUM) * sizeof(bool));
	memset(m_Frames, 0, (KEYS_NUM + BUTTONS_NUM) * sizeof(unsigned int));

	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetCursorPosCallback(window, CursorPosCallback);
}

void Events::OnUpdate()
{
	m_MouseDelta = glm::vec2(0.0f);
	m_CurrentFrame++;
}

bool Events::GetKeyDown(unsigned int keycode)
{
	return m_Keys[keycode] && m_Frames[keycode] == m_CurrentFrame;
}

bool Events::GetKeyUp(unsigned int keycode)
{
	return !m_Keys[keycode] && m_Frames[keycode] == m_CurrentFrame;
}

bool Events::GetKey(unsigned int keycode)
{
	return m_Keys[keycode];
}

bool Events::GetMouseButtonDown(unsigned int button)
{
	return m_Keys[KEYS_NUM + button] && m_Frames[KEYS_NUM + button] == m_CurrentFrame;
}

bool Events::GetMouseButtonUp(unsigned int button)
{
	return !m_Keys[KEYS_NUM + button] && m_Frames[KEYS_NUM + button] == m_CurrentFrame;
}

bool Events::GetMouseButton(unsigned int button)
{
	return m_Keys[KEYS_NUM + button];
}

bool Events::MouseEntered(GameObject object)
{
	

	return false;
}

void Events::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		m_Keys[key] = true;
		m_Frames[key] = m_CurrentFrame;
	}
	else if (action == GLFW_RELEASE)
	{
		m_Keys[key] = false;
		m_Frames[key] = m_CurrentFrame;
	}
}

void Events::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		m_Keys[KEYS_NUM + button] = true;
		m_Frames[KEYS_NUM + button] = m_CurrentFrame;
	}
	else if (action == GLFW_RELEASE)
	{
		m_Keys[KEYS_NUM + button] = false;
		m_Frames[KEYS_NUM + button] = m_CurrentFrame;
	}
}

#include <iostream>
void Events::CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	float xPos = static_cast<float>(xpos);
	float yPos = static_cast<float>(ypos);

	glm::vec2 newMousePos = glm::vec2(xPos, yPos);

	m_MouseDelta.x = newMousePos.x - m_MousePos.x;
	m_MouseDelta.y = m_MousePos.y - newMousePos.y;

	m_MousePos = newMousePos;
}
