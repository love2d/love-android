rem Build instruction assume using WSL + Clang for Windows (with MSVC x86+x64 toolset for -m32 switch)
rem This assume NDK r23c or later. See https://github.com/LuaJIT/LuaJIT/issues/477 for more information.

rem Make sure LuaJIT (yes, you need LuaJIT interpreter) and the NDK toolchain binaries is already in
rem your PATH environment variable. If you're confused which part of the NDK should be added your path:
rem <NDK_ROOT>\toolchains\llvm\prebuilt\windows-x86_64\bin

mkdir android\arm64-v8a
mkdir android\armeabi-v7a
mkdir android\x86
mkdir android\x86_64

rem Reset error level
type nul

rem ARMv8
call :compile arm64-v8a aarch64-linux-android 21
if "%ERRORLEVEL%" == "1" goto :error

rem ARMv7
call :compile armeabi-v7a armv7a-linux-androideabi 16 -m32
if not "%ERRORLEVEL%" == "0" goto :error

rem x86
call :compile x86 i686-linux-android 16 -m32
if not "%ERRORLEVEL%" == "0" goto :error

rem x86_64
call :compile x86_64 x86_64-linux-android 21
if not "%ERRORLEVEL%" == "0" goto :error

goto :done

:compile
if exist android\%1\libluajit.a exit /b 0
wsl make clean
if not "%ERRORLEVEL%" == "0" goto :error
wsl make HOST_LUA=luajit.exe "HOST_CC=clang.exe %4" HOST_CFLAGS=-D_CRT_SECURE_NO_WARNINGS CC=clang CROSS=%2- "STATIC_CC=%2%3-clang -fPIC" "DYNAMIC_CC=%2%3-clang -fPIC" "TARGET_AR=llvm-ar.exe rcus" TARGET_LD=%2%3-clang CCDEBUG=-g TARGET_LDFLAGS=-fuse-ld=lld TARGET_STRIP=llvm-strip.exe amalg -j%NUMBER_OF_PROCESSORS%
if not "%ERRORLEVEL%" == "0" goto :error
copy src\libluajit.a android\%1\libluajit.a
if not "%ERRORLEVEL%" == "0" goto :error
xcopy src\jit android\%1\jit /I
del android\%1\jit\.gitignore
goto :done

:post_cleanup
del src\host\buildvm.ilk
del src\host\buildvm.pdb
exit /b 0

:error
call :post_cleanup
exit /b 1

:done
wsl make clean
call :post_cleanup
exit /b 0
