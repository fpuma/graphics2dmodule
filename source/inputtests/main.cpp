#include <precompiledapplication.h>
#include <input/iinput.h>
#include <application/iapplication.h>
#include <application/commondefinitions.h>

using namespace puma;

int main()
{
    auto graphics = app::IApplication::create();
    auto ip = input::IInput::create();

    app::Extent extent = { 500,500,100,100 };
    graphics->init();
    graphics->createWindow( extent, "InputTest" );

    while ( !graphics->shouldQuit() )
    {
        ip->update();
        graphics->update();
    };

    return 0;
}