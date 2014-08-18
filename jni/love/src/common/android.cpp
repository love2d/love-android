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
    jclass activity = env->FindClass("org/love2d/android/GameActivity");

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

const char* getSelectedGameFile()
{
	static const char *path = NULL;

	if (!path) {
		JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
		jclass activity = env->FindClass("org/love2d/android/GameActivity");

		jmethodID getGamePath = env->GetStaticMethodID(activity, "getGamePath", "()Ljava/lang/String;");
		jstring gamePath = (jstring) env->CallStaticObjectMethod(activity, getGamePath);
		const char *utf = env->GetStringUTFChars(gamePath, 0);
		if (utf)
		{
			path = SDL_strdup(utf);
			env->ReleaseStringUTFChars(gamePath, utf);
		}

		env->DeleteLocalRef (gamePath);
		env->DeleteLocalRef (activity);
	}

	return path;
}

bool openURL(const std::string &url)
{
	JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
	jclass activity = env->FindClass("org/love2d/android/GameActivity");

	jmethodID openURL= env->GetStaticMethodID(activity, "openURL", "(Ljava/lang/String;)V");
	jstring url_jstring = (jstring) env->NewStringUTF (url.c_str());

	env->CallStaticVoidMethod (activity, openURL, url_jstring); 	

	env->DeleteLocalRef (url_jstring);
	env->DeleteLocalRef (activity);
	return true;
}

void vibrate (double seconds)
{
	JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
	jclass activity = env->FindClass("org/love2d/android/GameActivity");

	jmethodID vibrate_method = env->GetStaticMethodID(activity, "vibrate", "(D)V");
	env->CallStaticVoidMethod(activity, vibrate_method, seconds);

	env->DeleteLocalRef (activity);
}

} // android
} // love

#endif // LOVE_ANDROID
