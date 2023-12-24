LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	audio_a2dp_hw.c

LOCAL_C_INCLUDES+= . $(LOCAL_PATH)/../utils/include
LOCAL_CFLAGS := -Wno-unused-parameter

LOCAL_CFLAGS += -std=c99

LOCAL_SHARED_LIBRARIES := \
	libcutils liblog

LOCAL_SHARED_LIBRARIES += \
	libpower

LOCAL_MODULE := audio.a2dp.default
LOCAL_MODULE_RELATIVE_PATH := hw

LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
