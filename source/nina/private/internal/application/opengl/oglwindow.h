#pragma once

#include <nina/application/ioglwindow.h>
#include <internal/application/opengl/oglrenderer.h>

namespace puma::nina
{
    class OglWindow : public IOglWindow
    {
    public:
        OglWindow( const Extent& _windowExtent, const char* _windowName );
        ~OglWindow();

        void setWindowSize( s32 _width, s32 _height ) override;
        void setWindowPosition( s32 _x, s32 _y ) override;
        void setWindowTitle( const char* _title ) override;

        OglRenderer* getRenderer() override { return m_renderer.get(); }
        const OglRenderer* getRenderer() const override { return m_renderer.get(); }

        Extent getExtent() const override { return m_extent; }

        OglWindowId getWindowId() const override { return m_windowId; }

        bool isValid() const override { return m_windowId.isValid(); }

    private:

        Extent m_extent = {};
        OglWindowId m_windowId;
        std::unique_ptr<OglRenderer> m_renderer = nullptr;
    };
}

