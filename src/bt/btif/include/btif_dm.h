/******************************************************************************
 *
 *  Copyright (C) 2009-2012 Broadcom Corporation
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

#ifndef BTIF_DM_H
#define BTIF_DM_H

#include "bta_api.h"
/************************************************************************************
**  Functions
********************************************************************************/

/**
 * BTIF callback to switch context from bte to btif
 */
void bte_dm_evt(tBTA_DM_SEC_EVT event, tBTA_DM_SEC *p_data);

/**
 * Notify BT disable being initiated. DM may chose to abort
 * pending commands, like pairing
 */
void btif_dm_on_disable(void);

/**
 * Out-of-band functions
 */
#if (BTM_OOB_INCLUDED == TRUE)
void btif_dm_set_oob_for_io_req(tBTA_OOB_DATA  *p_oob_data);
#ifdef BTIF_DM_OOB_TEST
void btif_dm_load_local_oob(void);
void btif_dm_proc_loc_oob(BOOLEAN valid, BT_OCTET16 c, BT_OCTET16 r);
BOOLEAN btif_dm_proc_rmt_oob(BD_ADDR bd_addr,  BT_OCTET16 p_c, BT_OCTET16 p_r);
#endif /* BTIF_DM_OOB_TEST */
#endif /* BTM_OOB_INCLUDED */
#if (BLE_INCLUDED == TRUE)

typedef struct
{
    UINT8       ltk[BT_OCTET16_LEN];
    UINT8       rand[BT_OCTET8_LEN];
    UINT16      ediv;
    UINT8       sec_level;
    UINT8       key_size;
}btif_dm_ble_penc_keys_t;

typedef struct
{
    UINT32          counter;
    UINT8           csrk[BT_OCTET16_LEN];
    UINT8           sec_level;
}btif_dm_ble_pcsrk_keys_t;

typedef struct
{
    UINT16      div;
    UINT8       key_size;
    UINT8       sec_level;
}btif_dm_ble_lenc_keys_t;

typedef struct
{
    UINT32          counter;
    UINT16          div;
    UINT8           sec_level;

}btif_dm_ble_lcsrk_keys_t;

typedef struct
{
    BOOLEAN                   is_penc_key_rcvd;
    btif_dm_ble_penc_keys_t   penc_key;       /* received peer encryption key */
    BOOLEAN                   is_pcsrk_key_rcvd;
    btif_dm_ble_pcsrk_keys_t  pcsrk_key;       /* received peer device SRK */
    BOOLEAN                   is_pid_key_rcvd;
    UINT8                     pid_key[BT_OCTET16_LEN];        /* peer device ID key */
    BOOLEAN                   is_lenc_key_rcvd;
    btif_dm_ble_lenc_keys_t   lenc_key;       /* local encryption reproduction keys LTK = = d1(ER,DIV,0)*/
    BOOLEAN                   is_lcsrk_key_rcvd;
    btif_dm_ble_lcsrk_keys_t  lcsrk_key;      /* local device CSRK = d1(ER,DIV,1)*/
} btif_dm_ble_cb_t;

#define BTIF_DM_LE_KEY_PENC        BTA_LE_KEY_PENC
#define BTIF_DM_LE_KEY_PID         BTA_LE_KEY_PID
#define BTIF_DM_LE_KEY_PCSRK       BTA_LE_KEY_PCSRK
#define BTIF_DM_LE_KEY_LENC        BTA_LE_KEY_LENC
#define BTIF_DM_LE_KEY_LID         BTA_LE_KEY_LID
#define BTIF_DM_LE_KEY_LCSRK       BTA_LE_KEY_LCSRK

#define BTIF_DM_LE_LOCAL_KEY_IR       (1<<0)
#define BTIF_DM_LE_LOCAL_KEY_IRK      (1<<1)
#define BTIF_DM_LE_LOCAL_KEY_DHK      (1<<2)
#define BTIF_DM_LE_LOCAL_KEY_ER       (1<<3)

void btif_dm_load_ble_local_keys(void);
void btif_dm_get_ble_local_keys(tBTA_DM_BLE_LOCAL_KEY_MASK *p_key_mask, BT_OCTET16 er,
                                   tBTA_BLE_LOCAL_ID_KEYS *p_id_keys);
void btif_dm_save_ble_bonding_keys(void);
void btif_dm_remove_ble_bonding_keys(void);
void btif_dm_ble_sec_req_evt(tBTA_DM_BLE_SEC_REQ *p_ble_req);

void btif_dm_update_ble_remote_properties( BD_ADDR bd_addr, BD_NAME bd_name,
                                           tBT_DEVICE_TYPE dev_type);

#endif /* BLE_INCLUDED */

#endif
