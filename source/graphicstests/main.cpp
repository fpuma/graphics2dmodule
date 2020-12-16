#include <precompiledgraphics.h>
#include <application/graphicdefinitions.h>
#include <application/iapplication.h>
#include <application/irenderer.h>
#include <application/iwindow.h>
#include <texturemanager/itexturemanager.h>
#include <texturemanager/texture.h>

#include <iostream>

using namespace puma::app;

int main( int argc, char* argv[] )
{
    auto appPtr = IApplication::create();
    auto textureManagerPtr = ITextureManager::create();

    Extent extent = { 500,500,100,100 };
    Extent extent2 = { 500,500,700,100 };
    appPtr->init();

    WindowHandle windowHandle = appPtr->createWindow( extent, "AppTest" );
    WindowHandle windowHandle2 = appPtr->createWindow( extent, "AppTest2" );
    assert( appPtr->getWindow( windowHandle )->isValid() );

    IRenderer* renderer = appPtr->getWindow( windowHandle )->getRenderer();
    assert( renderer->isValid() );

    IRenderer* renderer2 = appPtr->getWindow( windowHandle2 )->getRenderer();
    assert( renderer2->isValid() );

    renderer->setDefaultBackgroundColor( { 0, 0, 0, 255 } );
    renderer2->setDefaultBackgroundColor( { 0, 255, 0, 255 } );

    Texture myTexture = textureManagerPtr->loadTexture( "../asset/programmerdrawing.png" );
    assert( myTexture.isValid() );

    std::cout << myTexture.getOriginalSize().width << " " << myTexture.getOriginalSize().height;

    bool shouldQuit = false;

    while ( !shouldQuit )
    {
        appPtr->update();
        
        renderer->beginRender();
        

        renderer->renderCircle( 50, 50, 25, { 255,0,0,255 } );

        Extent textureExtent = { myTexture.getOriginalSize().width, myTexture.getOriginalSize().height, 0, 0 };
        Extent targetExtent = { 200, 200, 200, 200 };
        renderer->renderTexture( myTexture, textureExtent, targetExtent, 0.0f );

        renderer->endRender();
        
        //renderer2->beginRender();
        //renderer2->endRender();

        shouldQuit = appPtr->shouldQuit();
    }

    
}