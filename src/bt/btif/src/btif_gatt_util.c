/******************************************************************************
 *
 *  Copyright (C) 2009-2013 Broadcom Corporation
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

#include <hardware/bluetooth.h>
#include <hardware/bt_gatt.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define LOG_TAG "BtGatt.btif"

#include "bta_api.h"
#include "bta_gatt_api.h"
#include "bta_jv_api.h"
#include "bd.h"
#include "btif_storage.h"

#include "btif_common.h"
#include "btif_dm.h"
#include "btif_util.h"
#include "btif_gatt.h"
#include "btif_gatt_util.h"
#include "btif_config.h"

#if BTA_GATT_INCLUDED == TRUE

#define GATTC_READ_VALUE_TYPE_VALUE          0x0000  /* Attribute value itself */
#define GATTC_READ_VALUE_TYPE_AGG_FORMAT     0x2905  /* Characteristic Aggregate Format*/

static char BASE_UUID[16] = {
    0xfb, 0x34, 0x9b, 0x5f, 0x80, 0x00, 0x00, 0x80,
    0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

extern bt_status_t btif_dm_remove_bond(const bt_bdaddr_t *bd_addr);

int uuidType(unsigned char* p_uuid)
{
    int i = 0;
    int match = 0;
    int all_zero = 1;

    for(i = 0; i != 16; ++i)
    {
        if (i == 12 || i == 13)
            continue;

        if (p_uuid[i] == BASE_UUID[i])
            ++match;

        if (p_uuid[i] != 0)
            all_zero = 0;
    }
    if (all_zero)
        return 0;
    if (match == 12)
        return LEN_UUID_32;
    if (match == 14)
        return LEN_UUID_16;
    return LEN_UUID_128;
}

/*******************************************************************************
 * BTIF -> BTA conversion functions
 *******************************************************************************/

void btif_to_bta_uuid(tBT_UUID *p_dest, bt_uuid_t *p_src)
{
    char *p_byte = (char*)p_src;
    int i = 0;

    p_dest->len = uuidType(p_src->uu);

    switch (p_dest->len)
    {
        case LEN_UUID_16:
            p_dest->uu.uuid16 = (p_src->uu[13] << 8) + p_src->uu[12];
            break;

        case LEN_UUID_32:
            p_dest->uu.uuid32  = (p_src->uu[13] <<  8) + p_src->uu[12];
            p_dest->uu.uuid32 += (p_src->uu[15] << 24) + (p_src->uu[14] << 16);
            break;

        case LEN_UUID_128:
            for(i = 0; i != 16; ++i)
                p_dest->uu.uuid128[i] = p_byte[i];
            break;

        default:
            ALOGE("%s: Unknown UUID length %d!", __FUNCTION__, p_dest->len);
            break;
    }
}

void btif_to_bta_gatt_id(tBTA_GATT_ID *p_dest, btgatt_gatt_id_t *p_src)
{
    p_dest->inst_id = p_src->inst_id;
    btif_to_bta_uuid(&p_dest->uuid, &p_src->uuid);
}

void btif_to_bta_srvc_id(tBTA_GATT_SRVC_ID *p_dest, btgatt_srvc_id_t *p_src)
{
    p_dest->id.inst_id = p_src->id.inst_id;
    btif_to_bta_uuid(&p_dest->id.uuid, &p_src->id.uuid);
    p_dest->is_primary = p_src->is_primary;
}

void btif_to_bta_response(tBTA_GATTS_RSP *p_dest, btgatt_response_t* p_src)
{
    p_dest->attr_value.auth_req = p_src->attr_value.auth_req;
    p_dest->attr_value.handle   = p_src->attr_value.handle;
    p_dest->attr_value.len      = p_src->attr_value.len;
    p_dest->attr_value.offset   = p_src->attr_value.offset;
    memcpy(p_dest->attr_value.value, p_src->attr_value.value, GATT_MAX_ATTR_LEN);
}

void btif_to_bta_uuid_mask(tBTA_DM_BLE_PF_COND_MASK *p_mask, bt_uuid_t *p_src)
{
    char *p_byte = (char*)p_src;
    int i = 0;

    switch (uuidType(p_src->uu))
    {
        case LEN_UUID_16:
            p_mask->uuid16_mask = (p_src->uu[13] << 8) + p_src->uu[12];
            break;

        case LEN_UUID_32:
            p_mask->uuid32_mask = (p_src->uu[13] <<  8) + p_src->uu[12];
            p_mask->uuid32_mask += (p_src->uu[15] << 24) + (p_src->uu[14] << 16);
            break;

        case LEN_UUID_128:
            for(i = 0; i != 16; ++i)
                p_mask->uuid128_mask[i] = p_byte[i];
            break;

        default:
            break;
    }
}

/*******************************************************************************
 * BTA -> BTIF conversion functions
 *******************************************************************************/

void bta_to_btif_uuid(bt_uuid_t *p_dest, tBT_UUID *p_src)
{
    int i = 0;

    if (p_src->len == LEN_UUID_16 || p_src->len == LEN_UUID_32)
    {
        for(i=0; i != 16; ++i)
            p_dest->uu[i] = BASE_UUID[i];
    }

    switch (p_src->len)
    {
        case 0:
            break;

        case LEN_UUID_16:
            p_dest->uu[12] = p_src->uu.uuid16 & 0xff;
            p_dest->uu[13] = (p_src->uu.uuid16 >> 8) & 0xff;
            break;

        case LEN_UUID_32:
            p_dest->uu[12] = p_src->uu.uuid16 & 0xff;
            p_dest->uu[13] = (p_src->uu.uuid16 >> 8) & 0xff;
            p_dest->uu[14] = (p_src->uu.uuid32 >> 16) & 0xff;
            p_dest->uu[15] = (p_src->uu.uuid32 >> 24) & 0xff;
            break;

        case LEN_UUID_128:
            for(i=0; i != 16; ++i)
                p_dest->uu[i] = p_src->uu.uuid128[i];
            break;

        default:
            ALOGE("%s: Unknown UUID length %d!", __FUNCTION__, p_src->len);
            break;
    }
}


void bta_to_btif_gatt_id(btgatt_gatt_id_t *p_dest, tBTA_GATT_ID *p_src)
{
    p_dest->inst_id = p_src->inst_id;
    bta_to_btif_uuid(&p_dest->uuid, &p_src->uuid);
}

void bta_to_btif_srvc_id(btgatt_srvc_id_t *p_dest, tBTA_GATT_SRVC_ID *p_src)
{
    p_dest->id.inst_id = p_src->id.inst_id;
    bta_to_btif_uuid(&p_dest->id.uuid, &p_src->id.uuid);
    p_dest->is_primary = p_src->is_primary;
}


/*******************************************************************************
 * Utility functions
 *******************************************************************************/

uint16_t get_uuid16(tBT_UUID *p_uuid)
{
    if (p_uuid->len == LEN_UUID_16)
    {
        return p_uuid->uu.uuid16;
    }
    else if (p_uuid->len == LEN_UUID_128)
    {
        UINT16 u16;
        UINT8 *p = &p_uuid->uu.uuid128[LEN_UUID_128 - 4];
        STREAM_TO_UINT16(u16, p);
        return u16;
    }
    else  /* p_uuid->len == LEN_UUID_32 */
    {
        return(UINT16) p_uuid->uu.uuid32;
    }
}

uint16_t set_read_value(btgatt_read_params_t *p_dest, tBTA_GATTC_READ *p_src)
{
    int i = 0;
    uint16_t descr_type = 0;
    uint16_t len = 0;

    p_dest->status = p_src->status;
    bta_to_btif_srvc_id(&p_dest->srvc_id, &p_src->srvc_id);
    bta_to_btif_gatt_id(&p_dest->char_id, &p_src->char_id);
    bta_to_btif_gatt_id(&p_dest->descr_id, &p_src->descr_type);

    descr_type = get_uuid16(&p_src->descr_type.uuid);

    switch (descr_type)
    {
        case GATT_UUID_CHAR_AGG_FORMAT:
            /* not supported */
            p_dest->value_type = GATTC_READ_VALUE_TYPE_AGG_FORMAT;
            break;

        default:
            if (( p_src->status == BTA_GATT_OK ) &&(p_src->p_value != NULL))
            {
                ALOGI("%s unformat.len = %d ", __FUNCTION__, p_src->p_value->unformat.len);
                p_dest->value.len = p_src->p_value->unformat.len;
                if ( p_src->p_value->unformat.len > 0  && p_src->p_value->unformat.p_value != NULL )
                {
                    memcpy(p_dest->value.value, p_src->p_value->unformat.p_value,
                           p_src->p_value->unformat.len);
                }
                len += p_src->p_value->unformat.len;
            }
            else
            {
                p_dest->value.len = 0;
            }

            p_dest->value_type = GATTC_READ_VALUE_TYPE_VALUE;
            break;
    }

    return len;
}

/*******************************************************************************
 * Encrypted link map handling
 *******************************************************************************/

static void btif_gatt_set_encryption_cb (BD_ADDR bd_addr, tBTA_TRANSPORT transport, tBTA_STATUS result);

static BOOLEAN btif_gatt_is_link_encrypted (BD_ADDR bd_addr)
{
    if (bd_addr == NULL)
        return FALSE;

    return BTA_JvIsEncrypted(bd_addr);
}

static void btif_gatt_set_encryption_cb (BD_ADDR bd_addr, tBTA_TRANSPORT transport, tBTA_STATUS result)
{
    UNUSED(transport);

    if (result != BTA_SUCCESS && result != BTA_BUSY)
    {
        bt_bdaddr_t bda;
        bdcpy(bda.address, bd_addr);

        btif_dm_remove_bond(&bda);
    }
}

void btif_gatt_check_encrypted_link (BD_ADDR bd_addr)
{
    char buf[100];

    bt_bdaddr_t bda;
    bdcpy(bda.address, bd_addr);
    int device_type = 0;
    int addr_type = 0;

#if (!defined(BLE_DELAY_REQUEST_ENC) || (BLE_DELAY_REQUEST_ENC == FALSE))
    if ((btif_storage_get_ble_bonding_key(&bda, BTIF_DM_LE_KEY_PENC,
                    buf, sizeof(btif_dm_ble_penc_keys_t)) == BT_STATUS_SUCCESS)
        && !btif_gatt_is_link_encrypted(bd_addr))
    {
        tBTA_GATT_TRANSPORT transport = BTA_GATT_TRANSPORT_LE;

        btif_get_device_type(bd_addr, &addr_type, &device_type);
        switch(device_type)
        {
            case BT_DEVICE_TYPE_BREDR:
                transport = BTA_GATT_TRANSPORT_BR_EDR;
                break;

            case BT_DEVICE_TYPE_BLE:
                transport = BTA_GATT_TRANSPORT_LE;
                break;

            case BT_DEVICE_TYPE_DUMO:
                transport = BTA_GATT_TRANSPORT_LE_BR_EDR;
                break;

            default:
                BTIF_TRACE_ERROR1 (" GATT Encrypt :Invalid device type %d",device_type);
                return;
        }
        BTA_DmSetEncryption(bd_addr,transport,
                            &btif_gatt_set_encryption_cb, BTM_BLE_SEC_ENCRYPT);
    }
#endif
}

/*******************************************************************************
 * Device information
 *******************************************************************************/

BOOLEAN btif_get_device_type(BD_ADDR bd_addr, int *addr_type, int *device_type)
{
    if (device_type == NULL || addr_type == NULL)
        return FALSE;

    bt_bdaddr_t bda;
    bdcpy(bda.address, bd_addr);

    char bd_addr_str[18] = {0};
    bd2str(&bda, &bd_addr_str);

    if (!btif_config_get_int("Remote", bd_addr_str, "DevType", device_type))
        return FALSE;

    if (!btif_config_get_int("Remote", bd_addr_str, "AddrType", addr_type))
        return FALSE;

    ALOGD("%s: Device [%s] type %d, addr. type %d", __FUNCTION__, bd_addr_str, *device_type, *addr_type);
    return TRUE;
}

#endif
