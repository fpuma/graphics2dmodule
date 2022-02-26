#pragma once

#include <input/devices/ikeyboard.h>
#include <internal/input/devices/devicehelper.h>

namespace puma::app
{
    class Keyboard : public IKeyboard, public DeviceKeyStates<KeyboardKeyStates>
    {
    public:

        bool keyState( KeyboardKey _keyboardKey ) const override { return inputState( static_cast<InputId>(_keyboardKey) ); }
        bool keyPressed( KeyboardKey _keyboardKey ) const override { return inputPressed( static_cast<InputId>(_keyboardKey) ); }
        bool keyReleased( KeyboardKey _keyboardKey ) const override { return inputReleased( static_cast<InputId>(_keyboardKey) ); }

    protected:

        void internalClearStates() override {}
    };
}