#pragma once

#include <utils/graphics/dimensions.h>

namespace puma::nina
{
    class ISdlRenderer;

    class ISdlWindow : public NonCopyable
    {
    public:

        virtual ~ISdlWindow() {}

        virtual ISdlRenderer* getRenderer() = 0;
        virtual const ISdlRenderer* getRenderer() const = 0;

        virtual void setWindowSize( s32 _width, s32 _height ) = 0;
        virtual void setWindowPosition( s32 _x, s32 _y ) = 0;
        virtual void setWindowTitle( const char* _title ) =0;

        virtual Extent getExtent() const = 0;

        virtual SdlWindowId getWindowId() const = 0;

        virtual bool isValid() const = 0;
    };
}