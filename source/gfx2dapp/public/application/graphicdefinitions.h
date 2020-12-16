#pragma once

namespace puma::app
{
    struct Extent
    {
        s32 width;
        s32 height;
        s32 xPos;
        s32 yPos;
    };

    struct Rect
    {
        s32 width = 0;
        s32 height = 0;
    };

    struct Color
    {
        unsigned char red = 0;
        unsigned char green = 0;
        unsigned char blue = 0;
        unsigned char alpha = 255;
    };

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

}