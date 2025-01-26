#include <precompiledapplication.h>
#include <nina/application/iapplication.h>
#include <nina/application/ioglrenderer.h>
#include <nina/application/ioglwindow.h>
#include <nina/application/isdlrenderer.h>
#include <nina/application/isdlwindow.h>
#include <utils/logger/logger.h>
#include <utils/logger/output/consolelogoutput.h>
#include <utils/graphics/color.h>
#include <utils/graphics/dimensions.h>
#include <nina/texturemanager/itexturemanager.h>
#include <nina/texturemanager/texture.h>

#include <vector>
#include <iostream>

#include "tests.h"

using namespace puma::nina;
using namespace puma;

void testTextureManager();
void testApplication();

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

    //testTextureManager();
    testApplication();
    return 0;
}

void testTextureManager()
{
    auto appPtr = IApplication::create();
    appPtr->init();
    Extent extent = { 500,500,100,100 };
    SdlWindowId windowId = appPtr->createSdlWindow( extent, "AppTest" );
    ITextureManager* textureManagerPtr = appPtr->getWindow( windowId )->getRenderer()->getTextureManager();

    Texture myTexture = textureManagerPtr->loadTexture( "../asset/programmerdrawing.png" );
    Texture myTexture2 = textureManagerPtr->loadTexture( "../asset/programmerdrawing.png" );
    FontHandle myFont = textureManagerPtr->loadFont( "../asset/Blitztark_v0-Regular.ttf" );
    Texture myText3 = textureManagerPtr->loadText( { "Test text", "../asset/Blitztark_v0-Regular.ttf", Color::Blue() } );

    textureManagerPtr->unloadText( myText3 );
    textureManagerPtr->unloadTexture( myTexture );
    textureManagerPtr->unloadFont( myFont );

    while (!appPtr->shouldQuit())
    {
        appPtr->update();
    }

    appPtr->uninit();

}

void testApplication()
{
    auto appPtr = IApplication::create();
    
    appPtr->init();

    appPtr->getLogger()->addOutput<ConsoleLogOutput>();

    bool shouldQuit = false;

    SdlTest0 test0;
    SdlTest1 test1;
    OglTest0 test2;

    test0.initTest(appPtr.get());
    test1.initTest(appPtr.get());
    test2.initTest(appPtr.get());

    while ( !shouldQuit )
    {
        appPtr->update();
        
        test0.updateTest(appPtr.get());
        test1.updateTest(appPtr.get());
        test2.updateTest(appPtr.get());

        shouldQuit = appPtr->shouldQuit();
    }

    appPtr->uninit();
}