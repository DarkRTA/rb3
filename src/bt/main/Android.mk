LOCAL_PATH:= $(call my-dir)

#
# Bluetooth HW module
#

include $(CLEAR_VARS)

# HAL layer
LOCAL_SRC_FILES:= \
	../btif/src/bluetooth.c

# platform specific
LOCAL_SRC_FILES+= \
	bte_main.c \
	bte_init.c \
	bte_version.c \
	bte_logmsg.c \
	bte_conf.c

# BTIF
LOCAL_SRC_FILES += \
    ../btif/src/btif_core.c \
    ../btif/src/btif_dm.c \
    ../btif/src/btif_storage.c \
    ../btif/src/btif_util.c \
    ../btif/src/btif_sm.c \
    ../btif/src/btif_hf.c \
    ../btif/src/btif_av.c \
    ../btif/src/btif_rc.c \
    ../btif/src/btif_media_task.c \
    ../btif/src/btif_hh.c \
    ../btif/src/btif_hl.c \
    ../btif/src/btif_sock.c \
    ../btif/src/btif_sock_rfc.c \
    ../btif/src/btif_sock_thread.c \
    ../btif/src/btif_sock_sdp.c \
    ../btif/src/btif_sock_util.c \
    ../btif/src/btif_pan.c \
    ../btif/src/btif_config.c \
    ../btif/src/btif_config_util.cpp \
    ../btif/src/btif_profile_queue.c

# callouts
LOCAL_SRC_FILES+= \
    ../btif/co/bta_sys_co.c \
    ../btif/co/bta_fs_co.c \
    ../btif/co/bta_ag_co.c \
    ../btif/co/bta_dm_co.c \
    ../btif/co/bta_av_co.c \
    ../btif/co/bta_hh_co.c \
    ../btif/co/bta_hl_co.c \
    ../btif/co/bta_pan_co.c

# sbc encoder
LOCAL_SRC_FILES+= \
	../embdrv/sbc/encoder/srce/sbc_analysis.c \
	../embdrv/sbc/encoder/srce/sbc_dct.c \
	../embdrv/sbc/encoder/srce/sbc_dct_coeffs.c \
	../embdrv/sbc/encoder/srce/sbc_enc_bit_alloc_mono.c \
	../embdrv/sbc/encoder/srce/sbc_enc_bit_alloc_ste.c \
	../embdrv/sbc/encoder/srce/sbc_enc_coeffs.c \
	../embdrv/sbc/encoder/srce/sbc_encoder.c \
	../embdrv/sbc/encoder/srce/sbc_packing.c \

LOCAL_SRC_FILES+= \
	../udrv/ulinux/uipc.c

LOCAL_C_INCLUDES+= . \
	$(LOCAL_PATH)/../bta/include \
	$(LOCAL_PATH)/../bta/sys \
	$(LOCAL_PATH)/../bta/dm \
	$(LOCAL_PATH)/../gki/common \
	$(LOCAL_PATH)/../gki/ulinux \
	$(LOCAL_PATH)/../include \
	$(LOCAL_PATH)/../stack/include \
	$(LOCAL_PATH)/../stack/l2cap \
	$(LOCAL_PATH)/../stack/a2dp \
	$(LOCAL_PATH)/../stack/btm \
	$(LOCAL_PATH)/../stack/avdt \
	$(LOCAL_PATH)/../hcis \
	$(LOCAL_PATH)/../hcis/include \
	$(LOCAL_PATH)/../hcis/patchram \
	$(LOCAL_PATH)/../udrv/include \
	$(LOCAL_PATH)/../btif/include \
	$(LOCAL_PATH)/../btif/co \
	$(LOCAL_PATH)/../hci/include\
	$(LOCAL_PATH)/../brcm/include \
	$(LOCAL_PATH)/../embdrv/sbc/encoder/include \
	$(LOCAL_PATH)/../audio_a2dp_hw \
	$(LOCAL_PATH)/../utils/include \
	$(bdroid_C_INCLUDES) \
	external/tinyxml2

LOCAL_CFLAGS += -DBUILDCFG $(bdroid_CFLAGS) -Werror -Wno-error=maybe-uninitialized -Wno-error=uninitialized

ifeq ($(TARGET_PRODUCT), full_crespo)
     LOCAL_CFLAGS += -DTARGET_CRESPO
endif
ifeq ($(TARGET_PRODUCT), full_crespo4g)
     LOCAL_CFLAGS += -DTARGET_CRESPO
endif
ifeq ($(TARGET_PRODUCT), full_maguro)
     LOCAL_CFLAGS += -DTARGET_MAGURO
endif

# Fix this
#ifeq ($(TARGET_VARIANT), eng)
#     LOCAL_CFLAGS += -O2 # and other production release flags
#else
#     LOCAL_CFLAGS +=
#endif

LOCAL_SHARED_LIBRARIES := \
    libcutils \
    libpower \
    libbt-hci \
    libbt-utils

#LOCAL_WHOLE_STATIC_LIBRARIES := libbt-brcm_gki libbt-brcm_stack libbt-brcm_bta
LOCAL_STATIC_LIBRARIES := libbt-brcm_gki libbt-brcm_bta libbt-brcm_stack libtinyxml2

LOCAL_MODULE := bluetooth.default
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_REQUIRED_MODULES := libbt-hci libbt-vendor bt_stack.conf bt_did.conf auto_pair_devlist.conf

include $(BUILD_SHARED_LIBRARY)
