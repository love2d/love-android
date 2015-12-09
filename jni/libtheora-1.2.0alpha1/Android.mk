LOCAL_PATH:= $(call my-dir)

# libtheora
include $(CLEAR_VARS)

LOCAL_MODULE    := libtheora
LOCAL_CFLAGS    := -fexceptions -g -Dlinux -DHAVE_GCC_DESTRUCTOR=1 -DOPT_GENERIC -DREAL_IS_FLOAT
LOCAL_CPPFLAGS  := ${LOCAL_CFLAGS}

LOCAL_C_INCLUDES  :=  \
	${LOCAL_PATH}/include \
	${LOCAL_PATh}/lib/arm \
	${LOCAL_PATh}/lib \
	${LOCAL_PATH}/../libogg-1.3.2/include

		
LOCAL_SRC_FILES := \
	$(filter-out \
	,$(subst $(LOCAL_PATH)/,,\
	$(wildcard ${LOCAL_PATH}/lib/*.c) \
  ))

# $(info local includes $(LOCAL_C_INCLUDES))

include $(BUILD_STATIC_LIBRARY)

