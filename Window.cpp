#include "Window.h"

Window::Window(const std::string title, int width, int height)
	: m_Title(title), m_Width(width), m_Height(height)
{
	Init();
}

Window::~Window()
{
    glfwTerminate();
}

int Window::Init()
{
    if (!glfwInit())
    {
        return -1;
    }

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);

    if (!m_Window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(m_Window);
	return 0;
}

void Window::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Update()
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(m_Window);
}
