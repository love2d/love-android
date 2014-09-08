LOCAL_PATH:= $(call my-dir)

# libogg
include $(CLEAR_VARS)

LOCAL_MODULE    := libopenal
LOCAL_CFLAGS    := -DAL_ALEXT_PROTOTYPES -DAL_BUILD_LIBRARY -D_GNU_SOURCE=1 -D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE=700 -std=c99 -Drestrict=__restrict

LOCAL_CPPFLAGS  := ${LOCAL_CFLAGS}

LOCAL_C_INCLUDES  :=  \
	${LOCAL_PATH}/include \
	${LOCAL_PATH}/Alc \
	${LOCAL_PATH}/OpenAL32/Include
		
LOCAL_SRC_FILES := \
	$(filter-out \
	 Alc/mixer_neon.c \
	 Alc/mixer_inc.c \
	 Alc/mixer_sse.c \
	 Alc/mixer_sse2.c \
	 Alc/mixer_sse41.c \
	, $(subst $(LOCAL_PATH)/,,\
		${LOCAL_PATH}/Alc/backends/base.c \
		${LOCAL_PATH}/Alc/backends/loopback.c \
		${LOCAL_PATH}/Alc/backends/null.c \
		${LOCAL_PATH}/Alc/backends/opensl.c \
		${LOCAL_PATH}/Alc/backends/wave.c \
		$(wildcard ${LOCAL_PATH}/common/*.c) \
		$(wildcard ${LOCAL_PATH}/Alc/midi/*.c) \
		$(wildcard ${LOCAL_PATH}/Alc/effects/*.c) \
		$(wildcard ${LOCAL_PATH}/Alc/*.c) \
		$(wildcard ${LOCAL_PATH}/OpenAL32/*.c) \
	))

LOCAL_LDLIBS := -lOpenSLES

include $(BUILD_SHARED_LIBRARY)
