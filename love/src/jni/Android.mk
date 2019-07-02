IS_NDK_R17 := $(shell python $(call my-dir)/detect_ndkrel.py $(NDK_ROOT)/source.properties 17)
IS_ANDROID_21 := $(shell python $(call my-dir)/detect_androidapi.py $(TARGET_PLATFORM) 21)
include $(call all-subdir-makefiles)
