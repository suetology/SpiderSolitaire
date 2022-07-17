#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window
{
public:
	static int Init(int width, int height, const char* title, glm::vec3 backgroundColor = glm::vec3(0.0f));
	static int Init(const char* title, glm::vec3 backgroundColor = glm::vec3(0.0f));
	static bool Opened();
	static void OnUpdate();
	static void Clear();
	static void Close();
	static void Terminate();
	inline static GLFWwindow* GetWindow() { return m_Window; }
	inline static int GetWidth() { return m_Width; }
	inline static int GetHeight() { return m_Heigth; }
	inline static float GetAspectRatio() { return m_AspectRatio; }

private:
	static float m_AspectRatio;
	static int m_Width, m_Heigth;
	static const char* m_Title;
	static glm::vec3 m_BackgroundColor;
	static GLFWwindow* m_Window;

	static void WindowResizeCallback(GLFWwindow* window, int width, int height);
};

