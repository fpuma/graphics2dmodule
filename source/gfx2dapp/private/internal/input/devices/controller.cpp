#include "precompiledapplication.h"

#include <internal/input/devices/devicehelper.h>
#include <internal/input/sdlinputmapping.h>

#include "controller.h"

namespace puma::app
{
    namespace
    {
        float convertJoystickAxis( s32 _raw )
        {
            return _raw / (_raw < 0 ? -32768.0f : 32767.0f);
        }

        float convertJoystickTrigger( s32 _raw )
        {
            return (_raw + 32768) / 65535.0f;
        }
    }

    void Controller::updateStates( s32 _sdlInputId, InputButtonEvent _buttonEvent )
    {
        internalUpdateKeyStates( kSdlControllerMapping, _sdlInputId, _buttonEvent );
    }

    void Controller::setRightJoystickX( s32 _value )
    {
        m_rightJoystickPosition.x = convertJoystickAxis( _value );
    }

    void Controller::setRightJoystickY( s32 _value )
    {
        m_rightJoystickPosition.y = convertJoystickAxis( _value );
    }

    void Controller::setLeftJoystickX( s32 _value )
    {
        m_leftJoystickPosition.x = convertJoystickAxis( _value );
    }

    void Controller::setLeftJoystickY( s32 _value )
    {
        m_leftJoystickPosition.y = convertJoystickAxis( _value );
    }

    void Controller::setRightTrigger( s32 _value )
    {
        m_rightTrigger = convertJoystickTrigger( _value );
    }

    void Controller::setLeftTrigger( s32 _value )
    {
        m_leftTrigger = convertJoystickTrigger( _value );
    }
}