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

// LOVE
#include "common/config.h"
#include "common/Exception.h"
#include "Touch.h"

// SDL
#include <SDL_touch.h>

namespace love
{
namespace touch
{
namespace sdl
{

int Touch::getTouchCount() const
{
	int count = 0;

	for (int i = 0; i < SDL_GetNumTouchDevices(); i++)
		count += SDL_GetNumTouchFingers(SDL_GetTouchDevice(i));

	return count;
}

Touch::TouchInfo Touch::getTouch(int index) const
{
	SDL_TouchID deviceID = 0;

	int touchcount = 0;
	int fingerindex = -1;

	// Find the device and finger index from the given external index.
	for (int i = 0; i < SDL_GetNumTouchDevices(); i++)
	{
		deviceID = SDL_GetTouchDevice(i);
		int fingercount = SDL_GetNumTouchFingers(deviceID);

		if (index < touchcount + fingercount)
		{
			fingerindex = index - touchcount;
			break;
		}

		touchcount += fingercount;
	}

	if (fingerindex < 0)
		throw love::Exception("Invalid touch index.");

	SDL_Finger *finger = SDL_GetTouchFinger(deviceID, fingerindex);

	if (finger == nullptr)
		throw love::Exception("Cannot get touch info.");

	TouchInfo info = {};

	info.id = (int64) finger->id;
	info.x = finger->x;
	info.y = finger->y;
	info.pressure = finger->pressure;

	return info;
}

const char *Touch::getName() const
{
	return "love.touch.sdl";
}

} // sdl
} // touch
} // love
