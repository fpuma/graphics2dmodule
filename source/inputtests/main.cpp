#include <precompiledgraphics.h>
#include <input/iinput.h>
#include <application/iapplication.h>
#include <application/graphicdefinitions.h>

using namespace puma::app;

int main()
{
    auto graphics = IApplication::create();
    auto ip = input::IInput::create();

    Extent extent = { 100,100,100,100 };
    graphics->init();

    while ( !graphics->shouldQuit() )
    {
        ip->update();
        graphics->update();
    };

    return 0;
}