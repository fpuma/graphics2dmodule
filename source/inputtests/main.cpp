#include <precompiledapplication.h>
#include <application/iapplication.h>
#include <application/iwindow.h>
#include <application/irenderer.h>
#include <input/iinput.h>
#include <utils/graphics/dimensions.h>
#include <logger/logger.h>
#include <logger/output/consolelogoutput.h>

#include <input/devices/ikeyboard.h>
#include <input/devices/imouse.h>
#include <input/devices/icontroller.h>

#include <utils/formatstring.h>

using namespace puma;
using namespace puma::app;

#define PRINT_WHEN_USED_CONTROLLER(KEY) if ( ip->getController().keyPressed( KEY ) ) \
{\
    std::cout << #KEY << " PRESSED" << std::endl;\
}\
if ( ip->getController().keyReleased( KEY ) )\
{\
    std::cout << #KEY << " RELEASED" << std::endl;\
}


int main()
{
    auto appPtr = IApplication::create();
    appPtr->init();
    appPtr->getLogger()->addOutput<ConsoleLogOutput>();
    auto ip = app::IInput::create();

    Extent extent = { 500,500,100,100 };
    WindowHandle window = appPtr->createWindow( extent, "InputTest" );

    ip->init();

    IWindow* windowPtr = appPtr->getWindow( window );
    IRenderer* rendererPtr = windowPtr->getRenderer();
    rendererPtr->setDefaultBackgroundColor( Color::Black() );

    while ( !appPtr->shouldQuit() )
    {
        ip->update();
        appPtr->update();

        PRINT_WHEN_USED_CONTROLLER( ControllerKey::CB_DPAD_UP );
        PRINT_WHEN_USED_CONTROLLER( ControllerKey::CB_DPAD_RIGHT );
        PRINT_WHEN_USED_CONTROLLER( ControllerKey::CB_DPAD_DOWN );
        PRINT_WHEN_USED_CONTROLLER( ControllerKey::CB_DPAD_LEFT );
        PRINT_WHEN_USED_CONTROLLER( ControllerKey::CB_A );
        PRINT_WHEN_USED_CONTROLLER( ControllerKey::CB_B );
        PRINT_WHEN_USED_CONTROLLER( ControllerKey::CB_X );
        PRINT_WHEN_USED_CONTROLLER( ControllerKey::CB_Y );
        PRINT_WHEN_USED_CONTROLLER( ControllerKey::CB_LB );
        PRINT_WHEN_USED_CONTROLLER( ControllerKey::CB_RB );
        PRINT_WHEN_USED_CONTROLLER( ControllerKey::CB_SELECT );
        PRINT_WHEN_USED_CONTROLLER( ControllerKey::CB_START );
        PRINT_WHEN_USED_CONTROLLER( ControllerKey::CB_LSTICK );
        PRINT_WHEN_USED_CONTROLLER( ControllerKey::CB_RSTICK );

        rendererPtr->beginRender();
        rendererPtr->renderText( { 0, 0 },
            Color::White(),
            formatString( "%.4f | %.4f", ip->getController().getLeftJoystickPosition().x, ip->getController().getLeftJoystickPosition().y ).c_str() );
        rendererPtr->renderText( { 0, 15 },
            Color::White(),
            formatString( "%.4f | %.4f", ip->getController().getRightJoystickPosition().x, ip->getController().getRightJoystickPosition().y ).c_str() );
        rendererPtr->renderText( { 0, 30 },
            Color::White(),
            formatString( "%.4f", ip->getController().getLeftTrigger() ).c_str() );
        rendererPtr->renderText( { 0, 45 },
            Color::White(),
            formatString( "%.4f", ip->getController().getRightTrigger() ).c_str() );
        rendererPtr->endRender();
        
    };

    appPtr->uninit();

    return 0;
}