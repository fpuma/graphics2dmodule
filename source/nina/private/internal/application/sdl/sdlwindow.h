#pragma once

#include <nina/application/isdlwindow.h>
#include <internal/application/sdl/sdlrenderer.h>

struct SDL_Window;
struct SDL_Renderer;

namespace puma::nina
{
    class SdlWindow : public ISdlWindow
    {
    public:
        SdlWindow( const Extent& _windowExtent, const char* _windowName );
        ~SdlWindow();

        void setWindowSize( s32 _width, s32 _height ) override;
        void setWindowPosition( s32 _x, s32 _y ) override;
        void setWindowTitle( const char* _title ) override;

        SdlRenderer* getRenderer() override { return m_renderer.get(); }
        const SdlRenderer* getRenderer() const override { return m_renderer.get(); }

        Extent getExtent() const override { return m_extent; }

        SdlWindowId getWindowId() const override { return m_windowId; }

        bool isValid() const override { return m_windowId.isValid(); }

    private:

        Extent m_extent = {};
        SdlWindowId m_windowId;
        std::unique_ptr<SdlRenderer> m_renderer = nullptr;
    };
}

