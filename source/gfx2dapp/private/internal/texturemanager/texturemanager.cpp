#include <precompiledapplication.h>

#include "texturemanager.h"

#include <internal/application/renderer.h>
#include <utils/graphics/dimensions.h>
#include <utils/hash.h>

#include <functional>

#include <SDL_Image.h>
#include <SDL_ttf.h>


namespace puma::app
{
    std::unique_ptr<ITextureManager> ITextureManager::create( IRenderer* _renderer )
    {
        return std::make_unique<TextureManager>( _renderer );
    }

    TextureManager::TextureManager( IRenderer* _renderer )
    {
        m_renderer = _renderer;
    }

    TextureManager::~TextureManager()
    {
        clearTextures();
    }

    //Loaders

    Texture TextureManager::loadTexture( const char* _texturePath )
    {
        TextureData textureData = { _texturePath, {} };

        auto itFoundTexture = m_textures.find( textureData );

        if ( m_textures.end() != itFoundTexture )
        {
            return itFoundTexture->texture;
        }
        else
        {
            SDL_Texture* newTexture = nullptr;

            SDL_Surface* loadedSurface = IMG_Load( _texturePath );
            if ( loadedSurface == nullptr )
            {
                std::cout << "Unable to load image " << _texturePath << "! SDL_image Error: " << IMG_GetError() << std::endl;
            }
            else
            {
                newTexture = SDL_CreateTextureFromSurface( (SDL_Renderer*)m_renderer->getRendererHandle(), loadedSurface );
                if ( newTexture == nullptr )
                {
                    std::cout << "Unable to create texture from " << _texturePath << "! SDL Error: " << SDL_GetError() << std::endl;
                }

                SDL_FreeSurface( loadedSurface );
            }

            Rect originalSize = {};
            SDL_QueryTexture( newTexture, nullptr, nullptr, &originalSize.width, &originalSize.height );

            textureData.texture = Texture ( newTexture, originalSize );
            m_textures.insert( textureData );

            return textureData.texture;
        }
    }

    FontHandle TextureManager::loadFont( const char* _fontPath )
    {
        FontData fontData = { _fontPath, nullptr };
        auto itFoundFont = m_fonts.find( fontData );

        if ( m_fonts.end() != itFoundFont )
        {
            return itFoundFont->font;
        }
        else
        {
            TTF_Font* font = TTF_OpenFont( _fontPath, 72 );
            if ( nullptr == font )
            {
                std::cout << "Unable to create font from " << _fontPath << "! TTF Error: " << TTF_GetError() << std::endl;
            }

            fontData.font = font;

            m_fonts.insert( fontData );
            return font;
        }
    }

    //template <class T>
    //inline void hash_combine( std::size_t& seed, const T& v )
    //{
    //    std::hash<T> hasher;
    //    seed ^= hasher( v ) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    //}

    Texture TextureManager::loadText( const TexturizedTextInfo& _textInfo )
    {
        size_t hashResult = 0;
        hashCombine( hashResult, _textInfo.fontPath );
        hashCombine( hashResult, _textInfo.text );
        hashCombine( hashResult, _textInfo.color.red );
        hashCombine( hashResult, _textInfo.color.green );
        hashCombine( hashResult, _textInfo.color.blue );
        TextData textData = { _textInfo, {}, hashResult };

        auto itFound = m_texts.find( textData );

        if ( itFound != m_texts.end() )
        {
            return itFound->texture;
        }
        else
        {
            auto itFoundFont = m_fonts.find( { _textInfo.fontPath, nullptr } );

            assert( itFoundFont != m_fonts.end() ); //That font has not been loaded

            Texture texturizedText = textToTexture( _textInfo.text, itFoundFont->font, _textInfo.color );
            textData.texture = texturizedText;

            m_texts.insert( textData );
            return textData.texture;
        }
    }

    //Unloaders

    void TextureManager::unloadTexture( const Texture& _texture )
    {
        TextureData textureData = { {}, _texture };

        auto itFound = m_textures.find( textureData );
        if ( m_textures.end() != itFound )
        {
            SDL_DestroyTexture( (SDL_Texture*)itFound->texture.getHandle() );
            m_textures.erase( itFound );
        }
    }

    void TextureManager::unloadFont( FontHandle _fontHandle )
    {
        FontData fontData = { {}, _fontHandle };

        auto itFound = m_fonts.find( fontData );
        if ( m_fonts.end() != itFound )
        {
            TTF_CloseFont( (TTF_Font*)itFound->font );
            m_fonts.erase( itFound );
        }
    }

    void TextureManager::unloadText( const Texture& _texture )
    {
       /* for ( const TextureID& textureId : _textureIds )
        {
            auto itFound = m_sdlTextures.find( textureId );
            if ( m_sdlTextures.end() != itFound )
            {
                SDL_DestroyTexture( (SDL_Texture*)itFound->second.getHandle() );
                m_sdlTextures.erase( textureId );
            }
        }*/
    }

    //Private

    Texture TextureManager::textToTexture( const char* _text, FontHandle _font, const Color& _color )
    {
        SDL_Color color = { _color.red, _color.green, _color.blue };
        
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid( _font, _text, color );
        
        if ( nullptr == surfaceMessage )
        {
            std::cout << "Unable to create surface for text: " << _text << "! SDL Error: " << SDL_GetError() << std::endl;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface( (SDL_Renderer*)m_renderer->getRendererHandle(), surfaceMessage );

        if ( nullptr == texture )
        {
            std::cout << "Unable to create text texture: " << _text << "! SDL Error: " << SDL_GetError() << std::endl;
        }
        Rect originalSize = {};
        SDL_QueryTexture( texture, nullptr, nullptr, &originalSize.width, &originalSize.height );

        return Texture( texture, originalSize );
    }

    void TextureManager::clearTextures()
    {
        for ( const TextureData& textureData : m_textures )
        {
            SDL_DestroyTexture( textureData.texture.getHandle() );
        }
        m_textures.clear();

        for ( const FontData& fontData : m_fonts )
        {
            TTF_CloseFont( fontData.font );
        }
        m_fonts.clear();

        for ( const TextData& textData : m_texts )
        {
            SDL_DestroyTexture( textData.texture.getHandle() );
        }
        m_texts.clear();
    }
}