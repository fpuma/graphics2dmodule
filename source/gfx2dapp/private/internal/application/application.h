#pragma once
#include <application/iapplication.h>
#include <internal/application/renderer.h>
#include <internal/texturemanager/texturemanager.h>

namespace puma::app
{
    class Window;
    struct Extent;

    using WindowPtr = std::unique_ptr<Window>;
    using WindowMap = std::map<WindowHandle, WindowPtr>;

    class Application final : public IApplication
    {
    public:
        Application();
        ~Application();

        void init() override;
        void uninit() override;
        void update() override;
        
        WindowHandle createWindow( const Extent& _extent, const char* _windowName ) override;
        void removeWindow( WindowHandle _windowHandle ) override;

        IWindow* getWindow( WindowHandle _windowHandle );
        const IWindow* getWindow( WindowHandle _windowHandle ) const;

        bool shouldQuit() const override { return m_shouldQuit; }

        void consumeSdlEvents() override { m_peekSdlEvents = false; }
        void peekSdlEvents() override { m_peekSdlEvents = true; }

    private:

        WindowMap m_windows;
        
        bool m_shouldQuit = false;
        bool m_peekSdlEvents = false;
    };
}