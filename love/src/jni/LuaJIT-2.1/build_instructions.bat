rem Build instruction assume using WSL + Clang for Windows (with MSVC x86+x64 toolset for -m32 switch)
rem This assume NDK r19 or later. See https://github.com/LuaJIT/LuaJIT/issues/477 for more information.

rem Make sure LuaJIT and the prebuilt is already in your PATH environment variable.
rem As of commit 384d6d5 in LuaJIT v2.1 repository, lj_ircall.h.patch is no longer needed.

rem If you're confused which one should be added your path:
rem <NDK_ROOT>\toolchains\llvm\prebuilt\windows-x86_64\bin

mkdir android\arm64-v8a
mkdir android\armeabi-v7a
mkdir android\x86
mkdir android\x86_64

rem Reset error level
type nul

rem ARMv8
if not exist android\arm64-v8a\libluajit.a (
	wsl make clean
	if "%ERRORLEVEL%" == "1" goto :error
	wsl make HOST_LUA=luajit.exe HOST_CC=clang.exe HOST_CFLAGS=-D_CRT_SECURE_NO_WARNINGS CC=clang CROSS=aarch64-linux-android- STATIC_CC=aarch64-linux-android21-clang "DYNAMIC_CC=aarch64-linux-android21-clang -fPIC" "TARGET_AR=aarch64-linux-android-ar.exe rcus" TARGET_LD=aarch64-linux-android21-clang TARGET_STRIP=aarch64-linux-android-strip.exe amalg -j4
	if "%ERRORLEVEL%" == "1" goto :error
	copy src\libluajit.a android\arm64-v8a\libluajit.a
	if "%ERRORLEVEL%" == "1" goto :error
)

rem ARMv7
if not exist android\armeabi-v7a\libluajit.a (
	wsl make clean
	if "%ERRORLEVEL%" == "1" goto :error
	wsl make HOST_LUA=luajit.exe "HOST_CC=clang.exe -m32" HOST_CFLAGS=-D_CRT_SECURE_NO_WARNINGS CC=clang CROSS=arm-linux-android- STATIC_CC=armv7a-linux-androideabi16-clang "DYNAMIC_CC=armv7a-linux-androideabi16-clang -fPIC" "TARGET_AR=arm-linux-androideabi-ar.exe rcus" TARGET_LD=armv7a-linux-androideabi16-clang TARGET_STRIP=arm-linux-androideabi-strip.exe amalg -j4
	if "%ERRORLEVEL%" == "1" goto :error
	copy src\libluajit.a android\armeabi-v7a\libluajit.a
	if "%ERRORLEVEL%" == "1" goto :error
)

rem x86
if not exist android\x86\libluajit.a (
	wsl make clean
	if "%ERRORLEVEL%" == "1" goto :error
	wsl make HOST_LUA=luajit.exe "HOST_CC=clang.exe -m32" HOST_CFLAGS=-D_CRT_SECURE_NO_WARNINGS CC=clang CROSS=i686-linux-android- STATIC_CC=i686-linux-android16-clang "DYNAMIC_CC=i686-linux-android16-clang -fPIC" "TARGET_AR=i686-linux-android-ar.exe rcus" TARGET_LD=i686-linux-android16-clang TARGET_STRIP=i686-linux-android-strip.exe amalg -j4
	if "%ERRORLEVEL%" == "1" goto :error
	copy src\libluajit.a android\x86\libluajit.a
	if "%ERRORLEVEL%" == "1" goto :error
)

rem x86_64
if not exist android\x86_64\libluajit.a (
	wsl make clean
	if "%ERRORLEVEL%" == "1" goto :error
	wsl make HOST_LUA=luajit.exe HOST_CC=clang.exe HOST_CFLAGS=-D_CRT_SECURE_NO_WARNINGS CC=clang CROSS=x86_64-linux-android- STATIC_CC=x86_64-linux-android21-clang "DYNAMIC_CC=x86_64-linux-android21-clang -fPIC" "TARGET_AR=x86_64-linux-android-ar.exe rcus" TARGET_LD=x86_64-linux-android21-clang TARGET_STRIP=x86_64-linux-android-strip.exe amalg -j4
	if "%ERRORLEVEL%" == "1" goto :error
	copy src\libluajit.a android\x86_64\libluajit.a
	if "%ERRORLEVEL%" == "1" goto :error
)

goto :done

:error
exit /b 1

:done
wsl make clean
exit /b 0
