#include <precompiledapplication.h>

#include "texturemanager.h"

#include <internal/application/renderer.h>
#include <internal/applogger/applogger.h>

#include <utils/graphics/dimensions.h>
#include <utils/hash.h>

#include <functional>

#include <SDL_Image.h>
#include <SDL_ttf.h>


namespace puma::app
{
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
                gAppLogger->error(formatString( "Unable to load image <%s>! SDL_image Error: %s", _texturePath, IMG_GetError() ).c_str());
            }
            else
            {
                newTexture = SDL_CreateTextureFromSurface( (SDL_Renderer*)m_renderer->getRendererHandle(), loadedSurface );
                if ( newTexture == nullptr )
                {
                    gAppLogger->error( formatString( "Unable to create texture from <%s>! SDL Error: %s", _texturePath, SDL_GetError() ).c_str() );
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
                gAppLogger->error( formatString( "Unable to create font from <%s>! TTF Error: ", _fontPath, TTF_GetError() ).c_str() );
            }

            fontData.font = font;

            m_fonts.insert( fontData );
            return font;
        }
    }

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
            gAppLogger->error( formatString( "Unable to create surface for text: %s! SDL Error: ", _text, SDL_GetError() ).c_str() );
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface( (SDL_Renderer*)m_renderer->getRendererHandle(), surfaceMessage );

        if ( nullptr == texture )
        {
            gAppLogger->error( formatString( "Unable to create text texture: %s! SDL Error: %s", _text, SDL_GetError() ).c_str() );
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