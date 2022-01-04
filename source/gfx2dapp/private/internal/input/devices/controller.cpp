#include "precompiledapplication.h"

#include <internal/input/devices/devicehelper.h>
#include <internal/input/sdlinputmapping.h>

#include "controller.h"

namespace puma::app
{

    void Controller::updateStates( s32 _sdlInputId, InputButtonEvent _buttonEvent )
    {
        internalUpdateKeyStates( kSdlControllerMapping, _sdlInputId, _buttonEvent );
    }
}