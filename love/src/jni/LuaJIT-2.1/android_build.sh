#!/usr/bin/env bash
# LuaJIT Android Build Script (macOS version)

set -e
set -o pipefail
set -x # <--- 在这里添加这一行

# --- 基础配置 ---
export ANDROID_NDK_HOME=/Users/hjr/Library/Android/sdk/ndk/29.0.13599879
export TARGET_API_LEVEL=21

# 工具链目录
TOOLCHAIN=$ANDROID_NDK_HOME/toolchains/llvm/prebuilt/darwin-x86_64/bin
export PATH=$TOOLCHAIN:$PATH

# --- 自动检测 macOS 主版本号，设置 MACOSX_DEPLOYMENT_TARGET ---
if [[ "$OSTYPE" == "darwin"* ]]; then
  MACOS_VER=$(sw_vers -productVersion | cut -d. -f1)
  export MACOSX_DEPLOYMENT_TARGET="${MACOS_VER}.0"
  echo "Using MACOSX_DEPLOYMENT_TARGET=$MACOSX_DEPLOYMENT_TARGET"
fi

# macOS SDK 路径
SDK_PATH=$(xcrun --show-sdk-path)

# 输出目录
OUTDIR=android
mkdir -p "$OUTDIR/arm64-v8a" "$OUTDIR/armeabi-v7a" "$OUTDIR/x86" "$OUTDIR/x86_64"

# 检测 host luajit
if command -v luajit >/dev/null 2>&1; then
    HOST_LUA=$(command -v luajit)
else
    echo "Error: luajit not found. Try: brew install luajit"
    exit 1
fi

echo "Using host luajit: $HOST_LUA"

# 并发数
CPU_COUNT=$(getconf _NPROCESSORS_ONLN)

# --- 根据平台选择正确的 llvm-ar 参数 ---
if [[ "$OSTYPE" == "darwin"* ]]; then
  TARGET_AR="llvm-ar rcs"
else
  TARGET_AR="llvm-ar rcus"
fi

# 编译函数
build_luajit() {
    ABI=$1
    TRIPLE=$2
    API=$3
    TARGET_ARCH_NAME=$4
    EXTRA_CFLAGS=$5
    EXTRA_LDFLAGS=$6

    echo "--------------------------------------------"
    echo "Building LuaJIT for $ABI ($TRIPLE, API $API)"
    echo "--------------------------------------------"

    DESTDIR="$OUTDIR/$ABI"
    mkdir -p "$DESTDIR"

    make clean || true
    make \
        HOST_LUA="$HOST_LUA" \
        "HOST_CC=clang -DLUAJIT_HOST -isysroot $SDK_PATH" \
        HOST_CFLAGS=-D_CRT_SECURE_NO_WARNINGS \
        "BUILDVM_FLAGS=-a $TARGET_ARCH_NAME" \
        CC=clang \
        CROSS="${TRIPLE}-" \
        "STATIC_CC=${TRIPLE}${API}-clang -fPIC $EXTRA_CFLAGS" \
        "DYNAMIC_CC=${TRIPLE}${API}-clang -fPIC $EXTRA_CFLAGS" \
        "TARGET_AR=$TARGET_AR" \
        TARGET_SYS=Linux \
        TARGET_LD=${TRIPLE}${API}-clang \
        "TARGET_LDFLAGS=-fuse-ld=lld $EXTRA_LDFLAGS" \
        "TARGET_SHLDFLAGS=$EXTRA_LDFLAGS" \
        TARGET_STRIP=llvm-strip \
        TARGET_SONAME=libluajit.so \
        CCDEBUG=-g \
        amalg -j$CPU_COUNT

    cp src/libluajit.a "$DESTDIR/libluajit.a" || true
    cp src/libluajit.so "$DESTDIR/libluajit.so" || true
    cp src/luajit.h "$DESTDIR/libluajit.h" || true
    mkdir -p "$DESTDIR/jit"
    cp -r src/jit/* "$DESTDIR/jit/" || true
    rm -f "$DESTDIR/jit/.gitignore"

    make clean
}

# 四个 ABI
build_luajit arm64-v8a aarch64-linux-android $TARGET_API_LEVEL arm64 "" "-Wl,-z,max-page-size=16384 -llog"
# build_luajit armeabi-v7a armv7a-linux-androideabi $TARGET_API_LEVEL arm -m32 "-llog"
# build_luajit x86 i686-linux-android $TARGET_API_LEVEL x86 -m32 "-llog"
# build_luajit x86_64 x86_64-linux-android $TARGET_API_LEVEL x64 "" "-Wl,-z,max-page-size=16384 -llog"

echo "✅ All builds done! Output in $OUTDIR/"
