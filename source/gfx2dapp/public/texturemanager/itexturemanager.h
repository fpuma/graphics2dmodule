#pragma once
#include <texturemanager/texture.h>

namespace puma::app
{
    class ITextureManager : public NonCopyable
    {
    public:
        
        static std::unique_ptr<ITextureManager> create();

        virtual ~ITextureManager() = default;

        virtual Texture loadTexture( const char* _path ) = 0;
        virtual FontHandle loadFont( const char* _fontPath ) = 0;
        virtual Texture textToTexture( const char* _text, FontHandle _font, Color _color ) = 0;
    };
}