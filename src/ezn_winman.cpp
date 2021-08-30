#include <iostream>
#include <GLFW/glfw3.h>
#include <ezn_winman.h>

namespace ezn
{
    
Winman::Winman()
{
    // if(!glfwInit())
    // {
    //     printf("unable to initialize glfw\n");
    //     return;
    // }

    glfwSetErrorCallback(Winman::ErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    glfwDestroyWindow(window);

}

Winman::~Winman()
{
    glfwTerminate();
}

void Winman::ErrorCallback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error (%d): %s\n", error, description);
}

} // namespace ezn