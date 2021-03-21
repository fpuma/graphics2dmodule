#include <precompiledapplication.h>

#include "input.h"

#include <internal/input/sdlinputmapping.h>
#include <internal/applogger/applogger.h>

#include <SDL.h>

namespace puma::input
{
    constexpr int kSdlEventBufferSize = 10;

    std::unique_ptr<IInput> IInput::create()
    {
        return std::make_unique<Input>();
    }

    namespace
    {
        InputID resolveInputID( SDL_Keycode _sdlKeyCode )
        {
            auto itInputId = kSdlInputMapping.find( _sdlKeyCode );
            InputID result = InputID::TotalKeys;
            if ( kSdlInputMapping.end() != itInputId )
            {
                result = itInputId->second;
            }
            else
            {
                gAppLogger->error( formatString( "Error: Key not recognized! %d", _sdlKeyCode ).c_str() ); 
            }
            return result;
        }
    }

    Input::Input()
    {
        init();
    }

    Input::~Input()
    {
        uninit();
    }

    void Input::init()
    {
        if ( SDL_InitSubSystem( SDL_INIT_EVENTS ) < 0 )
        {
            gAppLogger->error( formatString( "Error initializing SDL Events: %s", SDL_GetError() ).c_str() );
            return;
        }
        else
        {
            gAppLogger->info( "SDL Events subsystem initialized correctly." );
        }
    }

    void Input::uninit()
    {
        SDL_QuitSubSystem( SDL_INIT_EVENTS );
    }

    void Input::update()
    {
        SDL_Event sdlEvents[kSdlEventBufferSize];
        SDL_PumpEvents();
        SDL_eventaction sdlEventAction = m_peekSdlEvents ? SDL_PEEKEVENT : SDL_GETEVENT;

        int eventsRetreived = SDL_PeepEvents( sdlEvents, kSdlEventBufferSize, sdlEventAction, SDL_KEYDOWN, SDL_KEYUP );
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
            case SDL_MOUSEBUTTONDOWN:
            case SDL_KEYDOWN:
            {
                InputID inputId = resolveInputID( currentEvent.key.keysym.sym );
                if ( inputId < InputID::TotalKeys )
                {
                    m_inputState[(int)inputId] = true;
                }
                break;
            }
            case SDL_MOUSEBUTTONUP:
            case SDL_KEYUP:
            {
                InputID inputId = resolveInputID( currentEvent.key.keysym.sym );
                if ( inputId < InputID::TotalKeys )
                {
                    m_inputState[(int)inputId] = false;
                }
                break;
            }
            case SDL_MOUSEMOTION:
            {
                m_mousePosition.x = static_cast<int>(currentEvent.motion.x);
                m_mousePosition.y = static_cast<int>(currentEvent.motion.y);
                break;
            }
            default: 
                break;
            }
        }
    }
}