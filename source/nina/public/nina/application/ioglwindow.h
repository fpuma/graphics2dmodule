#pragma once

#include <utils/graphics/dimensions.h>

#include <utils/noncopyable.h>

namespace puma::nina
{
    class IOglRenderer;

    class IOglWindow : public NonCopyable
    {
    public:

        virtual ~IOglWindow() {}

        virtual IOglRenderer* getRenderer() = 0;
        virtual const IOglRenderer* getRenderer() const = 0;

        virtual void setWindowSize( s32 _width, s32 _height ) = 0;
        virtual void setWindowPosition( s32 _x, s32 _y ) = 0;
        virtual void setWindowTitle( const char* _title ) =0;

        virtual Extent getExtent() const = 0;

        virtual WindowHandle getWindowHandle() const = 0;

        virtual bool isValid() const = 0;
    };
}