#include <iostream>
#include <cassert>
#include <ezn_window.h>
#include <ezn_winman.h>

namespace ezn
{

Window::Window(Winman *winman)
{
    printf("create window\n");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    this->windowHandle = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if(!this->windowHandle)
    {
        fprintf(stderr, "Unable to create window\n");
        return;
    }

    glfwMakeContextCurrent(this->windowHandle);

    this->input = new Input({this});

    this->winman = winman;
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
        this->input->NextFrame();
        if(glfwWindowShouldClose(this->windowHandle))
        {
            this->Close();
        }
    }
}

std::array<int,2> Window::GetFramebufferSize()
{
    std::array<int,2> dimensions = {};
    glfwGetFramebufferSize(this->windowHandle, &dimensions[0], &dimensions[1]);
    return dimensions;
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(this->windowHandle);
}


} // namespace ezn