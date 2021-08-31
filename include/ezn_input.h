#ifndef __EZN_INPUT_H__
#define __EZN_INPUT_H__

#include <inttypes.h>
#include <unordered_map>

#include <ezn_input_codes.h>

namespace ezn
{

class Input
{
public:
    struct State
    {
        uint64_t keys[8];   // 512 bits for key state
    };

    struct CreateParams
    {
        void *windowHandle;
    };

public:
    Input();
    Input(const CreateParams &params);
    ~Input();

private:
    State currentInputState;
    State previousInputState;
    void *windowHandle;
    void KeyEventCallback(KeyCode key, InputAction action);

private:
    static std::unordered_map<void*,Input*> windowHandleToInput;
    static void GlfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mod);

    static KeyCode GetKeyCode(int key);
    static InputAction GetInputAction(int action);
};

}

#endif