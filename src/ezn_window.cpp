#include <iostream>
#include <ezn_window.h>

namespace ezn
{

Window::Window ()
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

    this->input = Input({this->windowHandle});
}

Window::~Window()
{
    if(this->windowHandle) 
    {
        printf("destroy window\n");
        glfwDestroyWindow(this->windowHandle);
    }
    this->windowHandle = nullptr;
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(this->windowHandle);
}


} // namespace ezn