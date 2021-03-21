#include <precompiledapplication.h>
#include <application/iapplication.h>
#include <input/iinput.h>
#include <utils/graphics/dimensions.h>
#include <logger/logger.h>
#include <logger/output/consolelogoutput.h>

using namespace puma;

int main()
{
    auto graphics = app::IApplication::create();
    graphics->getLogger()->addOutput<ConsoleLogOutput>();
    auto ip = input::IInput::create();

    Extent extent = { 500,500,100,100 };
    graphics->createWindow( extent, "InputTest" );

    while ( !graphics->shouldQuit() )
    {
        ip->update();
        graphics->update();
    };

    return 0;
}