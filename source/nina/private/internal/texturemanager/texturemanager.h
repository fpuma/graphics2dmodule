#pragma once

#include <nina/texturemanager/itexturemanager.h>

#include <string>

namespace puma::nina
{
    class TextureManager final : public ITextureManager
    {
    public:
        TextureManager( IRenderer* _renderer );
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

            bool operator < ( const TextureData& _other ) const
            {
                return (texture.isValid() && _other.texture.isValid()) ?
                    texture.getHandle() < _other.texture.getHandle() :
                    PathHash{}(path) < PathHash{}( _other.path );
            }
        };

        struct FontData
        {
            std::string path;
            FontHandle font = nullptr;

            bool operator < ( const FontData& _other ) const
            {
                return (font != nullptr && _other.font != nullptr) ?
                    font < _other.font :
                    PathHash{}(path) < PathHash{}(_other.path);
            }
        };

        struct TextData
        {
            TexturizedTextInfo textInfo;
            Texture texture;
            u64 hash = 0;

            bool operator < ( const TextData& _other ) const
            {
                return (texture.isValid() && _other.texture.isValid()) ?
                    texture.getHandle() < _other.texture.getHandle() :
                    hash < _other.hash;
            }


        };

        std::set<TextureData> m_textures;
        std::set<FontData> m_fonts;
        std::set<TextData> m_texts;
        
        IRenderer* m_renderer = nullptr;
    };
}