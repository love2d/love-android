LOCAL_PATH:= $(call my-dir)

# libogg
include $(CLEAR_VARS)

LOCAL_MODULE    := libopenal
LOCAL_CFLAGS    := -fexceptions -g -Dlinux -DAL_ALEXT_PROTOTYPES=1 -DHAVE_GCC_DESTRUCTOR=1 -DOPT_GENERIC -DREAL_IS_FLOAT
LOCAL_CPPFLAGS  := ${LOCAL_CFLAGS}

LOCAL_C_INCLUDES  :=  \
	${LOCAL_PATH}/include \
	${LOCAL_PATH}/OpenAL32/Include
		
LOCAL_SRC_FILES := \
	$(filter-out , $(subst $(LOCAL_PATH)/,,\
	${LOCAL_PATH}/Alc/backends/loopback.c \
	${LOCAL_PATH}/Alc/backends/null.c \
	${LOCAL_PATH}/Alc/backends/android.c \
	${LOCAL_PATH}/Alc/backends/wave.c \
	$(wildcard ${LOCAL_PATH}/Alc/*.c) \
	$(wildcard ${LOCAL_PATH}/OpenAL32/*.c) \
	))

# $(info libopenal: include dirs $(LOCAL_C_INCLUDES))
# $(info libopenal: src files $(LOCAL_SRC_FILES))

include $(BUILD_STATIC_LIBRARY)
