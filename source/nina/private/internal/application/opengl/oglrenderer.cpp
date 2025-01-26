#include <precompiledapplication.h>

#include "oglrenderer.h"
          
#include <internal/application/opengl/oglwindow.h>
#include <internal/applogger/applogger.h>
#include <nina/texturemanager/texture.h>

#include <utils/graphics/dimensions.h>
#include <utils/geometry/geometryhelpers.h>

#include <SDL.h>

#include <iterator>

namespace puma::nina
{
    OglRenderer::OglRenderer(OglWindow& _window )
        : m_window(_window)
    {
        SDL_Window* sdlWindow = SDL_GetWindowFromID( _window.getWindowId().value() );

        m_oglRenderer = SDL_GL_CreateContext(sdlWindow);
        if (!m_oglRenderer)
        {
            gAppLogger->error(formatString("Could not create OGL context. Error: %s", SDL_GetError()).c_str());
        }

        // Initialize GLAD
        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            gAppLogger->error("Failed to initialize GLAD");
        }
    }

    OglRenderer::~OglRenderer()
    {
        SDL_GL_DeleteContext( m_oglRenderer );
        m_oglRenderer = nullptr;
    }

    void OglRenderer::beginRender() const
    {
        // Clear the screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OglRenderer::endRender() const
    {
        SDL_Window* sdlWindow = SDL_GetWindowFromID(m_window.getWindowId().value());
        SDL_GL_SwapWindow(sdlWindow);
    }
}
