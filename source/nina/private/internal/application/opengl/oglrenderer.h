#pragma once

#include <nina/application/ioglrenderer.h>
#include <utils/graphics/color.h>

#include <glad.h>
#include <SDL.h>

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

        bool isValid() const override { return m_oglRenderer != nullptr; }

        void setDefaultBackgroundColor( const Color& _bgColor ) override { m_bgColor = _bgColor; }

    private:

        const OglWindow& m_window;

        SDL_GLContext m_oglRenderer;
        Color m_bgColor = { 0, 0, 255, 255 };
    };
}