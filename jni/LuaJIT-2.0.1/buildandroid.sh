#!/bin/bash
#================================================================#
# Build script based on 
#   https://github.com/moai/moai-dev/blob/master/ant/libmoai/jni/luajit/build.sh
#================================================================#

host_os=`uname -s | tr "[:upper:]" "[:lower:]"`
host_arch=`uname -m`

if [ -f android/armeabi/libluajit.a ] &&
    [ -f android/armeabi-v7a/libluajit.a ]; then
    echo "LuaJIT Already built"
    exit 0
fi

NDK_BUILD_LOCATION=${ANDROID_NDK}
if [[ x$NDK_BUILD_LOCATION = "x" ]]; then
    echo "The Android NDK must be on your path."
    exit 1
fi

NDK="${NDK_BUILD_LOCATION%/ndk-build}"

if [[ x$NDK = "x" ]]; then
    echo "The Android NDK must be on your path."
    exit 1
fi

NDKABI=8
NDKVER=$NDK/toolchains/arm-linux-androideabi-4.6
NDKP=$NDKVER/prebuilt/${host_os}-${host_arch}/bin/arm-linux-androideabi-
NDKF="--sysroot $NDK/platforms/android-$NDKABI/arch-arm"
CFLAGS=""

buildLuaJIT()
{
    arch="$1"
    ndkarch="$2"
    DESTDIR=../android/$arch
    mkdir -p $DESTDIR 2>/dev/null
    rm "$DESTDIR"/*.a 2>/dev/null
    make clean
    make HOST_CC="gcc -m32" CROSS=$NDKP TARGET_SYS=Linux TARGET_FLAGS="$NDKF $ndkarch" TARGET_CFLAGS="$CFLAGS" libluajit.a

    if [ -f libluajit.a ]; then
        mv libluajit.a $DESTDIR/libluajit.a
    fi;
}

cd src

# Android/ARM, armeabi (ARMv5TE soft-float), Android 2.2+ (Froyo)
buildLuaJIT armeabi

# Android/ARM, armeabi-v7a (ARMv7 VFP), Android 4.0+ (ICS)
buildLuaJIT armeabi-v7a "-march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16 -Wl,--fix-cortex-a8"

make clean
