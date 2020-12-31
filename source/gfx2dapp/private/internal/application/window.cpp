#include <precompiledapplication.h>

#include "window.h"

#include <SDL.h>

namespace puma::app
{
    
    Window::Window( const Extent& _windowExtent, const char* _windowName )
    {
        m_extent = _windowExtent;

        SDL_Window* sdlWindow = SDL_CreateWindow( _windowName, _windowExtent.xPos, _windowExtent.yPos, _windowExtent.width, _windowExtent.height, SDL_WINDOW_SHOWN );

        if ( nullptr == sdlWindow )
        {
            std::cout << "SDL Window could not be created. Error: " << SDL_GetError() << std::endl;
        }
        else
        {
            m_windowHandle = SDL_GetWindowID( sdlWindow );
            m_renderer = std::make_unique<Renderer>( *this );
        }
    }

    Window::~Window()
    {
        SDL_Window* sdlWindow = SDL_GetWindowFromID( m_windowHandle );
        assert( nullptr != sdlWindow );
        SDL_DestroyWindow( sdlWindow );
        m_windowHandle = kInvalidWindowHandle;
        m_renderer.reset();
    }

    WindowHandle Window::getWindowHandle() const
    {
        return m_windowHandle;
    }
}

