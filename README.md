Android Port of LÖVE, an awesome 2D game engine for Lua (http://love2d.org)  
Copyright (c) 2006-2020 LOVE Development Team

![](https://github.com/love2d/love-android/workflows/build/badge.svg)

Download:
---------

You can download pre-built Android packages from https://github.com/love2d/love/releases/latest that allow
you to run .love files by opening them using a file manager of your choice.

Important:
----------

If you want to build from source, make sure to clone the submodules too. Often errors include missing
liblove.so and "Missing LÖVE" error when building. A proper way to clone this repository is:

```
git clone --recurse-submodules https://github.com/love2d/love-android
```

Add `-b <branch name>` and `--depth 1` if needed.

If you already cloned the repository but forgot to initialize the submodules, execute:

```
git submodule sync --recursive
git submodule update --init --force --recursive
```

In the repository directory. For the last command, add `--depth 1` if needed.

Instructions:
-------------

Detailed instructions can be viewed at https://github.com/love2d/love-android/wiki

Quick Start:
------------

Install the Android SDK with SDK API 30 and Android NDK 21.3.6528147, set the environment variables:

* `ANDROID_HOME` to your Android SDK location.

(you may have to adjust the paths to the install directories of the Android
SDK on your system) and run

```
$ ./gradlew assembleNormal
```

in the root folder of this project. This should give you a .apk file in the `app/build/outputs/apk/normal`
subdirectory that you can then sign and install on your phone. The `normal` .apk flavor is what you normally have
when downloading one from love2d.org.

If you want to put your game inside the APK, put your zipped \*.love in `app/src/main/assets` with name `game.love`
then change the package name, application display name, and the icons. Afterwards, run either `gradlew assembleEmbedRelease`
to generate APK which you can install or `gradlew bundleEmbedRelease` which you can upload to Play Store.

Alternatively, you can install Android Studio. After opening it for the first time, open it's SDK Manager
and on the tab "SDK Tools", select NDK. After that, open the repository root.

Notice: Previously, the embed + APKTool method is preferred, but recent announcements by Google causes that method
to obsolete.

Bugs:
-----

Bugs and/or feature requests should be reported to the issue tracker at:
* https://github.com/love2d/love-android/issues - for internal, LÖVE-Android-specific stuff
* https://github.com/love2d/love/issues - for LÖVE in general

Changelog:
----------

11.3:

* Contains all relevant changes for desktop LÖVE [11.3](https://love2d.org/wiki/11.3).
* Added support for microphone recording on Android. **This is disabled in Play Store builds**.
* Added t.audio.mic (`false` by default). On Android, setting it to true requests microphone recording permission from the user.
* Fixed performance regression on Android devices with Adreno GPU.
* Fixed video playback support on Android devices with Adreno GPU.

11.2:

* Contains all relevant changes for desktop LÖVE [11.2](https://love2d.org/wiki/11.2).
* Added support for ARM64 devices to comply with Play Store requirements.
* Fixed `love.system.openURL` crashing in some cases.
* Changed target SDK to 28 so it comply with Play Store requirements.

0.10.2:

* Contains all relevant changes for desktop LÖVE [0.10.2](https://love2d.org/wiki/0.10.2).
* Upgrade of SDL2 to 2.0.5 (fixes an issue with the accelerometer)

0.10.1:

* Contains all relevant changes for desktop LÖVE [0.10.1](https://love2d.org/wiki/0.10.1).
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

This project contains code from multiple projects using various licenses. Please look at LOVE
[license.txt](https://github.com/love2d/love/blob/master/license.txt) for the respective licenses.
