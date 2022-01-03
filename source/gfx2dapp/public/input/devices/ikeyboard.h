#pragma once

#include <input/inputids.h>

namespace puma::app
{
    class IKeyboard
    {
    public:

        virtual bool keyState( KeyboardKey _keyboardKey ) const = 0;
        virtual bool keyPressed( KeyboardKey _keyboardKey ) const = 0;
        virtual bool keyReleased( KeyboardKey _keyboardKey ) const = 0;
    };
}