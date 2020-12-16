#include <precompiledapplication.h>
#include <input/iinput.h>
#include <application/iapplication.h>
#include <application/commondefinitions.h>

using namespace puma;

int main()
{
    auto graphics = app::IApplication::create();
    auto ip = input::IInput::create();

    app::Extent extent = { 100,100,100,100 };
    graphics->init();

    while ( !graphics->shouldQuit() )
    {
        ip->update();
        graphics->update();
    };

    return 0;
}