/******************************************************************************
 *
 *  Copyright (C) 1999-2012 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

/******************************************************************************
 *
 *  This file contains the Bluetooth Manager (BTM) API function external
 *  definitions.
 *
 ******************************************************************************/
#ifndef BTM_BLE_API_H
#define BTM_BLE_API_H

#include "btm_api.h"

#define CHNL_MAP_LEN    5
typedef UINT8 tBTM_BLE_CHNL_MAP[CHNL_MAP_LEN];

/* 0x00-0x04 only used for set advertising parameter command */
#define BTM_BLE_CONNECT_EVT     0x00   /* 0x00-0x04 only used for set advertising
                                            parameter command */
#define BTM_BLE_CONNECT_DIR_EVT 0x01   /* Connectable directed advertising */
#define BTM_BLE_DISCOVER_EVT    0x02  /* Scannable undirected advertising */
#define BTM_BLE_NON_CONNECT_EVT 0x03  /* Non connectable undirected advertising */
#define BTM_BLE_CONNECT_LO_DUTY_DIR_EVT 0x04        /* Connectable low duty
                                                       cycle directed advertising  */
    /* 0x00 - 0x05 can be received on adv event type */
#define BTM_BLE_SCAN_RSP_EVT    0x04
#define BTM_BLE_SCAN_REQ_EVT    0x05
#define BTM_BLE_UNKNOWN_EVT     0xff

#define BTM_BLE_UNKNOWN_EVT     0xff

#define BTM_BLE_SCAN_MODE_PASS      0
#define BTM_BLE_SCAN_MODE_ACTI      1
#define BTM_BLE_SCAN_MODE_NONE      0xff
typedef UINT8 tBTM_BLE_SCAN_MODE;

/* advertising channel map */
#define BTM_BLE_ADV_CHNL_37    (0x01 << 0)
#define BTM_BLE_ADV_CHNL_38    (0x01 << 1)
#define BTM_BLE_ADV_CHNL_39    (0x01 << 2)
typedef UINT8 tBTM_BLE_ADV_CHNL_MAP;

/*d efault advertising channel map */
#ifndef BTM_BLE_DEFAULT_ADV_CHNL_MAP
#define BTM_BLE_DEFAULT_ADV_CHNL_MAP   (BTM_BLE_ADV_CHNL_37| BTM_BLE_ADV_CHNL_38| BTM_BLE_ADV_CHNL_39)
#endif

/* advertising filter policy */
#define AP_SCAN_CONN_ALL           0x00        /* default */
#define AP_SCAN_WL_CONN_ALL        0x01
#define AP_SCAN_ALL_CONN_WL        0x02
#define AP_SCAN_CONN_WL            0x03
#define AP_SCAN_CONN_POLICY_MAX    0x04
typedef UINT8   tBTM_BLE_AFP;

/* default advertising filter policy */
#ifndef BTM_BLE_DEFAULT_AFP
#define BTM_BLE_DEFAULT_AFP   AP_SCAN_CONN_ALL
#endif

/* scanning filter policy */
#define SP_ADV_ALL     0x00     /* accept adv pakt from all, directed adv pkt not directed to me is ignored */
#define SP_ADV_WL      0x01     /* accept adv pakt from device in white list, directed adv pkt not directed to me is ignored */
typedef UINT8   tBTM_BLE_SFP;

#ifndef BTM_BLE_DEFAULT_SFP
#define BTM_BLE_DEFAULT_SFP   SP_ADV_ALL
#endif

/* adv parameter boundary values */
#define BTM_BLE_ADV_INT_MIN            0x0020
#define BTM_BLE_ADV_INT_MAX            0x4000

/* connection parameter boundary values */
#define BTM_BLE_SCAN_INT_MIN            0x0004
#define BTM_BLE_SCAN_INT_MAX            0x4000
#define BTM_BLE_SCAN_WIN_MIN            0x0004
#define BTM_BLE_SCAN_WIN_MAX            0x4000
#define BTM_BLE_CONN_INT_MIN            0x0006
#define BTM_BLE_CONN_INT_MAX            0x0C80
#define BTM_BLE_CONN_LATENCY_MAX        500
#define BTM_BLE_CONN_SUP_TOUT_MIN       0x000A
#define BTM_BLE_CONN_SUP_TOUT_MAX       0x0C80
#define BTM_BLE_CONN_PARAM_UNDEF        0xffff      /* use this value when a specific value not to be overwritten */
#define BTM_BLE_CONN_SUP_TOUT_DEF       700

/* default connection parameters if not configured, use GAP recommend value for auto/selective connection */
/* default scan interval */
#ifndef BTM_BLE_SCAN_FAST_INT
#define BTM_BLE_SCAN_FAST_INT    96    /* 30 ~ 60 ms (use 60)  = 96 *0.625 */
#endif
/* default scan window for background connection, applicable for auto connection or selective conenction */
#ifndef BTM_BLE_SCAN_FAST_WIN
#define BTM_BLE_SCAN_FAST_WIN   48      /* 30 ms = 48 *0.625 */
#endif

/* default scan paramter used in reduced power cycle (background scanning) */
#ifndef BTM_BLE_SCAN_SLOW_INT_1
#define BTM_BLE_SCAN_SLOW_INT_1    2048    /* 1.28 s   = 2048 *0.625 */
#endif
#ifndef BTM_BLE_SCAN_SLOW_WIN_1
#define BTM_BLE_SCAN_SLOW_WIN_1   18      /* 11.25 ms = 18 *0.625 */
#endif

/* default scan paramter used in reduced power cycle (background scanning) */
#ifndef BTM_BLE_SCAN_SLOW_INT_2
#define BTM_BLE_SCAN_SLOW_INT_2    4096    /* 2.56 s   = 4096 *0.625 */
#endif
#ifndef BTM_BLE_SCAN_SLOW_WIN_2
#define BTM_BLE_SCAN_SLOW_WIN_2   36      /* 22.5 ms = 36 *0.625 */
#endif

/* default connection interval min */
#ifndef BTM_BLE_CONN_INT_MIN_DEF
#define BTM_BLE_CONN_INT_MIN_DEF     24      /* recommended min: 30ms  = 24 * 1.25 */
#endif
/* default connectino interval max */
#ifndef BTM_BLE_CONN_INT_MAX_DEF
#define BTM_BLE_CONN_INT_MAX_DEF     40      /* recommended max: 50 ms = 56 * 1.25 */
#endif
/* default slave latency */
#ifndef BTM_BLE_CONN_SLAVE_LATENCY_DEF
#define BTM_BLE_CONN_SLAVE_LATENCY_DEF  0      /* 0 */
#endif
/* default supervision timeout */
#ifndef BTM_BLE_CONN_TIMEOUT_DEF
#define BTM_BLE_CONN_TIMEOUT_DEF    2000
#endif

#define BTM_BLE_DIR_CONN_FALLBACK_UNDIR         1
#define BTM_BLE_DIR_CONN_FALLBACK_NO_ADV        2

#ifndef BTM_BLE_DIR_CONN_FALLBACK
#define BTM_BLE_DIR_CONN_FALLBACK   BTM_BLE_DIR_CONN_FALLBACK_UNDIR
#endif

#define BTM_CMAC_TLEN_SIZE          8                   /* 64 bits */
#define BTM_BLE_AUTH_SIGN_LEN       12                   /* BLE data signature length 8 Bytes + 4 bytes counter*/
typedef UINT8 BLE_SIGNATURE[BTM_BLE_AUTH_SIGN_LEN];         /* Device address */

#ifndef BTM_BLE_HOST_SUPPORT
#define BTM_BLE_HOST_SUPPORT		0x01
#endif

#ifndef BTM_BLE_SIMULTANEOUS_HOST
#define BTM_BLE_SIMULTANEOUS_HOST	0x01
#endif

/* Structure returned with Rand/Encrypt complete callback */
typedef struct
{
    UINT8   status;
    UINT8   param_len;
    UINT16  opcode;
    UINT8   param_buf[BT_OCTET16_LEN];
} tBTM_RAND_ENC;

/* General callback function for notifying an application that a synchronous
** BTM function is complete. The pointer contains the address of any returned data.
*/
typedef void (tBTM_RAND_ENC_CB) (tBTM_RAND_ENC *p1);

#define BTM_BLE_FILTER_TARGET_SCANNER       0x01
#define BTM_BLE_FILTER_TARGET_ADVR          0x00

#define BTM_BLE_POLICY_BLACK_ALL            0x00    /* relevant to both */
#define BTM_BLE_POLICY_ALLOW_SCAN           0x01    /* relevant to advertiser */
#define BTM_BLE_POLICY_ALLOW_CONN           0x02    /* relevant to advertiser */
#define BTM_BLE_POLICY_WHITE_ALL            0x03    /* relevant to both */

typedef struct
{
    UINT8               adv_int_min;
    UINT8               adv_int_max;
    tBTM_BLE_CHNL_MAP   chnl_map;

}tBTM_BLE_ADV_PARAMS;

/* ADV data flag bit definition used for BTM_BLE_AD_TYPE_FLAG */
#define BTM_BLE_LIMIT_DISC_FLAG         (0x01 << 0)
#define BTM_BLE_GEN_DISC_FLAG           (0x01 << 1)
#define BTM_BLE_BREDR_NOT_SPT           (0x01 << 2)
/* 4.1 spec adv flag for simultaneous BR/EDR+LE connection support */
#define BTM_BLE_DMT_CONTROLLER_SPT      (0x01 << 3)
#define BTM_BLE_DMT_HOST_SPT            (0x01 << 4)

#define BTM_BLE_NON_LIMIT_DISC_FLAG     (0x00 )         /* lowest bit unset */
#define BTM_BLE_ADV_FLAG_MASK           (BTM_BLE_LIMIT_DISC_FLAG | BTM_BLE_BREDR_NOT_SPT | BTM_BLE_GEN_DISC_FLAG)
#define BTM_BLE_LIMIT_DISC_MASK         (BTM_BLE_LIMIT_DISC_FLAG )

#define BTM_BLE_AD_BIT_DEV_NAME        (0x00000001 << 0)
#define BTM_BLE_AD_BIT_FLAGS           (0x00000001 << 1)
#define BTM_BLE_AD_BIT_MANU            (0x00000001 << 2)
#define BTM_BLE_AD_BIT_TX_PWR          (0x00000001 << 3)
#define BTM_BLE_AD_BIT_INT_RANGE       (0x00000001 << 5)
#define BTM_BLE_AD_BIT_SERVICE         (0x00000001 << 6)
#define BTM_BLE_AD_BIT_SERVICE_SOL     (0x00000001 << 7)
#define BTM_BLE_AD_BIT_SERVICE_DATA    (0x00000001 << 8)
#define BTM_BLE_AD_BIT_SIGN_DATA       (0x00000001 << 9)
#define BTM_BLE_AD_BIT_SERVICE_128SOL  (0x00000001 << 10)
#define BTM_BLE_AD_BIT_APPEARANCE      (0x00000001 << 11)
#define BTM_BLE_AD_BIT_PUBLIC_ADDR      (0x00000001 << 12)
#define BTM_BLE_AD_BIT_RANDOM_ADDR       (0x00000001 << 13)
#define BTM_BLE_AD_BIT_SERVICE_32        (0x00000001 << 4)
#define BTM_BLE_AD_BIT_SERVICE_32SOL     (0x00000001 << 14)

#define BTM_BLE_AD_BIT_PROPRIETARY     (0x00000001 << 15)

typedef  UINT32  tBTM_BLE_AD_MASK;

#define BTM_BLE_AD_TYPE_FLAG            HCI_EIR_FLAGS_TYPE                  /* 0x01 */
#define BTM_BLE_AD_TYPE_16SRV_PART      HCI_EIR_MORE_16BITS_UUID_TYPE       /* 0x02 */
#define BTM_BLE_AD_TYPE_16SRV_CMPL      HCI_EIR_COMPLETE_16BITS_UUID_TYPE   /* 0x03 */
#define BTM_BLE_AD_TYPE_32SRV_PART      HCI_EIR_MORE_32BITS_UUID_TYPE       /* 0x04 */
#define BTM_BLE_AD_TYPE_32SRV_CMPL      HCI_EIR_COMPLETE_32BITS_UUID_TYPE   /* 0x05 */
#define BTM_BLE_AD_TYPE_128SRV_PART     HCI_EIR_MORE_128BITS_UUID_TYPE       /* 0x06 */
#define BTM_BLE_AD_TYPE_128SRV_CMPL     HCI_EIR_COMPLETE_128BITS_UUID_TYPE   /* 0x07 */
#define BTM_BLE_AD_TYPE_NAME_SHORT      HCI_EIR_SHORTENED_LOCAL_NAME_TYPE       /* 0x08 */
#define BTM_BLE_AD_TYPE_NAME_CMPL       HCI_EIR_COMPLETE_LOCAL_NAME_TYPE        /* 0x09 */
#define BTM_BLE_AD_TYPE_TX_PWR          HCI_EIR_TX_POWER_LEVEL_TYPE             /* 0x0A */
#define BTM_BLE_AD_TYPE_DEV_CLASS       0x0D
#define BTM_BLE_AD_TYPE_SM_TK           0x10
#define BTM_BLE_AD_TYPE_SM_OOB_FLAG     0x11
#define BTM_BLE_AD_TYPE_INT_RANGE       0x12
#define BTM_BLE_AD_TYPE_SOL_SRV_UUID    0x14
#define BTM_BLE_AD_TYPE_128SOL_SRV_UUID 0x15
#define BTM_BLE_AD_TYPE_SERVICE_DATA    0x16
#define BTM_BLE_AD_TYPE_PUBLIC_TARGET   0x17
#define BTM_BLE_AD_TYPE_RANDOM_TARGET   0x18
#define BTM_BLE_AD_TYPE_APPEARANCE      0x19
#define BTM_BLE_AD_TYPE_ADV_INT         0x1a
#define BTM_BLE_AD_TYPE_32SOL_SRV_UUID  0x1b
#define BTM_BLE_AD_TYPE_32SERVICE_DATA  0x1c
#define BTM_BLE_AD_TYPE_128SERVICE_DATA 0x1d

#define BTM_BLE_AD_TYPE_MANU            HCI_EIR_MANUFACTURER_SPECIFIC_TYPE      /* 0xff */
typedef UINT8   tBTM_BLE_AD_TYPE;

/* slave preferred connection interval range */
typedef struct
{
    UINT16  low;
    UINT16  hi;

}tBTM_BLE_INT_RANGE;

/* Service tag supported in the device */
typedef struct
{
    UINT8       num_service;
    BOOLEAN     list_cmpl;
    UINT16      *p_uuid;
}tBTM_BLE_SERVICE;

/* Service tag supported in the device */
typedef struct
{
    UINT8       num_service;
    BOOLEAN     list_cmpl;
    UINT32      *p_uuid;
}tBTM_BLE_32SERVICE;


typedef struct
{
    UINT8       len;
    UINT8      *p_val;
}tBTM_BLE_MANU;


typedef struct
{
    tBT_UUID    service_uuid;
    UINT8       len;
    UINT8      *p_val;
}tBTM_BLE_SERVICE_DATA;


typedef struct
{
    UINT8       adv_type;
    UINT8       len;
    UINT8       *p_val;     /* number of len byte */
}tBTM_BLE_PROP_ELEM;

typedef struct
{
    UINT8                   num_elem;
    tBTM_BLE_PROP_ELEM      *p_elem;
}tBTM_BLE_PROPRIETARY;

typedef struct
{
    tBTM_BLE_SERVICE_DATA   *p_service_data;
    tBTM_BLE_MANU           manu;           /* manufactuer data */
    tBTM_BLE_INT_RANGE      int_range;      /* slave prefered conn interval range */
    tBTM_BLE_SERVICE        services;       /* services */
    tBTM_BLE_32SERVICE      service_32b;     /* 32 bits Service UUID */
    tBTM_BLE_32SERVICE      sol_service_32b;    /* List of 32 bit Service Solicitation UUIDs */
    UINT16                  appearance;
    UINT8                   flag;
    tBTM_BLE_PROPRIETARY    *p_proprietary;
}tBTM_BLE_ADV_DATA;

/* These are the fields returned in each device adv packet.  It
** is returned in the results callback if registered.
*/
typedef struct
{
    UINT8               conn_mode;
    tBTM_BLE_AD_MASK    ad_mask;        /* mask of the valid adv data field */
    UINT8               flag;
    UINT8               tx_power_level;
    UINT8               remote_name_len;
    UINT8               *p_remote_name;
    tBTM_BLE_SERVICE    service;
} tBTM_BLE_INQ_DATA;

enum
{
    BTM_BLE_CONN_NONE,
    BTM_BLE_CONN_AUTO,
    BTM_BLE_CONN_SELECTIVE
};
typedef UINT8   tBTM_BLE_CONN_TYPE;

typedef BOOLEAN (tBTM_BLE_SEL_CBACK)(BD_ADDR random_bda,     UINT8 *p_remote_name);

/* callback function for SMP signing algorithm, signed data in little endian order with tlen bits long */
typedef void (tBTM_BLE_SIGN_CBACK)(void *p_ref_data, UINT8 *p_signing_data);
typedef void (tBTM_BLE_VERIFY_CBACK)(void *p_ref_data, BOOLEAN match);
/* random address set complete callback */
typedef void (tBTM_BLE_RANDOM_SET_CBACK) (BD_ADDR random_bda);

typedef void (tBTM_BLE_SCAN_REQ_CBACK)(BD_ADDR remote_bda, tBLE_ADDR_TYPE addr_type, UINT8 adv_evt);

/*****************************************************************************
**  EXTERNAL FUNCTION DECLARATIONS
*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*******************************************************************************
**
** Function         BTM_SecAddBleDevice
**
** Description      Add/modify device.  This function will be normally called
**                  during host startup to restore all required information
**                  for a LE device stored in the NVRAM.
**
** Parameters:      bd_addr          - BD address of the peer
**                  bd_name          - Name of the peer device.  NULL if unknown.
**                  dev_type         - Remote device's device type.
**                  addr_type        - LE device address type.
**
** Returns          TRUE if added OK, else FALSE
**
*******************************************************************************/
BTM_API extern BOOLEAN BTM_SecAddBleDevice (BD_ADDR bd_addr, BD_NAME bd_name,
                                           tBT_DEVICE_TYPE dev_type, tBLE_ADDR_TYPE addr_type);

/*******************************************************************************
**
** Function         BTM_SecAddBleKey
**
** Description      Add/modify LE device information.  This function will be
**                  normally called during host startup to restore all required
**                  information stored in the NVRAM.
**
** Parameters:      bd_addr          - BD address of the peer
**                  p_le_key         - LE key values.
**                  key_type         - LE SMP key type.
*
** Returns          TRUE if added OK, else FALSE
**
*******************************************************************************/
BTM_API extern BOOLEAN BTM_SecAddBleKey (BD_ADDR bd_addr, tBTM_LE_KEY_VALUE *p_le_key,
                                         tBTM_LE_KEY_TYPE key_type);

/*******************************************************************************
**
** Function         BTM_BleSetAdvParams
**
** Description      This function is called to set advertising parameters.
**
** Parameters:       None.
**
** Returns          void
**
*******************************************************************************/
BTM_API extern tBTM_STATUS BTM_BleSetAdvParams(UINT16 adv_int_min, UINT16 adv_int_max,
                                tBLE_BD_ADDR *p_dir_bda, tBTM_BLE_ADV_CHNL_MAP chnl_map);

/*******************************************************************************
**
** Function         BTM_BleWriteAdvData
**
** Description      This function is called to write advertising data.
**
** Parameters:       None.
**
** Returns          void
**
*******************************************************************************/
BTM_API extern tBTM_STATUS BTM_BleWriteAdvData(tBTM_BLE_AD_MASK  data_mask,
                                               tBTM_BLE_ADV_DATA *p_data);

/*******************************************************************************
**
** Function         BTM_BleSetAdvParams
**
** Description      This function is called to set advertising parameters.
**
** Parameters       adv_int_min: minimum advertising interval
**                  adv_int_max: maximum advertising interval
**                  p_dir_bda: connectable direct initiator's LE device address
**                  chnl_map: advertising channel map.
**
** Returns          void
**
*******************************************************************************/
BTM_API extern void BTM_BleReadAdvParams (UINT16 *adv_int_min, UINT16 *adv_int_max,
                            tBLE_BD_ADDR *p_dir_bda, tBTM_BLE_ADV_CHNL_MAP *p_chnl_map);


/*******************************************************************************
**
** Function         BTM_BleSetScanParams
**
** Description      This function is called to set Scan parameters.
**
** Parameters       adv_int_min: minimum advertising interval
**                  adv_int_max: maximum advertising interval
**                  scan_type: scan mode.
**
** Returns          void
**
*******************************************************************************/
BTM_API extern void BTM_BleSetScanParams(UINT16 scan_interval, UINT16 scan_window,
                                         tBTM_BLE_SCAN_MODE scan_type);

/*******************************************************************************
**
** Function         BTM_BleWriteScanRsp
**
** Description      This function is called to write LE scan response.
**
** Parameters:      p_scan_rsp: scan response.
**
** Returns          status
**
*******************************************************************************/
BTM_API extern tBTM_STATUS BTM_BleWriteScanRsp(tBTM_BLE_AD_MASK data_mask,
                                               tBTM_BLE_ADV_DATA *p_data);

/*******************************************************************************
**
** Function         BTM_BleObserve
**
** Description      This procedure keep the device listening for advertising
**                  events from a broadcast device.
**
** Parameters       start: start or stop observe.
**
** Returns          void
**
*******************************************************************************/
BTM_API extern tBTM_STATUS BTM_BleObserve(BOOLEAN start, UINT8 duration,
                           tBTM_INQ_RESULTS_CB *p_results_cb, tBTM_CMPL_CB *p_cmpl_cb);


/*******************************************************************************
**
** Function         BTM_GetDeviceIDRoot
**
** Description      This function is called to read the local device identity
**                  root.
**
** Returns          void
**                  the local device ER is copied into er
**
*******************************************************************************/
BTM_API extern void BTM_GetDeviceIDRoot (BT_OCTET16 ir);

/*******************************************************************************
**
** Function         BTM_GetDeviceEncRoot
**
** Description      This function is called to read the local device encryption
**                  root.
**
** Returns          void
**                  the local device ER is copied into er
**
*******************************************************************************/
BTM_API extern void BTM_GetDeviceEncRoot (BT_OCTET16 er);

/*******************************************************************************
**
** Function         BTM_GetDeviceDHK
**
** Description      This function is called to read the local device DHK.
**
** Returns          void
**                  the local device DHK is copied into dhk
**
*******************************************************************************/
BTM_API extern void BTM_GetDeviceDHK (BT_OCTET16 dhk);

/*******************************************************************************
**
** Function         BTM_SecurityGrant
**
** Description      This function is called to grant security process.
**
** Parameters       bd_addr - peer device bd address.
**                  res     - result of the operation BTM_SUCCESS if success.
**                            Otherwise, BTM_REPEATED_ATTEMPTS is too many attempts.
**
** Returns          None
**
*******************************************************************************/
BTM_API extern void BTM_SecurityGrant(BD_ADDR bd_addr, UINT8 res);

/*******************************************************************************
**
** Function         BTM_BlePasskeyReply
**
** Description      This function is called after Security Manager submitted
**                  passkey request to the application.
**
** Parameters:      bd_addr      - Address of the device for which passkey was requested
**                  res          - result of the operation SMP_SUCCESS if success
**                  passkey - numeric value in the range of
**                  BTM_MIN_PASSKEY_VAL(0) - BTM_MAX_PASSKEY_VAL(999999(0xF423F)).
**
*******************************************************************************/
BTM_API extern void BTM_BlePasskeyReply (BD_ADDR bd_addr, UINT8 res, UINT32 passkey);

/*******************************************************************************
**
** Function         BTM_LeOobDataReply
**
** Description      This function is called to provide the OOB data for
**                  SMP in response to BTM_LE_OOB_REQ_EVT
**
** Parameters:      bd_addr     - Address of the peer device
**                  res         - result of the operation SMP_SUCCESS if success
**                  p_data      - simple pairing Randomizer  C.
**
*******************************************************************************/
BTM_API extern void BTM_BleOobDataReply(BD_ADDR bd_addr, UINT8 res, UINT8 len, UINT8 *p_data);


/*******************************************************************************
**
** Function         BTM_BleDataSignature
**
** Description      This function is called to sign the data using AES128 CMAC
**                  algorith.
**
** Parameter        bd_addr: target device the data to be signed for.
**                  p_text: singing data
**                  len: length of the signing data
**                  signature: output parameter where data signature is going to
**                             be stored.
**
** Returns          TRUE if signing sucessul, otherwise FALSE.
**
*******************************************************************************/
BTM_API extern BOOLEAN BTM_BleDataSignature (BD_ADDR bd_addr, UINT8 *p_text, UINT16 len,
                                             BLE_SIGNATURE signature);

/*******************************************************************************
**
** Function         BTM_BleVerifySignature
**
** Description      This function is called to verify the data signature
**
** Parameter        bd_addr: target device the data to be signed for.
**                  p_orig:  original data before signature.
**                  len: length of the signing data
**                  counter: counter used when doing data signing
**                  p_comp: signature to be compared against.

** Returns          TRUE if signature verified correctly; otherwise FALSE.
**
*******************************************************************************/
BTM_API extern BOOLEAN BTM_BleVerifySignature (BD_ADDR bd_addr, UINT8 *p_orig,
                                            UINT16 len, UINT32 counter,
                                            UINT8 *p_comp);

/*******************************************************************************
**
** Function         BTM_ReadConnectionAddr
**
** Description      This function is called to set the local device random address
**                  .
**
** Returns          void
**
*******************************************************************************/
BTM_API extern void BTM_ReadConnectionAddr (BD_ADDR remote_bda, BD_ADDR local_conn_addr,
                                            tBLE_ADDR_TYPE *p_addr_type);



/*******************************************************************************
**
** Function         BTM_ReadRemoteConnectionAddr
**
** Description      This function is read the remote device address currently used
**                  .
**
** Returns          void
**
*******************************************************************************/
BTM_API extern BOOLEAN BTM_ReadRemoteConnectionAddr(BD_ADDR pseudo_addr,
                                                    BD_ADDR conn_addr,
                                                    tBLE_ADDR_TYPE *p_addr_type);

/*******************************************************************************
**
** Function         BTM_BleLoadLocalKeys
**
** Description      Local local identity key, encryption root or sign counter.
**
** Parameters:      key_type: type of key, can be BTM_BLE_KEY_TYPE_ID, BTM_BLE_KEY_TYPE_ER
**                            or BTM_BLE_KEY_TYPE_COUNTER.
**                  p_key: pointer to the key.
*
** Returns          non2.
**
*******************************************************************************/
BTM_API extern void BTM_BleLoadLocalKeys(UINT8 key_type, tBTM_BLE_LOCAL_KEYS *p_key);


/*******************************************************************************
**
** Function         BTM_BleSetBgConnType
**
** Description      This function is called to set BLE background connection
**                  procedure type. It can be auto connection, or selective connection.
**
** Parameters       conn_type: it can be auto connection, or selective connection.
**                  p_select_cback: callback function when selective connection procedure
**                              is being used.
**
** Returns          void
**
*******************************************************************************/
BTM_API extern BOOLEAN BTM_BleSetBgConnType(tBTM_BLE_CONN_TYPE   conn_type,
                                    tBTM_BLE_SEL_CBACK   *p_select_cback);

/*******************************************************************************
**
** Function         BTM_BleUpdateBgConnDev
**
** Description      This function is called to add or remove a device into/from
**                  background connection procedure. The background connection
*                   procedure is decided by the background connection type, it can be
*                   auto connection, or selective connection.
**
** Parameters       add_remove: TRUE to add; FALSE to remove.
**                  remote_bda: device address to add/remove.
**
** Returns          void
**
*******************************************************************************/
BTM_API extern BOOLEAN BTM_BleUpdateBgConnDev(BOOLEAN add_remove, BD_ADDR   remote_bda);


/********************************************************
**
** Function         BTM_BleSetPrefConnParams
**
** Description      Set a peripheral's preferred connection parameters. When
**                  any of the value does not want to be updated while others
**                  do, use BTM_BLE_CONN_PARAM_UNDEF for the ones want to
**                  leave untouched.
**
** Parameters:      bd_addr          - BD address of the peripheral
**                  min_conn_int     - minimum preferred connection interval
**                  max_conn_int     - maximum preferred connection interval
**                  slave_latency    - preferred slave latency
**                  supervision_tout - preferred supervision timeout
**
** Returns          void
**
*******************************************************************************/
BTM_API extern  void BTM_BleSetPrefConnParams (BD_ADDR bd_addr,
                                               UINT16 min_conn_int,  UINT16 max_conn_int,
                                               UINT16 slave_latency, UINT16 supervision_tout);

/******************************************************************************
**
** Function         BTM_BleSetConnScanParams
**
** Description      Set scan parameters used in BLE connection request
**
** Parameters:      scan_interval    - scan interval
**                  scan_window      - scan window
**
** Returns          void
**
*******************************************************************************/
BTM_API extern  void BTM_BleSetConnScanParams (UINT16 scan_interval, UINT16 scan_window);

/*******************************************************************************
**
** Function         BTM_CheckAdvData
**
** Description      This function is called to get ADV data for a specific type.
**
** Parameters       p_adv - pointer of ADV data
**                  type   - finding ADV data type
**                  p_length - return the length of ADV data not including type
**
** Returns          pointer of ADV data
**
*******************************************************************************/
BTM_API extern  UINT8 *BTM_CheckAdvData( UINT8 *p_adv, UINT8 type, UINT8 *p_length);

/*******************************************************************************
**
** Function         BTM_ReadDevInfo
**
** Description      This function is called to read the device/address type
**                  of BD address.
**
** Parameter        remote_bda: remote device address
**                  p_dev_type: output parameter to read the device type.
**                  p_addr_type: output parameter to read the address type.
**
*******************************************************************************/
BTM_API extern void BTM_ReadDevInfo (BD_ADDR remote_bda, tBT_DEVICE_TYPE *p_dev_type,
                                     tBLE_ADDR_TYPE *p_addr_type);

/*******************************************************************************
**
** Function         BTM_BleBroadcast
**
** Description      This function is to start or stop broadcasting.
**
** Parameters       start: start or stop broadcasting.
**
** Returns          status.
**
*******************************************************************************/
BTM_API extern tBTM_STATUS BTM_BleBroadcast(BOOLEAN start);

/*******************************************************************************
**
** Function         BTM_RegisterScanReqEvt
**
** Description      This function is called to register a scan request callback
**                  on the advertiser.
**
** Parameters       p_scan_req_cback: scan request callback.  If NULL, remove the
**                                    registration.
**
** Returns          void
**
*******************************************************************************/
BTM_API extern void BTM_RegisterScanReqEvt(tBTM_BLE_SCAN_REQ_CBACK *p_scan_req_cback);

/*******************************************************************************
**
** Function         BTM_BleConfigPrivacy
**
** Description      This function is called to enable or disable the privacy in
**                  the local device.
**
** Parameters       enable: TRUE to enable it; FALSE to disable it.
**
** Returns          void
**
*******************************************************************************/
BTM_API extern void BTM_BleConfigPrivacy(BOOLEAN enable);

/*******************************************************************************
**
** Function         BTM_BleSetConnMode
**
** Description      This function is called to set BLE connectable mode for a
**                  peripheral device.
**
** Parameters       directed: is directed connectable mode, or non-directed.
**                  p_dir_bda: connectable direct initiator's LE device address
**
** Returns          void
**
*******************************************************************************/
BTM_API extern tBTM_STATUS BTM_BleSetConnMode(BOOLEAN directed);

/*******************************************************************************
**
** Function         BTM_BleTurnOnPrivacyOnRemote
**
** Description      This function is called to enable or disable the privacy on the
**                  remote device.
**
** Parameters       bd_addr: remote device address.
**                  privacy_on: TRUE to enable it; FALSE to disable it.
**
** Returns          void
**
*******************************************************************************/
BTM_API extern void BTM_BleTurnOnPrivacyOnRemote(BD_ADDR bd_addr,
                                                 BOOLEAN privacy_on);


/*******************************************************************************
**
** Function         BTM_BleUpdateAdvWhitelist
**
** Description      Add or remove device from advertising white list
**
** Returns          void
**
*******************************************************************************/
BTM_API extern BOOLEAN BTM_BleUpdateAdvWhitelist(BOOLEAN add_remove, BD_ADDR emote_bda);

/*******************************************************************************
**
** Function         BTM_BleUpdateAdvFilterPolicy
**
** Description      This function update the filter policy of advertiser.
**
** Parameter        adv_policy: advertising filter policy
**
** Return           void
*******************************************************************************/
BTM_API extern void BTM_BleUpdateAdvFilterPolicy(tBTM_BLE_AFP adv_policy);

/*******************************************************************************
**
** Function         BTM_BleReceiverTest
**
** Description      This function is called to start the LE Receiver test
**
** Parameter       rx_freq - Frequency Range
**               p_cmd_cmpl_cback - Command Complete callback
**
*******************************************************************************/
void BTM_BleReceiverTest(UINT8 rx_freq, tBTM_CMPL_CB *p_cmd_cmpl_cback);


/*******************************************************************************
**
** Function         BTM_BleTransmitterTest
**
** Description      This function is called to start the LE Transmitter test
**
** Parameter       tx_freq - Frequency Range
**                       test_data_len - Length in bytes of payload data in each packet
**                       packet_payload - Pattern to use in the payload
**                       p_cmd_cmpl_cback - Command Complete callback
**
*******************************************************************************/
void BTM_BleTransmitterTest(UINT8 tx_freq, UINT8 test_data_len,
                                 UINT8 packet_payload, tBTM_CMPL_CB *p_cmd_cmpl_cback);

/*******************************************************************************
**
** Function         BTM_BleTestEnd
**
** Description      This function is called to stop the in-progress TX or RX test
**
** Parameter       p_cmd_cmpl_cback - Command complete callback
**
*******************************************************************************/
void BTM_BleTestEnd(tBTM_CMPL_CB *p_cmd_cmpl_cback);

/*******************************************************************************
**
** Function         BTM_UseLeLink
**
** Description      This function is to select the underneath physical link to use.
**
** Returns          TRUE to use LE, FALSE use BR/EDR.
**
*******************************************************************************/
BTM_API extern BOOLEAN BTM_UseLeLink (BD_ADDR bd_addr);

/*******************************************************************************
**
** Function         BTM_BleStackEnable
**
** Description      Enable/Disable BLE functionality on stack regarless controller
**                  capability.
**
** Parameters:      enable: TRUE to enable, FALSE to disable.
**
** Returns          TRUE if added OK, else FALSE
**
*******************************************************************************/
BTM_API extern tBTM_STATUS BTM_BleStackEnable (BOOLEAN enable);

#ifdef __cplusplus
}
#endif

#endif
