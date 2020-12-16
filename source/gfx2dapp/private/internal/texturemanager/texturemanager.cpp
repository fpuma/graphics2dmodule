#include <precompiledapplication.h>

#include "texturemanager.h"

#include <internal/application/renderer.h>

#include <SDL_Image.h>

namespace puma::app
{
    std::unique_ptr<ITextureManager> ITextureManager::create()
    {
        return std::make_unique<TextureManager>();
    }

    TextureManager::TextureManager()
    {}

    TextureManager::~TextureManager()
    {
        releaseTextures();
    }

    Texture TextureManager::loadTexture( IRenderer* _renderer, const char* _texturePath )
    {
#ifdef _DEBUG
        auto it = std::find_if(m_sdlTextures.begin(), m_sdlTextures.end(), [&_texturePath](const TexturePathPair& pair)->bool
        {
            return 0 == strcmp( pair.second, _texturePath );
        } );

        assert( it == m_sdlTextures.end() );
#endif


        SDL_Texture* newTexture = nullptr;

        SDL_Surface* loadedSurface = IMG_Load( _texturePath );
        if ( loadedSurface == nullptr )
        {
            std::cout << "Unable to load image " << _texturePath << "! SDL_image Error: " << IMG_GetError() << std::endl;
            return Texture( nullptr, Rect{} );
        }
        else
        {
            newTexture = SDL_CreateTextureFromSurface( _renderer->getRendererHandle(), loadedSurface );
            if ( newTexture == nullptr )
            {
                std::cout<< "Unable to create texture from " << _texturePath << "! SDL Error: " << SDL_GetError() << std::endl;
                return Texture( nullptr, Rect{} );
            }

            SDL_FreeSurface( loadedSurface );
        }

        Rect originalSize = {};
        SDL_QueryTexture( newTexture, nullptr, nullptr, &originalSize.width, &originalSize.height );

        Texture result( newTexture, originalSize );

        m_sdlTextures.push_back( std::make_pair( newTexture, _texturePath ));

        return result;
    }

    FontHandle TextureManager::loadFont( const char* _fontPath )
    {
        TTF_Font* font = TTF_OpenFont( _fontPath, 72 );
        if ( nullptr == font )
        {
            std::cout << "Unable to create font from " << _fontPath << "! TTF Error: " << TTF_GetError() << std::endl;
        }
        FontHandle result = (s32) m_sdlFonts.size();
        m_sdlFonts.push_back( font );
        return result;
    }

    Texture TextureManager::textToTexture( IRenderer* _renderer, const char* _text, FontHandle _font, Color _color )
    {
        SDL_Color color = { _color.red, _color.green, _color.blue };
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid( m_sdlFonts[_font], _text, color );
        
        if ( nullptr == surfaceMessage )
        {
            std::cout << "Unable to create surface for text: " << _text << "! SDL Error: " << SDL_GetError() << std::endl;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface( _renderer->getRendererHandle(), surfaceMessage );

        if ( nullptr == texture )
        {
            std::cout << "Unable to create text texture: " << _text << "! SDL Error: " << SDL_GetError() << std::endl;
        }
        Rect originalSize = {};
        SDL_QueryTexture( texture, nullptr, nullptr, &originalSize.width, &originalSize.height );
        Texture result( texture, originalSize );

        m_sdlTextures.push_back( std::make_pair( texture, _text ) );

        return result;
    }

    void TextureManager::releaseTextures()
    {
        while ( m_sdlTextures.size() != 0 )
        {
            TexturePathPair& pair = m_sdlTextures.back();
            SDL_DestroyTexture( pair.first );
            m_sdlTextures.pop_back();
        }
    }

}