#include "Window.h"
#include "Sandbox.h"

int main()
{
    Sandbox sandbox;
    ((Application)sandbox).Start();
    sandbox.Start();

    Window window;

    while (!window.ShouldClose())
    {
        window.Clear();

        ((Application)sandbox).Update();
        sandbox.Update();

        window.Update();
    }

    return 0;
}