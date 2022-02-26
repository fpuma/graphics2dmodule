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

        bool wasMousePositionUpdated() const override { return m_mousePositionUpdated; }
        MousePosition getMousePosition() const override { return m_mousePosition; }
        MouseWheelState getMouseWheelState() const override { return m_wheelState; }

        void setMousePosition( MousePosition _mousePosition ) { m_mousePosition = _mousePosition; m_mousePositionUpdated = true; }
        void setMouseWheelState( MouseWheelState _mouseWheelState ) { m_wheelState = _mouseWheelState; }

    protected:

        void internalClearStates() { m_mousePositionUpdated = false; }

    private:

        bool m_mousePositionUpdated = false;
        MousePosition m_mousePosition = {};
        MouseWheelState m_wheelState = MouseWheelState::MW_IDLE;
    };
}