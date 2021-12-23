#pragma once

namespace puma::app
{
    class IInput
    {
    public:
        
        static std::unique_ptr<IInput> create();

        virtual ~IInput() {}

        virtual void init() = 0;
        virtual void uninit() = 0;

        virtual void update() = 0;

        virtual bool getKeyState( InputId _inputId ) = 0;
        virtual bool keyPressed( InputId _inputId ) = 0;
        virtual bool keyReleased( InputId _inputId ) = 0;

        virtual MousePosition getMousePosition() = 0;

        virtual void consumeSdlEvents() = 0;
        virtual void peekSdlEvents() = 0;

    };
}