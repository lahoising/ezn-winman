#ifndef __EZN_INPUT_H__
#define __EZN_INPUT_H__

#include <inttypes.h>
#include <unordered_map>

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
    void KeyEventCallback(int key, int action);

private:
    static std::unordered_map<void*,Input*> windowHandleToInput;
    static void GlfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mod);
};

}

#endif