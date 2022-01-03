#pragma once

#include <input/inputids.h>
#include <input/inputdefinitions.h>

namespace puma::app
{
    class IMouse
    {
    public:

        virtual bool buttonState( MouseKey _mouseKey ) const = 0;
        virtual bool buttonPressed( MouseKey _mouseKey ) const = 0;
        virtual bool buttonReleased( MouseKey _mouseKey ) const = 0;

        virtual MousePosition getMousePosition() const = 0;
    };
}