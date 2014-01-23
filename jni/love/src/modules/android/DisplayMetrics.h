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

#ifndef LOVE_ANDROID_DISPLAY_METRICS_H
#define LOVE_ANDROID_DISPLAY_METRICS_H

// LOVE
#include "common/Object.h"

namespace love
{
namespace android
{

/**
 * A DisplayMetrics describe a general information about a display, such as its size, density, and font scaling.
 **/
class DisplayMetrics : public Object
{
public:

	/**
	 * Constructor.
	 **/
	DisplayMetrics();

	/**
	 * Destructor.
	 **/
	virtual ~DisplayMetrics() {}

	/**
	 * The logical density of the display.
	 **/
	float getDensity();

	/**
	 * A scaling factor for fonts displayed on the display.
	 **/
	float getScaledDensity();

	/**
	 * The screen density expressed as dots-per-inch.
	 **/
	int getDensityDpi();

	/**
	 * The absolute width of the display in pixels.
	 **/
	int getWidthPixels();

	/**
	 * The absolute height of the display in pixels.
	 **/
	int getHeightPixels();

	/**
	 * The exact physical pixels per inch of the screen in the X dimension.
	 **/
	float getXdpi();

	/**
	 * The exact physical pixels per inch of the screen in the X dimension.
	 **/
	float getYdpi();

private:
	float density;
	float scaledDensity;
	int densityDpi;
	int widthPixels;
	int heightPixels;
	float xdpi;
	float ydpi;

}; // DisplayMetrics

} // android
} // love

#endif // LOVE_ANDROID_DISPLAY_METRICS_H
