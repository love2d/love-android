/**
 * Copyright (c) 2006-2014 LOVE Development Team
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 **/

#ifndef LOVE_ANDROID_WRAP_DISPLAY_METRICS_H
#define LOVE_ANDROID_WRAP_DISPLAY_METRICS_H

#include "common/runtime.h"
#include "DisplayMetrics.h"

namespace love
{
namespace android
{

DisplayMetrics *luax_checkdisplaymetrics(lua_State *L, int idx);
int w_getDensity(lua_State *L);
int w_getScaledDensity(lua_State *L);
int w_getDensityDpi(lua_State *L);
int w_getWidthPixels(lua_State *L);
int w_getHeightPixels(lua_State *L);
int w_getXdpi(lua_State *L);
int w_getYdpi(lua_State *L);
extern "C" int luaopen_displaymetrics(lua_State *L);

} // android
} // love

#endif // LOVE_ANDROID_WRAP_DISPLAY_METRICS_H
