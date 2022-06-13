#include "Window.h"
#include "Sandbox.h"

int main()
{
    Window window;

    Sandbox sandbox;
    ((Application)sandbox).Start();
    sandbox.Start();


    while (!window.ShouldClose())
    {
        window.Clear();

        ((Application)sandbox).Update();
        sandbox.Update();

        window.Update();
    }

    return 0;
}