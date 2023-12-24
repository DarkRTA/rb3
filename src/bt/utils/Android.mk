LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES:= $(LOCAL_PATH)/include \
                   $(LOCAL_PATH)/../gki/ulinux \
                   $(bdroid_C_INCLUDES)

LOCAL_CFLAGS += $(bdroid_CFLAGS) -std=c99

LOCAL_PRELINK_MODULE:=false
LOCAL_SRC_FILES:= \
    ./src/bt_utils.c

LOCAL_MODULE := libbt-utils
LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := libcutils liblog libc
LOCAL_MODULE_CLASS := SHARED_LIBRARIES

include $(BUILD_SHARED_LIBRARY)
