LOCAL_PATH:= $(call my-dir)

# libogg
include $(CLEAR_VARS)

LOCAL_MODULE    := libphysfs
LOCAL_CFLAGS    := -fexceptions -g -Dlinux -Dunix \
	-DPHYSFS_NO_CDROM_SUPPORT=1 -DAL_ALEXT_PROTOTYPES=1 \
	-DHAVE_GCC_DESTRUCTOR=1 -DOPT_GENERIC -DREAL_IS_FLOAT \
	-DPHYSFS_SUPPORTS_APK=1 -DPHYSFS_SUPPORTS_ZIP=1 \
	-DPHYSFS_SUPPORTS_ZIP=1 -DPHYSFS_SUPPORTS_7Z=1 \
	-DPHYSFS_SUPPORTS_GRP=1 -DPHYSFS_SUPPORTS_QPAK=1 \
	-DPHYSFS_SUPPORTS_HOG=1 -DPHYSFS_SUPPORTS_MVL=1 \
	-DPHYSFS_SUPPORTS_WAD=1

LOCAL_CPPFLAGS  := ${LOCAL_CFLAGS}

LOCAL_C_INCLUDES  :=  \
	${LOCAL_PATH}
		
LOCAL_SRC_FILES := \
	$(filter-out \
  , $(subst $(LOCAL_PATH)/,,\
	$(wildcard ${LOCAL_PATH}/*.c) \
	$(wildcard ${LOCAL_PATH}/lzma/*.c) \
	$(wildcard ${LOCAL_PATH}/zlib123/*.c) \
	$(wildcard ${LOCAL_PATH}/archivers/*.c) \
	$(wildcard ${LOCAL_PATH}/platform/*.c) ))

$(info libphysfs: include dirs $(LOCAL_C_INCLUDES))
$(info libphysfs: src files $(LOCAL_SRC_FILES))

include $(BUILD_STATIC_LIBRARY)
