#pragma once

#include "Window.h"
#include "GameObject.h"	

#include <glm/glm.hpp>

#define KEYS_NUM 1024
#define BUTTONS_NUM 8

class Events
{
	friend class Window;

private:
	static bool* m_Keys;
	static unsigned int* m_Frames;
	static unsigned int m_CurrentFrame;
	static glm::vec2 m_MousePos;
	static glm::vec2 m_MouseDelta;

	static void Init(GLFWwindow* window);
	static void OnUpdate();

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
public:
	static bool GetKeyDown(unsigned int keycode);
	static bool GetKeyUp(unsigned int keycode);
	static bool GetKey(unsigned int keycode);

	static bool GetMouseButtonDown(unsigned int button);
	static bool GetMouseButtonUp(unsigned int button);
	static bool GetMouseButton(unsigned int button);

	static bool MouseEntered(GameObject object);

	inline static glm::vec2 GetMousePos() { return m_MousePos; }
	inline static glm::vec2 GetMouseDelta() { return m_MouseDelta; }
};