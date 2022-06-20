#pragma once

#include <nina/input/inputids.h>

namespace puma::nina
{
    class IController
    {
    public:

        virtual ~IController() {}

        virtual bool buttonState( ControllerButton _controllerKey ) const = 0;
        virtual bool buttonPressed( ControllerButton _controllerKey ) const = 0;
        virtual bool buttonReleased( ControllerButton _controllerKey ) const = 0;

        virtual bool wasRightJoystickUpdated() const = 0;
        virtual bool wasLeftJoystickUpdated() const = 0;
        virtual bool wasRightTriggerUpdated() const = 0;
        virtual bool wasLeftTriggerUpdated() const = 0;

        virtual JoystickPosition getRightJoystickPosition() const = 0;
        virtual JoystickPosition getLeftJoystickPosition() const = 0;

        virtual float getRightTrigger() const = 0;
        virtual float getLeftTrigger() const = 0;

        virtual ControllerId getControllerId() const = 0;

    };
}