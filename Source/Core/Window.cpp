#include "Window.h"

#include "Events.h"

float Window::m_AspectRatio;
int Window::m_Width;
int Window::m_Height;
float Window::m_Scale;
const char* Window::m_Title;
glm::vec3 Window::m_BackgroundColor;
GLFWwindow* Window::m_Window;

int Window::Init(int width, int height, const char* title, float scale, glm::vec3 backgroundColor)
{
    m_Width = width;
    m_Height = height;
    m_Scale = scale;
    m_AspectRatio = (float)m_Width / m_Height;
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

int Window::Init(const char* title, float scale, glm::vec3 backgroundColor)
{
    m_Width = 1920;
    m_Height = 1080;
    m_Scale = scale;
    m_AspectRatio = (float)m_Width / m_Height;
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

glm::vec2 Window::WorldToScreenPoint(glm::vec2 worldPoint)
{
    glm::vec2 screenPoint;
    screenPoint.x = glm::round((worldPoint.x / 2 / m_Scale / m_AspectRatio + 0.5f) * m_Width);
    screenPoint.y = glm::round((1 - (worldPoint.y / 2 / m_Scale + 0.5f)) * m_Height);
    return screenPoint;
}

glm::vec2 Window::ScreenToWorldPoint(glm::vec2 screenPoint)
{
    glm::vec2 worldPoint;
    worldPoint.x = (screenPoint.x / m_Width - 0.5f) * 2 * m_Scale * m_AspectRatio;
    worldPoint.y = -(screenPoint.y / m_Height - 0.5f) * 2 * m_Scale;
    return worldPoint;
}

void Window::Close()
{
    glfwSetWindowShouldClose(m_Window, true);
}

void Window::WindowResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    m_Width = width;
    m_Height = height;
    m_AspectRatio = (float)width / height;
}
