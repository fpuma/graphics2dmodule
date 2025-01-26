#include <precompiledapplication.h>

#include "application.h"

#include <internal/application/opengl/oglwindow.h>
#include <internal/application/sdl/sdlwindow.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>

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

    OglWindowId Application::createOglWindow(const Extent& _extent, const char* _windowName)
    {
        auto windowPtr = std::make_unique<OglWindow>(_extent, _windowName);
        assert(windowPtr->isValid());

        OglWindowId windowHandle = windowPtr->getWindowId();

        m_oglWindows.insert(std::pair(windowHandle, std::move(windowPtr)));

        return windowHandle;
    }

    SdlWindowId Application::createSdlWindow( const Extent& _extent, const char* _windowName )
    {
        auto windowPtr = std::make_unique<SdlWindow>( _extent, _windowName );
        assert( windowPtr->isValid() );
        
        SdlWindowId windowHandle = windowPtr->getWindowId();

        m_sdlWindows.insert( std::pair( windowHandle, std::move( windowPtr ) ) );

        return windowHandle;
    }

    void Application::removeWindow( SdlWindowId _windowId )
    {
        auto foundIt = m_sdlWindows.find(_windowId);

        assert( foundIt != m_sdlWindows.end() );

        m_sdlWindows.erase( foundIt );
    }

    void Application::removeWindow(OglWindowId _windowId)
    {
        auto foundIt = m_oglWindows.find(_windowId);

        assert(foundIt != m_oglWindows.end());

        m_oglWindows.erase(foundIt);
    }

    void Application::uninit()
    {
        m_sdlWindows.clear();

        TTF_Quit();
        SDL_QuitSubSystem( SDL_INIT_VIDEO );
        freeAllocatedPollyInts();
    }

    namespace internalNinaApplication
    {
        template <class WindowType, class WindowIdType>
        WindowType* findWindow(const std::unordered_map<WindowIdType, std::unique_ptr<WindowType>>& _windowMap, WindowIdType _windowId)
        {
            assert(_windowId.isValid());
            auto foundIt = _windowMap.find(_windowId);

            WindowType* result = nullptr;

            if (foundIt != _windowMap.end())
            {
                result = foundIt->second.get();
            }

            return result;
        }
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
                    {
                        SdlWindow* sdlWindow = internalNinaApplication::findWindow(m_sdlWindows, SdlWindowId(event.window.windowID));
                        if (nullptr != sdlWindow)
                        {
                            m_sdlWindows.erase(SdlWindowId(event.window.windowID));
                            break;
                        }
                    }

                    {
                        OglWindow* oglWindow = internalNinaApplication::findWindow(m_oglWindows, OglWindowId(event.window.windowID));
                        if (nullptr != oglWindow)
                        {
                            m_oglWindows.erase(OglWindowId(event.window.windowID));
                            break;
                        }
                    }

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

        if ( m_sdlWindows.empty() )
        {
            m_shouldQuit = true;
        }
    }

    IOglWindow* Application::getWindow(OglWindowId _windowId)
    {
        return static_cast<IOglWindow*>(internalNinaApplication::findWindow(m_oglWindows, _windowId));
    }

    const IOglWindow* Application::getWindow(OglWindowId _windowId) const
    {
        return static_cast<IOglWindow*>(internalNinaApplication::findWindow(m_oglWindows, _windowId));
    }

    ISdlWindow* Application::getWindow( SdlWindowId _windowId )
    {
        return static_cast<ISdlWindow*>(internalNinaApplication::findWindow(m_sdlWindows, _windowId));
    }

    const ISdlWindow* Application::getWindow( SdlWindowId _windowId) const
    {
        return static_cast<ISdlWindow*>(internalNinaApplication::findWindow(m_sdlWindows, _windowId));
    }
}