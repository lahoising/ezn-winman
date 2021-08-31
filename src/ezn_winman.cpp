#include <iostream>
#include <GLFW/glfw3.h>

#include <ezn_winman.h>
#include <ezn_window.h>

namespace ezn
{
    
Winman::Winman()
{
    if(!glfwInit())
    {
        printf("unable to initialize glfw\n");
        return;
    }

    glfwSetErrorCallback(Winman::ErrorCallback);
}

Winman::~Winman()
{
    for(Window *ptr : this->windows)
        delete ptr;
    glfwTerminate();
}

Window *Winman::CreateWindow()
{
    Window *window = new Window();
    this->windows.emplace(window);
    return window;
}

void Winman::Update()
{
    glfwPollEvents();
}

void Winman::ErrorCallback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error (%d): %s\n", error, description);
}

} // namespace ezn