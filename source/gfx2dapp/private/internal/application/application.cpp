#include <precompiledapplication.h>

#include <internal/application/application.h>

#include <internal/application/window.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <assert.h>
#include <vector>

namespace puma::app
{
    constexpr s32 kSdlEventBufferSize = 10;

    Application::Application() {}
    Application::~Application() {}

    std::unique_ptr<IApplication> IApplication::create()
    {
        return std::make_unique<Application>();
    }

    void Application::init()
    {
        if ( SDL_InitSubSystem( SDL_INIT_VIDEO ) < 0 )
        {
            std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
            return;
        }

        if ( TTF_Init() == -1 )
        {
            std::cout << "Error initializing SDL TTF: " << TTF_GetError() << std::endl;
        }
    }

    WindowHandle Application::createWindow( const Extent& _extent, const char* _windowName )
    {
        auto windowPtr = std::make_unique<Window>( _extent, _windowName );
        assert( windowPtr->isValid() );
        
        WindowHandle windowHandle = windowPtr->getWindowHandle();

        m_windows.insert( std::pair( windowHandle, std::move( windowPtr ) ) );

        return windowHandle;
    }

    void Application::uninit()
    {
        m_windows.clear();

        TTF_Quit();
        SDL_QuitSubSystem( SDL_INIT_VIDEO );
    }

    void Application::update()
    {
        SDL_Event sdlEvents[kSdlEventBufferSize];
        SDL_PumpEvents();
        SDL_eventaction sdlEventAction = m_peekSdlEvents ? SDL_PEEKEVENT : SDL_GETEVENT;

        s32 eventsRetreived = SDL_PeepEvents( sdlEvents, kSdlEventBufferSize, sdlEventAction, SDL_QUIT, SDL_QUIT );
        eventsRetreived = SDL_PeepEvents( sdlEvents + eventsRetreived, kSdlEventBufferSize - eventsRetreived, sdlEventAction, SDL_DISPLAYEVENT, SDL_WINDOWEVENT );

        if (eventsRetreived < 0)
        {
            std::cout << "Error retreiving SDL_QUIT: " << SDL_GetError() << std::endl;
        }
        assert( eventsRetreived >= 0 );
        for (s32 eventIndex = 0; eventIndex < eventsRetreived; ++eventIndex)
        {
            SDL_Event event = sdlEvents[eventIndex];
			switch (event.type)
			{
			case SDL_QUIT:
			{
				m_shouldQuit = true;
				break;
			}

            case SDL_WINDOWEVENT:
            {
                switch ( event.window.event )
                {
                case SDL_WINDOWEVENT_CLOSE:
                {
                    auto foundIt = m_windows.find( event.window.windowID );
                    assert( foundIt != m_windows.end() );

                    m_windows.erase( foundIt->first );

                    break;
                }
                default: break;
                }
            }

			default:
				break;
			}
        }

        if ( m_windows.empty() )
        {
            m_shouldQuit = true;
        }
    }

    IWindow* Application::getWindow( WindowHandle _windowHandle )
    {
        auto foundIt = m_windows.find( _windowHandle );

        IWindow* result = nullptr;

        if ( foundIt != m_windows.end() )
        {
            result = foundIt->second.get();
        }

        return result;
    }

    const IWindow* Application::getWindow( WindowHandle _windowHandle ) const
    {
        auto foundIt = m_windows.find( _windowHandle );

        IWindow* result = nullptr;

        if ( foundIt != m_windows.end() )
        {
            result = foundIt->second.get();
        }

        return result;
    }
}