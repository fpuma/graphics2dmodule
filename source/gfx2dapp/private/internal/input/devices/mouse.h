#pragma once

#include <input/devices/imouse.h>
#include <input/inputdefinitions.h>
#include <internal/input/devices/devicehelper.h>

namespace puma::app
{
    class Mouse : public IMouse, public DeviceKeyStates<MouseKeyStates>
    {
    public:

        bool buttonState( MouseButton _mouseKey ) const override { return inputState( static_cast<InputId>(_mouseKey) ); }
        bool buttonPressed( MouseButton _mouseKey ) const override { return inputPressed( static_cast<InputId>(_mouseKey) ); }
        bool buttonReleased( MouseButton _mouseKey ) const override { return inputReleased( static_cast<InputId>(_mouseKey) ); }

        MousePosition getMousePosition() const override { return m_mousePosition; }

        void setMousePosition( MousePosition _mousePosition ) { m_mousePosition = _mousePosition; }

    private:

        MousePosition m_mousePosition = {};
    };
}