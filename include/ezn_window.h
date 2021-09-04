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
    struct CreateParams
    {
        std::array<int,2> dimensions;
        const char *title;
        Winman *winman;
    };

public:
    Window(const CreateParams &params);
    ~Window();

    void SwapBuffers();
    void Close();

    void Update();

    std::array<int,2> GetFramebufferSize();
    void SetFullscreen(int monitorIndex);

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