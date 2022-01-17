#pragma once

#include <input/inputdefinitions.h>
#include <input/inputids.h>

namespace puma::app
{
    //MOUSE
    enum class MouseEventType
    {
        Position,
        Wheel,
        Button,
    };

    struct MouseButtonEvent
    {
        InputButtonEvent inputEvent;
        MouseButton mouseButton;
    };

    union MouseEventData
    {
        MouseEventData() {}

        MousePosition positionEvent;
        MouseWheelState mouseWheel;
        MouseButtonEvent buttonEvent = {};
    };

    //CONTROLLER
    enum class ControllerEventType
    {
        Joystick,
        Trigger,
        Button,
    };

    struct ControllerJoystickEvent
    {
        ControllerJoystick joystick;
        float joystickValue;
    };

    struct ControllerTriggerEvent
    {
        ControllerTrigger trigger;
        float triggerValue;
    };

    struct ControllerButtonEvent
    {
        InputButtonEvent inputEvent;
        ControllerButton controllerButton;
    };

    union ControllerEventData
    {
        ControllerEventData() {}

        ControllerJoystickEvent joystickEvent;
        ControllerTriggerEvent triggerEvent;
        ControllerButtonEvent buttonEvent;
    };


    class IInputListener
    {
    public:

        virtual ~IInputListener() {}

        virtual void onKeyboardEvent( InputButtonEvent _inputEvent, KeyboardKey _key ) const = 0;
        virtual void onMouseEvent( MouseEventType _eventType, const MouseEventData& _mouseEventData ) const = 0;
        virtual void onControllerEvent( ControllerId _id, ControllerEventType _eventType, const ControllerEventData& _eventData ) const = 0;
    };
}