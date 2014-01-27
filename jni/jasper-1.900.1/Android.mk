LOCAL_PATH:= $(call my-dir)

# libogg
include $(CLEAR_VARS)

LOCAL_MODULE    := libjasper
LOCAL_CFLAGS    := -fexceptions -g -Dlinux -Dunix \
	-DHAVE_GCC_DESTRUCTOR=1 -DOPT_GENERIC -DREAL_IS_FLOAT 

LOCAL_CPPFLAGS  := ${LOCAL_CFLAGS}

LOCAL_C_INCLUDES  :=  \
	${LOCAL_PATH}/src/libjasper/include \
	${LOCAL_PATH}/../jpeg-9a/
		
LOCAL_SRC_FILES := \
	$(filter-out \
		src/libjasper/jpg/jpg_dummy.c \
	,$(subst $(LOCAL_PATH)/,,\
	$(wildcard ${LOCAL_PATH}/src/libjasper/*.c) \
	$(wildcard ${LOCAL_PATH}/src/libjasper/jpc/*.c) \
	$(wildcard ${LOCAL_PATH}/src/libjasper/pnm/*.c) \
	$(wildcard ${LOCAL_PATH}/src/libjasper/jp2/*.c) \
	$(wildcard ${LOCAL_PATH}/src/libjasper/pgx/*.c) \
	$(wildcard ${LOCAL_PATH}/src/libjasper/bmp/*.c) \
	$(wildcard ${LOCAL_PATH}/src/libjasper/jpg/*.c) \
	$(wildcard ${LOCAL_PATH}/src/libjasper/ras/*.c) \
	$(wildcard ${LOCAL_PATH}/src/libjasper/mif/*.c) \
	$(wildcard ${LOCAL_PATH}/src/libjasper/base/*.c) ))

# $(info libjasper: include dirs $(LOCAL_C_INCLUDES))
# $(info libjasper: src files $(LOCAL_SRC_FILES))

include $(BUILD_STATIC_LIBRARY)
