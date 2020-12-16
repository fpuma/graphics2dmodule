#pragma once

namespace puma::app
{
    class IWindow;
    class ITextureManager;
    struct Extent;

    class IApplication : public NonCopyable
    {
    public:
        virtual ~IApplication() {}

        static std::unique_ptr<IApplication> create();

        virtual void init() = 0;

        virtual void uninit() = 0;
        virtual void update() = 0;

        virtual WindowHandle createWindow( const Extent& _extent, const char* _windowName ) = 0;
        
        virtual IWindow* getWindow( WindowHandle _windowHandle ) = 0;
        virtual const IWindow* getWindow( WindowHandle _windowHandle ) const = 0;

        virtual bool shouldQuit() const = 0;

        virtual void consumeSdlEvents() = 0;
        virtual void peekSdlEvents() = 0;

    };
}