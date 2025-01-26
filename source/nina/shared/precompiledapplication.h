#pragma once

#include <utils/genericid.h>
#include <utils/numerictypes.h>
#include <utils/noncopyable.h>
#include <utils/formatstring.h>

#include <nina/texturemanager/texturedefinitions.h>
#include <nina/input/inputdefinitions.h>
#include <nina/input/inputids.h>

#include <algorithm>
#include <array>
#include <assert.h>
#include <map>
#include <memory>
#include <set>
#include <vector>

struct SDL_Texture;
struct SDL_Renderer;
struct _TTF_Font;

namespace puma::nina
{
    class SdlWindowId;
    class OglWindowId;
    using TextureHandle = SDL_Texture*;
    using RendererHandle = SDL_Renderer*;
    using FontHandle = _TTF_Font*;

    using ControllerId = u32;
}

DECLARE_GENERIC_ID(puma::nina::OglWindowId, puma::u32, 0)
DECLARE_GENERIC_ID(puma::nina::SdlWindowId, puma::u32, 0)