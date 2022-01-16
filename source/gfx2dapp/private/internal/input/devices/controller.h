#pragma once

#include <input/devices/icontroller.h>
#include <internal/input/devices/devicehelper.h>

namespace puma::app
{
    class Controller : public IController, public DeviceKeyStates<ControllerKeyStates>
    {
    public:

        Controller() {}
        Controller( s32 _sdlId, ControllerId _controllerId );

        bool buttonState( ControllerButton _controllerKey ) const override { return inputState( static_cast<InputId>(_controllerKey) ); }
        bool buttonPressed( ControllerButton _controllerKey ) const override { return inputPressed( static_cast<InputId>(_controllerKey) ); }
        bool buttonReleased( ControllerButton _controllerKey ) const override { return inputReleased( static_cast<InputId>(_controllerKey) ); }

        JoystickPosition getRightJoystickPosition() const override { return m_rightJoystickPosition; }
        JoystickPosition getLeftJoystickPosition() const override { return m_leftJoystickPosition; }

        float getRightTrigger() const override { return m_rightTrigger; }
        float getLeftTrigger() const override { return m_leftTrigger; }

        ControllerId getControllerId() const override { return m_controllerId; }

        void setRightJoystickX( s32 _value );
        void setRightJoystickY( s32 _value );

        void setLeftJoystickX( s32 _value );
        void setLeftJoystickY( s32 _value );

        void setRightTrigger( s32 _value ); 
        void setLeftTrigger( s32 _value ); 

        s32 getSdlId() const { return m_sdlId; }

    private:

        JoystickPosition m_rightJoystickPosition;
        JoystickPosition m_leftJoystickPosition;

        float m_rightTrigger = 0.0f;
        float m_leftTrigger = 0.0f;

        ControllerId m_controllerId = kMaxU32;

        s32 m_sdlId = -1;
    };
}