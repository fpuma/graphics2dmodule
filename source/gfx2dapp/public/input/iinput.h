#pragma once

namespace puma::app::input
{
    class IInput
    {
    public:
        
        static std::unique_ptr<IInput> create();

        virtual ~IInput() {}

        virtual void init() = 0;
        virtual void uninit() = 0;

        virtual void update() = 0;

        virtual bool getKeyState( InputID _inputId ) = 0;

        virtual MousePosition getMousePosition() = 0;

        virtual void consumeSdlEvents() = 0;
        virtual void peekSdlEvents() = 0;

    };
}