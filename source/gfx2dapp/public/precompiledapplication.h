#pragma once

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include <input/inputdefinitions.h>
#include <input/inputids.h>

#include <utils/numerictypes.h>
#include <utils/noncopyable.h>

struct SDL_Texture;
struct SDL_Renderer;

using TextureHandle = SDL_Texture*;
using WindowHandle = puma::u32;
using RendererHandle = SDL_Renderer*;
using FontHandle = puma::s32;