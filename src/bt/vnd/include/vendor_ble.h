/******************************************************************************
 *
 *  Copyright (C) 2003-2014 Broadcom Corporation
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

/*****************************************************************************
**
**  Name:          vendor_ble.h
**
**  Description:   This file contains vendor specific feature header
**                 for BLE
******************************************************************************/
#ifndef VENDOR_BLE_H
#define VENDOR_BLE_H

#include "btm_int.h"
#include "btm_ble_api.h"
#include "vendor_api.h"

/* BLE meta vsc header: 1 bytes of sub_code, 1 byte of PCF action */
#define BTM_BLE_META_HDR_LENGTH     2
#define BTM_BLE_PF_FEAT_SEL_LEN     12
#define BTM_BLE_PCF_ENABLE_LEN      2
#define BTM_BLE_META_ADDR_LEN       7
#define BTM_BLE_META_UUID_LEN       40
#define BTM_BLE_META_ADD_IRK_LEN        24
#define BTM_BLE_META_REMOVE_IRK_LEN     8
#define BTM_BLE_META_CLEAR_IRK_LEN      1
#define BTM_BLE_META_READ_IRK_LEN       2
#define BTM_BLE_META_ADD_WL_ATTR_LEN    9

#define BTM_BLE_PF_BIT_TO_MASK(x)          (UINT32)(1 << (x))
#define BTM_BLE_PF_SELECT_NONE              0
#define BTM_BLE_PF_ADDR_FILTER_BIT          BTM_BLE_PF_BIT_TO_MASK(BTM_BLE_PF_ADDR_FILTER)
#define BTM_BLE_PF_SRVC_DATA_BIT            BTM_BLE_PF_BIT_TO_MASK(BTM_BLE_PF_SRVC_DATA)
#define BTM_BLE_PF_SRVC_UUID_BIT            BTM_BLE_PF_BIT_TO_MASK(BTM_BLE_PF_SRVC_UUID)
#define BTM_BLE_PF_SRVC_SOL_UUID_BIT        BTM_BLE_PF_BIT_TO_MASK(BTM_BLE_PF_SRVC_SOL_UUID)
#define BTM_BLE_PF_LOCAL_NAME_BIT           BTM_BLE_PF_BIT_TO_MASK(BTM_BLE_PF_LOCAL_NAME)
#define BTM_BLE_PF_MANU_DATA_BIT            BTM_BLE_PF_BIT_TO_MASK(BTM_BLE_PF_MANU_DATA)
#define BTM_BLE_PF_SRVC_DATA_PATTERN_BIT    BTM_BLE_PF_BIT_TO_MASK(BTM_BLE_PF_SRVC_DATA_PATTERN)
typedef UINT8 tBTM_BLE_PF_SEL_MASK;


#define BTM_BLE_MAX_FILTER_COUNTER  (BTM_BLE_MAX_ADDR_FILTER + 1) /* per device filter + one generic filter indexed by 0 */

typedef struct
{
    BOOLEAN         in_use;
    BD_ADDR         bd_addr;
    UINT32          feat_mask;      /* per BD_ADDR feature mask */
    UINT8           pf_counter[BTM_BLE_PF_TYPE_MAX]; /* number of filter indexed by tBTM_BLE_PF_COND_TYPE */
}tBTM_BLE_PF_COUNT;


/* control block for BLE customer specific feature */
typedef struct
{
    BOOLEAN             enable;

    UINT8               op_type;
    tBTM_BLE_PF_COUNT   addr_filter_count[BTM_BLE_MAX_FILTER_COUNTER]; /* per BDA filter indexed by tBTM_BLE_PF_COND_TYPE */
    tBLE_BD_ADDR        cur_filter_target;

    tBTM_BLE_PF_CMPL_CBACK *p_scan_pf_cback;
}tBTM_BLE_VENDOR_CB;

#ifdef __cplusplus
extern "C"
{
#endif

#if VENDOR_DYNAMIC_MEMORY == FALSE
BTM_API extern tBTM_BLE_VENDOR_CB  btm_ble_vendor_cb;
#else
BTM_API extern tBTM_BLE_VENDOR_CB *btm_ble_vendor_ptr;
#define btm_ble_vendor_cb (*btm_ble_vendor_ptr)
#endif


extern void btm_ble_vendor_init(void);
extern BOOLEAN btm_ble_vendor_write_device_wl_attribute (tBLE_ADDR_TYPE addr_type, BD_ADDR bd_addr, UINT8 attribute);
#ifdef __cplusplus
}
#endif

#endif


