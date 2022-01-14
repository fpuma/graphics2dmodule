#pragma once

#include <input/inputids.h>

namespace puma::app
{
    class IController
    {
    public:

        virtual bool keyState( ControllerKey _controllerKey ) const = 0;
        virtual bool keyPressed( ControllerKey _controllerKey ) const = 0;
        virtual bool keyReleased( ControllerKey _controllerKey ) const = 0;

        virtual JoystickPosition getRightJoystickPosition() const = 0;
        virtual JoystickPosition getLeftJoystickPosition() const = 0;

        virtual float getRightTrigger() const = 0;
        virtual float getLeftTrigger() const = 0;

    };
}