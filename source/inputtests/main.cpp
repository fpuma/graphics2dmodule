#include <precompiledgraphics.h>
#include <input/iinput.h>
#include <graphics/igraphics.h>
#include <graphics/graphicdefinitions.h>

using namespace puma;

int main()
{
    auto graphics = gfx::IGraphics::create();
    auto ip = input::IInput::create();

    gfx::Extent extent = { 100,100,100,100 };
    graphics->init( extent, "InputTest" );

    while ( !graphics->shouldQuit() )
    {
        ip->update();
        graphics->update();
    };

    return 0;
}