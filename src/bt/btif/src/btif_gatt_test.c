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

#define LOG_TAG "BtGatt.btif_test"

#include "btif_common.h"
#include "btif_util.h"

#if (defined(BLE_INCLUDED) && (BLE_INCLUDED == TRUE))

#include "bta_api.h"
#include "bta_gatt_api.h"
#include "bd.h"
#include "btif_storage.h"
#include "bte_appl.h"

#include "btif_gatt.h"
#include "btif_gatt_util.h"
#include "btif_dm.h"

#include "gatt_api.h"

/*******************************************************************************
 * Typedefs & Macros
 *******************************************************************************/

typedef struct
{
    tGATT_IF    gatt_if;
    UINT16      conn_id;
} btif_test_cb_t;

/*******************************************************************************
 * Static variables
 *******************************************************************************/

static const char * disc_name[GATT_DISC_MAX] =
{
    "Unknown",
    "GATT_DISC_SRVC_ALL",
    "GATT_DISC_SRVC_BY_UUID",
    "GATT_DISC_INC_SRVC",
    "GATT_DISC_CHAR",
    "GATT_DISC_CHAR_DSCPT"
};

static btif_test_cb_t test_cb;

/*******************************************************************************
 * Callback functions
 *******************************************************************************/

static char * format_uuid(tBT_UUID bt_uuid, char *str_buf)
{
    int x = 0;

    if (bt_uuid.len == LEN_UUID_16)
    {
        sprintf(str_buf, "0x%04x", bt_uuid.uu.uuid16);
    }
    else if (bt_uuid.len == LEN_UUID_128)
    {
        x += sprintf(&str_buf[x], "%02x%02x%02x%02x-%02x%02x-%02x%02x",
                bt_uuid.uu.uuid128[15], bt_uuid.uu.uuid128[14],
                bt_uuid.uu.uuid128[13], bt_uuid.uu.uuid128[12],
                bt_uuid.uu.uuid128[11], bt_uuid.uu.uuid128[10],
                bt_uuid.uu.uuid128[9], bt_uuid.uu.uuid128[8]);
        sprintf(&str_buf[x], "%02x%02x-%02x%02x%02x%02x%02x%02x",
                bt_uuid.uu.uuid128[7], bt_uuid.uu.uuid128[6],
                bt_uuid.uu.uuid128[5], bt_uuid.uu.uuid128[4],
                bt_uuid.uu.uuid128[3], bt_uuid.uu.uuid128[2],
                bt_uuid.uu.uuid128[1], bt_uuid.uu.uuid128[0]);
    }
    else
        sprintf(str_buf, "Unknown (len=%d)", bt_uuid.len);

    return str_buf;
}

static void btif_test_connect_cback(tGATT_IF gatt_if, BD_ADDR bda, UINT16 conn_id,
                                    BOOLEAN connected, tGATT_DISCONN_REASON reason, tBT_TRANSPORT transport)
{
    UNUSED(gatt_if);
    UNUSED(bda);
    UNUSED(reason);
    UNUSED (transport);

    ALOGD("%s: conn_id=%d, connected=%d", __FUNCTION__, conn_id, connected);
    test_cb.conn_id = connected ? conn_id : 0;
}

static void btif_test_command_complete_cback(UINT16 conn_id, tGATTC_OPTYPE op,
                                tGATT_STATUS status, tGATT_CL_COMPLETE *p_data)
{
    ALOGD ("%s: op_code=0x%02x, conn_id=0x%x. status=0x%x",
            __FUNCTION__, op, conn_id, status);

    switch (op)
    {
        case GATTC_OPTYPE_READ:
        case GATTC_OPTYPE_WRITE:
        case GATTC_OPTYPE_CONFIG:
        case GATTC_OPTYPE_EXE_WRITE:
        case GATTC_OPTYPE_NOTIFICATION:
            break;

        case GATTC_OPTYPE_INDICATION:
            GATTC_SendHandleValueConfirm(conn_id, p_data->handle);
            break;

        default:
            ALOGD ("%s: Unknown op_code (0x%02x)", __FUNCTION__, op);
            break;
    }
}


static void btif_test_discovery_result_cback(UINT16 conn_id, tGATT_DISC_TYPE disc_type,
                                           tGATT_DISC_RES *p_data)
{
    char    str_buf[50];
    UNUSED(conn_id);

    ALOGD("------ GATT Discovery result %-22s -------", disc_name[disc_type]);
    ALOGD("      Attribute handle: 0x%04x (%d)", p_data->handle, p_data->handle);

    if (disc_type != GATT_DISC_CHAR_DSCPT) {
        ALOGD("        Attribute type: %s", format_uuid(p_data->type, str_buf));
    }

    switch (disc_type)
    {
        case GATT_DISC_SRVC_ALL:
            ALOGD("          Handle range: 0x%04x ~ 0x%04x (%d ~ %d)",
                  p_data->handle, p_data->value.group_value.e_handle,
                  p_data->handle, p_data->value.group_value.e_handle);
            ALOGD("          Service UUID: %s",
                    format_uuid(p_data->value.group_value.service_type, str_buf));
            break;

        case GATT_DISC_SRVC_BY_UUID:
            ALOGD("          Handle range: 0x%04x ~ 0x%04x (%d ~ %d)",
                  p_data->handle, p_data->value.handle,
                  p_data->handle, p_data->value.handle);
            break;

        case GATT_DISC_INC_SRVC:
            ALOGD("          Handle range: 0x%04x ~ 0x%04x (%d ~ %d)",
                  p_data->value.incl_service.s_handle, p_data->value.incl_service.e_handle,
                  p_data->value.incl_service.s_handle, p_data->value.incl_service.e_handle);
            ALOGD("          Service UUID: %s",
                  format_uuid(p_data->value.incl_service.service_type, str_buf));
            break;

        case GATT_DISC_CHAR:
            ALOGD("            Properties: 0x%02x",
                  p_data->value.dclr_value.char_prop);
            ALOGD("   Characteristic UUID: %s",
                  format_uuid(p_data->value.dclr_value.char_uuid, str_buf));
            break;

        case GATT_DISC_CHAR_DSCPT:
            ALOGD("       Descriptor UUID: %s", format_uuid(p_data->type, str_buf));
            break;
    }

    ALOGD("-----------------------------------------------------------");
}

static void btif_test_discovery_complete_cback(UINT16 conn_id,
                                               tGATT_DISC_TYPE disc_type,
                                               tGATT_STATUS status)
{
    UNUSED(conn_id);
    UNUSED(disc_type);
    ALOGD("%s: status=%d", __FUNCTION__, status);
}

static tGATT_CBACK btif_test_callbacks =
{
    btif_test_connect_cback ,
    btif_test_command_complete_cback,
    btif_test_discovery_result_cback,
    btif_test_discovery_complete_cback,
    NULL,
    NULL
};

/*******************************************************************************
 * Implementation
 *******************************************************************************/

bt_status_t btif_gattc_test_command_impl(uint16_t command, btgatt_test_params_t* params)
{
    switch(command) {
        case 0x01: /* Enable */
        {
            ALOGD("%s: ENABLE - enable=%d", __FUNCTION__, params->u1);
            if (params->u1)
            {
                tBT_UUID app_uuid = {LEN_UUID_128,{0xAE}};
                test_cb.gatt_if = GATT_Register(&app_uuid, &btif_test_callbacks);
                GATT_StartIf(test_cb.gatt_if);
            } else {
                GATT_Deregister(test_cb.gatt_if);
                test_cb.gatt_if = 0;
            }
            break;
        }

        case 0x02: /* Connect */
        {
            ALOGD("%s: CONNECT - device=%02x:%02x:%02x:%02x:%02x:%02x (dev_type=%d)",
                __FUNCTION__,
                params->bda1->address[0], params->bda1->address[1],
                params->bda1->address[2], params->bda1->address[3],
                params->bda1->address[4], params->bda1->address[5],
                params->u1);

            if (params->u1 == BT_DEVICE_TYPE_BLE)
                BTM_SecAddBleDevice(params->bda1->address, NULL, BT_DEVICE_TYPE_BLE, 0);

            if ( !GATT_Connect(test_cb.gatt_if, params->bda1->address, TRUE, BT_TRANSPORT_LE) )
            {
                ALOGE("%s: GATT_Connect failed!", __FUNCTION__);
            }
            break;
        }

        case 0x03: /* Disconnect */
        {
            ALOGD("%s: DISCONNECT - conn_id=%d", __FUNCTION__, test_cb.conn_id);
            GATT_Disconnect(test_cb.conn_id);
            break;
        }

        case 0x04: /* Discover */
        {
            char buf[50] = {0};
            tGATT_DISC_PARAM        param;
            memset(&param, 0, sizeof(tGATT_DISC_PARAM));

            if (params->u1 >= GATT_DISC_MAX)
            {
                ALOGE("%s: DISCOVER - Invalid type (%d)!", __FUNCTION__, params->u1);
                return 0;
            }

            param.s_handle = params->u2;
            param.e_handle = params->u3;
            btif_to_bta_uuid(&param.service, params->uuid1);

            ALOGD("%s: DISCOVER (%s), conn_id=%d, uuid=%s, handles=0x%04x-0x%04x",
                  __FUNCTION__, disc_name[params->u1], test_cb.conn_id,
                  format_uuid(param.service, buf), params->u2, params->u3);
            GATTC_Discover(test_cb.conn_id, params->u1, &param);
            break;
        }

        case 0xF0: /* Pairing configuration */
            ALOGD("%s: Setting pairing config auth=%d, iocaps=%d, keys=%d/%d/%d",
                  __FUNCTION__, params->u1, params->u2, params->u3, params->u4,
                  params->u5);

            bte_appl_cfg.ble_auth_req = params->u1;
            bte_appl_cfg.ble_io_cap = params->u2;
            bte_appl_cfg.ble_init_key = params->u3;
            bte_appl_cfg.ble_resp_key = params->u4;
            bte_appl_cfg.ble_max_key_size = params->u5;
            break;

        default:
            ALOGE("%s: UNKNOWN TEST COMMAND 0x%02x", __FUNCTION__, command);
            break;
    }
    return 0;
}

#endif
