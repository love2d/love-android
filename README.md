Android Port of LÖVE, the awesome 2D game engine LÖVE (http://love2d.org)
Copyright (c) 2013-2017 Martin Felis <martin@fysx.org>

Instructions:
-------------

For detailed instructions please refer to the wiki at [https://bitbucket.org/MartinFelis/love-android-sdl2/wiki/Home](https://bitbucket.org/MartinFelis/love-android-sdl2/wiki/Home).

Download:
---------

You can download pre-built Android packages from
[https://bitbucket.org/rude/love/downloads](https://bitbucket.org/rude/love/downloads)
that allow you to run .love files by opening them using a file manager of
your choice.

Quick Start:
------------

Install the Android NDK and the Android SDK with SDK API 28, set the
environment variables:

* `ANDROID_HOME` to your Android SDK location.

* `ANDROID_NDK_HOME` to your Android NDK location. NDK r16 or later; r19 also work.

    ndk.dir=/opt/android-ndk
    sdk.dir=/opt/android-sdk

(you may have to adjust the paths to the install directories of the Android
SDK and Android NDK on your system) and run

    ./gradlew assemble

in the root folder of this project. This should give you a .apk file in the
app/build/outputs/apk/ subdirectory that you can then install on your phone.

Alternatively, you can install Android Studio. After opening it for the first time,
open it's SDK Manager and on the tab "SDK Tools", select NDK. After that, open the
repository root.


Bugs:
-----

Bugs and feature requests should be reported to the issue tracker at https://bitbucket.org/MartinFelis/love-android-sdl2/issues?status=new&status=open

Changelog:
----------

11.2:

* Contains all relevant changes for desktop LÖVE 11.2.
* Added support for ARM64 devices to comply with Play Store requirements.
* Fixed `love.system.openURL` crashing in some cases.
* Changed target SDK to 28 so it comply with Play Store requirements.

0.10.2:

* Contains all relevant changes for desktop LÖVE 0.10.2.
* Upgrade of SDL2 to 2.0.5 (fixes an issue with the accelerometer)

0.10.1:

This release contains all bugfixes of the desktop 0.10.1 release. Android
specific fixes are:
* Added a new love.conf flag t.externalstorage, which determines whether files are saved in internal or external storage on Android devices.
* Fixed audio on Android to pause when the app is inactive, and resume when the app becomes active again.
* Fixed a driver bug on some Android devices which caused all objects to show up as black.
* Fixed love.graphics.clear(colortable) causing crashes on OpenGL ES 2 systems when a Canvas is active.
* New icons

0.10.0:

* first official release!
* Disabled JIT by default as it can cause performance problems. To enable JIT call jit.on()

0.10.0-alpha2:

* Update to the next love API 0.10.0 (not yet officially released)
* Added building of libtheora
* Updated LuaJIT from 2.0.1 to 2.1
* Fixed a compatibility issue with Android 2.3 devices
* Updated libogg from 1.3.2. to 1.3.5
* Updated OpenAL to 1.17.0
* Updated SDL2 to a dev version of 2.0.4

0.9.2a:

* Added bugfix for ParticleSystem:clone

0.9.2:

* updated API to match that of LÖVE 0.9.2
* love.window.setFullscreen can be used to switch between regular and immersive mode without status and navbar
* added loading of games by opening a main.lua file
* quitting LÖVE now conforms to the Android application lifecycle
* stop vibrator when app is paused
* fixed battery drain by properly pausing OpenAL device
* fixed printing of non-number and non-string values
* fixed compilation of Android NDK r10
* fixed compilation warnings concerning ```APP_PLATFORM```
* old instance is shut down when opening a new game (note: it may crash when opening games at a high frequency, e.g. more than 2 per second)
* updated OpenAL-Soft to version 1.16.0
* updated to newer SDL version (f9244b2a151)

0.9.1b:

* added love.system.vibrate(seconds)
* print statements are now redirected to logcat. Output is prefixed with "[LOVE] "
* removed DevIL, libpng, libjpeg, libmng, and libtiff
* pngs are loaded using lodepng and jpegs using libturbo-jpeg
* repeatedly fixed a bug which caused Release builds to crash
* update to latest mobile-common branch

0.9.1a:

* using latest SDL\_androidgl.c (fixes some random performance issues)
* using latest love-android @ changeset 8659be0e75a3 (adds support for
	compressed textures)

0.9.1:

* uses 0.9.1 API
* fixed crash on Moto G (and possibly other devices). This was a nasty bug that would just show a blue screen without an error message. The bug was resolved using the help of headchant
* fixed loading of jpegs (it probably hasn't worked up to now)
* fixed issues with looping over active touches. This fix was sponsored by slime!

beta2:

* fixed bug with canvases
* fixed writing of files when no identity in conf.lua was set
* added file association (somewhat experimental)

beta1:

* fixed nasty crash on startup bug
* fixed love.filesystem.getDirectoryItems()

alpha9:

* Packaged games do not get duplicated for loading, instead are loaded from memory (!!!)
* Using inofficial physfs 2.1
* Removed love.android.getDisplayMetrics(), instead use love.window.getPixelScale() 
* Properly link LGPL libraries dynamically. Everything else is linked statically
* Added an icon (design by @josefnpat)
* Fixed crash on startup on OUYA (and possibly other devices)

alpha8:

* Exposing DisplayMetrics in love.android.getDisplayMetrics())
* Accelerometer is now available as a joystick
* enabled armv6 compilation (larger files, better compatibility with Tegra2 devices)
* updated to latest mobile-common branch (including (very) basic multi-touch gesture tracking)
* updated OpenAL from 1.13 to 1.15.1
* updated jpeg library from 8c to 9a
* updated lcms from 2.2 to 2.5
* updated libogg from 1.3.0 to 1.3.1
* updated libvorbis from 1.3.2 to 1.3.4
* updated mpg123 from 1.13.4 to 1.17.0

alpha7:

* love.system.getOS() now returns "Android"
* hardware search key is reported as "search"
* switched to mobile-common branch
* using new love.touch module (love.touchpressed(id,x,y,p), love.touchmoved(id,x,y,p), love.touchmoved(id,x,y,p))
* added LOVE_ANDROID define

License:
--------

This project contains code from multiple projects using various licenses.
Please look into the folders of love/src/jni/<projectname>/ for the respective
licenses. A possibly incomplete overview of dependent and included
libraries and licenses is the following:

* FreeType2 (FreeType Project License)
* libjpeg-turbo (custom license)
* libmodplug (public domain)
* libogg (BSD License)
* libvorbis (BSD License)
* LuaJIT (MIT License)
* mpg123 (LGPL 2.1 License)
* openal-soft (LGPL 2 License)
* physfs (zlib License)
* SDL2 (zlib License)

This project also includes LÖVE, which itself is licensed under the zlib
license but includes the following libraries that are subject to other
licenses:

* modified Box2D (original Box2D license is zlib)
* ddsparse (MIT License)
* enet (MIT License)
* glad (MIT License)
* lodepng (zlib License)
* luasocket (MIT License)
* SimplexNoise1234 (public domain)
* stb_image (public domain)
* utf8 (Boost License)
* wuff (public domain)

As for the other code, modifications to LÖVE, and build system files are
are published under the zlib license (same as LÖVE).
