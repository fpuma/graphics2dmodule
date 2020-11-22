#include <precompiledgraphics.h>

#include <internal/graphics.h>

#include <internal/window.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <assert.h>
#include <vector>

namespace puma::gfx
{
    constexpr s32 kSdlEventBufferSize = 10;

    Graphics::Graphics() {}
    Graphics::~Graphics() {}

    std::unique_ptr<IGraphics> IGraphics::create()
    {
        return std::make_unique<Graphics>();
    }

    void Graphics::init( const Extent& _extent, const char* _windowName )
    {
        if ( SDL_InitSubSystem( SDL_INIT_VIDEO ) < 0 )
        {
            std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
            return;
        }

        if ( TTF_Init() == -1 )
        {
            std::cout << "Error initializing SDL TTF: " << TTF_GetError() << std::endl;
        }

        m_window = std::make_unique<Window>();
        m_window->init( _extent, _windowName );
        assert( m_window->isValid() );
        
        m_renderer = std::make_unique<Renderer>();
        m_renderer->init( *m_window );
        assert( m_renderer->isValid() );

        m_textureManager = std::make_unique<TextureManager>( *m_renderer );
    }

    void Graphics::uninit()
    {
        m_textureManager->releaseTextures();
        m_renderer->uninit();
        m_window->uninit();

        TTF_Quit();
        SDL_QuitSubSystem( SDL_INIT_VIDEO );
    }

    void Graphics::update()
    {
        SDL_Event sdlEvents[kSdlEventBufferSize];
        SDL_PumpEvents();
        SDL_eventaction sdlEventAction = m_peekSdlEvents ? SDL_PEEKEVENT : SDL_GETEVENT;

        s32 eventsRetreived = SDL_PeepEvents( sdlEvents, kSdlEventBufferSize, sdlEventAction, 255, 257 );
        if (eventsRetreived < 0)
        {
            std::cout << "Error retreiving SDL_QUIT: " << SDL_GetError() << std::endl;
        }
        assert( eventsRetreived >= 0 );
        for (s32 eventIndex = 0; eventIndex < eventsRetreived; ++eventIndex)
        {
			switch (sdlEvents[eventIndex].type)
			{
			case SDL_QUIT:
			{
				m_shouldQuit = true;
				break;
			}

			default:
				break;
			}
        }
    }

    Extent Graphics::getWindowExtent() const
    { 
        return m_window->getExtent(); 
    }
}