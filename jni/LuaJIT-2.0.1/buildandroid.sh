NDK=${ANDROID_NDK}
NDKABI=8
NDKVER=$NDK/toolchains/arm-linux-androideabi-4.6
NDKP=$NDKVER/prebuilt/linux-x86_64/bin/arm-linux-androideabi-
NDKF="--sysroot $NDK/platforms/android-$NDKABI/arch-arm"
NDKARCH="-march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3"
# NDKARCH="-march=armv7-a"
make HOST_CC="gcc -m32" CROSS=$NDKP TARGET_FLAGS="$NDKF $NDKARCH"

# NDKVER=$NDK/toolchains/arm-linux-androideabi-4.6
# NDKP=$NDKVER/prebuilt/linux-x86_64/bin/arm-linux-androideabi-
# NDKF="--sysroot $NDK/platforms/android-$NDKABI/arch-arm"
# NDKARCH="-march=armv7-a -mfloat-abi=softfp -Wl,--fix-cortex-a8"
# make HOST_CC="gcc -m32 -fPIC" CROSS=$NDKP TARGET_FLAGS="$NDKF $NDKARCH"
