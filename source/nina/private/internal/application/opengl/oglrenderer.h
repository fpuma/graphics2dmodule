#pragma once

#include <nina/application/ioglrenderer.h>
#include <utils/graphics/color.h>

struct SDL_Window;
struct SDL_Renderer;

namespace puma::nina
{
    class OglWindow;

    class OglRenderer final : public IOglRenderer
    {
    public:
        OglRenderer(OglWindow& _window );
        ~OglRenderer();

        void beginRender() const override;
        void endRender() const override;

        bool isValid() const override { return m_sdlRenderer != nullptr; }

        void setDefaultBackgroundColor( const Color& _bgColor ) override { m_bgColor = _bgColor; }

        const RendererHandle getRendererHandle() const { return m_sdlRenderer; }
        RendererHandle getRendererHandle() { return m_sdlRenderer; }
       
    private:

        SDL_Renderer* m_sdlRenderer = nullptr;
        Color m_bgColor = { 0, 0, 255, 255 };
    };
}