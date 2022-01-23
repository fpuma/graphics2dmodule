#pragma once

#include <input/inputdefinitions.h>
#include <input/inputids.h>

namespace puma::app
{
    class IInputListener
    {
    public:

        virtual ~IInputListener() {}

        virtual void onKeyboardKey( KeyboardKey _key ) const = 0;
        
        virtual void onMouseButton( MouseButton _button ) const = 0;
        virtual void onMouseWheel( MouseWheelState _wheelState ) const = 0;
        virtual void onMousePosition( MousePosition _wheelState ) const = 0;

        virtual void onControllerButton( ControllerId _id, ControllerButton _buttonId) const = 0;
        virtual void onControllerJoystick( ControllerId _id, ControllerJoystick _joystickId, float _joystickValue ) const = 0;
        virtual void onControllerTrigger( ControllerId _id, ControllerTrigger _triggerId, float _triggerValue ) const = 0;
    };
}