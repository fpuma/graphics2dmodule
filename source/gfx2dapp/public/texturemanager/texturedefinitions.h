#pragma once

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
}