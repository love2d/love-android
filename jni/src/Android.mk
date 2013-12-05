LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL2-2.0.1

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	main.cpp

LOCAL_CXXFLAGS := -std=c++0x
LOCAL_SHARED_LIBRARIES := SDL2 liblua libogg libvorbis libmpg123 libmodplug libopenal libjpeg libtiff libphysfs libmng libfreetype liblcms libpng libjasper libdevil
LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog 

include $(BUILD_SHARED_LIBRARY)
