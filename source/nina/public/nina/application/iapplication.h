#pragma once

namespace puma
{
    class Logger;
    struct Extent;
}

namespace puma::nina
{
    class ISdlWindow;
    class IOglWindow;

    class IApplication : public NonCopyable
    {
    public:
        virtual ~IApplication() {}

        static std::unique_ptr<IApplication> create();

        virtual void init() = 0;

        virtual void uninit() = 0;
        virtual void update() = 0;

        virtual OglWindowId createOglWindow(const Extent& _extent, const char* _windowName) = 0;
        virtual SdlWindowId createSdlWindow( const Extent& _extent, const char* _windowName ) = 0;
        
        virtual IOglWindow* getWindow(OglWindowId _windowHandle ) = 0;
        virtual const IOglWindow* getWindow(OglWindowId _windowHandle ) const = 0;

        virtual ISdlWindow* getWindow(SdlWindowId _windowHandle) = 0;
        virtual const ISdlWindow* getWindow(SdlWindowId _windowHandle) const = 0;
        
        virtual void removeWindow(OglWindowId _windowHandle ) = 0;
        virtual void removeWindow(SdlWindowId _windowHandle) = 0;

        virtual bool shouldQuit() const = 0;

        virtual void consumeSdlEvents() = 0;
        virtual void peekSdlEvents() = 0;

        virtual Logger* getLogger() = 0;

    };
}