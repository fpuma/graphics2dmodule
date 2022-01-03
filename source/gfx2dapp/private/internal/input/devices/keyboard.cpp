#include "precompiledapplication.h"

#include <internal/input/devices/devicehelper.h>
#include <internal/input/sdlinputmapping.h>

#include "keyboard.h"

namespace puma::app
{

    void Keyboard::updateStates( s32 _sdlInputId, InputButtonEvent _buttonEvent )
    {
        internalUpdateKeyStates( kSdlKeyboardMapping, _sdlInputId, _buttonEvent );
    }
}