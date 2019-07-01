NDK_R17 := $(shell python $(call my-dir)/detect_ndkrel.py $(NDK_ROOT)/source.properties 17)
include $(call all-subdir-makefiles)
