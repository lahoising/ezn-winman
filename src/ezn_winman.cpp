#include <iostream>
#include <GLFW/glfw3.h>
#include <ezn_winman.h>

namespace ezn
{
    
Winman::Winman()
{
    if(!glfwInit())
    {
        printf("unable to initialize glfw\n");
        return;
    }
}

Winman::~Winman()
{
    glfwTerminate();
}

} // namespace ezn