#include <precompiledapplication.h>

#include <internal/input/devices/devicehelper.h>
#include <internal/input/sdlinputmapping.h>

#include "mouse.h"

namespace puma::app
{

    void Mouse::updateStates( u8 _sdlInputId, InputButtonEvent _buttonEvent )
    {
        internalUpdateKeyStates( kSdlMouseMapping, _sdlInputId, _buttonEvent );
    }
}
