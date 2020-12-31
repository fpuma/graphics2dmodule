#pragma once

#include <application/iwindow.h>
#include <internal/application/renderer.h>

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

        bool isValid() const override { return m_windowHandle != kInvalidWindowHandle; }

    private:

        Extent m_extent = {};
        WindowHandle m_windowHandle = kInvalidWindowHandle;
        std::unique_ptr<Renderer> m_renderer = nullptr;
    };
}

