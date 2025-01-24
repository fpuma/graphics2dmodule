#pragma once

#include <utils/noncopyable.h>

namespace puma
{
    struct Color;
    struct Extent;
    struct ScreenPos;
}

namespace puma::nina
{
    class Texture;
    class ITextureManager;

    class IOglRenderer : public NonCopyable
    {
    public:
        virtual ~IOglRenderer() = default;

        virtual bool isValid() const = 0;
        virtual void beginRender() const = 0;
        virtual void endRender() const = 0;

        virtual void setDefaultBackgroundColor( const Color& _bgColor ) = 0;

        virtual const RendererHandle getRendererHandle() const = 0;
        virtual RendererHandle getRendererHandle() = 0;
    };
}