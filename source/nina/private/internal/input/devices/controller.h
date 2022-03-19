#pragma once

#include <input/devices/icontroller.h>
#include <internal/input/devices/devicehelper.h>

namespace puma::nina
{
    class Controller : public IController, public DeviceKeyStates<ControllerKeyStates>
    {
    public:

        Controller() {}
        Controller( s32 _sdlId, ControllerId _controllerId );

        bool buttonState( ControllerButton _controllerKey ) const override { return inputState( static_cast<InputId>(_controllerKey) ); }
        bool buttonPressed( ControllerButton _controllerKey ) const override { return inputPressed( static_cast<InputId>(_controllerKey) ); }
        bool buttonReleased( ControllerButton _controllerKey ) const override { return inputReleased( static_cast<InputId>(_controllerKey) ); }

        bool wasRightJoystickUpdated() const override { return m_updatedMotionsFlags & RightJoystickUpdated; }
        bool wasLeftJoystickUpdated() const override { return m_updatedMotionsFlags & LeftJoystickUpdated; }
        bool wasRightTriggerUpdated() const override { return m_updatedMotionsFlags & RightTriggerUpdated; }
        bool wasLeftTriggerUpdated() const override { return m_updatedMotionsFlags & LeftTriggerUpdated; }

        JoystickPosition getRightJoystickPosition() const override { return m_rightJoystickPosition; }
        JoystickPosition getLeftJoystickPosition() const override { return m_leftJoystickPosition; }

        float getRightTrigger() const override { return m_rightTrigger; }
        float getLeftTrigger() const override { return m_leftTrigger; }

        ControllerId getControllerId() const override { return m_controllerId; }

        void setRightJoystickX( float _value );
        void setRightJoystickY( float _value );

        void setLeftJoystickX( float _value );
        void setLeftJoystickY( float _value );

        void setRightTrigger( float _value ); 
        void setLeftTrigger( float _value ); 

        s32 getSdlId() const { return m_sdlId; }

    protected:

        void internalClearStates() override { m_updatedMotionsFlags = 0; }

    private:

        enum
        {
            RightJoystickUpdated = 0x01,
            LeftJoystickUpdated = 0x02,
            RightTriggerUpdated = 0x04,
            LeftTriggerUpdated = 0x08,
        };

        u8 m_updatedMotionsFlags = 0;

        JoystickPosition m_rightJoystickPosition;
        JoystickPosition m_leftJoystickPosition;

        float m_rightTrigger = 0.0f;
        float m_leftTrigger = 0.0f;

        ControllerId m_controllerId = kMaxU32;

        s32 m_sdlId = -1;
    };
}