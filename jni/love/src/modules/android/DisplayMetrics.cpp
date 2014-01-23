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

#include "DisplayMetrics.h"
#include "core/android/SDL_android.h"

namespace love
{
namespace android
{

DisplayMetrics::DisplayMetrics()
{
	JNIEnv *env = Android_JNI_GetEnv();

	jclass activity = env->FindClass("org/love2d/android/GameActivity");
	jmethodID getMetrics = env->GetStaticMethodID(activity, "getMetrics", "()Landroid/util/DisplayMetrics;");
	jobject metrics = env->CallStaticObjectMethod(activity, getMetrics);
	jclass metricsClass = env->GetObjectClass(metrics);

	// Density
	density = env->GetFloatField(metrics, env->GetFieldID(metricsClass, "density", "F"));
	scaledDensity = env->GetFloatField(metrics, env->GetFieldID(metricsClass, "scaledDensity", "F"));
	densityDpi = env->GetIntField(metrics, env->GetFieldID(metricsClass, "densityDpi", "I"));

	// Size
	widthPixels = env->GetIntField(metrics, env->GetFieldID(metricsClass, "widthPixels", "I"));
	heightPixels = env->GetIntField(metrics, env->GetFieldID(metricsClass, "heightPixels", "I"));

	// DPI
	xdpi = env->GetFloatField(metrics, env->GetFieldID(metricsClass, "xdpi", "F"));
	ydpi = env->GetFloatField(metrics, env->GetFieldID(metricsClass, "ydpi", "F"));
}

float DisplayMetrics::getDensity()
{
	return density;
}

float DisplayMetrics::getScaledDensity()
{
	return scaledDensity;
}

int DisplayMetrics::getDensityDpi()
{
	return densityDpi;
}

int DisplayMetrics::getWidthPixels()
{
	return widthPixels;
}

int DisplayMetrics::getHeightPixels()
{
	return heightPixels;
}

float DisplayMetrics::getXdpi()
{
	return xdpi;
}

float DisplayMetrics::getYdpi()
{
	return ydpi;
}

} // android
} // love
