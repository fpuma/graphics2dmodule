#pragma once

namespace puma
{
    class Logger;
    struct Extent;
}

namespace puma::nina
{
    class ISdlRenderer;
    class ISdlWindow;

    class IApplication : public NonCopyable
    {
    public:
        virtual ~IApplication() {}

        static std::unique_ptr<IApplication> create();

        virtual void init() = 0;

        virtual void uninit() = 0;
        virtual void update() = 0;

        virtual WindowHandle createWindow( const Extent& _extent, const char* _windowName ) = 0;
        virtual void removeWindow( WindowHandle _windowHandle ) = 0;

        virtual ISdlWindow* getWindow( WindowHandle _windowHandle ) = 0;
        virtual const ISdlWindow* getWindow( WindowHandle _windowHandle ) const = 0;

        virtual bool shouldQuit() const = 0;

        virtual void consumeSdlEvents() = 0;
        virtual void peekSdlEvents() = 0;

        virtual Logger* getLogger() = 0;

    };
}