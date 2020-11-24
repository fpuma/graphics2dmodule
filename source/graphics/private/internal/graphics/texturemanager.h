#pragma once
#include <graphics/itexturemanager.h>

#include <graphics/graphicdefinitions.h>

#include <SDL_ttf.h>

#include <vector>

namespace puma::gfx
{
    class Renderer;

    class TextureManager final : public ITextureManager
    {
    public:
        TextureManager( Renderer& _renderer )
            : m_renderer( _renderer ) {}
        ~TextureManager();

        Texture loadTexture( const char* _texturePath ) override;
        FontHandle loadFont( const char* _fontPath );
        Texture textToTexture( const char* _text, FontHandle _font, Color _color );

        void releaseTextures();

    private:

        using TexturePathPair = std::pair<TextureHandle, const char*>;

        std::vector<TexturePathPair> m_sdlTextures;
        std::vector<TTF_Font*> m_sdlFonts;

        Renderer& m_renderer;
    };
}