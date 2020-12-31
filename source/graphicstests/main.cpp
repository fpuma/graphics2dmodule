#include <precompiledapplication.h>
#include <application/iapplication.h>
#include <application/irenderer.h>
#include <application/iwindow.h>
#include <utils/graphics/color.h>
#include <utils/graphics/dimensions.h>
#include <texturemanager/itexturemanager.h>
#include <texturemanager/texture.h>

#include <vector>
#include <iostream>

using namespace puma::app;
using namespace puma;

int main( int argc, char* argv[] )
{
    auto appPtr = IApplication::create();
    auto textureManagerPtr = ITextureManager::create();

    std::vector<WindowHandle> windows;

    Extent extent = { 500,500,100,100 };
    Extent extent2 = { 500,500,700,100 };
    appPtr->init();

    WindowHandle windowHandle = appPtr->createWindow( extent, "AppTest" );
    WindowHandle windowHandle2 = appPtr->createWindow( extent2, "AppTest2" );
    assert( appPtr->getWindow( windowHandle )->isValid() );

    windows.emplace_back( windowHandle );
    windows.emplace_back( windowHandle2 );

    for ( WindowHandle wh : windows )
    {
        IRenderer* renderer = appPtr->getWindow( wh )->getRenderer();
        assert( renderer->isValid() );

        renderer->setDefaultBackgroundColor( { 0, 0, 0, 255 } );
    }

    Texture myTexture = textureManagerPtr->loadTexture( appPtr->getWindow(windowHandle)->getRenderer(), "../asset/programmerdrawing.png" );
    assert( myTexture.isValid() );

    std::cout << myTexture.getOriginalSize().width << " " << myTexture.getOriginalSize().height;

    bool shouldQuit = false;

    while ( !shouldQuit )
    {
        appPtr->update();
        

        for ( WindowHandle wh : windows )
        {
            IWindow* window = appPtr->getWindow( wh );

            if ( window != nullptr )
            {
                IRenderer* renderer = window->getRenderer();
                renderer->beginRender();

                if ( wh == windowHandle )
                {                   
                    Extent textureExtent = { myTexture.getOriginalSize().width, myTexture.getOriginalSize().height, 0, 0 };
                    Extent targetExtent = { 200, 200, 200, 200 };
                    renderer->renderTexture( myTexture, textureExtent, targetExtent, 0.0f );
                }

                if ( wh == windowHandle2 )
                {
                    renderer->renderCircle( 50, 50, 25, { 255,0,0,255 } );
                }

                renderer->endRender();
            }
        }

        shouldQuit = appPtr->shouldQuit();
    }

    
}