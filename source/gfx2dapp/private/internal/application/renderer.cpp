#include <precompiledgraphics.h>

#include "renderer.h"
          
#include <application/graphicdefinitions.h>
#include <internal/application/window.h>
#include <texturemanager/texture.h>

#include <iostream>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>

namespace puma::app
{
    Renderer::Renderer( Window& _window )
    {
        m_sdlRenderer = SDL_CreateRenderer( _window.getSdlWindow(), -1, SDL_RENDERER_ACCELERATED );
        if ( nullptr == m_sdlRenderer )
        {
            std::cout << "SDL Renderer could not be created. Error: " << SDL_GetError() << std::endl;
        }
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

    void Renderer::renderText( const s32 _xPos, const s32 _yPos, const char* _text ) const
    {
        stringRGBA( m_sdlRenderer, (s16)_xPos, (s16)_yPos, _text, 255, 0, 255, 255 );
    }

    void Renderer::renderPolygon( const s16* _xCoords, const s16* _yCoords, s32 vertexCount, const Color& _color )
    {
        polygonRGBA( m_sdlRenderer, _xCoords, _yCoords, vertexCount, _color.red, _color.green, _color.blue, _color.alpha );
    }

    void Renderer::renderSolidPolygon( const s16* _xCoords, const s16* _yCoords, s32 vertexCount, const Color& _color )
    {
        filledPolygonRGBA( m_sdlRenderer, _xCoords, _yCoords, vertexCount, _color.red, _color.green, _color.blue, _color.alpha );
    }

    void Renderer::renderCircle( const s32 _xCenter, const s32 _yCenter, s32 _radius, const Color& _color )
    {
        circleRGBA( m_sdlRenderer, (s16)_xCenter, (s16)_yCenter, (s16)_radius, _color.red, _color.green, _color.blue, _color.alpha );
    }

    void Renderer::renderSolidCircle( const s32 _xCenter, const s32 _yCenter, s32 _radius, const Color& _color )
    {
        filledCircleRGBA( m_sdlRenderer, (s16)_xCenter, (s16)_yCenter, (s16)_radius, _color.red, _color.green, _color.blue, _color.alpha );
    }

    void Renderer::renderSegment( const s32 _x1, const s32 _y1, const s32 _x2, const s32 _y2, const Color& _color )
    {
        lineRGBA( m_sdlRenderer, (s16)_x1, (s16)_y1, (s16)_x2, (s16)_y2, _color.red, _color.green, _color.blue, _color.alpha );
    }
}
