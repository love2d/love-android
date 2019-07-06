LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libopenal
# Filled later. The config.h is based on very minimal config of ARM32
LOCAL_CFLAGS := -std=c99 -DAL_ALEXT_PROTOTYPES
# Is there any devices without NEON support in 2019?
LOCAL_ARM_NEON := true

# Target conditionals
ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
	# Defines for ARM32
	LOCAL_CFLAGS += \
		-DHAVE_NEON \
		-DSIZEOF_LONG=4
else ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
	# Defines for ARM64
	LOCAL_CFLAGS += \
		-DHAVE_POSIX_MEMALIGN \
		-DHAVE_NEON \
		-DHAVE_LOG2F \
		-DHAVE_STRTOF \
		-DSIZEOF_LONG=8 \
		-DHAVE_PTHREAD_MUTEX_TIMEDLOCK
else ifeq ($(TARGET_ARCH_ABI),x86)
	# Defines for x86. UNTESTED!
	LOCAL_CFLAGS += \
		-DHAVE_SSE \
		-DHAVE_SSE2 \
		-DHAVE_SSE3 \
		-DSIZEOF_LONG=4 \
		-DHAVE_CPUID_H \
		-DHAVE_GCC_GET_CPUID \
else ifeq ($(TARGET_ARCH_ABI),x86_64)
	# Defines for x86-64. UNTESTED!
	LOCAL_CFLAGS += \
		-DHAVE_POSIX_MEMALIGN \
		-DHAVE_SSE \
		-DHAVE_SSE2 \
		-DHAVE_SSE3 \
		-DHAVE_SSE4_1 \
		-DHAVE_LOG2F \
		-DHAVE_STRTOF \
		-DSIZEOF_LONG=8 \
		-DHAVE_CPUID_H \
		-DHAVE_GCC_GET_CPUID \
		-DHAVE_PTHREAD_MUTEX_TIMEDLOCK
endif

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/include \
	$(LOCAL_PATH)/common \
	$(LOCAL_PATH)/Alc \
	$(LOCAL_PATH)/OpenAL32/Include
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_SRC_FILES := \
	common/alcomplex.c \
	common/almalloc.c \
	common/atomic.c \
	common/rwlock.c \
	common/threads.c \
	common/uintmap.c \
	OpenAL32/alAuxEffectSlot.c \
	OpenAL32/alBuffer.c \
	OpenAL32/alEffect.c \
	OpenAL32/alError.c \
	OpenAL32/alExtension.c \
	OpenAL32/alFilter.c \
	OpenAL32/alListener.c \
	OpenAL32/alSource.c \
	OpenAL32/alState.c \
	OpenAL32/event.c \
	OpenAL32/sample_cvt.c \
	Alc/ALc.c \
	Alc/ALu.c \
	Alc/alconfig.c \
	Alc/bs2b.c \
	Alc/converter.c \
	Alc/mastering.c \
	Alc/ringbuffer.c \
	Alc/effects/autowah.c \
	Alc/effects/chorus.c \
	Alc/effects/compressor.c \
	Alc/effects/dedicated.c \
	Alc/effects/distortion.c \
	Alc/effects/echo.c \
	Alc/effects/equalizer.c \
	Alc/effects/fshifter.c \
	Alc/effects/modulator.c \
	Alc/effects/null.c \
	Alc/effects/pshifter.c \
	Alc/effects/reverb.c \
	Alc/filters/filter.c \
	Alc/filters/nfc.c \
	Alc/filters/splitter.c \
	Alc/helpers.c \
	Alc/hrtf.c \
	Alc/uhjfilter.c \
	Alc/ambdec.c \
	Alc/bformatdec.c \
	Alc/panning.c \
	Alc/mixvoice.c \
	Alc/mixer/mixer_c.c \
	Alc/backends/base.c \
	Alc/backends/loopback.c \
	Alc/backends/null.c \
	Alc/backends/opensl.c \
	Alc/backends/wave.c

LOCAL_LDLIBS := -lOpenSLES -llog
LOCAL_STATIC_LIBRARIES :=

# CPU-specific instructions
ifneq (,$(findstring HAVE_SSE4_1,${LOCAL_CFLAGS}))
	# SSE4.1 mixer
	LOCAL_SRC_FILES += \
		Alc/mixer/mixer_sse.c \
		Alc/mixer/mixer_sse2.c \
		Alc/mixer/mixer_sse3.c \
		Alc/mixer/mixer_sse41.c
else ifneq (,$(findstring HAVE_SSE3,${LOCAL_CFLAGS}))
	# SSE3 mixer
	LOCAL_SRC_FILES += \
		Alc/mixer/mixer_sse.c \
		Alc/mixer/mixer_sse2.c \
		Alc/mixer/mixer_sse3.c
else ifneq (,$(findstring HAVE_NEON,${LOCAL_CFLAGS}))
	# NEON mixer
	LOCAL_SRC_FILES += Alc/mixer/mixer_neon.c
endif

# NDK R17 Support library
ifeq ($(IS_NDK_R17),yes)
	# Well, NDK r17 (is it?) defines all function regardless of API level
	ifeq (,$(findstring HAVE_LOG2F,${LOCAL_CFLAGS}))
		LOCAL_CFLAGS += -DHAVE_LOG2F
	endif
	# Also only link with android_support for older than 21
	ifeq ($(IS_ANDROID_21),no)
		LOCAL_STATIC_LIBRARIES += android_support
	endif
endif

include $(BUILD_SHARED_LIBRARY)
