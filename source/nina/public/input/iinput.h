#pragma once

#include <input/iinputlistener.h>

namespace puma::nina
{
    class IMouse;
    class IKeyboard;
    class IController;

    class IInput
    {
    public:
        
        static std::unique_ptr<IInput> create();

        static const char* getInputName( KeyboardKey _key );
        static const char* getInputName( MouseButton _button );
        static const char* getInputName( MouseWheelState _wheel );
        static const char* getInputName( ControllerButton _button );

        virtual ~IInput() {}

        virtual void init() = 0;
        virtual void uninit() = 0;

        virtual void update() = 0;

        virtual const IMouse& getMouse() const = 0;
        virtual const IKeyboard& getKeyboard() const = 0;
        virtual const IController& getController( ControllerId _id ) const = 0;
        virtual u32 getControllerCount() const = 0;

        virtual void setInputListener( std::unique_ptr<IInputListener>&& _inputListener ) = 0;
        virtual void clearInputListener() = 0;

        virtual void consumeSdlEvents() = 0;
        virtual void peekSdlEvents() = 0;



    };
}