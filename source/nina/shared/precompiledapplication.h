#pragma once

#include <algorithm>
#include <array>
#include <assert.h>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include <utils/numerictypes.h>
#include <utils/noncopyable.h>
#include <utils/formatstring.h>

#include <nina/texturemanager/texturedefinitions.h>
#include <nina/input/inputdefinitions.h>
#include <nina/input/inputids.h>


struct SDL_Texture;
struct SDL_Renderer;
struct _TTF_Font;

namespace puma::nina
{
    using WindowHandle = u32;
    using TextureHandle = SDL_Texture*;
    using RendererHandle = SDL_Renderer*;
    using FontHandle = _TTF_Font*;

    constexpr WindowHandle kInvalidWindowHandle = 0;

    using ControllerId = u32;
}
