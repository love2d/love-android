#ifndef _LJ_LOG_H
#define _LJ_LOG_H

// ==========================
// Android 平台 (logcat + printf)
// ==========================
#if defined(__ANDROID__) && !defined(LUAJIT_HOST)
#include <android/log.h>
#include <stdio.h>

#define LJ_LOG_TAG "LuaJIT"

#define LJ_LOGI(...) do { \
    __android_log_print(ANDROID_LOG_INFO,  LJ_LOG_TAG, __VA_ARGS__); \
    printf("[INFO] "); printf(__VA_ARGS__); printf("\n"); fflush(stdout); \
} while(0)

#define LJ_LOGE(...) do { \
    __android_log_print(ANDROID_LOG_ERROR, LJ_LOG_TAG, __VA_ARGS__); \
    fprintf(stderr, "[ERROR] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); fflush(stderr); \
} while(0)

#define LJ_LOGD(...) do { \
    __android_log_print(ANDROID_LOG_DEBUG, LJ_LOG_TAG, __VA_ARGS__); \
    printf("[DEBUG] "); printf(__VA_ARGS__); printf("\n"); fflush(stdout); \
} while(0)

// ==========================
// 非 Android 平台 (macOS/Linux host)
// ==========================
#else
#include <stdio.h>
#include <stdlib.h>

// 环境变量开关 DEBUG
static inline int lj_log_debug_enabled() {
    const char *env = getenv("LJ_LOG_DEBUG");
    return (env && *env == '1');
}

#define LJ_LOGI(...) do { \
    printf("[INFO] "); printf(__VA_ARGS__); printf("\n"); fflush(stdout); \
} while(0)

#define LJ_LOGE(...) do { \
    fprintf(stderr, "[ERROR] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); fflush(stderr); \
} while(0)

#define LJ_LOGD(...) do { \
    if (lj_log_debug_enabled()) { \
        printf("[DEBUG] "); printf(__VA_ARGS__); printf("\n"); fflush(stdout); \
    } \
} while(0)

#endif // __ANDROID__

#endif // _LJ_LOG_H
