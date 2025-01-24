#include <precompiledapplication.h>

#include "oglrenderer.h"
          
#include <internal/application/opengl/oglwindow.h>
#include <internal/applogger/applogger.h>
#include <nina/texturemanager/texture.h>

#include <utils/graphics/dimensions.h>
#include <utils/geometry/geometryhelpers.h>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include <iterator>

namespace puma::nina
{
    OglRenderer::OglRenderer(OglWindow& _window )
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
    }

    OglRenderer::~OglRenderer()
    {
        SDL_DestroyRenderer( m_sdlRenderer );
        m_sdlRenderer = nullptr;
    }

    void OglRenderer::beginRender() const
    {
        SDL_SetRenderDrawColor( m_sdlRenderer, m_bgColor.red, m_bgColor.green, m_bgColor.blue, m_bgColor.alpha );
        SDL_RenderClear( m_sdlRenderer );
    }

    void OglRenderer::endRender() const
    {
        SDL_RenderPresent( m_sdlRenderer );
    }
}
