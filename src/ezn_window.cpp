#include <iostream>
#include <cassert>
#include <ezn_window.h>
#include <ezn_winman.h>

namespace ezn
{

Window::Window(const Window::CreateParams &params)
{
    printf("create window\n");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    this->windowHandle = glfwCreateWindow(params.dimensions[0], params.dimensions[1], params.title, NULL, NULL);
    if(!this->windowHandle)
    {
        fprintf(stderr, "Unable to create window\n");
        return;
    }

    glfwMakeContextCurrent(this->windowHandle);

    this->input = new Input({this});

    this->winman = params.winman;
    winman->AddWindow(this);
}

Window::~Window()
{
    this->Close();
}

void Window::Close()
{
    this->winman->RemoveWindow(this);

    if(this->input)
    {
        delete this->input;
    }
    this->input = nullptr;

    if(this->windowHandle) 
    {
        printf("destroy window\n");
        glfwDestroyWindow(this->windowHandle);
    }
    this->windowHandle = nullptr;
}

void Window::Update()
{
    assert(("window update function is not set", this->onUpdate));
    this->onUpdate(this);
    if(this->input) 
    {
        if(glfwWindowShouldClose(this->windowHandle))
        {
            this->Close();
            return;
        }
        this->input->NextFrame();
        this->SwapBuffers();
    }
}

std::array<int,2> Window::GetFramebufferSize()
{
    std::array<int,2> dimensions = {};
    glfwGetFramebufferSize(this->windowHandle, &dimensions[0], &dimensions[1]);
    return dimensions;
}

void Window::SetFullscreen(int monitorIndex)
{
    GLFWmonitor *monitor = nullptr;
    int w = 800,h = 600;
    if(monitorIndex >= 0)
    {
        int monitorCount;
        GLFWmonitor **monitors = glfwGetMonitors(&monitorCount);
        monitorIndex = std::clamp(monitorIndex, 0, monitorCount);
        monitor = monitors[monitorIndex];

        glfwGetWindowSize(this->windowHandle, &w, &h);
    }

    glfwSetWindowMonitor(
        this->windowHandle,
        monitor,
        0, 0, w, h,
        GLFW_DONT_CARE
    );
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(this->windowHandle);
}


} // namespace ezn