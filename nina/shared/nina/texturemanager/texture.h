#pragma once

#include <utils/graphics/dimensions.h>


namespace puma::nina
{
    class Texture
    {
    public:
        Texture() {}
        Texture( TextureHandle _textureHandle, Rect _originalSize )
            : m_textureHandle( _textureHandle )
            , m_originalSize( _originalSize )
        {}

        bool            isValid()           const { return m_textureHandle != nullptr; }
        TextureHandle   getHandle()         const { return m_textureHandle; }
        Rect            getOriginalSize()   const { return m_originalSize; }
        
    private:

        TextureHandle m_textureHandle = nullptr;
        Rect m_originalSize = {};
    };
}