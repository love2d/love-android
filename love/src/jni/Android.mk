NDK_R17 := $(shell python $(call my-dir)/detect_ndkrel.py $(NDK_ROOT)/source.properties 17)
ANDROID_21_OR_LATER := $(shell python $(call my-dir)/detect_androidapi.py $(NDK_ROOT)/source.properties 17)
include $(call all-subdir-makefiles)
