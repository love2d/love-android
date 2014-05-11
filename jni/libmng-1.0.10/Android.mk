LOCAL_PATH:= $(call my-dir)

# libogg
include $(CLEAR_VARS)

LOCAL_MODULE    := libmng
LOCAL_CFLAGS    := -fexceptions -g -Dlinux -Dunix \
	-DHAVE_GCC_DESTRUCTOR=1 -DOPT_GENERIC -DREAL_IS_FLOAT \

LOCAL_CPPFLAGS  := ${LOCAL_CFLAGS}

LOCAL_C_INCLUDES  :=  \
	${LOCAL_PATH}/ \
	${LOCAL_PATH}/../jpeg-8d \
		
LOCAL_SRC_FILES := \
	$(filter-out \
  , $(subst $(LOCAL_PATH)/,,\
	$(wildcard ${LOCAL_PATH}/*.c) ))

# $(info libmng: include dirs $(LOCAL_C_INCLUDES))
# $(info libmng: src files $(LOCAL_SRC_FILES))

include $(BUILD_STATIC_LIBRARY)
