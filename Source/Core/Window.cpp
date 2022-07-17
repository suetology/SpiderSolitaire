#include "Window.h"

#include "Events.h"

float Window::m_AspectRatio;
int Window::m_Width;
int Window::m_Heigth;
const char* Window::m_Title;
glm::vec3 Window::m_BackgroundColor;
GLFWwindow* Window::m_Window;

#include <iostream>
int Window::Init(int width, int height, const char* title, glm::vec3 backgroundColor)
{
    m_Width = width;
    m_Heigth = height;
    m_AspectRatio = (float)m_Width / m_Heigth;
    m_Title = title;
    m_BackgroundColor = backgroundColor;

    if (!glfwInit())
        return -1;

    m_Window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!m_Window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(m_Window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        return -1;
    }

    Events::Init(m_Window);

    glfwSetWindowSizeCallback(m_Window, WindowResizeCallback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 0;
}

int Window::Init(const char* title, glm::vec3 backgroundColor)
{
    m_Width = 1920;
    m_Heigth = 1080;
    m_AspectRatio = (float)m_Width / m_Heigth;
    m_Title = title;
    m_BackgroundColor = backgroundColor;

    if (!glfwInit())
        return -1;

    m_Window = glfwCreateWindow(1920, 1080, title, glfwGetPrimaryMonitor(), NULL);

    if (!m_Window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(m_Window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        return -1;
    }

    Events::Init(m_Window);

    glfwSetWindowSizeCallback(m_Window, WindowResizeCallback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 0;
}

bool Window::Opened()
{
	return !glfwWindowShouldClose(m_Window);
}

void Window::OnUpdate()
{
    Events::OnUpdate();

    glfwSwapBuffers(m_Window);
    glfwPollEvents();

}

void Window::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(m_BackgroundColor.r, m_BackgroundColor.g, m_BackgroundColor.b, 1.0f);
}

void Window::Terminate()
{
    glfwTerminate();
}

void Window::Close()
{
    glfwSetWindowShouldClose(m_Window, true);
}

void Window::WindowResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    m_Width = width;
    m_Heigth = height;
    m_AspectRatio = (float)width / height;
}
