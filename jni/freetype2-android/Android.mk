LOCAL_PATH:= $(call my-dir)

# libogg
include $(CLEAR_VARS)

LOCAL_MODULE    := libfreetype
LOCAL_CFLAGS    := -fexceptions -g -Dlinux -Dunix -DFT2_BUILD_LIBRARY=1 \
	-DHAVE_GCC_DESTRUCTOR=1 -DOPT_GENERIC -DREAL_IS_FLOAT 

LOCAL_CPPFLAGS  := ${LOCAL_CFLAGS}

LOCAL_C_INCLUDES  :=  \
	${LOCAL_PATH}/include \
	${LOCAL_PATH}/src
		
LOCAL_SRC_FILES := \
	$(filter-out \
	,$(subst $(LOCAL_PATH)/,,\
	${LOCAL_PATH}/src/autofit/autofit.c \
	$(wildcard ${LOCAL_PATH}/src/base/*.c) \
	$(wildcard ${LOCAL_PATH}/src/pshinter/*.c) \
	$(wildcard ${LOCAL_PATH}/src/psnames/*.c) \
	$(wildcard ${LOCAL_PATH}/src/raster/*.c) \
	$(wildcard ${LOCAL_PATH}/src/sfnt/*.c) \
	$(wildcard ${LOCAL_PATH}/src/smooth/*.c) \
	$(wildcard ${LOCAL_PATH}/src/truetype/*.c) ))

$(info libfreetype: include dirs $(LOCAL_C_INCLUDES))
$(info libfreetype: src files $(LOCAL_SRC_FILES))

include $(BUILD_STATIC_LIBRARY)
