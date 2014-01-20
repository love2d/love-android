Android Port of LÖVE, the awesome 2D game engine LÖVE (http://love2d.org)
Copyright (c) 2013 Martin Felis <martin@fysx.org>

Instructions:
-------------

Install the Android NDK and the Android SDK with SDK API 12 and run

    ndk-build

and after that

    ant debug

in the root folder of this project or load the project using Eclipse and
compile/run it using Eclipse.

This should give you a .apk file in the bin/ subdirectory that you can then
install on your phone.

Changelog:
----------

alpha7:
- love.system.getOS() now returns "Android"
- hardware search key is reported as "search"
- switched to mobile-common branch
- using new love.touch module (love.touchpressed(id,x,y,p), love.touchmoved(id,x,y,p), love.touchmoved(id,x,y,p))
- added LOVE_ANDROID define

License:
--------

This project contains code from various projects using various licenses.
Please look into the folders of jni/<projectname>/ for the respective
licenses.

As for the other code and build system files, these are published under the
zlib license (same as LÖVE).
