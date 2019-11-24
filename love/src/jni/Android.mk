LOVE_JNI_DIR := $(call my-dir)
IS_NDK_R17 := $(shell python ${LOVE_JNI_DIR}/detect_ndkrel.py $(NDK_ROOT)/source.properties 17)
IS_ANDROID_21 := $(shell python ${LOVE_JNI_DIR}/detect_androidapi.py $(TARGET_PLATFORM) 21)
HAS_LOVE := $(shell python ${LOVE_JNI_DIR}/detect_love.py ${LOVE_JNI_DIR})

ifneq (${HAS_LOVE},yes)
    $(error Missing LOVE. Make sure to initialize the submodule correctly!)
endif

include $(call all-subdir-makefiles)
