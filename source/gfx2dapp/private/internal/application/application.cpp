#include <precompiledapplication.h>

#include "application.h"

#include <internal/application/window.h>

#include <SDL.h>
#include <SDL_ttf.h>

namespace puma::nina
{
    constexpr s32 kSdlEventBufferSize = 10;

    std::unique_ptr<IApplication> IApplication::create()
    {
        return std::make_unique<Application>();
    }

    void Application::init()
    {
        DefaultInstance<AppLogger, Application>::setInstance( &m_appLogger );

        if ( SDL_InitSubSystem( SDL_INIT_VIDEO ) < 0 )
        {
            m_appLogger.error( formatString( "Error initializing SDL: %s", SDL_GetError() ).c_str() );
            return;
        }
        else
        {
            m_appLogger.info( formatString( "SDL initialized" ).c_str() );
        }

        if ( TTF_Init() == -1 )
        {
            m_appLogger.error( formatString( "Error initializing SDL TTF: %s", TTF_GetError() ).c_str() );
        }
        else
        {
            m_appLogger.info( formatString( "SDL TTF initialized" ).c_str() );
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

    void Application::removeWindow( WindowHandle _windowHandle )
    {
        auto foundIt = m_windows.find( _windowHandle );

        assert( foundIt != m_windows.end() );

        m_windows.erase( foundIt );
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
            m_appLogger.error( formatString( "Error retreiving SDL events: %s", SDL_GetError() ).c_str() );
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
                break;
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

    namespace
    {
        IWindow* findWindow( const WindowMap& _windowMap, WindowHandle _windowHandle )
        {
            assert( kInvalidWindowHandle != _windowHandle );
            auto foundIt = _windowMap.find( _windowHandle );

            IWindow* result = nullptr;

            if ( foundIt != _windowMap.end() )
            {
                result = foundIt->second.get();
            }

            return result;
        }

        IRenderer* getWindowRenderer( const WindowMap& _windowMap, WindowHandle _windowHandle )
        {
            assert( kInvalidWindowHandle != _windowHandle );
            IRenderer* result = nullptr;
            IWindow* defaultWindow = findWindow( _windowMap, _windowHandle );

            if ( nullptr != defaultWindow )
            {
                result = defaultWindow->getRenderer();
            }

            return result;
        }
    }

    IWindow* Application::getWindow( WindowHandle _windowHandle )
    {
        return findWindow( m_windows, _windowHandle );
    }

    const IWindow* Application::getWindow( WindowHandle _windowHandle ) const
    {
        return findWindow( m_windows, _windowHandle );
    }
}