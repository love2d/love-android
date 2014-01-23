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

#include "wrap_Android.h"
#include "wrap_DisplayMetrics.h"

namespace love
{
namespace android
{

static Android *instance = nullptr;

int w_getDisplayMetrics(lua_State *L)
{
	DisplayMetrics *metrics = 0;
	EXCEPT_GUARD(metrics = instance->getDisplayMetrics();)
	luax_pushtype(L, "DisplayMetrics", ANDROID_DISPLAY_METRICS_T, metrics);
	return 1;
}

// List of functions to wrap.
static const luaL_Reg functions[] =
{
	{ "getDisplayMetrics", w_getDisplayMetrics },
	{ 0, 0 }
};

// Types for this module.
static const lua_CFunction types[] =
{
	luaopen_displaymetrics,
	0
};

extern "C" int luaopen_love_android(lua_State *L)
{
	if (instance == 0)
	{
		EXCEPT_GUARD(instance = new Android();)
	}
	else
		instance->retain();

	WrappedModule w;
	w.module = instance;
	w.name = "android";
	w.flags = MODULE_T;
	w.functions = functions;
	w.types = types;

	int n = luax_register_module(L, w);

	return n;
}

} // android
} // love
