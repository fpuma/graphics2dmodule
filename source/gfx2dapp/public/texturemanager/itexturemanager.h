#pragma once
#include <texturemanager/texture.h>

namespace puma::app
{
    class IRenderer;

    class ITextureManager : public NonCopyable
    {
    public:
        
        static std::unique_ptr<ITextureManager> create();

        virtual ~ITextureManager() = default;

        virtual Texture loadTexture( IRenderer* _renderer, const char* _path ) = 0;
        virtual Texture textToTexture( IRenderer* _renderer, const char* _text, FontHandle _font, Color _color ) = 0;
        virtual FontHandle loadFont( const char* _fontPath ) = 0;
    };
}