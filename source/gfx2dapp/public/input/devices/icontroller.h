#pragma once

#include <input/inputids.h>

namespace puma::app
{
    class IController
    {
    public:

        virtual bool buttonState( ControllerButton _controllerKey ) const = 0;
        virtual bool buttonPressed( ControllerButton _controllerKey ) const = 0;
        virtual bool buttonReleased( ControllerButton _controllerKey ) const = 0;

        virtual JoystickPosition getRightJoystickPosition() const = 0;
        virtual JoystickPosition getLeftJoystickPosition() const = 0;

        virtual float getRightTrigger() const = 0;
        virtual float getLeftTrigger() const = 0;

        virtual ControllerId getControllerId() const = 0;

    };
}