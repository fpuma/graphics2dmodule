#pragma once

#include <nina/texturemanager/itexturemanager.h>

#include <string>

namespace puma::nina
{
    class TextureManager final : public ITextureManager
    {
    public:
        TextureManager( ISdlRenderer* _renderer );
        ~TextureManager();

        Texture loadTexture( const char* _texturePath ) override;
        FontHandle loadFont( const char* _fontPath ) override;
        Texture loadText( const TexturizedTextInfo& _textInfo ) override;

        void unloadTexture( const Texture& _texture ) override;
        void unloadFont( FontHandle _fontHandle ) override;
        void unloadText( const Texture& _texture ) override;

        void clearTextures() override;

    private:

        Texture textToTexture( const char* _text, FontHandle _font, const Color& _color );

        using PathHash = std::hash<std::string>;

        struct TextureData
        {
            std::string path;
            Texture texture;
        };

        struct FontData
        {
            std::string path;
            FontHandle font = nullptr;
        };

        struct TextData
        {
            TexturizedTextInfo textInfo;
            Texture texture;
        };

        std::vector<TextureData> m_textures;
        std::vector<FontData> m_fonts;
        std::vector<TextData> m_texts;
        
        ISdlRenderer* m_renderer = nullptr;
    };
}