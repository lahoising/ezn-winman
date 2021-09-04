#ifndef __EZN_WINDOW_H__
#define __EZN_WINDOW_H__

#include <memory>
#include <functional>
#include <array>
#include <GLFW/glfw3.h>

#include <ezn_input.h>

namespace ezn
{

class Winman;

class Window
{
public:
    typedef std::function<void(Window*)> OnUpdate;

public:
    Window(Winman *winman);
    ~Window();

    void SwapBuffers();
    void Close();

    void Update();

    std::array<int,2> GetFramebufferSize();

    void *GetWindowHandle(){ return this->windowHandle; }
    Input &GetInput(){ return *this->input; }

public:
    OnUpdate onUpdate;

private:
    Winman *winman;
    GLFWwindow *windowHandle;
    Input *input;
};

} // namespace ezn

#endif