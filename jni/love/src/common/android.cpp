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

#include "android.h"

#ifdef LOVE_ANDROID

#include "SDL.h"
#include "jni.h"

namespace love
{
namespace android
{

double getScreenScale()
{
  static double result = -1.;

  if (result == -1.) {
    JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
    jclass activity = env->FindClass("org/libsdl/app/SDLActivity");

    jmethodID getMetrics = env->GetStaticMethodID(activity, "getMetrics", "()Landroid/util/DisplayMetrics;");
    jobject metrics = env->CallStaticObjectMethod(activity, getMetrics);
    jclass metricsClass = env->GetObjectClass(metrics);

    result = env->GetFloatField(metrics, env->GetFieldID(metricsClass, "density", "F"));

    env->DeleteLocalRef (metricsClass);
    env->DeleteLocalRef (metrics);
    env->DeleteLocalRef (activity);
  }

  return result;
}

} // android
} // love

#endif // LOVE_ANDROID
