#pragma once
#include <application/graphicdefinitions.h>
#include <memory>

struct SDL_Window;
struct SDL_Renderer;

namespace puma::gfx
{

    class Window
    {
    public:
        Window() {}

        Window( const Window& ) = delete;
        Window& operator=( const Window& ) = delete;

        void init( const Extent& _windowExtent, const char* _windowName );
        void uninit();

        SDL_Window* getSDLWindow() const { return m_sdlWindow; }

        Extent getExtent() const { return m_extent; }

        bool isValid() const { return m_sdlWindow != nullptr; }

    private:

        Extent m_extent = {};
        SDL_Window* m_sdlWindow = nullptr;
 
    };
}

