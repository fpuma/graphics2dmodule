#pragma once

#include <input/inputids.h>

namespace puma::nina
{
    class IKeyboard
    {
    public:

        virtual ~IKeyboard() {}

        virtual bool keyState( KeyboardKey _keyboardKey ) const = 0;
        virtual bool keyPressed( KeyboardKey _keyboardKey ) const = 0;
        virtual bool keyReleased( KeyboardKey _keyboardKey ) const = 0;
    };
}