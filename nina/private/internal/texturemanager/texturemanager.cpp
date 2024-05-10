#include <precompiledapplication.h>

#include "texturemanager.h"

#include <internal/application/renderer.h>
#include <internal/applogger/applogger.h>

#include <utils/graphics/dimensions.h>
#include <utils/hash.h>

#include <functional>

#include <SDL_Image.h>
#include <SDL_ttf.h>


namespace puma::nina
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
        auto itFoundTexture = std::find_if( m_textures.begin(), m_textures.end(), [&]( const TextureData& _td ) 
            {
                return std::strcmp( _td.path.c_str(), _texturePath ) == 0;
            });

        if (m_textures.end() != itFoundTexture)
        {
            gAppLogger->info( formatString( "Texture <%s> found. Getting from manager", _texturePath ).c_str() );
            return itFoundTexture->texture;
        }
        else
        {
            gAppLogger->info( formatString( "Texture <%s> not found. Loading from disk", _texturePath ).c_str() );
            SDL_Texture* newTexture = nullptr;

            SDL_Surface* loadedSurface = IMG_Load( _texturePath );
            if (loadedSurface == nullptr)
            {
                gAppLogger->error( formatString( "Unable to load image <%s>! SDL_image Error: %s", _texturePath, IMG_GetError() ).c_str() );
            }
            else
            {
                newTexture = SDL_CreateTextureFromSurface( (SDL_Renderer*)m_renderer->getRendererHandle(), loadedSurface );
                if (newTexture == nullptr)
                {
                    gAppLogger->error( formatString( "Unable to create texture from <%s>! SDL Error: %s", _texturePath, SDL_GetError() ).c_str() );
                }

                SDL_FreeSurface( loadedSurface );
            }

            Rect originalSize = {};
            SDL_QueryTexture( newTexture, nullptr, nullptr, &originalSize.width, &originalSize.height );

            TextureData textureData = { _texturePath, Texture( newTexture, originalSize ) };
            m_textures.emplace_back( textureData );

            return textureData.texture;
        }
    }

    FontHandle TextureManager::loadFont( const char* _fontPath )
    {
        auto itFoundFont = std::find_if( m_fonts.begin(), m_fonts.end(), [&_fontPath]( const FontData& _fd ) 
            {
                return std::strcmp( _fd.path.c_str(), _fontPath );
            });

        if (m_fonts.end() != itFoundFont)
        {
            gAppLogger->info( formatString( "Font <%s> found. Getting from manager", _fontPath ).c_str() );
            return itFoundFont->font;
        }
        else
        {
            gAppLogger->info( formatString( "Font <%s> not found. Loading from disk", _fontPath ).c_str() );
            TTF_Font* font = TTF_OpenFont( _fontPath, 72 );
            if (nullptr == font)
            {
                gAppLogger->error( formatString( "Unable to create font from <%s>! TTF Error: ", _fontPath, TTF_GetError() ).c_str() );
            }

            FontData fontData = { _fontPath, font };

            m_fonts.emplace_back( fontData );
            return font;
        }
    }

    Texture TextureManager::loadText( const TexturizedTextInfo& _textInfo )
    {
        auto itFound = std::find_if( m_texts.begin(), m_texts.end(), [&_textInfo]( const TextData& _td )
            {
                return  std::strcmp( _td.textInfo.fontPath, _textInfo.fontPath ) == 0 &&
                    std::strcmp( _td.textInfo.text, _textInfo.text ) == 0 &&
                    _td.textInfo.color == _textInfo.color;
            } );

        if (itFound != m_texts.end())
        {
            return itFound->texture;
        }
        else
        {
            auto itFoundFont = std::find_if( m_fonts.begin(), m_fonts.end(), [&_textInfo]( const FontData& _f )
                {
                    return std::strcmp( _f.path.c_str(), _textInfo.fontPath ) == 0;
                } );

            assert( itFoundFont != m_fonts.end() ); //That font has not been loaded

            Texture texturizedText = textToTexture( _textInfo.text, itFoundFont->font, _textInfo.color );
            TextData textData = { _textInfo, texturizedText };

            m_texts.emplace_back( textData );
            return textData.texture;
        }
    }

    //Unloaders

    void TextureManager::unloadTexture( const Texture& _texture )
    {
        auto itFound = std::find_if( m_textures.begin(), m_textures.end(), [&_texture]( const TextureData& _td ) 
            {
                return _td.texture.getHandle() == _texture.getHandle();
            } );

        assert( m_textures.end() != itFound ); //Did not find texture to unload
        if ( m_textures.end() != itFound )
        {
            SDL_DestroyTexture( (SDL_Texture*)itFound->texture.getHandle() );
            m_textures.erase( itFound );
        }
    }

    void TextureManager::unloadFont( FontHandle _fontHandle )
    {
        auto itFound = std::find_if( m_fonts.begin(), m_fonts.end(), [&_fontHandle]( const FontData& _fd )
            {
                return _fd.font == _fontHandle;
            } );

        assert( m_fonts.end() != itFound ); //Did not find font to unload
        if ( m_fonts.end() != itFound )
        {
            TTF_CloseFont( (TTF_Font*)itFound->font );
            m_fonts.erase( itFound );
        }
    }

    void TextureManager::unloadText( const Texture& _texture )
    {
        auto itFound = std::find_if( m_texts.begin(), m_texts.end(), [&_texture]( const TextData& _td )
            {
                return _td.texture.getHandle() == _texture.getHandle();
            } );

        assert( m_texts.end() != itFound ); //Did not find text to unload
        if (m_texts.end() != itFound)
        {
            SDL_DestroyTexture( (SDL_Texture*)itFound->texture.getHandle() );
            m_texts.erase( itFound );
        }
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