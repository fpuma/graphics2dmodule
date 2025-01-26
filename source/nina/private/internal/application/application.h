#pragma once
#include <nina/application/iapplication.h>
#include <internal/application/sdl/sdlrenderer.h>
#include <internal/texturemanager/texturemanager.h>
#include <internal/applogger/applogger.h>

namespace puma::nina
{
    class SdlWindow;
    class OglWindow;

    class Application final : public IApplication
    {
    public:

        void init() override;
        void uninit() override;
        void update() override;
        
        OglWindowId createOglWindow(const Extent& _extent, const char* _windowName) override;
        SdlWindowId createSdlWindow( const Extent& _extent, const char* _windowName ) override;
        
        IOglWindow* getWindow(OglWindowId _windowId) override;
        const IOglWindow* getWindow(OglWindowId _windowId) const override;

        ISdlWindow* getWindow(SdlWindowId _windowId) override;
        const ISdlWindow* getWindow(SdlWindowId _windowId) const override;

        void removeWindow(OglWindowId _windowId) override;
        void removeWindow(SdlWindowId _windowId) override;

        bool shouldQuit() const override { return m_shouldQuit; }

        void consumeSdlEvents() override { m_peekSdlEvents = false; }
        void peekSdlEvents() override { m_peekSdlEvents = true; }

        Logger* getLogger() override { return m_appLogger.getLogger(); }

    private:

        std::unordered_map<SdlWindowId, std::unique_ptr<SdlWindow>>  m_sdlWindows;
        std::unordered_map<OglWindowId, std::unique_ptr<OglWindow>>  m_oglWindows;
        
        bool m_shouldQuit = false;
        bool m_peekSdlEvents = false;

        AppLogger m_appLogger;
    };
}