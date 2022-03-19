#pragma once

#include <utils/graphics/dimensions.h>

namespace puma::nina
{
    class IRenderer;

    class IWindow : public NonCopyable
    {
    public:

        virtual ~IWindow() {}

        virtual IRenderer* getRenderer() = 0;
        virtual const IRenderer* getRenderer() const = 0;

        virtual Extent getExtent() const = 0;

        virtual WindowHandle getWindowHandle() const = 0;

        virtual bool isValid() const = 0;
    };
}