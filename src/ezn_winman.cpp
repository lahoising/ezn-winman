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
    this->Close();
}

void Winman::Close()
{
    for(Window *ptr : this->windows)
        delete ptr;
    glfwTerminate();
}

void Winman::Update()
{
    glfwPollEvents();

    for(Window *ptr : this->windows)
    {
        ptr->Update();
    }

    while(!this->windowCloseQueue.empty())
    {
        this->windows.erase(this->windowCloseQueue.front());
        this->windowCloseQueue.pop();
    }
}

int Winman::GetMonitorsCount(){ int count; glfwGetMonitors(&count); return count; }

void Winman::ToggleVSync(bool on)
{
    glfwSwapInterval(on? 1 : 0);
}

void Winman::ErrorCallback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error (%d): %s\n", error, description);
}

} // namespace ezn