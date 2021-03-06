#include <functional>
#include <algorithm>
#include <iostream>
#include <GLFW/glfw3.h>

#include <ezn_window.h>
#include <ezn_input.h>

namespace ezn
{

constexpr int keyStateSizeInBits = sizeof(uint64_t) * 8;
constexpr int keyStateIndex(int key){ return key / keyStateSizeInBits; }
constexpr int keyBit(int key){ return 1 << (key % keyStateSizeInBits); }

std::unordered_map<void*,Window*> Input::handleToWindow;
    
Input::Input(){}

Input::Input(const Input::CreateParams &params)
    : window(params.window), currentInputState({}), previousInputState({})
{
    GLFWwindow *windowHandle = (GLFWwindow*)this->window->GetWindowHandle();
    Input::handleToWindow[windowHandle] = this->window;
    glfwSetKeyCallback(windowHandle, Input::GlfwKeyCallback);
}

Input::~Input()
{
    Input::handleToWindow.erase(this->window->GetWindowHandle());
}

void Input::NextFrame()
{
    this->previousInputState = this->currentInputState;
}

bool Input::IsKeyPressed(const KeyCode key) const
{
    int keyStateIndex = key / (sizeof(uint64_t) * 8);
    return this->currentInputState.keys[keyStateIndex] & keyBit(key);
}

bool Input::KeyJustPressed(const KeyCode key) const
{
    int stateIndex = keyStateIndex(key);
    int bit = keyBit(key);
    return  (this->currentInputState.keys[stateIndex] & bit) &&
            ((this->previousInputState.keys[stateIndex] & bit) == 0);
}

bool Input::KeyReleased(const KeyCode key) const
{
    int stateIndex = keyStateIndex(key);
    int bit = keyBit(key);
    return  ((this->currentInputState.keys[stateIndex] & bit) == 0) &&
            (this->previousInputState.keys[stateIndex] & bit);
}

void Input::KeyEventCallback(const KeyCode key, const InputAction action, const KeyMod mod)
{
    switch (action)
    {
    case InputAction::ACTION_PRESSED:
        this->currentInputState.keys[keyStateIndex(key)] |= keyBit(key);
        break;
    case InputAction::ACTION_RELEASED:
        this->currentInputState.keys[keyStateIndex(key)] &= ~keyBit(key);
        break;
    default: break;
    }

    for(auto &callback : this->callbacks)
        callback(key, action, mod);
}

void Input::AddKeyboardCallback(EventCallback callback)
{
    this->callbacks.push_back(callback);
}

void Input::RemoveKeyboardCallback(EventCallback callback)
{
}

void Input::GlfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mod)
{
    Input::handleToWindow[window]->GetInput().KeyEventCallback(
        Input::GetKeyCode(key), 
        Input::GetInputAction(action),
        Input::GetKeyMod(mod));
}

KeyCode Input::GetKeyCode(const int key)
{
    switch (key)
    {
    case GLFW_KEY_Q: return KeyCode::KEY_Q;
    case GLFW_KEY_W: return KeyCode::KEY_W;
    case GLFW_KEY_E: return KeyCode::KEY_E;
    case GLFW_KEY_R: return KeyCode::KEY_R;
    case GLFW_KEY_T: return KeyCode::KEY_T;
    case GLFW_KEY_Y: return KeyCode::KEY_Y;
    case GLFW_KEY_U: return KeyCode::KEY_U;
    case GLFW_KEY_I: return KeyCode::KEY_I;
    case GLFW_KEY_O: return KeyCode::KEY_O;
    case GLFW_KEY_P: return KeyCode::KEY_P;
    case GLFW_KEY_A: return KeyCode::KEY_A;
    case GLFW_KEY_S: return KeyCode::KEY_S;
    case GLFW_KEY_D: return KeyCode::KEY_D;
    case GLFW_KEY_F: return KeyCode::KEY_F;
    case GLFW_KEY_G: return KeyCode::KEY_G;
    case GLFW_KEY_H: return KeyCode::KEY_H;
    case GLFW_KEY_J: return KeyCode::KEY_J;
    case GLFW_KEY_K: return KeyCode::KEY_K;
    case GLFW_KEY_L: return KeyCode::KEY_L;
    case GLFW_KEY_Z: return KeyCode::KEY_Z;
    case GLFW_KEY_X: return KeyCode::KEY_X;
    case GLFW_KEY_C: return KeyCode::KEY_C;
    case GLFW_KEY_V: return KeyCode::KEY_V;
    case GLFW_KEY_B: return KeyCode::KEY_B;
    case GLFW_KEY_N: return KeyCode::KEY_N;
    case GLFW_KEY_M: return KeyCode::KEY_M;

    case GLFW_KEY_SPACE: return KeyCode::KEY_SPACE;
    case GLFW_KEY_ESCAPE: return KeyCode::KEY_ESC;
    case GLFW_KEY_ENTER: return KeyCode::KEY_ENTER;
    case GLFW_KEY_BACKSPACE: return KeyCode::KEY_BACKSPACE;
    case GLFW_KEY_LEFT: return KeyCode::KEY_LEFT;
    case GLFW_KEY_RIGHT: return KeyCode::KEY_RIGHT;
    case GLFW_KEY_UP: return KeyCode::KEY_UP;
    case GLFW_KEY_DOWN: return KeyCode::KEY_DOWN;
    case GLFW_KEY_0: return KeyCode::KEY_0;
    case GLFW_KEY_1: return KeyCode::KEY_1;
    case GLFW_KEY_2: return KeyCode::KEY_2;
    case GLFW_KEY_3: return KeyCode::KEY_3;
    case GLFW_KEY_4: return KeyCode::KEY_4;
    case GLFW_KEY_5: return KeyCode::KEY_5;
    case GLFW_KEY_6: return KeyCode::KEY_6;
    case GLFW_KEY_7: return KeyCode::KEY_7;
    case GLFW_KEY_8: return KeyCode::KEY_8;
    case GLFW_KEY_9: return KeyCode::KEY_9;
    case GLFW_KEY_LEFT_CONTROL: return KeyCode::KEY_CTRL;
    case GLFW_KEY_LEFT_ALT: return KeyCode::KEY_ALT;
    case GLFW_KEY_LEFT_SHIFT: return KeyCode::KEY_SHIFT;

    default: return KeyCode::KEY_INVALID;
    }
}

InputAction Input::GetInputAction(const int action)
{
    switch (action)
    {
    case GLFW_PRESS: return InputAction::ACTION_PRESSED;
    case GLFW_RELEASE: return InputAction::ACTION_RELEASED;
    default: return InputAction::ACTION_INVALID;
    }
}

KeyMod Input::GetKeyMod(const int mod)
{
    switch (mod)
    {
    case GLFW_MOD_CONTROL: return KeyMod::MOD_CTRL;
    case GLFW_MOD_SHIFT: return KeyMod::MOD_SHIFT;
    case GLFW_MOD_ALT: return KeyMod::MOD_ALT;
    default: return KeyMod::MOD_UNKNOWN;
    }
}

bool ModdedKey::operator==(const ModdedKey &other) const
{
    return this->key == other.key &&
        this->ctrl == other.ctrl &&
        this->shift == other.shift &&
        this->alt == other.alt;
}

} // namespace ezn

namespace std
{

std::size_t hash<ezn::ModdedKey>::operator()(const ezn::ModdedKey &key) const
{
    std::size_t ret = key.key << 3;
    if(key.ctrl) ret |= 1 << 2;
    if(key.shift) ret |= 1 << 1;
    if(key.alt) ret |= 1;
    return ret;
}

}