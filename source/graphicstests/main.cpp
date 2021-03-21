#include <precompiledapplication.h>
#include <application/iapplication.h>
#include <application/irenderer.h>
#include <application/iwindow.h>
#include <logger/logger.h>
#include <logger/output/consolelogoutput.h>
#include <utils/graphics/color.h>
#include <utils/graphics/dimensions.h>
#include <texturemanager/itexturemanager.h>
#include <texturemanager/texture.h>

#include <vector>
#include <iostream>

using namespace puma::app;
using namespace puma;

void testTextureManager();
void testApplication();

int main( int argc, char* argv[] )
{
    //testTextureManager();
    testApplication();
    return 0;
}

void testTextureManager()
{
    auto appPtr = IApplication::create();
    Extent extent = { 500,500,100,100 };
    WindowHandle windowHandle = appPtr->createWindow( extent, "AppTest" );
    ITextureManager* textureManagerPtr = appPtr->getWindow( windowHandle )->getRenderer()->getTextureManager();

    Texture myTexture = textureManagerPtr->loadTexture( "../asset/programmerdrawing.png" );
    Texture myTexture2 = textureManagerPtr->loadTexture( "../asset/programmerdrawing.png" );

    textureManagerPtr->unloadTexture( myTexture );
}

void testApplication()
{
    auto appPtr = IApplication::create();

    appPtr->getLogger()->addOutput<ConsoleLogOutput>();

    std::vector<WindowHandle> windows;

    Extent extent = { 500,500,100,100 };
    Extent extent2 = { 500,500,700,100 };

    WindowHandle windowHandle = appPtr->createWindow( extent, "AppTest" );
    WindowHandle windowHandle2 = appPtr->createWindow( extent2, "AppTest2" );
    assert( appPtr->getWindow( windowHandle )->isValid() );

    windows.emplace_back( windowHandle );
    windows.emplace_back( windowHandle2 );

    auto textureManagerPtr = appPtr->getWindow( windowHandle )->getRenderer()->getTextureManager() ;
    auto textureManagerPtr2 = appPtr->getWindow( windowHandle2 )->getRenderer()->getTextureManager();

    for ( WindowHandle wh : windows )
    {
        IRenderer* renderer = appPtr->getWindow( wh )->getRenderer();
        assert( renderer->isValid() );

        renderer->setDefaultBackgroundColor( { 0, 0, 0, 255 } );
    }

    Texture myTexture = textureManagerPtr->loadTexture( "../asset/programmerdrawing.png" );
    FontHandle myFont = textureManagerPtr2->loadFont( "../asset/Blitztark_v0-Regular.ttf" );
    Texture myText = textureManagerPtr2->loadText( { "Short", "../asset/Blitztark_v0-Regular.ttf", Color::Green() } );
    Texture myText2 = textureManagerPtr2->loadText( { "Longer text", "../asset/Blitztark_v0-Regular.ttf", Color::Blue() } );
    
    if ( myFont == nullptr )
    {
        //To prevent warning in release
        assert( false );
    }
    assert( myTexture.isValid() );
    assert( myText.isValid() );

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
                    Extent textureExtent = { myText.getOriginalSize().width, myText.getOriginalSize().height, 0, 0 };
                    Extent textureExtent2 = { myText2.getOriginalSize().width, myText2.getOriginalSize().height, 0, 0 };
                    
                    float textAspectRatio = (float)myText.getOriginalSize().width / (float)myText.getOriginalSize().height;
                    Extent targetExtent = { (s32)(60*textAspectRatio), 60, 50, 50 };
                    renderer->renderTexture( myText, textureExtent, targetExtent, 0.0f );
                                 
                    float text2AspectRatio = (float)myText2.getOriginalSize().width / (float)myText2.getOriginalSize().height;
                    targetExtent = { (s32)(text2AspectRatio*60), 60, 50, 125 };
                    renderer->renderTexture( myText2, textureExtent2, targetExtent, 0.0f );
                    renderer->renderCircle( 250, 250, 25, { 255,0,0,255 } );
                }

                renderer->endRender();
            }
        }

        shouldQuit = appPtr->shouldQuit();
    }

}