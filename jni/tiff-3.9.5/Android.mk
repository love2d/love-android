LOCAL_PATH:= $(call my-dir)

# libogg
include $(CLEAR_VARS)

LOCAL_MODULE    := libtiff
LOCAL_CFLAGS    := -fexceptions -g -Dlinux -DAL_ALEXT_PROTOTYPES=1 -DHAVE_GCC_DESTRUCTOR=1 -DOPT_GENERIC -DREAL_IS_FLOAT
LOCAL_CPPFLAGS  := ${LOCAL_CFLAGS}

LOCAL_C_INCLUDES  :=  \
	${LOCAL_PATH}/libtiff \
	${LOCAL_PATH}/../jpeg-8c
		
LOCAL_SRC_FILES := \
	$(filter-out \
	  libtiff/tif_acorn.c libtiff/tif_apple.c libtiff/tif_atari.c \
		libtiff/tif_msdos.c libtiff/tif_win3.c libtiff/tif_win32.c \
  , $(subst $(LOCAL_PATH)/,,\
	$(wildcard ${LOCAL_PATH}/libtiff/*.c) ))

$(info libtiff: include dirs $(LOCAL_C_INCLUDES))
$(info libtiff: src files $(LOCAL_SRC_FILES))

include $(BUILD_STATIC_LIBRARY)
