#pragma once

#include <texturemanager/itexturemanager.h>

#include <SDL_ttf.h>

namespace puma::app
{
    class Renderer;

    class TextureManager final : public ITextureManager
    {
    public:
        TextureManager();
        ~TextureManager();

        Texture loadTexture( IRenderer* _renderer, const char* _texturePath ) override;
        Texture textToTexture( IRenderer* _renderer, const char* _text, FontHandle _font, const Color& _color ) override;
        FontHandle loadFont( const char* _fontPath ) override;

        void releaseTextures();

    private:

        using TexturePathPair = std::pair<TextureHandle, const char*>;

        std::vector<TexturePathPair> m_sdlTextures;
        std::vector<TTF_Font*> m_sdlFonts;
    };
}