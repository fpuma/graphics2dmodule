#include <precompiledgraphics.h>

#include <internal/application/window.h>

#include <application/graphicdefinitions.h>

#include <iostream>
#include <SDL.h>

namespace puma::gfx
{
    
    void Window::init( const Extent& _windowExtent, const char* _windowName )
    {
        m_extent = _windowExtent;

        m_sdlWindow = SDL_CreateWindow( _windowName, _windowExtent.xPos, _windowExtent.yPos, _windowExtent.width, _windowExtent.height, SDL_WINDOW_SHOWN );

        if ( nullptr == m_sdlWindow )
        {
            std::cout << "SDL Window could not be created. Error: " << SDL_GetError() << std::endl;
        }
    }

    void Window::uninit()
    {
        SDL_DestroyWindow( m_sdlWindow );
        m_sdlWindow = nullptr;
    }

}

