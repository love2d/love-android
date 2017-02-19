LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libluajit
LOCAL_SRC_FILES := android/$(TARGET_ARCH_ABI)/libluajit.a

include $(PREBUILT_STATIC_LIBRARY)
