#pragma once

#include <application/iwindow.h>
#include <internal/application/renderer.h>

struct SDL_Window;
struct SDL_Renderer;

namespace puma::nina
{
    class Window : public IWindow
    {
    public:
        Window( const Extent& _windowExtent, const char* _windowName );
        ~Window();

        void setWindowSize( s32 _width, s32 _height ) override;
        void setWindowPosition( s32 _x, s32 _y ) override;

        Renderer* getRenderer() override { return m_renderer.get(); }
        const Renderer* getRenderer() const override { return m_renderer.get(); }

        Extent getExtent() const override { return m_extent; }

        WindowHandle getWindowHandle() const override { return m_windowHandle; }

        bool isValid() const override { return m_windowHandle != kInvalidWindowHandle; }

    private:

        Extent m_extent = {};
        WindowHandle m_windowHandle = kInvalidWindowHandle;
        std::unique_ptr<Renderer> m_renderer = nullptr;
    };
}

