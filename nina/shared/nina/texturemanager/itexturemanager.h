#pragma once
#include <nina/texturemanager/texture.h>

namespace puma
{
    struct Color;
}

namespace puma::nina
{
    class IRenderer;

    class ITextureManager : public NonCopyable
    {
    public:
        
        virtual ~ITextureManager() = default;

        virtual Texture loadTexture( const char* _texturePath ) = 0;
        virtual FontHandle loadFont( const char* _fontPath ) = 0;
        virtual Texture loadText( const TexturizedTextInfo& _textInfo ) = 0;

        virtual void unloadTexture( const Texture& _texture ) = 0;
        virtual void unloadFont( FontHandle _fontHandle ) = 0;
        virtual void unloadText( const Texture& _texture ) = 0;

        virtual void clearTextures() = 0;
    };
}