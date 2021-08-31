#include <functional>
#include <iostream>
#include <GLFW/glfw3.h>
#include <ezn_input.h>

namespace ezn
{

std::unordered_map<void*,Input*> Input::windowHandleToInput;
    
Input::Input(){}

Input::Input(const Input::CreateParams &params)
    : windowHandle(params.windowHandle)
{
    Input::windowHandleToInput[this->windowHandle] = this;
    glfwSetKeyCallback((GLFWwindow*)this->windowHandle, Input::GlfwKeyCallback);
}

Input::~Input()
{
    Input::windowHandleToInput.erase(this->windowHandle);
}

void Input::KeyEventCallback(int key, int action)
{
    printf("something pressed\n");
}

void Input::GlfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mod)
{
    Input::windowHandleToInput[window]->KeyEventCallback(key, action);
}

} // namespace ezn