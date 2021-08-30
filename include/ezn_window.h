#ifndef __EZN_WINDOW_H__
#define __EZN_WINDOW_H__

#include <memory>
#include <GLFW/glfw3.h>

namespace ezn
{

class Window
{
public:
    Window();
    ~Window();

private:
    GLFWwindow *windowHandle;
};

} // namespace ezn

#endif