#pragma once

namespace puma::app
{

    class Mouse;
    class Keyboard;

    class IInput
    {
    public:
        
        static std::unique_ptr<IInput> create();

        virtual ~IInput() {}

        virtual void init() = 0;
        virtual void uninit() = 0;

        virtual void update() = 0;

        virtual bool keyState( MouseKey _key ) const = 0;
        virtual bool keyState( KeyboardKey _key ) const = 0;

        virtual bool keyPressed( MouseKey _key ) const = 0;
        virtual bool keyPressed( KeyboardKey _key ) const = 0;

        virtual bool keyReleased( MouseKey _key ) const = 0;
        virtual bool keyReleased( KeyboardKey _key ) const = 0;

        virtual void consumeSdlEvents() = 0;
        virtual void peekSdlEvents() = 0;

    };
}