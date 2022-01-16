#pragma once

namespace puma::app
{
    enum class InputButtonEvent
    {
        Up,
        Down,
    };

    struct MousePosition
    {
        int x = 0;
        int y = 0;
    };

    struct JoystickPosition
    {
        float x = 0.0f;
        float y = 0.0f;
    };
}