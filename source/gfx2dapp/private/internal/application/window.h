#pragma once
#include <application/iwindow.h>
#include <application/commondefinitions.h>
#include <internal/application/renderer.h>

#include <memory>

struct SDL_Window;
struct SDL_Renderer;

namespace puma::app
{

    class Window : public IWindow
    {
    public:
        Window( const Extent& _windowExtent, const char* _windowName );
        ~Window();

        Renderer* getRenderer() override { return m_renderer.get(); }
        const Renderer* getRenderer() const override { return m_renderer.get(); }

        Extent getExtent() const override { return m_extent; }

        WindowHandle getWindowHandle() const override;

        bool isValid() const override { return m_sdlWindow != nullptr; }

        const SDL_Window* getSdlWindow() const { return m_sdlWindow; }
        SDL_Window* getSdlWindow() { return m_sdlWindow; }

    private:

        Extent m_extent = {};
        SDL_Window* m_sdlWindow = nullptr;
        std::unique_ptr<Renderer> m_renderer;
 
    };
}

