#pragma once

#include <input/inputdefinitions.h>
#include <internal/input/devices/devicehelper.h>

namespace puma::app
{
    class Mouse : public DeviceKeyStates<MouseKeyStates>
    {
    public:

        void updateStates( u8 _sdlInputId, InputButtonEvent _buttonEvent );
        void setMousePosition( MousePosition _mousePosition ) { m_mousePosition = _mousePosition; }
        MousePosition getMousePosition() const { return m_mousePosition; }

    private:

        MousePosition m_mousePosition = {};
    };
}