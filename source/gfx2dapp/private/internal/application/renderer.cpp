#include <precompiledapplication.h>

#include "renderer.h"
          
#include <internal/application/window.h>
#include <internal/applogger/applogger.h>
#include <texturemanager/texture.h>

#include <utils/graphics/dimensions.h>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include <iterator>

namespace puma::app
{
    Renderer::Renderer( Window& _window )
    {
        SDL_Window* sdlWindow = SDL_GetWindowFromID( _window.getWindowHandle() );
        m_sdlRenderer = SDL_CreateRenderer( sdlWindow , -1, SDL_RENDERER_ACCELERATED );
        if ( nullptr == m_sdlRenderer )
        {
            gAppLogger->error( formatString( "SDL Renderer could not be created. Error: %s", SDL_GetError() ).c_str() );
        }
        else
        {
            gAppLogger->info( formatString( "SDL Renderer was created for window: %d", _window.getWindowHandle() ).c_str() );
        }

        m_textureManager = std::make_unique<TextureManager>( this );
    }

    Renderer::~Renderer()
    {
        SDL_DestroyRenderer( m_sdlRenderer );
        m_sdlRenderer = nullptr;
    }

    void Renderer::beginRender()
    {
        SDL_SetRenderDrawColor( m_sdlRenderer, m_bgColor.red, m_bgColor.green, m_bgColor.blue, m_bgColor.alpha );
        SDL_RenderClear( m_sdlRenderer );
    }

    void Renderer::endRender()
    {
        SDL_RenderPresent( m_sdlRenderer );
    }

    void Renderer::renderTexture( const Texture& _texture, const Extent& _textureExtent, const Extent& _targetExtent, float _rotation ) const
    {
        SDL_Rect textureRect;
        textureRect.x = _textureExtent.xPos;
        textureRect.y = _textureExtent.yPos;
        textureRect.w = _textureExtent.width;
        textureRect.h = _textureExtent.height;

        SDL_Rect targetRect;
        targetRect.x = _targetExtent.xPos;
        targetRect.y = _targetExtent.yPos;
        targetRect.w = _targetExtent.width;
        targetRect.h = _targetExtent.height;


        SDL_RenderCopyEx( m_sdlRenderer, _texture.getHandle(), &textureRect, &targetRect, _rotation, nullptr, SDL_FLIP_NONE );
    }

    void Renderer::renderText( const ScreenPos& _pos, const Color& _color, const char* _text ) const
    {
        stringRGBA( m_sdlRenderer, (s16)_pos.xCoord, (s16)_pos.yCoord, _text, _color.red, _color.green, _color.blue, _color.alpha );
    }

    namespace
    {
        void splitCoordsContainers( const std::vector<ScreenPos>& _vertices, std::vector<s16>& _outXCoords, std::vector<s16>& _outYCoords )
        {
            _outXCoords.clear();
            _outYCoords.clear();

            std::transform( _vertices.begin(), _vertices.end(), std::back_inserter( _outXCoords ), []( const ScreenPos& screenPos )
            {
                return (s16)screenPos.xCoord;
            } );

            std::transform( _vertices.begin(), _vertices.end(), std::back_inserter( _outYCoords ), []( const ScreenPos& screenPos )
            {
                return (s16)screenPos.yCoord;
            } );

            assert( _outXCoords.size() == _vertices.size() );
            assert( _outYCoords.size() == _vertices.size() );
        }
    }

    void Renderer::renderPolygon( const std::vector<ScreenPos>& _vertices, const Color& _color ) const
    {
        std::vector<s16> xCoords;
        std::vector<s16> yCoords;

        splitCoordsContainers( _vertices, xCoords, yCoords );

        polygonRGBA( m_sdlRenderer, xCoords.data(), yCoords.data(), (s32)_vertices.size(), _color.red, _color.green, _color.blue, _color.alpha );
    }

    void Renderer::renderSolidPolygon( const std::vector<ScreenPos>& _vertices, const Color& _color ) const
    {
        std::vector<s16> xCoords;
        std::vector<s16> yCoords;

        splitCoordsContainers( _vertices, xCoords, yCoords );

        filledPolygonRGBA( m_sdlRenderer, xCoords.data(), yCoords.data(), (s32)_vertices.size(), _color.red, _color.green, _color.blue, _color.alpha );
    }

    void Renderer::renderCircle( const ScreenPos& _pos, s32 _radius, const Color& _color ) const
    {
        circleRGBA( m_sdlRenderer, (s16)_pos.xCoord, (s16)_pos.yCoord, (s16)_radius, _color.red, _color.green, _color.blue, _color.alpha );
    }

    void Renderer::renderSolidCircle( const ScreenPos& _pos, s32 _radius, const Color& _color ) const
    {
        filledCircleRGBA( m_sdlRenderer, (s16)_pos.xCoord, (s16)_pos.yCoord, (s16)_radius, _color.red, _color.green, _color.blue, _color.alpha );
    }

    void Renderer::renderSegment( const ScreenPos& _pos0, const ScreenPos& _pos1, const Color& _color ) const
    {
        lineRGBA( m_sdlRenderer, (s16)_pos0.xCoord, (s16)_pos0.yCoord, (s16)_pos1.xCoord, (s16)_pos1.yCoord, _color.red, _color.green, _color.blue, _color.alpha );
    }
}
