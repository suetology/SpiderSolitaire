#pragma once

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <string>

class Window
{
public:
	Window(const std::string title = "The game", int width = 1280, int height = 720);
	virtual ~Window();

	int Init();
	void Clear();
	void Update();
	bool ShouldClose();

private:
	GLFWwindow* m_Window;
	std::string m_Title;
	int m_Width, m_Height;
};

