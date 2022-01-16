#include <precompiledapplication.h>

#include "input.h"

#include <internal/input/sdlinputmapping.h>
#include <internal/applogger/applogger.h>

#include <SDL.h>

#include <iostream>
#include "inputnames.h"

namespace puma::app
{
    constexpr int kSdlEventBufferSize = 10;

    std::unique_ptr<IInput> IInput::create()
    {
        return std::make_unique<Input>();
    }

    const char* IInput::getInputName( KeyboardKey _key )
    {
        const char* result = nullptr;
        if ( KeyboardKey::TotalKeys != _key )
        {
            auto itFoundName = kKeyboardKeyNames.find( static_cast<InputId>(_key) );

            if ( itFoundName != kKeyboardKeyNames.end() )
            {
                result = itFoundName->second;
            }
        }

        return result;
    }

    const char* IInput::getInputName( MouseButton _button )
    {
        const char* result = nullptr;
        if ( MouseButton::TotalButtons != _button )
        {
            auto itFoundName = kMouseKeyNames.find( static_cast<InputId>(_button) );

            if ( itFoundName != kMouseKeyNames.end() )
            {
                result = itFoundName->second;
            }
        }

        return result;
    }

    const char* IInput::getInputName( ControllerButton _button )
    {
        const char* result = nullptr;
        if ( ControllerButton::TotalButtons != _button )
        {
            auto itFoundName = kControllerKeyNames.find( static_cast<InputId>(_button) );

            if ( itFoundName != kControllerKeyNames.end() )
            {
                result = itFoundName->second;
            }
        }

        return result;
    }

    namespace
    {
        const char* resolveInputName( const InputNameMapping& _inputNames, InputId _inputId )
        {
            auto itInputId = _inputNames.find( _inputId );
            const char* result = nullptr;
            if ( _inputNames.end() != itInputId )
            {
                result = itInputId->second;
            }
            else
            {
                gAppLogger->error( formatString( "Error: InputID with no name! %d", _inputId ).c_str() );
            }
            return result;
        }
    }

    void Input::init()
    {
        if ( SDL_InitSubSystem( SDL_INIT_EVENTS ) < 0 )
        {
            gAppLogger->error( formatString( "Error initializing SDL Events: %s", SDL_GetError() ).c_str() );
            return;
        }
        
        if ( SDL_InitSubSystem( SDL_INIT_JOYSTICK ) < 0 )
        {
            gAppLogger->error( formatString( "Error initializing SDL Joystick: %s", SDL_GetError() ).c_str() );
        }

        gAppLogger->info( "SDL Events subsystem initialized correctly." );
        gAppLogger->info( formatString( "Controllers count: %d", SDL_NumJoysticks() ).c_str() );
        for ( s32 index = 0; index < SDL_NumJoysticks(); ++index )
        {
            SDL_JoystickOpen( index );
            SDL_JoystickID joystickId = SDL_JoystickGetDeviceInstanceID( index );
            SDL_Joystick* joystick = SDL_JoystickFromInstanceID( joystickId );
            gAppLogger->info( formatString( "Controller<%d>: %s", joystickId, SDL_JoystickName( joystick ) ).c_str() );
        }
    }

    void Input::uninit()
    {
        for ( s32 index = 0; index < SDL_NumJoysticks(); ++index )
        {
            SDL_JoystickID joystickId = SDL_JoystickGetDeviceInstanceID( index );
            SDL_Joystick* joystick = SDL_JoystickFromInstanceID( joystickId );
            SDL_JoystickClose( joystick );
        }
        SDL_QuitSubSystem( SDL_INIT_JOYSTICK );
        SDL_QuitSubSystem( SDL_INIT_EVENTS );
    }

    void Input::update()
    {
        clearPreviousStates();

        SDL_Event sdlEvents[kSdlEventBufferSize];
        SDL_PumpEvents();
        SDL_eventaction sdlEventAction = m_peekSdlEvents ? SDL_PEEKEVENT : SDL_GETEVENT;

        int eventsRetreived = SDL_PeepEvents( sdlEvents, kSdlEventBufferSize, sdlEventAction, SDL_KEYDOWN, /*SDL_KEYUP*/SDL_CONTROLLERDEVICEREMAPPED );
        if ( eventsRetreived < 0 )
        {
            gAppLogger->error( formatString( "Error retreiving SDL_QUIT: %s", SDL_GetError() ).c_str() );
        }
        assert( eventsRetreived >= 0 );
        for ( int eventIndex = 0; eventIndex < eventsRetreived; ++eventIndex )
        {
            SDL_Event currentEvent = sdlEvents[eventIndex];
            switch ( currentEvent.type )
            {
            case SDL_KEYDOWN:
            {
                updateKeyboardKey( currentEvent.key.keysym.sym, InputButtonEvent::Down );
                break;
            }
            case SDL_KEYUP:
            {
                updateKeyboardKey( currentEvent.key.keysym.sym, InputButtonEvent::Up );
                break;
            }
            case SDL_MOUSEMOTION:
            {
                m_mouseDevice.setMousePosition( { static_cast<int>(currentEvent.motion.x), static_cast<int>(currentEvent.motion.y) } );
                if ( nullptr != m_inputListener )
                {
                    MouseEventData eventData;
                    eventData.positionEvent = m_mouseDevice.getMousePosition();
                    m_inputListener->onMouseEvent( MouseEventType::Position, eventData );
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                updateMouseButton( currentEvent.button.button, InputButtonEvent::Down );
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                updateMouseButton( currentEvent.button.button, InputButtonEvent::Up );
                break;
            }
            case SDL_JOYBUTTONDOWN:
            {
                updateControllerButton( handleControllerBySdlId( currentEvent.jbutton.which ), SDL_TO_PUMA( currentEvent.jbutton.button ), InputButtonEvent::Down );
                break;
            }
            case SDL_JOYBUTTONUP:
            {
                updateControllerButton( handleControllerBySdlId( currentEvent.jbutton.which ), SDL_TO_PUMA( currentEvent.jbutton.button ), InputButtonEvent::Up );
                break;
            }
            case SDL_JOYAXISMOTION:
            {
                switch ( currentEvent.jaxis.axis )
                {
                case 0:
                {
                    Controller& controller = handleControllerBySdlId( currentEvent.jaxis.which );
                    controller.setLeftJoystickX( currentEvent.jaxis.value );
                    if ( nullptr != m_inputListener )
                    {
                        ControllerEventData eventData;
                        eventData.joystickEvent = { ControllerJoystick::CJ_LSTICK_X, controller.getLeftJoystickPosition().x };
                        m_inputListener->onControllerEvent( controller.getControllerId(), ControllerEventType::Joystick, eventData );
                    }
                    break;
                }
                case 1:
                {
                    Controller& controller = handleControllerBySdlId( currentEvent.jaxis.which );
                    controller.setLeftJoystickY( currentEvent.jaxis.value );
                    if ( nullptr != m_inputListener )
                    {
                        ControllerEventData eventData;
                        eventData.joystickEvent = { ControllerJoystick::CJ_LSTICK_Y, controller.getLeftJoystickPosition().y };
                        m_inputListener->onControllerEvent( controller.getControllerId(), ControllerEventType::Joystick, eventData );
                    }
                    break;
                }
                case 2:
                {
                    Controller& controller = handleControllerBySdlId( currentEvent.jaxis.which );
                    controller.setLeftTrigger( currentEvent.jaxis.value );
                    if ( nullptr != m_inputListener )
                    {
                        ControllerEventData eventData;
                        eventData.triggerEvent = { ControllerTrigger::CT_LTRIGGER, controller.getLeftTrigger() };
                        m_inputListener->onControllerEvent( controller.getControllerId(), ControllerEventType::Trigger, eventData );
                    }
                    break;
                }
                case 3:
                {
                    Controller& controller = handleControllerBySdlId( currentEvent.jaxis.which );
                    controller.setRightJoystickX( currentEvent.jaxis.value );
                    if ( nullptr != m_inputListener )
                    {
                        ControllerEventData eventData;
                        eventData.joystickEvent = { ControllerJoystick::CJ_RSTICK_X, controller.getRightJoystickPosition().x };
                        m_inputListener->onControllerEvent( controller.getControllerId(), ControllerEventType::Joystick, eventData );
                    }
                    break;
                }
                case 4:
                {
                    Controller& controller = handleControllerBySdlId( currentEvent.jaxis.which );
                    controller.setRightJoystickY( currentEvent.jaxis.value );
                    if ( nullptr != m_inputListener )
                    {
                        ControllerEventData eventData;
                        eventData.joystickEvent = { ControllerJoystick::CJ_RSTICK_Y, controller.getRightJoystickPosition().y };
                        m_inputListener->onControllerEvent( controller.getControllerId(), ControllerEventType::Joystick, eventData );
                    }
                    break;
                }
                case 5:
                {
                    Controller& controller = handleControllerBySdlId( currentEvent.jaxis.which );
                    controller.setRightTrigger( currentEvent.jaxis.value );
                    if ( nullptr != m_inputListener )
                    {
                        ControllerEventData eventData;
                        eventData.triggerEvent = { ControllerTrigger::CT_LTRIGGER, controller.getLeftTrigger() };
                        m_inputListener->onControllerEvent( controller.getControllerId(), ControllerEventType::Trigger, eventData );
                    }
                    break;
                }
                default:
                    break;
                }
                break;
            }
            //case SDL_JOYBALLMOTION:
            //{
            //    gAppLogger->info( formatString( "Controller: %d | Ball: %d | X: %d, Y: %d", currentEvent.jball.which, currentEvent.jball.ball, currentEvent.jball.xrel, currentEvent.jball.yrel ).c_str() );
            //    break;
            //}
            case SDL_JOYHATMOTION:
            {
                updateDPad( currentEvent.jhat.which, currentEvent.jhat.value );
                break;
            }
            default: 
                break;
            }
        }
    }

    void Input::clearPreviousStates()
    {
        m_mouseDevice.clearStates();
        m_keyboardDevice.clearStates();
        for ( Controller& controller : m_controllerDevices )
        {
            controller.clearStates();
        }
    }

    void Input::updateKeyboardKey( s32 _sdlInputId, InputButtonEvent _inputEvent )
    {
        InputId inputId = resolveInputID( kSdlKeyboardMapping, _sdlInputId );
        m_keyboardDevice.updateKeyStates( inputId, _inputEvent );
        if ( nullptr != m_inputListener )
        {
            m_inputListener->onKeyboardEvent( _inputEvent, static_cast<KeyboardKey>(inputId) );
        }
    }

    void Input::updateMouseButton( s32 _sdlInputId, InputButtonEvent _inputEvent )
    {
        InputId inputId = resolveInputID( kSdlMouseMapping, _sdlInputId );
        m_mouseDevice.updateKeyStates( inputId, _inputEvent );
        if ( nullptr != m_inputListener )
        {
            MouseEventData eventData;
            eventData.buttonEvent = { _inputEvent, static_cast<MouseButton>(inputId) };
            m_inputListener->onMouseEvent( MouseEventType::Button, eventData );
        }
    }

    void Input::updateControllerButton( Controller& controller, s32 _sdlInputId, InputButtonEvent _inputEvent )
    {
        InputId inputId = resolveInputID( kSdlControllerMapping, _sdlInputId );
        controller.updateKeyStates( inputId, _inputEvent );
        if ( nullptr != m_inputListener )
        {
            ControllerEventData eventData;
            eventData.buttonEvent = { _inputEvent, static_cast<ControllerButton>(inputId) };
            m_inputListener->onControllerEvent( controller.getControllerId(), ControllerEventType::Button, eventData );
        }
    }

    void Input::updateDPad( s32 _id, u32 input )
    {
        Controller& controller = handleControllerBySdlId( _id );

        if ( input == SDL_HAT_CENTERED )
        {
            if ( controller.buttonState( ControllerButton::CB_DPAD_UP ) )
            {
                updateControllerButton( controller, SDL_HAT_UP, InputButtonEvent::Up );
            }

            if ( controller.buttonState( ControllerButton::CB_DPAD_RIGHT ) )
            {
                updateControllerButton( controller, SDL_HAT_RIGHT, InputButtonEvent::Up );
            }

            if ( controller.buttonState( ControllerButton::CB_DPAD_LEFT ) )
            {
                updateControllerButton( controller, SDL_HAT_LEFT, InputButtonEvent::Up );
            }

            if ( controller.buttonState( ControllerButton::CB_DPAD_DOWN ) )
            {
                updateControllerButton( controller, SDL_HAT_DOWN, InputButtonEvent::Up );
            }
        }
        else
        {
            if ( input & SDL_HAT_UP )
            {
                updateControllerButton( controller, SDL_HAT_UP, InputButtonEvent::Down );
            }
            else if ( controller.buttonState( ControllerButton::CB_DPAD_UP ) )
            {
                updateControllerButton( controller, SDL_HAT_UP, InputButtonEvent::Up );
            }

            if ( input & SDL_HAT_DOWN )
            {
                updateControllerButton( controller, SDL_HAT_DOWN, InputButtonEvent::Down );
            }
            else if ( controller.buttonState( ControllerButton::CB_DPAD_DOWN ) )
            {
                updateControllerButton( controller, SDL_HAT_DOWN, InputButtonEvent::Up );
            }

            if ( input & SDL_HAT_LEFT )
            {
                updateControllerButton( controller, SDL_HAT_LEFT, InputButtonEvent::Down );
            }
            else if ( controller.buttonState( ControllerButton::CB_DPAD_LEFT ) )
            {
                updateControllerButton( controller, SDL_HAT_LEFT, InputButtonEvent::Up );
            }

            if ( input & SDL_HAT_RIGHT )
            {
                updateControllerButton( controller, SDL_HAT_RIGHT, InputButtonEvent::Down );
            }
            else if( controller.buttonState( ControllerButton::CB_DPAD_RIGHT ) )
            {
                updateControllerButton( controller, SDL_HAT_RIGHT, InputButtonEvent::Up );
            }
        }
    }

    Controller& Input::handleControllerBySdlId( s32 _id )
    {
        auto itFoundController = std::find_if( m_controllerDevices.begin(), m_controllerDevices.end(), [_id]( const Controller& _controller )
        {
            return _controller.getSdlId() == _id;
        } );

        if ( itFoundController != m_controllerDevices.end() )
        {
            return *itFoundController;
        }
        else
        {
            m_controllerDevices.push_back( Controller( _id, static_cast<ControllerId>(m_controllerDevices.size()) ) );
            return m_controllerDevices[m_controllerDevices.size() - 1];
        }
    }
}