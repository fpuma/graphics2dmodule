#include <precompiledgraphics.h>

#include <internal/input/input.h>
#include <internal/input/sdlinputmapping.h>

#include <SDL.h>

#include <assert.h>
#include <iostream>

#define PUMA_INPUT_DEBUG

#ifdef PUMA_INPUT_DEBUG
#include <internal/input/inputnames.h>
#endif

namespace puma
{
    constexpr int kSdlEventBufferSize = 10;

    std::unique_ptr<IInput> IInput::create()
    {
        return std::make_unique<Input>();
    }

    namespace
    {
#ifdef PUMA_INPUT_DEBUG
        void printKeyName( InputID _inputId, bool _keyPressed )
        {
            const char* action = _keyPressed ? "Key pressed: " : "Key released: ";
            auto itInputName = kInputNames.find( _inputId );
            assert( kInputNames.end() != itInputName );
            std::cout << action << itInputName->second << std::endl;
        }
#endif
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
                std::cout << "Error: Key not recognized!" << _sdlKeyCode << std::endl;
            }
            return result;
        }
    }

    void Input::init()
    {
        if ( SDL_Init( SDL_INIT_EVENTS ) < 0 )
        {
            std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
            return;
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
            std::cout << "Error retreiving SDL_QUIT: " << SDL_GetError() << std::endl;
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
#ifdef PUMA_INPUT_DEBUG
                    printKeyName( inputId, true );
#endif
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
#ifdef PUMA_INPUT_DEBUG
                    printKeyName( inputId, false );
#endif
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