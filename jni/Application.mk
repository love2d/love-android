# Uncomment this if you're using STL in your project
# See CPLUSPLUS-SUPPORT.html in the NDK documentation for more information
# APP_STL := stlport_static 
APP_STL := gnustl_shared
APP_ABI := armeabi armeabi-v7a
APP_CPPFLAGS := -frtti
APP_LDFLAGS := -llog -landroid -lz
APP_PLATFORM := 10
NDK_TOOLCHAIN_VERSION := 4.8

# APP_OPTIM := debug
