#include "Window.h"
#include "Events.h"

#include "../Game.h"

int main()
{
    Window::Init(640, 480, "Spider Solitaire", 2.5f, glm::vec3(0.1f, 0.6f, 0.0f));

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