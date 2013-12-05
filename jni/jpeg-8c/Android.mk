LOCAL_PATH:= $(call my-dir)

# libogg
include $(CLEAR_VARS)

LOCAL_MODULE    := libjpeg
LOCAL_CFLAGS    := -fexceptions -g -Dlinux -DAL_ALEXT_PROTOTYPES=1 -DHAVE_GCC_DESTRUCTOR=1 -DOPT_GENERIC -DREAL_IS_FLOAT
LOCAL_CPPFLAGS  := ${LOCAL_CFLAGS}

LOCAL_C_INCLUDES  :=  \
	${LOCAL_PATH}/
		
LOCAL_SRC_FILES := \
	$(filter-out \
	  example.c \
	  ansi2knr.c cjpeg.c ckconfig.c djpeg.c \
		jpegtran.c rdjpgcom.c wrjpgcom.c \
		jmemdos.c jmemmac.c \
  , $(subst $(LOCAL_PATH)/,,\
	$(wildcard ${LOCAL_PATH}/*.c) ))

# $(info libjpeg: include dirs $(LOCAL_C_INCLUDES))
# $(info libjpeg: src files $(LOCAL_SRC_FILES))

include $(BUILD_STATIC_LIBRARY)
