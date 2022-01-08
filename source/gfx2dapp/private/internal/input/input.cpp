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
                m_keyboardDevice.updateStates( currentEvent.key.keysym.sym, InputButtonEvent::Down );
                break;
            }
            case SDL_KEYUP:
            {
                m_keyboardDevice.updateStates( currentEvent.key.keysym.sym, InputButtonEvent::Up );
                break;
            }
            case SDL_MOUSEMOTION:
            {
                m_mouseDevice.setMousePosition( { static_cast<int>(currentEvent.motion.x), static_cast<int>(currentEvent.motion.y) } );
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                m_mouseDevice.updateStates( currentEvent.button.button, InputButtonEvent::Down );
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                m_mouseDevice.updateStates( currentEvent.button.button, InputButtonEvent::Up );
                break;
            }
            case SDL_JOYBUTTONDOWN:
            {
                m_controllerDevice.updateStates( SDL_TO_PUMA( currentEvent.jbutton.button ), InputButtonEvent::Down );
                break;
            }
            case SDL_JOYBUTTONUP:
            {
                m_controllerDevice.updateStates( SDL_TO_PUMA( currentEvent.jbutton.button ), InputButtonEvent::Up );
                break;
            }
            //case SDL_JOYAXISMOTION:
            //{
            //    gAppLogger->info( formatString( "Controller: %d | Axis: %d | Value: %d", currentEvent.jaxis.which, currentEvent.jaxis.axis, currentEvent.jaxis.value ).c_str() );
            //    break;
            //}
            //case SDL_JOYBALLMOTION:
            //{
            //    gAppLogger->info( formatString( "Controller: %d | Ball: %d | X: %d, Y: %d", currentEvent.jball.which, currentEvent.jball.ball, currentEvent.jball.xrel, currentEvent.jball.yrel ).c_str() );
            //    break;
            //}
            case SDL_JOYHATMOTION:
            {
                updateDPad( currentEvent.jhat.value );
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
        m_controllerDevice.clearStates();
    }

    void Input::updateDPad( u32 input )
    {
        if ( input == SDL_HAT_CENTERED )
        {
            m_controllerDevice.updateStates( SDL_HAT_UP, InputButtonEvent::Up );
            m_controllerDevice.updateStates( SDL_HAT_RIGHT, InputButtonEvent::Up );
            m_controllerDevice.updateStates( SDL_HAT_LEFT, InputButtonEvent::Up );
            m_controllerDevice.updateStates( SDL_HAT_DOWN, InputButtonEvent::Up );
        }
        
        if ( input & SDL_HAT_UP )
        {
            m_controllerDevice.updateStates( SDL_HAT_UP, InputButtonEvent::Down );
        }
        else
        {
            m_controllerDevice.updateStates( SDL_HAT_UP, InputButtonEvent::Up );
        }
        
        if ( input & SDL_HAT_DOWN )
        {
            m_controllerDevice.updateStates( SDL_HAT_DOWN, InputButtonEvent::Down );
        }
        else
        {
            m_controllerDevice.updateStates( SDL_HAT_DOWN, InputButtonEvent::Up );
        }
        
        if ( input & SDL_HAT_LEFT )
        {
            m_controllerDevice.updateStates( SDL_HAT_LEFT, InputButtonEvent::Down );
        }
        else
        {
            m_controllerDevice.updateStates( SDL_HAT_LEFT, InputButtonEvent::Up );
        }
        
        if ( input & SDL_HAT_RIGHT )
        {
            m_controllerDevice.updateStates( SDL_HAT_RIGHT, InputButtonEvent::Down );
        }
        else
        {
            m_controllerDevice.updateStates( SDL_HAT_RIGHT, InputButtonEvent::Up );
        }
    }
}