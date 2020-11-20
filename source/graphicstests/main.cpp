#include <precompiledgraphics.h>
#include <graphics/igraphics.h>
#include <graphics/graphicdefinitions.h>

using namespace puma::gfx;

int main()
{
    auto graphicsPtr = IGraphics::create();

    Extent extent = { 500,500,100,100 };
    graphicsPtr->init( extent , "GraphicsTest" );

    bool shouldQuit = false;

    while ( !shouldQuit )
    {
        graphicsPtr->update();

        shouldQuit = graphicsPtr->shouldQuit();
    }

    
}