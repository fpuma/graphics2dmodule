#pragma once

namespace puma
{
    struct Color;
    struct Extent;
    struct ScreenPos;
}

namespace puma::nina
{
    class Texture;
    class ITextureManager;

    class IRenderer : public NonCopyable
    {
    public:
        virtual ~IRenderer() = default;

        virtual bool isValid() const = 0;
        virtual void beginRender() const = 0;
        virtual void endRender() const = 0;

        virtual void setDefaultBackgroundColor( const Color& _bgColor ) = 0;

        virtual const RendererHandle getRendererHandle() const = 0;
        virtual RendererHandle getRendererHandle() = 0;

        virtual ITextureManager* getTextureManager() const = 0;

        virtual void renderTexture( const Texture& _texture, const Extent& _textureExtent, const Extent& _targetExtent, float _rotation ) const = 0;
        virtual void renderText( const ScreenPos& _pos, const Color& _color, const char* _text ) const = 0;

		virtual void renderPolygon( const std::vector<ScreenPos>& _vertices, const Color& _color ) const = 0;
		virtual void renderSolidPolygon( const std::vector<ScreenPos>& _vertices, const Color& _color ) const = 0;
		
        virtual void renderCircle( const ScreenPos& _pos, s32 _radius, const Color& _color ) const = 0;
		virtual void renderSolidCircle( const ScreenPos& _pos, s32 _radius, const Color& _color ) const = 0;
        
        virtual void renderSegment( const ScreenPos& _pos0, const ScreenPos& _pos1, const Color& _color ) const = 0;
    };
}