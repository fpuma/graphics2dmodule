#include <precompiledgraphics.h>
#include <application/graphicdefinitions.h>
#include <application/iapplication.h>
#include <application/irenderer.h>
#include <texturemanager/itexturemanager.h>
#include <texturemanager/texture.h>

using namespace puma::gfx;

int main( int argc, char* argv[] )
{
    auto graphicsPtr = IGraphics::create();

    Extent extent = { 500,500,100,100 };
    graphicsPtr->init( extent , "GraphicsTest" );

    bool shouldQuit = false;

    Texture myTexture = graphicsPtr->getTextureManager()->loadTexture( "../asset/programmerdrawing.png" );

    while ( !shouldQuit )
    {
        graphicsPtr->update();
        
        graphicsPtr->getRenderer()->beginRender();

        graphicsPtr->getRenderer()->renderCircle( 50, 50, 25, { 255,0,0,255 } );

        Extent textureExtent = { myTexture.getOriginalSize().width, myTexture.getOriginalSize().height, 0, 0 };
        Extent targetExtent = { 200, 200, 200, 200 };
        graphicsPtr->getRenderer()->renderTexture( myTexture, textureExtent, targetExtent, 0.0f );

        graphicsPtr->getRenderer()->endRender();
        
        shouldQuit = graphicsPtr->shouldQuit();
    }

    
}