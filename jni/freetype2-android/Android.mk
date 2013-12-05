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
	$(wildcard ${LOCAL_PATH}/src/base/*.c) \
	${LOCAL_PATH}/src/autofit/autofit.c \
	${LOCAL_PATH}/src/cff/cff.c \
	${LOCAL_PATH}/src/pshinter/pshinter.c \
	${LOCAL_PATH}/src/psnames/psnames.c \
	${LOCAL_PATH}/src/raster/raster.c \
	${LOCAL_PATH}/src/sfnt/sfnt.c \
	${LOCAL_PATH}/src/smooth/smooth.c \
	${LOCAL_PATH}/src/truetype/truetype.c \
  ))

# $(info libfreetype: include dirs $(LOCAL_C_INCLUDES))
# $(info libfreetype: src files $(LOCAL_SRC_FILES))

include $(BUILD_STATIC_LIBRARY)
