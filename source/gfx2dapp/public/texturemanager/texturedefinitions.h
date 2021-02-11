#pragma once

#include <utils/genericid.h>
#include <utils/graphics/color.h>

namespace puma::app
{
    struct TextureMap
    {
        float u = 1.0f;
        float v = 1.0f;
    };

    struct TextureSample
    {
        TextureMap upperLimit{ 1.0f, 1.0f };
        TextureMap lowerLimit{ 0.0f, 0.0f };
    };

    struct TexturizedTextInfo
    {
        const char* text;
        const char* fontPath;
        Color color;
    };
}