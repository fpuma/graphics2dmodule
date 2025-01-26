#include <precompiledapplication.h>

#include "sdlwindow.h"

#include <internal/applogger/applogger.h>

#include <SDL.h>

namespace puma::nina
{
    
    SdlWindow::SdlWindow( const Extent& _windowExtent, const char* _windowName )
    {
        m_extent = _windowExtent;

        SDL_Window* sdlWindow = SDL_CreateWindow( _windowName, _windowExtent.xPos, _windowExtent.yPos, _windowExtent.width, _windowExtent.height, SDL_WINDOW_SHOWN );

        if ( nullptr == sdlWindow )
        {
            gAppLogger->error( formatString( "SDL Window could not be created. Error: %s", SDL_GetError() ).c_str() );
        }
        else
        {
            m_windowId = SdlWindowId(SDL_GetWindowID(sdlWindow));
            gAppLogger->info(formatString("SDL Window: %d was created.", m_windowId.value()).c_str());
            m_renderer = std::make_unique<SdlRenderer>( *this );
        }
    }

    SdlWindow::~SdlWindow()
    {
        SDL_Window* sdlWindow = SDL_GetWindowFromID( m_windowId.value() );
        assert( nullptr != sdlWindow );
        SDL_DestroyWindow( sdlWindow );
        m_windowId.invalidate();
        m_renderer.reset();
    }

    void SdlWindow::setWindowSize( s32 _width, s32 _height )
    {
        SDL_Window* sdlWindow = SDL_GetWindowFromID( m_windowId.value() );
        if ( nullptr != sdlWindow )
        {
            SDL_SetWindowSize( sdlWindow, _width, _height );
            m_extent.width = _width;
            m_extent.height = _height;
        }
        else
        {
            gAppLogger->error( formatString( "SDL Window could not be retrieved. Error: %s", SDL_GetError() ).c_str() );
        }
    }

    void SdlWindow::setWindowPosition( s32 _x, s32 _y )
    {
        SDL_Window* sdlWindow = SDL_GetWindowFromID( m_windowId.value() );
        if ( nullptr != sdlWindow )
        {
            SDL_SetWindowPosition( sdlWindow, _x, _y);
            m_extent.xPos = _x;
            m_extent.yPos = _y;
        }
        else
        {
            gAppLogger->error( formatString( "SDL Window could not be retrieved. Error: %s", SDL_GetError() ).c_str() );
        }
    }

    void SdlWindow::setWindowTitle( const char* _title )
    {
        SDL_Window* sdlWindow = SDL_GetWindowFromID( m_windowId.value() );
        if ( nullptr != sdlWindow )
        {
            SDL_SetWindowTitle( sdlWindow, _title );
        }
        else
        {
            gAppLogger->error( formatString( "SDL Window could not be retrieved. Error: %s", SDL_GetError() ).c_str() );
        }
    }
}

