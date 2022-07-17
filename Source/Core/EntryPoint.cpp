#include "Window.h"
#include "Events.h"

#include "../Game.h"

int main()
{
    Window::Init(640, 480, "hello world", glm::vec3(0.2f, 0.3f, 0.8f));

    Game app;
    app.Start();

    while (Window::Opened())
    {
        Window::Clear();
        
        app.Update();

        if (Events::GetKeyDown(KEY_ESCAPE))
        {
            Window::Close();
        }

        Window::OnUpdate();
    }

    Window::Terminate();
    return 0;
}