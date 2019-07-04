LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libtheora
LOCAL_CFLAGS := -g -Wno-parentheses

LOCAL_C_INCLUDES := \
	${LOCAL_PATH}/include \
	${LOCAL_PATh}/lib \
	${LOCAL_PATH}/../libogg-1.3.2/include
LOCAL_EXPORT_C_INCLUDES := ${LOCAL_PATH}/include
LOCAL_SRC_FILES := \
	lib/apiwrapper.c \
	lib/bitpack.c \
	lib/decapiwrapper.c \
	lib/decinfo.c \
	lib/decode.c \
	lib/dequant.c \
	lib/fragment.c \
	lib/huffdec.c \
	lib/idct.c \
	lib/info.c \
	lib/internal.c \
	lib/quant.c \
	lib/state.c \
	lib/encoder_disabled.c

LOCAL_ARM_NEON := true

# Target conditionals
# It seems unfortunate that ARM codepath can't be used in here.
ifeq ($(TARGET_ARCH_ABI),x86)
	# Defines for x86. UNTESTED!
	LOCAL_CFLAGS += -DOC_X86_ASM
	LOCAL_SRC_FILES += \
		lib/x86/x86cpu.c \
		lib/x86/mmxidct.c \
		lib/x86/mmxfrag.c \
		lib/x86/mmxstate.c \
		lib/x86/sse2idct.c \
		lib/x86/x86state.c
else ifeq ($(TARGET_ARCH_ABI),x86_64)
	# Defines for x86-64. UNTESTED!
	LOCAL_CFLAGS += -DOC_X86_ASM -DOC_X86_64_ASM
	LOCAL_SRC_FILES += \
		lib/x86/x86cpu.c \
		lib/x86/mmxidct.c \
		lib/x86/mmxfrag.c \
		lib/x86/mmxstate.c \
		lib/x86/sse2idct.c \
		lib/x86/x86state.c
endif

LOCAL_STATIC_LIBRARIES := libogg

include $(BUILD_STATIC_LIBRARY)
