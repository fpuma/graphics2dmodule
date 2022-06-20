#include <precompiledapplication.h>
#include <nina/application/iapplication.h>
#include <nina/application/iwindow.h>
#include <nina/application/irenderer.h>
#include <nina/input/iinput.h>
#include <utils/graphics/dimensions.h>
#include <logger/logger.h>
#include <logger/output/consolelogoutput.h>

#include <nina/input/devices/ikeyboard.h>
#include <nina/input/devices/imouse.h>
#include <nina/input/devices/icontroller.h>
#include <nina/input/iinputlistener.h>

#include <utils/formatstring.h>

using namespace puma;
using namespace puma::nina;

class MyInputListener : public IInputListener
{
public:

    MyInputListener( IInput* _input )
        :input( _input )
    {}

    void onKeyboardKey( KeyboardKey _key, InputButtonEvent _event ) const override
    {
        if (_event == InputButtonEvent::Pressed)
        {
            std::cout << "Keyboard: " << input->getInputName(_key) << " PRESSED" << std::endl;
        }
        if (_event == InputButtonEvent::Released)
        {
            std::cout << "Keyboard: " << input->getInputName( _key ) << " RELEASED" << std::endl;
        }
    }
    
    void onMouseButton( MouseButton _mouseButton, InputButtonEvent _event ) const override
    {
        if(_event == InputButtonEvent::Pressed)
        {
            std::cout << "Mouse: " << input->getInputName( _mouseButton ) << " PRESSED" << std::endl;
        }
        if(_event == InputButtonEvent::Released)
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
        //std::cout << "Mouse pos: " << _mousePosition.x << " | " << _mousePosition.y << std::endl;
    }

    void onControllerButton( ControllerId _id, ControllerButton _buttonId, InputButtonEvent _event ) const override
    {
        if (_event == InputButtonEvent::Pressed)
        {
            std::cout << "Controller" << _id <<": " << input->getInputName( _buttonId ) << " PRESSED" << std::endl;
        }
        if (_event == InputButtonEvent::Released)
        {
            std::cout << "Controller" << _id << ": " << input->getInputName( _buttonId ) << " RELEASED" << std::endl;
        }
    }

    void onControllerJoystick( ControllerId _id, ControllerJoystick _joystickId, JoystickPosition _joystickValue ) const override 
    {
        //std::cout << "Controller: " << _id << " " << (ControllerJoystick::CJ_LSTICK == _joystickId ? "LEFT" : "RIGHT") << " joystick - " << _joystickValue.x << " | " << _joystickValue.y << std::endl;
    }
    
    void onControllerTrigger( ControllerId _id, ControllerTrigger _triggerId, float _triggerValue ) const override 
    {
        //std::cout << "Controller: " << _id << " " << (ControllerTrigger::CT_LTRIGGER == _triggerId ? "LEFT" : "RIGHT") << " trigger - " << _triggerValue << std::endl;
    }

    IInput* input;
};

int main()
{
    auto appPtr = IApplication::create();
    appPtr->init();
    appPtr->getLogger()->addOutput<ConsoleLogOutput>();
    auto ip = IInput::create();

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
            const IController& controller = ip->getController( controllerId );

            rendererPtr->renderText( { (s32)(controllerId * 250), 0 },
                Color::White(),
                formatString( "%.4f | %.4f", controller.getLeftJoystickPosition().x, controller.getLeftJoystickPosition().y ).c_str() );
            rendererPtr->renderText( { (s32)(controllerId * 250), 15 },
                Color::White(),
                formatString( "%.4f | %.4f", controller.getRightJoystickPosition().x, controller.getRightJoystickPosition().y ).c_str() );
            rendererPtr->renderText( { (s32)(controllerId * 250), 30 },
                Color::White(),
                formatString( "%.4f", controller.getLeftTrigger() ).c_str() );
            rendererPtr->renderText( { (s32)(controllerId * 250), 45 },
                Color::White(),
                formatString( "%.4f", controller.getRightTrigger() ).c_str() );

        }
        
        MousePosition mousePos = ip->getMouse().getMousePosition();

        rendererPtr->renderText( { mousePos.x, mousePos.y - 15 },
            Color::White(),
            formatString( "%d | %d", mousePos.x, mousePos.y ).c_str() );
        


        rendererPtr->endRender();
        
    };

    appPtr->uninit();

    return 0;
}