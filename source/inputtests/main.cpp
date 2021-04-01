#include <precompiledapplication.h>
#include <application/iapplication.h>
#include <input/iinput.h>
#include <utils/graphics/dimensions.h>
#include <logger/logger.h>
#include <logger/output/consolelogoutput.h>

using namespace puma;

int main()
{
    auto appPtr = app::IApplication::create();
    appPtr->init();
    appPtr->getLogger()->addOutput<ConsoleLogOutput>();
    auto ip = app::IInput::create();

    Extent extent = { 500,500,100,100 };
    appPtr->createWindow( extent, "InputTest" );

    while ( !appPtr->shouldQuit() )
    {
        ip->update();
        appPtr->update();
    };

    appPtr->uninit();

    return 0;
}