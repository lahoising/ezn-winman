#ifndef __EZN_INPUT_H__
#define __EZN_INPUT_H__

#include <inttypes.h>
#include <vector>
#include <functional>
#include <unordered_map>

#include <ezn_input_codes.h>

struct GLFWwindow;

namespace ezn
{

class Window;

struct ModdedKey
{
    KeyCode key;
    bool ctrl, shift, alt;

    bool operator==(const ModdedKey &other) const;
};

class Input
{
public:
    typedef std::function<void(const KeyCode key, const InputAction action, const KeyMod mod)> EventCallback;

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

    void AddKeyboardCallback(EventCallback callback);
    void RemoveKeyboardCallback(EventCallback callback);

private:
    void KeyEventCallback(const KeyCode key, const InputAction action, const KeyMod mod);

private:
    State currentInputState;
    State previousInputState;
    Window *window;
    std::vector<EventCallback> callbacks;

private:
    static std::unordered_map<void*,Window*> handleToWindow;
    static void GlfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mod);

    static KeyCode GetKeyCode(const int key);
    static InputAction GetInputAction(const int action);
    static KeyMod GetKeyMod(const int mod);
};

}

namespace std
{
    template<>
    struct hash<ezn::ModdedKey>
    {
        std::size_t operator()(const ezn::ModdedKey &key) const;
    };
}

#endif