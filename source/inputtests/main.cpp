#include <precompiledgraphics.h>
#include <input/iinput.h>
#include <graphics/igraphics.h>
#include <graphics/graphicdefinitions.h>

int main()
{
    auto graphics = puma::gfx::IGraphics::create();
    auto ip = puma::IInput::create();

    puma::gfx::Extent extent = { 100,100,100,100 };
    graphics->init( extent, "InputTest" );

    while ( !graphics->shouldQuit() )
    {
        ip->update();
        graphics->update();
    };

    return 0;
}