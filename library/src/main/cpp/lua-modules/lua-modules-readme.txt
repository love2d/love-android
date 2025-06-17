This folder should contain external Lua C modules that will be shipped along with LOVE. One for each folder

Each folder must contains:
* Either CMakeLists.txt or Android.mk.
  * If Android.mk is present:
    The Android.mk will be converted to CMakeLists.txt. This conversion may not 100% perfect!
    The LOCAL_MODULE_FILENAME must be set accordingly as ndk-build appends "lib" prefix from LOCAL_MODULE by default.
    For Lua includes and libraries, simply link the native library with "liblove".
    Note: This will convert Android.mk to CMakeLists.txt. The conversion may not 100% perfect. Conditionals are not
          parsed and treated as if all codepaths are taken. Modify the generated CMakeLists.txt if necessary!
    Caveat: If the library is meant to be loaded as require("my.library") then you MUST set LOCAL_MODULE_FILENAME to
            my.library (with dots).
  * If CMakeLists.txt is present:
    The CMake script is loaded directly. 
    For Lua includes and libraries, link with "luajit" target.
    Caveat: If the library is meant to be loaded as require("my.library") then you MUST set OUTPUT_NAME property to
            "my.library" (with dots) and PREFIX property to "" (empty string) on your CMake target using
            "set_target_properties".
* If your module interacts with Java-side, a file java.txt must contain where it should look Java source files.
  Example, if you have src/java/your/package/name/MyFile.java, then you need to write "src/java" in java.txt.
  If this file is absent, then your Java-side code will not be compiled along.

Note: There's bug in Android CMake support which prevents inclusion of imported *.so.
      More information about it here: https://issuetracker.google.com/issues/274493986
      In short:
      * If your library is simply an imported target (or prebuilt in ndk-build terms), convert it to standard target.
        Otherwise the associated *.so won't be bundled into the APK!
      * If your library depends on imported/prebuilt target, you must add your CMake target to the `app/build.gradle`
        as part of the targets that need to be compiled. Add your CMake target at
        `android.defaultConfig.externalNativeBuild.cmake.targets` property.
