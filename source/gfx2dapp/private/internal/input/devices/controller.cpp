#include "precompiledapplication.h"

#include "controller.h"

#include <internal/input/devices/devicehelper.h>
#include <internal/input/sdlinputmapping.h>

#include <math.h>

namespace puma::app
{
    Controller::Controller( s32 _sdlId, ControllerId _controllerId )
        : m_controllerId( _controllerId )
        , m_sdlId( _sdlId )
    {}

    void Controller::setRightJoystickX( float _value )
    {
        m_rightJoystickPosition.x = _value;
        m_updatedMotionsFlags = m_updatedMotionsFlags | RightJoystickUpdated;
    }

    void Controller::setRightJoystickY( float _value )
    {
        m_rightJoystickPosition.y = _value;
        m_updatedMotionsFlags = m_updatedMotionsFlags | RightJoystickUpdated;
    }

    void Controller::setLeftJoystickX( float _value )
    {
        m_leftJoystickPosition.x = _value;
        m_updatedMotionsFlags = m_updatedMotionsFlags | LeftJoystickUpdated;
    }

    void Controller::setLeftJoystickY( float _value )
    {
        m_leftJoystickPosition.y = _value;
        m_updatedMotionsFlags = m_updatedMotionsFlags | LeftJoystickUpdated;
    }

    void Controller::setRightTrigger( float _value )
    {
        m_rightTrigger = _value;
        m_updatedMotionsFlags = m_updatedMotionsFlags | RightTriggerUpdated;
    }

    void Controller::setLeftTrigger( float _value )
    {
        m_leftTrigger = _value;
        m_updatedMotionsFlags = m_updatedMotionsFlags | LeftTriggerUpdated;
    }
}