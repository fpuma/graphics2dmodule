
#include <SDL.h>
#include <Windows.h>

#include <gl/GL.h>
#include <vector>
#include <iostream>

int testApplication();

int main( int argc, char* argv[] )
{
#ifdef _DEBUG
    //------------------------------------
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

    //*
    _CrtSetBreakAlloc( -1 );
    /*/
    //_CrtSetBreakAlloc( 72 );
    //*/

    //---------------------------------------------------------------//
#endif

    return testApplication();
}


SDL_Window* window = nullptr;
SDL_GLContext context;

void render() {
    glClear( GL_COLOR_BUFFER_BIT );
    glColor3f( 1.0, 1.0, 1.0 );

    glBegin( GL_POLYGON );
    glVertex2f( -0.5, -0.5 );
    glVertex2f( -0.5, 0.5 );
    glVertex2f( 0.5, 0.5 );
    glVertex2f( 0.5, -0.5 );
    glEnd();

    SDL_GL_SwapWindow( window );
}

int testApplication()
{
    // Initialize SDL
    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        return 1;
    }

    // Create an SDL window and OpenGL context
    window = SDL_CreateWindow( "Hello, World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL );
    if (!window) {
        return 1;
    }

    context = SDL_GL_CreateContext( window );

    // Initialize OpenGL
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glOrtho( -1.0, 1.0, -1.0, 1.0, -1.0, 1.0 );
    glMatrixMode( GL_MODELVIEW );
    glTranslatef( 0.0f, 0.5f, 0.0f );

    // Main loop
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent( &event )) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        render();
    }

    // Cleanup and exit
    SDL_GL_DeleteContext( context );
    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}