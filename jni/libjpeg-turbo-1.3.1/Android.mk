LOCAL_PATH:= $(call my-dir)

# ------------------------------------------------------------------------
# Static library (slightly adjusted from https://github.com/folecr/jpeg8d)
# ------------------------------------------------------------------------

include $(CLEAR_VARS)

LOCAL_MODULE := libturbo-jpeg

LOCAL_MODULE_FILENAME := libturbo-jpeg

LOCAL_SRC_FILES := \
	$(filter-out \
		jccolext.c \
		jdcolext.c \
		jdmrgext.c \
		turbojpeg-jni.c \
		,$(subst $(LOCAL_PATH)/,,\
		$(wildcard ${LOCAL_PATH}/*.c) \
	))

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

include $(BUILD_STATIC_LIBRARY)
