#pragma once

#include <nina/application/irenderer.h>
#include <internal/texturemanager/texturemanager.h>
#include <utils/graphics/color.h>

struct SDL_Window;
struct SDL_Renderer;

namespace puma::nina
{
    class SdlWindow;

    class SdlRenderer final : public ISdlRenderer
    {
    public:
        SdlRenderer( SdlWindow& _window );
        ~SdlRenderer();

        void beginRender() const override;
        void endRender() const override;

        bool isValid() const override { return m_sdlRenderer != nullptr; }

        void setDefaultBackgroundColor( const Color& _bgColor ) override { m_bgColor = _bgColor; }

        const RendererHandle getRendererHandle() const { return m_sdlRenderer; }
        RendererHandle getRendererHandle() { return m_sdlRenderer; }
        
        TextureManager* getTextureManager() const override { return m_textureManager.get(); }

        void renderTexture( const Texture& _texture, const Extent& _textureExtent, const Extent& _targetExtent, float _rotation ) const override;

        void renderText( const ScreenPos& _pos, const Color& _color, const char* _text ) const override;
        
        void renderPolygon( const std::vector<ScreenPos>& _vertices, const Color& _color ) const override;
        void renderSolidPolygon( const std::vector<ScreenPos>& _vertices, const Color& _color ) const override;
        
        void renderCircle( const ScreenPos& _pos, s32 _radius, const Color& _color ) const override;
        void renderSolidCircle( const ScreenPos& _pos, s32 _radius, const Color& _color ) const override;
        
        void renderSegment( const ScreenPos& _pos0, const ScreenPos& _pos1, const Color& _color ) const override;

    private:

        SDL_Renderer* m_sdlRenderer = nullptr;
        Color m_bgColor = { 0, 0, 255, 255 };
        std::unique_ptr<TextureManager> m_textureManager;
    };
}