#pragma once

namespace puma::nina
{

    using InputId = u32;
    constexpr InputId kInvalidInputId = kMaxU32;
    
    enum class MouseButton : InputId
    {
        MB_LEFT,
        MB_MIDDLE,
        MB_RIGHT,
        MB_X1,
        MB_X2,
        TotalButtons,
    };

    enum class MouseWheelState : InputId
    {
        MW_IDLE,
        MW_UP,
        MW_RIGHT,
        MW_DOWN,
        MW_LEFT,
    };

    enum class KeyboardKey : InputId
    {
        KB_RETURN,
        KB_ESCAPE,
        KB_BACKSPACE,
        KB_TAB,
        KB_SPACE,
        KB_EXCLAIM,   // !
        KB_QUOTEDBL,  // "
        KB_HASH,      // #
        KB_PERCENT,   // %
        KB_DOLLAR,    // $
        KB_AMPERSAND, // &,
        KB_QUOTE,     // ',
        KB_LEFTPAREN, // (,
        KB_RIGHTPAREN,// ),
        KB_ASTERISK,  // *,
        KB_PLUS,      // +,
        KB_COMMA,     // ,,
        KB_MINUS,     // -,
        KB_PERIOD,    // .,
        KB_SLASH,     // /,

        KB_0,
        KB_1,
        KB_2,
        KB_3,
        KB_4,
        KB_5,
        KB_6,
        KB_7,
        KB_8,
        KB_9,

        KB_COLON,     // :
        KB_SEMICOLON, // ;
        KB_LESS,      // <
        KB_EQUALS,    // =
        KB_GREATER,   // >
        KB_QUESTION,  // ?
        KB_AT,        // @

        KB_LEFTBRACKET, // [
        KB_BACKSLASH,   // '\'
        KB_RIGHTBRACKET,// ]
        KB_CARET,       // ^
        KB_UNDERSCORE,  // _
        KB_BACKQUOTE,   // `

        KB_A,
        KB_B,
        KB_C,
        KB_D,
        KB_E,
        KB_F,
        KB_G,
        KB_H,
        KB_I,
        KB_J,
        KB_K,
        KB_L,
        KB_M,
        KB_N,
        KB_O,
        KB_P,
        KB_Q,
        KB_R,
        KB_S,
        KB_T,
        KB_U,
        KB_V,
        KB_W,
        KB_X,
        KB_Y,
        KB_Z,

        KB_CAPSLOCK,

        KB_F1,
        KB_F2,
        KB_F3,
        KB_F4,
        KB_F5,
        KB_F6,
        KB_F7,
        KB_F8,
        KB_F9,
        KB_F10,
        KB_F11,
        KB_F12,

        KB_PRINTSCREEN,
        KB_SCROLLLOCK,
        KB_PAUSE,
        KB_INSERT,
        KB_HOME,
        KB_PAGEUP,
        KB_DELETE,
        KB_END,
        KB_PAGEDOWN,
        KB_RIGHT,
        KB_LEFT,
        KB_DOWN,
        KB_UP,

        KB_NUMLOCKCLEAR,
        KB_NUM_DIVIDE,
        KB_NUM_MULTIPLY,
        KB_NUM_MINUS,
        KB_NUM_PLUS,
        KB_NUM_ENTER,
        KB_NUM_1,
        KB_NUM_2,
        KB_NUM_3,
        KB_NUM_4,
        KB_NUM_5,
        KB_NUM_6,
        KB_NUM_7,
        KB_NUM_8,
        KB_NUM_9,
        KB_NUM_0,
        KB_NUM_PERIOD,

        KB_APPLICATION, //Windows context menu key

        KB_LCTRL,
        KB_LSHIFT,
        KB_LALT,
        KB_LGUI, //Left windows key
        KB_RCTRL,
        KB_RSHIFT,
        KB_RALT,
        KB_RGUI, //Right windows key


        TotalKeys,
    };

    enum class ControllerButton : InputId
    {
        CB_DPAD_UP,
        CB_DPAD_RIGHT,
        CB_DPAD_DOWN,
        CB_DPAD_LEFT,
        CB_A,
        CB_B,
        CB_X,
        CB_Y,
        CB_LB,
        CB_RB,
        CB_SELECT,
        CB_START,
        CB_LSTICK,
        CB_RSTICK,
        TotalButtons,
    };

    enum class ControllerJoystickAxis : InputId
    {
        CJ_LSTICK_X,
        CJ_LSTICK_Y,
        CJ_RSTICK_X,
        CJ_RSTICK_Y,
    };

    enum class ControllerTrigger : InputId
    {
        CT_LTRIGGER,
        CT_RTRIGGER,
    };
}