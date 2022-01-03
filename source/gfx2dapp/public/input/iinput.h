#pragma once

namespace puma::app
{

    class IMouse;
    class IKeyboard;

    class IInput
    {
    public:
        
        static std::unique_ptr<IInput> create();

        virtual ~IInput() {}

        virtual void init() = 0;
        virtual void uninit() = 0;

        virtual void update() = 0;

        virtual const IMouse& getMouse() const = 0;
        virtual const IKeyboard& getKeyboard() const = 0;

        virtual void consumeSdlEvents() = 0;
        virtual void peekSdlEvents() = 0;

    };
}