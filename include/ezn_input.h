#ifndef __EZN_INPUT_H__
#define __EZN_INPUT_H__

#include <inttypes.h>
#include <unordered_map>

#include <ezn_input_codes.h>

struct GLFWwindow;

namespace ezn
{

class Window;

class Input
{
public:
    struct State
    {
        uint64_t keys[8];   // 512 bits for key state
    };

    struct CreateParams
    {
        Window *window;
    };

public:
    Input();
    Input(const CreateParams &params);
    ~Input();

    void NextFrame();

    bool IsKeyPressed(const KeyCode key) const;
    bool KeyJustPressed(const KeyCode key) const;
    bool KeyReleased(const KeyCode key) const;



private:
    void KeyEventCallback(const KeyCode key, const InputAction action);

private:
    State currentInputState;
    State previousInputState;
    Window *window;

private:
    static std::unordered_map<void*,Window*> handleToWindow;
    static void GlfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mod);

    static KeyCode GetKeyCode(const int key);
    static InputAction GetInputAction(const int action);
};

}

#endif