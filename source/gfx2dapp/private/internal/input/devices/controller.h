#pragma once

#include <input/devices/icontroller.h>
#include <internal/input/devices/devicehelper.h>

namespace puma::app
{
    class Controller : public IController, public DeviceKeyStates<ControllerKeyStates>
    {
    public:

        bool keyState( ControllerKey _controllerKey ) const override { return inputState( static_cast<InputId>(_controllerKey) ); }
        bool keyPressed( ControllerKey _controllerKey ) const override { return inputPressed( static_cast<InputId>(_controllerKey) ); }
        bool keyReleased( ControllerKey _controllerKey ) const override { return inputReleased( static_cast<InputId>(_controllerKey) ); }

        void updateStates( s32 _sdlInputId, InputButtonEvent _buttonEvent );
    };
}