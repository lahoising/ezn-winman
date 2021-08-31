#ifndef __EZN_WINDOW_H__
#define __EZN_WINDOW_H__

#include <memory>
#include <GLFW/glfw3.h>

#include <ezn_input.h>

namespace ezn
{

class Window
{
public:
    Window();
    ~Window();

    void SwapBuffers();

    const Input &GetInput(){ return this->input; }

private:
    GLFWwindow *windowHandle;
    Input input;
};

} // namespace ezn

#endif