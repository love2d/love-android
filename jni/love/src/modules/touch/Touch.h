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

#ifndef LOVE_TOUCH_TOUCH_H
#define LOVE_TOUCH_TOUCH_H

// LOVE
#include "common/int.h"
#include "common/Object.h"
#include "common/Module.h"

// C++
#include <vector>
#include <limits>

namespace love
{
namespace touch
{

class Touch : public Module
{
public:

	struct TouchInfo
	{
		int64 id; // Only unique for the duration of the touch-press.
		float x; // Normalized to [0, 1].
		float y; // Normalized to [0, 1].
		float pressure; // Normalized to [0, 1].
	};

	virtual ~Touch() {}

	/**
	 * Gets the number of current touch presses.
	 **/
	virtual int getTouchCount() const = 0;

	/**
	 * Gets information about a touch press. The index is unstable and should
	 * not be relied on being the same in between calls.
	 **/
	virtual TouchInfo getTouch(int index) const = 0;

}; // Touch

} // touch
} // love

#endif // LOVE_TOUCH_TOUCH_H
