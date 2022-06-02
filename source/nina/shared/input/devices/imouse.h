#pragma once

#include <input/inputids.h>
#include <input/inputdefinitions.h>

namespace puma::nina
{
    class IMouse
    {
    public:

        virtual ~IMouse() {}

        virtual bool buttonState( MouseButton _mouseKey ) const = 0;
        virtual bool buttonPressed( MouseButton _mouseKey ) const = 0;
        virtual bool buttonReleased( MouseButton _mouseKey ) const = 0;

        virtual bool wasMousePositionUpdated() const = 0;
        virtual MousePosition getMousePosition() const = 0;
        virtual MouseWheelState getMouseWheelState() const = 0;
    };
}