LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := lua

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_CFLAGS := -DLUA_ANSI
LOCAL_SRC_FILES := $(filter-out src/lua.c src/luac.c,$(subst $(LOCAL_PATH)/,, $(wildcard $(LOCAL_PATH)/src/*.c)))

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/src
LOCAL_LDLIBS := -lm

include $(BUILD_SHARED_LIBRARY)
