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
#include <input/iinputlistener.h>

#include <utils/formatstring.h>

using namespace puma;
using namespace puma::app;

class MyInputListener : public puma::app::IInputListener
{
public:

    MyInputListener( IInput* _input )
        :input( _input )
    {}

    void onKeyboardKey( KeyboardKey _key ) const override
    {
        if ( input->getKeyboard().keyPressed( _key ) )
        {
            std::cout << "Keyboard: " << input->getInputName(_key) << " PRESSED" << std::endl;
        }
        if ( input->getKeyboard().keyReleased( _key ) )
        {
            std::cout << "Keyboard: " << input->getInputName( _key ) << " RELEASED" << std::endl;
        }
    }
    
    void onMouseButton( MouseButton _mouseButton ) const override
    {
        if ( input->getMouse().buttonPressed( _mouseButton ) )
        {
            std::cout << "Mouse: " << input->getInputName( _mouseButton ) << " PRESSED" << std::endl;
        }
        if ( input->getMouse().buttonReleased( _mouseButton ) )
        {
            std::cout << "Mouse: " << input->getInputName( _mouseButton ) << " RELEASED" << std::endl;
        }
    }
    
    void onMouseWheel( MouseWheelState _mouseWheelState ) const override
    {
        std::cout << "Mouse: " << input->getInputName( _mouseWheelState ) << std::endl;
    }

    void onMousePosition( MousePosition _mousePosition ) const override
    {

    }

    void onControllerButton( ControllerId _id, ControllerButton _buttonId ) const override
    {
        if ( input->getController(_id).buttonPressed( _buttonId ) )
        {
            std::cout << "Controller" << _id <<": " << input->getInputName( _buttonId ) << " PRESSED" << std::endl;
        }
        if ( input->getController(_id).buttonReleased( _buttonId ) )
        {
            std::cout << "Controller" << _id << ": " << input->getInputName( _buttonId ) << " RELEASED" << std::endl;
        }
    }

    void onControllerJoystick( ControllerId _id, ControllerJoystick _joystickId, float _joystickValue ) const override {}
    void onControllerTrigger( ControllerId _id, ControllerTrigger _triggerId, float _triggerValue ) const override {}

    IInput* input;
};

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

    ip->setInputListener( std::move( std::make_unique<MyInputListener>( ip.get() ) ) );


    while ( !appPtr->shouldQuit() )
    {
        ip->update();
        appPtr->update();
        
        rendererPtr->beginRender();

        for ( u32 controllerId = 0; controllerId < ip->getControllerCount(); ++controllerId )
        {
            rendererPtr->renderText( { (s32)(controllerId * 250), 0 },
                Color::White(),
                formatString( "%.4f | %.4f", ip->getController( controllerId ).getLeftJoystickPosition().x, ip->getController( controllerId ).getLeftJoystickPosition().y ).c_str() );
            rendererPtr->renderText( { (s32)(controllerId * 250), 15 },
                Color::White(),
                formatString( "%.4f | %.4f", ip->getController( controllerId ).getRightJoystickPosition().x, ip->getController( controllerId ).getRightJoystickPosition().y ).c_str() );
            rendererPtr->renderText( { (s32)(controllerId * 250), 30 },
                Color::White(),
                formatString( "%.4f", ip->getController( controllerId ).getLeftTrigger() ).c_str() );
            rendererPtr->renderText( { (s32)(controllerId * 250), 45 },
                Color::White(),
                formatString( "%.4f", ip->getController( controllerId ).getRightTrigger() ).c_str() );
        }
        
        
        MousePosition mousePos = ip->getMouse().getMousePosition();

        rendererPtr->renderText( { mousePos.x, mousePos.y },
            Color::White(),
            formatString( "%d | %d", mousePos.x, mousePos.y ).c_str() );
        

        rendererPtr->endRender();
        
    };

    appPtr->uninit();

    return 0;
}