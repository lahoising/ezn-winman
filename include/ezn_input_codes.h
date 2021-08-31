#ifndef __EZN_INPUT_CODES_H__
#define __EZN_INPUT_CODES_H__

namespace ezn
{
    
enum KeyCode
{
    KEY_Q = 0,
    KEY_W,
    KEY_E,
    KEY_R,
    KEY_T,
    KEY_Y,
    KEY_U,
    KEY_I,
    KEY_O,
    KEY_P,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_Z,
    KEY_X,
    KEY_C,
    KEY_V,
    KEY_B,
    KEY_N,
    KEY_M,

    KEY_SPACE,
    KEY_ESC,
    KEY_ENTER,
    KEY_BACKSPACE,

    KEY_LEFT,
    KEY_RIGHT,
    KEY_UP,
    KEY_DOWN,

    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,

    KEY_CTRL,
    KEY_ALT,
    KEY_SHIFT,
};

enum InputAction
{
    ACTION_PRESSED,
    ACTION_RELEASED
};

} // namespace ezn

#endif