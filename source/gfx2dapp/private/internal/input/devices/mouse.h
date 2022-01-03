#pragma once

#include <input/devices/imouse.h>
#include <input/inputdefinitions.h>
#include <internal/input/devices/devicehelper.h>

namespace puma::app
{
    class Mouse : public IMouse, public DeviceKeyStates<MouseKeyStates>
    {
    public:

        bool buttonState( MouseKey _mouseKey ) const { return inputState( static_cast<InputId>(_mouseKey) ); }
        bool buttonPressed( MouseKey _mouseKey ) const { return inputPressed( static_cast<InputId>(_mouseKey) ); }
        bool buttonReleased( MouseKey _mouseKey ) const { return inputReleased( static_cast<InputId>(_mouseKey) ); }

        MousePosition getMousePosition() const override { return m_mousePosition; }

        void setMousePosition( MousePosition _mousePosition ) { m_mousePosition = _mousePosition; }

        void updateStates( u8 _sdlInputId, InputButtonEvent _buttonEvent );

    private:

        MousePosition m_mousePosition = {};
    };
}