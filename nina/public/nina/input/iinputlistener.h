#pragma once

#include <nina/input/inputdefinitions.h>
#include <nina/input/inputids.h>

namespace puma::nina
{
    class IInputListener
    {
    public:

        virtual ~IInputListener() {}

        virtual void onKeyboardKey( KeyboardKey _key, InputButtonEvent _event ) const = 0;
        
        virtual void onMouseButton( MouseButton _button, InputButtonEvent _event ) const = 0;
        virtual void onMouseWheel( MouseWheelState _wheelState ) const = 0;
        virtual void onMousePosition( MousePosition _mousePosition ) const = 0;

        virtual void onControllerButton( ControllerId _id, ControllerButton _buttonId, InputButtonEvent _event ) const = 0;
        virtual void onControllerJoystick( ControllerId _id, ControllerJoystick _joystickId, JoystickPosition _joystickPosition ) const = 0;
        virtual void onControllerTrigger( ControllerId _id, ControllerTrigger _triggerId, float _triggerValue ) const = 0;
    };
}