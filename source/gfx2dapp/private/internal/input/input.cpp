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
        InputId resolveInputID( const SDLInputMapping& _sdlInputMapping, s32 _sdlInputNumber )
        {
            auto itInputId = _sdlInputMapping.find( _sdlInputNumber );
            InputId result = kInvalidInputId;
            if ( _sdlInputMapping.end() != itInputId )
            {
                result = itInputId->second;
            }
            else
            {
                gAppLogger->error( formatString( "Error: Key not recognized! %d", _sdlInputNumber ).c_str() );
            }
            return result;
        }

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
                InputId inputId = resolveInputID( kSdlKeyboardMapping, currentEvent.key.keysym.sym );
                updateInputState( inputId, InputButtonEvent::Down );
                break;
            }
            case SDL_KEYUP:
            {
                InputId inputId = resolveInputID( kSdlKeyboardMapping, currentEvent.key.keysym.sym );
                updateInputState( inputId, InputButtonEvent::Up );
                break;
            }
            case SDL_MOUSEMOTION:
            {
                m_mousePosition.x = static_cast<int>(currentEvent.motion.x);
                m_mousePosition.y = static_cast<int>(currentEvent.motion.y);
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                InputId inputId = resolveInputID( kSdlMouseMapping, currentEvent.button.button );
                updateInputState( inputId, InputButtonEvent::Down );

                std::cout << "Mouse button: " << resolveInputName( kMouseKeyNames, inputId ) << " DOWN. Mouse instance: " << currentEvent.button.which << std::endl;
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                InputId inputId = resolveInputID( kSdlMouseMapping, currentEvent.button.button );
                updateInputState( inputId, InputButtonEvent::Up );

                std::cout << "Mouse button: " << resolveInputName( kMouseKeyNames, inputId ) << " UP. Mouse instance: " << currentEvent.button.which << std::endl;
                break;
            }
            
            case SDL_JOYBUTTONDOWN:
            {
                gAppLogger->info( formatString( "%d", currentEvent.jbutton.button ).c_str() );
                break;
            }
            default: 
                break;
            }
        }
    }

    void Input::clearPreviousStates()
    {
        for ( StateMask& stateMask : m_inputState )
        {
            stateMask &= ~ReleasedStateBit;
            stateMask &= ~PressedStateBit;
        }
    }

    void Input::updateInputState( InputId _inputId, InputButtonEvent _buttonEvent )
    {
        switch ( _buttonEvent )
        {
        case InputButtonEvent::Up:
        {
            if ( _inputId != kInvalidInputId )
            {
                if ( m_inputState[(int)_inputId] & CurrentStateBit )
                {
                    m_inputState[(int)_inputId] |= ReleasedStateBit;
                }
                else
                {
                    m_inputState[(int)_inputId] &= ~ReleasedStateBit;
                }

                m_inputState[(int)_inputId] &= ~CurrentStateBit;
            }
            break;
        }
        case InputButtonEvent::Down:
        {
            if ( _inputId != kInvalidInputId )
            {
                if ( m_inputState[(int)_inputId] & CurrentStateBit )
                {
                    m_inputState[(int)_inputId] &= ~PressedStateBit;
                }
                else
                {
                    m_inputState[(int)_inputId] |= PressedStateBit;
                }

                m_inputState[(int)_inputId] |= CurrentStateBit;
            }
            break;
        }
        default:
            break;
        }
    }
}