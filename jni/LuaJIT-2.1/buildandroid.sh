#!/bin/bash
#================================================================#
# Build script based on 
#   https://github.com/moai/moai-dev/blob/master/ant/libmoai/jni/luajit/build.sh
#================================================================#

host_os=`uname -s | tr "[:upper:]" "[:lower:]"`
host_arch=`uname -m`

if [ -f android/armeabi/libluajit.a ] &&
        [ -f android/armeabi-v7a/libluajit.a ] &&
        [ -f android/x86/libluajit.a ]; then
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

NDKABI=9

# Since OSX still has bash 3, we don't have associative arrays, fake them instead
armeabi=0
armeabiv7a=1
x86=2

NDKVER[$armeabi]="$NDK/toolchains/arm-linux-androideabi-4.8"
NDKP[$armeabi]="${NDKVER[$armeabi]}/prebuilt/${host_os}-${host_arch}/bin/arm-linux-androideabi-"
NDKF[$armeabi]="--sysroot \"$NDK/platforms/android-$NDKABI/arch-arm\""
CFLAGS[$armeabi]=""

NDKVER[$armeabiv7a]="${NDKVER[$armeabi]}"
NDKP[$armeabiv7a]="${NDKP[$armeabi]}"
NDKF[$armeabiv7a]="${NDKF[$armeabi]}"
CFLAGS[$armeabiv7a]="${CFLAGS[$armeabi]}"

NDKVER[$x86]="$NDK/toolchains/x86-4.8"
NDKP[$x86]="${NDKVER[$x86]}/prebuilt/${host_os}-${host_arch}/bin/i686-linux-android-"
NDKF[$x86]="--sysroot \"$NDK/platforms/android-$NDKABI/arch-x86\""
CFLAGS[$x86]="-DLUAJIT_NO_LOG2"

buildLuaJIT()
{
    archkey="$1"
    arch="$2"
    ndkarch="$3"
    DESTDIR=../android/$arch
    mkdir -p $DESTDIR 2>/dev/null
    rm "$DESTDIR"/*.a 2>/dev/null
    make clean
    make HOST_CC="gcc -m32" CROSS="${NDKP[$archkey]}" TARGET_SYS=Linux TARGET_FLAGS="${NDKF[$archkey]} $ndkarch" TARGET_CFLAGS="${CFLAGS[$archkey]}" libluajit.a

    if [ -f libluajit.a ]; then
        mv libluajit.a $DESTDIR/libluajit.a
    fi;
}

cd src

# Android/ARM, armeabi (ARMv5TE soft-float), Android 2.2+ (Froyo)
buildLuaJIT $armeabi armeabi

# Android/ARM, armeabi-v7a (ARMv7 VFP), Android 4.0+ (ICS)
buildLuaJIT $armeabiv7a armeabi-v7a "-march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16 -Wl,--fix-cortex-a8"

# Android/x86
buildLuaJIT $x86 x86

make clean
