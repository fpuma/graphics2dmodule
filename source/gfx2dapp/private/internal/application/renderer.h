#pragma once

#include <application/irenderer.h>
#include <application/graphicdefinitions.h>

struct SDL_Window;
struct SDL_Renderer;

namespace puma::gfx
{
    class Window;
    class Texture;
    struct Extent;

    class Renderer final : public IRenderer
    {
    public:
        Renderer() {}

        void init( const Window& _window );
        void uninit();

        void beginRender() override;
        void endRender() override;

        bool isValid() const override { return m_sdlRenderer != nullptr; }
        void renderTexture( const Texture& _texture, const Extent& _textureExtent, const Extent& _targetExtent, float _rotation ) const override;

        void setDefaultBackgroundColor( Color _bgColor ) override { m_bgColor = _bgColor; }

        //[fpuma] Improve rendering position of these primitives
        void renderText( const s32 _xPos, const s32 _yPos, const char* _text ) const override;
        void renderPolygon( const s16* _xCoords, const s16* _yCoords, s32 vertexCount, const Color& _color );
        void renderSolidPolygon( const s16* _xCoords, const s16* _yCoords, s32 vertexCount, const Color& _color );
        void renderCircle( const s32 _xCenter, const s32 _yCenter, s32 _radius, const Color& _color );
        void renderSolidCircle( const s32 _xCenter, const s32 _yCenter, s32 _radius, const Color& _color );
        void renderSegment( const s32 _x1, const s32 _y1, const s32 _x2, const s32 _y2, const Color& _color );
        //-----------------------------------------------------------

        SDL_Renderer* getSDLRenderer() const { return m_sdlRenderer; }

    private:

        SDL_Renderer* m_sdlRenderer = nullptr;
        Color m_bgColor = { 0, 0, 255, 255 };
    };
}