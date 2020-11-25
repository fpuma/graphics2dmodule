#pragma once
#include <graphics/igraphics.h>
#include <internal/graphics/renderer.h>
#include <internal/graphics/texturemanager.h>

#include <memory>
#include <assert.h>

namespace puma::gfx
{
    class Window;
    struct Extent;

    class Graphics final : public IGraphics
    {
    public:
        Graphics();
        ~Graphics();

        void init( const Extent& _extent, const char* _windowName ) override;
        void uninit() override;
        void update() override;
        
        const Renderer* getRenderer() const override { return m_renderer.get(); }
        Renderer* getRenderer() override { return m_renderer.get(); }

        const TextureManager* getTextureManager() const override { return m_textureManager.get(); }
        TextureManager* getTextureManager() override { return m_textureManager.get(); }

        Extent getWindowExtent() const override;
        bool shouldQuit() const override { return m_shouldQuit; }

        void consumeSdlEvents() override { m_peekSdlEvents = false; }
        void peekSdlEvents() override { m_peekSdlEvents = true; }

    private:

        std::unique_ptr<Window> m_window = nullptr;
        std::unique_ptr<Renderer> m_renderer = nullptr;
        std::unique_ptr<TextureManager> m_textureManager = nullptr;
        bool m_shouldQuit = false;

        bool m_peekSdlEvents = false;
    };
}