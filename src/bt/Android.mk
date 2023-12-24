LOCAL_PATH := $(call my-dir)

bdroid_CFLAGS := -Wno-unused-parameter

# Setup bdroid local make variables for handling configuration
ifneq ($(BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR),)
  bdroid_C_INCLUDES := $(BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR)
  bdroid_CFLAGS += -DHAS_BDROID_BUILDCFG
else
  bdroid_C_INCLUDES :=
  bdroid_CFLAGS += -DHAS_NO_BDROID_BUILDCFG
endif

bdroid_CFLAGS += -Wall -Werror

include $(call all-subdir-makefiles)

# Cleanup our locals
bdroid_C_INCLUDES :=
bdroid_CFLAGS :=
