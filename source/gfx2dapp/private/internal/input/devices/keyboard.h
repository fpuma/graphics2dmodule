#pragma once

#include <internal/input/devices/devicehelper.h>

namespace puma::app
{
    class Keyboard : public DeviceKeyStates<KeyboardKeyStates>
    {
    public:

        void updateStates( s32 _sdlInputId, InputButtonEvent _buttonEvent );
    };
}