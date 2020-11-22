#include <SDL.h>
#include <SDL_image.h>

namespace
{
    SDL_Texture* getTexture( SDL_Renderer* _renderer, const char* _path )
    {
        SDL_Surface* loadedSurface = IMG_Load( _path );
        SDL_Texture* texture = nullptr;
        
        texture = SDL_CreateTextureFromSurface( _renderer, loadedSurface );
        SDL_FreeSurface( loadedSurface );
        
        return texture;
    }
}

int main( int argc, char* argv[] )
{
    SDL_InitSubSystem( SDL_INIT_VIDEO );

    SDL_Window* window = SDL_CreateWindow( "SDL Test", 100, 100, 1000, 1000, SDL_WINDOW_SHOWN );
    SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

    bool quit = false;

    SDL_Texture* targetTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1000, 1000 );

    SDL_Texture* texture = getTexture( renderer, "../asset/programmerdrawing.png" );

    while ( !quit )
    {
        SDL_Event event;

        while ( SDL_PollEvent( &event ) != 0 )
        {
            switch ( event.type )
            {
            case SDL_QUIT:
            {
                quit = true;
                break;
            }

            default:
                break;
            }
        }


        //Set render texture
        SDL_SetRenderTarget( renderer, targetTexture );
        //Clear render texture
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
        SDL_RenderClear( renderer );


        SDL_Rect sourceRect = { 0, 0, 400, 400 };
        SDL_Rect targetRect = { 100, 100, 300, 300 };
        SDL_RenderCopy( renderer, texture, &sourceRect, &targetRect );
        SDL_SetRenderTarget( renderer, nullptr );

        SDL_Rect rect = { 0, 0, 1000, 1000 };
        SDL_RenderCopy( renderer, targetTexture, &rect, &rect );

        SDL_RenderPresent( renderer );
    }
   

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_QuitSubSystem( SDL_INIT_VIDEO );

    return 0;
}