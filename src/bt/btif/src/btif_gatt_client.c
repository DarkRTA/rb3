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


/*******************************************************************************
 *
 *  Filename:      btif_gatt_client.c
 *
 *  Description:   GATT client implementation
 *
 *******************************************************************************/

#include <hardware/bluetooth.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define LOG_TAG "BtGatt.btif"

#include "btif_common.h"
#include "btif_util.h"

#if (defined(BLE_INCLUDED) && (BLE_INCLUDED == TRUE))

#include "gki.h"
#include <hardware/bt_gatt.h>
#include "bta_api.h"
#include "bta_gatt_api.h"
#include "bd.h"
#include "btif_storage.h"
#include "btif_config.h"

#include "btif_gatt.h"
#include "btif_gatt_util.h"
#include "btif_dm.h"
#include "btif_storage.h"

#include "bta_vendor_api.h"
#include "vendor_api.h"

/*******************************************************************************
**  Constants & Macros
********************************************************************************/

#define ADV_FLAGS 0x02

#define CHECK_BTGATT_INIT() if (bt_gatt_callbacks == NULL)\
    {\
        ALOGW("%s: BTGATT not initialized", __FUNCTION__);\
        return BT_STATUS_NOT_READY;\
    } else {\
        ALOGD("%s", __FUNCTION__);\
    }


typedef enum {
    BTIF_GATTC_REGISTER_APP = 1000,
    BTIF_GATTC_UNREGISTER_APP,
    BTIF_GATTC_SCAN_START,
    BTIF_GATTC_SCAN_STOP,
    BTIF_GATTC_OPEN,
    BTIF_GATTC_CLOSE,
    BTIF_GATTC_SEARCH_SERVICE,
    BTIF_GATTC_GET_FIRST_CHAR,
    BTIF_GATTC_GET_NEXT_CHAR,
    BTIF_GATTC_GET_FIRST_CHAR_DESCR,
    BTIF_GATTC_GET_NEXT_CHAR_DESCR,
    BTIF_GATTC_GET_FIRST_INCL_SERVICE,
    BTIF_GATTC_GET_NEXT_INCL_SERVICE,
    BTIF_GATTC_READ_CHAR,
    BTIF_GATTC_READ_CHAR_DESCR,
    BTIF_GATTC_WRITE_CHAR,
    BTIF_GATTC_WRITE_CHAR_DESCR,
    BTIF_GATTC_EXECUTE_WRITE,
    BTIF_GATTC_REG_FOR_NOTIFICATION,
    BTIF_GATTC_DEREG_FOR_NOTIFICATION,
    BTIF_GATTC_REFRESH,
    BTIF_GATTC_READ_RSSI,
    BTIF_GATTC_LISTEN,
    BTIF_GATTC_SET_ADV_DATA,
    BTIF_GATTC_CONFIGURE_MTU,
    BTIF_GATTC_SCAN_FILTER_ENABLE,
    BTIF_GATTC_SCAN_FILTER_CONFIG,
    BTIF_GATTC_SCAN_FILTER_CLEAR
} btif_gattc_event_t;

#define BTIF_GATT_MAX_OBSERVED_DEV 40

#define BTIF_GATT_OBSERVE_EVT   0x1000
#define BTIF_GATTC_RSSI_EVT     0x1001
#define BTIF_GATTC_SCAN_FILTER_EVT   0x1003

/*******************************************************************************
**  Local type definitions
********************************************************************************/

typedef struct
{
    tBTA_BLE_AD_MASK mask;
    tBTA_BLE_ADV_DATA data;
} btgatt_adv_data;

typedef struct
{
    uint8_t     value[BTGATT_MAX_ATTR_LEN];
    btgatt_adv_data adv_data;
    bt_bdaddr_t bd_addr;
    btgatt_srvc_id_t srvc_id;
    btgatt_srvc_id_t incl_srvc_id;
    btgatt_gatt_id_t char_id;
    btgatt_gatt_id_t descr_id;
    bt_uuid_t   uuid;
    bt_uuid_t   uuid_mask;
    uint16_t    conn_id;
    uint16_t    len;
    uint16_t    mask;
    uint8_t     client_if;
    uint8_t     action;
    uint8_t     is_direct;
    uint8_t     search_all;
    uint8_t     auth_req;
    uint8_t     write_type;
    uint8_t     status;
    uint8_t     addr_type;
    uint8_t     start;
    uint8_t     has_mask;
    int8_t      rssi;
    uint8_t     flag;
    tBT_DEVICE_TYPE device_type;
    btgatt_transport_t transport;
} __attribute__((packed)) btif_gattc_cb_t;

typedef struct
{
    bt_bdaddr_t bd_addr;
    BOOLEAN     in_use;
}__attribute__((packed)) btif_gattc_dev_t;

typedef struct
{
    btif_gattc_dev_t remote_dev[BTIF_GATT_MAX_OBSERVED_DEV];
    uint8_t            addr_type;
    uint8_t            next_storage_idx;
}__attribute__((packed)) btif_gattc_dev_cb_t;

/*******************************************************************************
**  Static variables
********************************************************************************/

extern const btgatt_callbacks_t *bt_gatt_callbacks;
static btif_gattc_dev_cb_t  btif_gattc_dev_cb;
static btif_gattc_dev_cb_t  *p_dev_cb = &btif_gattc_dev_cb;
static uint8_t rssi_request_client_if;

/*******************************************************************************
**  Static functions
********************************************************************************/

static void btapp_gattc_req_data(UINT16 event, char *p_dest, char *p_src)
{
    tBTA_GATTC *p_dest_data = (tBTA_GATTC*)p_dest;
    tBTA_GATTC *p_src_data = (tBTA_GATTC*)p_src;

    if (!p_src_data || !p_dest_data)
       return;

    // Copy basic structure first
    memcpy(p_dest_data, p_src_data, sizeof(tBTA_GATTC));

    // Allocate buffer for request data if necessary
    switch (event)
    {
        case BTA_GATTC_READ_CHAR_EVT:
        case BTA_GATTC_READ_DESCR_EVT:

            if (p_src_data->read.p_value != NULL)
            {
                p_dest_data->read.p_value = GKI_getbuf(sizeof(tBTA_GATT_READ_VAL));

                if (p_dest_data->read.p_value != NULL)
                {
                    memcpy(p_dest_data->read.p_value, p_src_data->read.p_value,
                        sizeof(tBTA_GATT_READ_VAL));

                    // Allocate buffer for att value if necessary
                    if (get_uuid16(&p_src_data->read.descr_type.uuid) != GATT_UUID_CHAR_AGG_FORMAT
                      && p_src_data->read.p_value->unformat.len > 0
                      && p_src_data->read.p_value->unformat.p_value != NULL)
                    {
                        p_dest_data->read.p_value->unformat.p_value =
                                       GKI_getbuf(p_src_data->read.p_value->unformat.len);
                        if (p_dest_data->read.p_value->unformat.p_value != NULL)
                        {
                            memcpy(p_dest_data->read.p_value->unformat.p_value,
                                   p_src_data->read.p_value->unformat.p_value,
                                   p_src_data->read.p_value->unformat.len);
                        }
                    }
                }
            }
            else
            {
                BTIF_TRACE_WARNING2("%s :Src read.p_value ptr is NULL for event  0x%x",
                                    __FUNCTION__, event);
                p_dest_data->read.p_value = NULL;

            }
            break;

        default:
            break;
    }
}

static void btapp_gattc_free_req_data(UINT16 event, tBTA_GATTC *p_data)
{
    switch (event)
    {
        case BTA_GATTC_READ_CHAR_EVT:
        case BTA_GATTC_READ_DESCR_EVT:
            if (p_data != NULL && p_data->read.p_value != NULL)
            {
                if (get_uuid16 (&p_data->read.descr_type.uuid) != GATT_UUID_CHAR_AGG_FORMAT
                  && p_data->read.p_value->unformat.len > 0
                  && p_data->read.p_value->unformat.p_value != NULL)
                {
                    GKI_freebuf(p_data->read.p_value->unformat.p_value);
                }
                GKI_freebuf(p_data->read.p_value);
            }
            break;

        default:
            break;
    }
}

static void btif_gattc_init_dev_cb(void)
{
    memset(p_dev_cb, 0, sizeof(btif_gattc_dev_cb_t));
}

static void btif_gattc_add_remote_bdaddr (BD_ADDR p_bda, uint8_t addr_type)
{
    BOOLEAN found=FALSE;
    uint8_t i;
    for (i = 0; i < BTIF_GATT_MAX_OBSERVED_DEV; i++)
    {
        if (!p_dev_cb->remote_dev[i].in_use )
        {
            memcpy(p_dev_cb->remote_dev[i].bd_addr.address, p_bda, BD_ADDR_LEN);
            p_dev_cb->addr_type = addr_type;
            p_dev_cb->remote_dev[i].in_use = TRUE;
            ALOGD("%s device added idx=%d", __FUNCTION__, i  );
            break;
        }
    }

    if ( i == BTIF_GATT_MAX_OBSERVED_DEV)
    {
        i= p_dev_cb->next_storage_idx;
        memcpy(p_dev_cb->remote_dev[i].bd_addr.address, p_bda, BD_ADDR_LEN);
        p_dev_cb->addr_type = addr_type;
        p_dev_cb->remote_dev[i].in_use = TRUE;
        ALOGD("%s device overwrite idx=%d", __FUNCTION__, i  );
        p_dev_cb->next_storage_idx++;
        if(p_dev_cb->next_storage_idx >= BTIF_GATT_MAX_OBSERVED_DEV)
               p_dev_cb->next_storage_idx = 0;
    }
}

static BOOLEAN btif_gattc_find_bdaddr (BD_ADDR p_bda)
{
    uint8_t i;
    for (i = 0; i < BTIF_GATT_MAX_OBSERVED_DEV; i++)
    {
        if (p_dev_cb->remote_dev[i].in_use &&
            !memcmp(p_dev_cb->remote_dev[i].bd_addr.address, p_bda, BD_ADDR_LEN))
        {
            return TRUE;
        }
    }
    return FALSE;
}

static void btif_gattc_update_properties ( btif_gattc_cb_t *p_btif_cb )
{
    uint8_t remote_name_len;
    uint8_t *p_eir_remote_name=NULL;
    bt_bdname_t bdname;

    p_eir_remote_name = BTA_CheckEirData(p_btif_cb->value,
                                         BTM_EIR_COMPLETE_LOCAL_NAME_TYPE, &remote_name_len);

    if(p_eir_remote_name == NULL)
    {
        p_eir_remote_name = BTA_CheckEirData(p_btif_cb->value,
                                BT_EIR_SHORTENED_LOCAL_NAME_TYPE, &remote_name_len);
    }

    if(p_eir_remote_name)
    {
         memcpy(bdname.name, p_eir_remote_name, remote_name_len);
         bdname.name[remote_name_len]='\0';

        ALOGD("%s BLE device name=%s len=%d dev_type=%d", __FUNCTION__, bdname.name,
              remote_name_len, p_btif_cb->device_type  );
        btif_dm_update_ble_remote_properties( p_btif_cb->bd_addr.address,   bdname.name,
                                               p_btif_cb->device_type);
    }

    btif_storage_set_remote_addr_type( &p_btif_cb->bd_addr, p_btif_cb->addr_type);
}

static void btif_gattc_upstreams_evt(uint16_t event, char* p_param)
{
    ALOGD("%s: Event %d", __FUNCTION__, event);

    tBTA_GATTC *p_data = (tBTA_GATTC*)p_param;
    switch (event)
    {
        case BTA_GATTC_REG_EVT:
        {
            bt_uuid_t app_uuid;
            bta_to_btif_uuid(&app_uuid, &p_data->reg_oper.app_uuid);
            HAL_CBACK(bt_gatt_callbacks, client->register_client_cb
                , p_data->reg_oper.status
                , p_data->reg_oper.client_if
                , &app_uuid
            );
            break;
        }

        case BTA_GATTC_DEREG_EVT:
            break;

        case BTA_GATTC_READ_CHAR_EVT:
        {
            btgatt_read_params_t data;
            set_read_value(&data, &p_data->read);

            HAL_CBACK(bt_gatt_callbacks, client->read_characteristic_cb
                , p_data->read.conn_id, p_data->read.status, &data);
            break;
        }

        case BTA_GATTC_WRITE_CHAR_EVT:
        case BTA_GATTC_PREP_WRITE_EVT:
        {
            btgatt_write_params_t data;
            bta_to_btif_srvc_id(&data.srvc_id, &p_data->write.srvc_id);
            bta_to_btif_gatt_id(&data.char_id, &p_data->write.char_id);

            HAL_CBACK(bt_gatt_callbacks, client->write_characteristic_cb
                , p_data->write.conn_id, p_data->write.status, &data
            );
            break;
        }

        case BTA_GATTC_EXEC_EVT:
        {
            HAL_CBACK(bt_gatt_callbacks, client->execute_write_cb
                , p_data->exec_cmpl.conn_id, p_data->exec_cmpl.status
            );
            break;
        }

        case BTA_GATTC_SEARCH_CMPL_EVT:
        {
            HAL_CBACK(bt_gatt_callbacks, client->search_complete_cb
                , p_data->search_cmpl.conn_id, p_data->search_cmpl.status);
            break;
        }

        case BTA_GATTC_SEARCH_RES_EVT:
        {
            btgatt_srvc_id_t data;
            bta_to_btif_srvc_id(&data, &(p_data->srvc_res.service_uuid));
            HAL_CBACK(bt_gatt_callbacks, client->search_result_cb
                , p_data->srvc_res.conn_id, &data);
            break;
        }

        case BTA_GATTC_READ_DESCR_EVT:
        {
            btgatt_read_params_t data;
            set_read_value(&data, &p_data->read);

            HAL_CBACK(bt_gatt_callbacks, client->read_descriptor_cb
                , p_data->read.conn_id, p_data->read.status, &data);
            break;
        }

        case BTA_GATTC_WRITE_DESCR_EVT:
        {
            btgatt_write_params_t data;
            bta_to_btif_srvc_id(&data.srvc_id, &p_data->write.srvc_id);
            bta_to_btif_gatt_id(&data.char_id, &p_data->write.char_id);
            bta_to_btif_gatt_id(&data.descr_id, &p_data->write.descr_type);

            HAL_CBACK(bt_gatt_callbacks, client->write_descriptor_cb
                , p_data->write.conn_id, p_data->write.status, &data);
            break;
        }

        case BTA_GATTC_NOTIF_EVT:
        {
            btgatt_notify_params_t data;

            bdcpy(data.bda.address, p_data->notify.bda);

            bta_to_btif_srvc_id(&data.srvc_id, &p_data->notify.char_id.srvc_id);
            bta_to_btif_gatt_id(&data.char_id, &p_data->notify.char_id.char_id);
            memcpy(data.value, p_data->notify.value, p_data->notify.len);

            data.is_notify = p_data->notify.is_notify;
            data.len = p_data->notify.len;

            HAL_CBACK(bt_gatt_callbacks, client->notify_cb
                , p_data->notify.conn_id, &data);

            if (p_data->notify.is_notify == FALSE)
            {
                BTA_GATTC_SendIndConfirm(p_data->notify.conn_id,
                                         &p_data->notify.char_id);
            }
            break;
        }

        case BTA_GATTC_OPEN_EVT:
        {
            bt_bdaddr_t bda;
            bdcpy(bda.address, p_data->open.remote_bda);

            HAL_CBACK(bt_gatt_callbacks, client->open_cb, p_data->open.conn_id
                , p_data->open.status, p_data->open.client_if, &bda);

            if (GATT_DEF_BLE_MTU_SIZE != p_data->open.mtu && p_data->open.mtu)
            {
                HAL_CBACK(bt_gatt_callbacks, client->configure_mtu_cb, p_data->open.conn_id
                    , p_data->open.status , p_data->open.mtu);
            }

            if (p_data->open.status == BTA_GATT_OK)
                btif_gatt_check_encrypted_link(p_data->open.remote_bda);
            break;
        }

        case BTA_GATTC_CLOSE_EVT:
        {
            bt_bdaddr_t bda;
            bdcpy(bda.address, p_data->close.remote_bda);
            HAL_CBACK(bt_gatt_callbacks, client->close_cb, p_data->close.conn_id
                , p_data->status, p_data->close.client_if, &bda);
            break;
        }

        case BTA_GATTC_ACL_EVT:
            ALOGD("BTA_GATTC_ACL_EVT: status = %d", p_data->status);
            /* Ignore for now */
            break;

        case BTA_GATTC_CANCEL_OPEN_EVT:
            break;

        case BTIF_GATT_OBSERVE_EVT:
        {
            btif_gattc_cb_t *p_btif_cb = (btif_gattc_cb_t*)p_param;
            uint8_t remote_name_len;
            uint8_t *p_eir_remote_name=NULL;
            bt_device_type_t dev_type;
            bt_property_t properties;

            p_eir_remote_name = BTA_CheckEirData(p_btif_cb->value,
                                         BTM_EIR_COMPLETE_LOCAL_NAME_TYPE, &remote_name_len);

            if(p_eir_remote_name == NULL)
            {
                p_eir_remote_name = BTA_CheckEirData(p_btif_cb->value,
                                BT_EIR_SHORTENED_LOCAL_NAME_TYPE, &remote_name_len);
            }

            if ((p_btif_cb->addr_type != BLE_ADDR_RANDOM) || (p_eir_remote_name))
            {
               if (!btif_gattc_find_bdaddr(p_btif_cb->bd_addr.address))
               {
                  static const char* exclude_filter[] =
                        {"LinkKey", "LE_KEY_PENC", "LE_KEY_PID", "LE_KEY_PCSRK", "LE_KEY_LENC", "LE_KEY_LCSRK"};

                  btif_gattc_add_remote_bdaddr(p_btif_cb->bd_addr.address, p_btif_cb->addr_type);
                  btif_gattc_update_properties(p_btif_cb);
                  btif_config_filter_remove("Remote", exclude_filter, sizeof(exclude_filter)/sizeof(char*),
                  BTIF_STORAGE_MAX_ALLOWED_REMOTE_DEVICE);
               }

            }

            if (( p_btif_cb->device_type == BT_DEVICE_TYPE_DUMO)&&
               (p_btif_cb->flag & BTA_BLE_DMT_CONTROLLER_SPT) &&
               (p_btif_cb->flag & BTA_BLE_DMT_HOST_SPT))
             {
                btif_storage_set_dmt_support_type (&(p_btif_cb->bd_addr), TRUE);
             }

             dev_type =  p_btif_cb->device_type;
             BTIF_STORAGE_FILL_PROPERTY(&properties,
                        BT_PROPERTY_TYPE_OF_DEVICE, sizeof(dev_type), &dev_type);
             btif_storage_set_remote_device_property(&(p_btif_cb->bd_addr), &properties);

            HAL_CBACK(bt_gatt_callbacks, client->scan_result_cb,
                      &p_btif_cb->bd_addr, p_btif_cb->rssi, p_btif_cb->value);
            break;
        }

        case BTIF_GATTC_RSSI_EVT:
        {
            btif_gattc_cb_t *p_btif_cb = (btif_gattc_cb_t*)p_param;
            HAL_CBACK(bt_gatt_callbacks, client->read_remote_rssi_cb, p_btif_cb->client_if,
                      &p_btif_cb->bd_addr, p_btif_cb->rssi, p_btif_cb->status);
            break;
        }

        case BTA_GATTC_LISTEN_EVT:
        {
            HAL_CBACK(bt_gatt_callbacks, client->listen_cb
                , p_data->reg_oper.status
                , p_data->reg_oper.client_if
            );
            break;
        }

        case BTA_GATTC_CFG_MTU_EVT:
        {
            HAL_CBACK(bt_gatt_callbacks, client->configure_mtu_cb, p_data->cfg_mtu.conn_id
                , p_data->cfg_mtu.status , p_data->cfg_mtu.mtu);
            break;
        }
        case BTIF_GATTC_SCAN_FILTER_EVT:
        {
            btif_gattc_cb_t *p_btif_cb = (btif_gattc_cb_t*)p_param;
            HAL_CBACK(bt_gatt_callbacks, client->scan_filter_cb, p_btif_cb->action,
                      p_btif_cb->status);
            break;
        }

        default:
            ALOGE("%s: Unhandled event (%d)!", __FUNCTION__, event);
            break;
    }

    btapp_gattc_free_req_data(event, p_data);
}

static void bta_gattc_cback(tBTA_GATTC_EVT event, tBTA_GATTC *p_data)
{
    bt_status_t status = btif_transfer_context(btif_gattc_upstreams_evt,
                    (uint16_t) event, (void*)p_data, sizeof(tBTA_GATTC), btapp_gattc_req_data);
    ASSERTC(status == BT_STATUS_SUCCESS, "Context transfer failed!", status);
}

static void bta_scan_results_cb (tBTA_DM_SEARCH_EVT event, tBTA_DM_SEARCH *p_data)
{
    btif_gattc_cb_t btif_cb;
    uint8_t len;

    switch (event)
    {
        case BTA_DM_INQ_RES_EVT:
        {
            bdcpy(btif_cb.bd_addr.address, p_data->inq_res.bd_addr);
            btif_cb.device_type = p_data->inq_res.device_type;
            btif_cb.rssi = p_data->inq_res.rssi;
            btif_cb.addr_type = p_data->inq_res.ble_addr_type;
            btif_cb.flag = p_data->inq_res.flag;
            if (p_data->inq_res.p_eir)
            {
                memcpy(btif_cb.value, p_data->inq_res.p_eir, 62);
                if (BTA_CheckEirData(p_data->inq_res.p_eir, BTM_EIR_COMPLETE_LOCAL_NAME_TYPE,
                                      &len))
                {
                    p_data->inq_res.remt_name_not_required  = TRUE;
                }
            }
        }
        break;

        case BTA_DM_INQ_CMPL_EVT:
        {
            BTIF_TRACE_DEBUG2("%s  BLE observe complete. Num Resp %d",
                              __FUNCTION__,p_data->inq_cmpl.num_resps);
            return;
        }

        default:
        BTIF_TRACE_WARNING2("%s : Unknown event 0x%x", __FUNCTION__, event);
        return;
    }
    btif_transfer_context(btif_gattc_upstreams_evt, BTIF_GATT_OBSERVE_EVT,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static void btm_read_rssi_cb (tBTM_RSSI_RESULTS *p_result)
{
    btif_gattc_cb_t btif_cb;

    bdcpy(btif_cb.bd_addr.address, p_result->rem_bda);
    btif_cb.rssi = p_result->rssi;
    btif_cb.status = p_result->status;
    btif_cb.client_if = rssi_request_client_if;
    btif_transfer_context(btif_gattc_upstreams_evt, BTIF_GATTC_RSSI_EVT,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static void bta_scan_filter_cmpl_cb(tBTA_DM_BLE_PF_EVT event,
                        tBTA_DM_BLE_PF_COND_TYPE cfg_cond, tBTA_STATUS status)
{
    btif_gattc_cb_t btif_cb;
    btif_cb.status = status;
    btif_cb.action = event;
    btif_transfer_context(btif_gattc_upstreams_evt, BTIF_GATTC_SCAN_FILTER_EVT,
                          (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static void btgattc_handle_event(uint16_t event, char* p_param)
{
    tBTA_GATT_STATUS           status;
    tBT_UUID                   uuid;
    tBTA_GATT_SRVC_ID          srvc_id;
    tGATT_CHAR_PROP            out_char_prop;
    tBTA_GATTC_CHAR_ID         in_char_id;
    tBTA_GATTC_CHAR_ID         out_char_id;
    tBTA_GATTC_CHAR_DESCR_ID   in_char_descr_id;
    tBTA_GATTC_CHAR_DESCR_ID   out_char_descr_id;
    tBTA_GATTC_INCL_SVC_ID     in_incl_svc_id;
    tBTA_GATTC_INCL_SVC_ID     out_incl_svc_id;
    tBTA_GATT_UNFMT            descr_val;

    btif_gattc_cb_t* p_cb = (btif_gattc_cb_t*)p_param;
    if (!p_cb) return;

    ALOGD("%s: Event %d", __FUNCTION__, event);

    switch (event)
    {
        case BTIF_GATTC_REGISTER_APP:
            btif_to_bta_uuid(&uuid, &p_cb->uuid);
            BTA_GATTC_AppRegister(&uuid, bta_gattc_cback);
            break;

        case BTIF_GATTC_UNREGISTER_APP:
            BTA_GATTC_AppDeregister(p_cb->client_if);
            break;

        case BTIF_GATTC_SCAN_START:
            btif_gattc_init_dev_cb();
            BTA_DmBleObserve(TRUE, 0, bta_scan_results_cb);
            break;

        case BTIF_GATTC_SCAN_STOP:
            BTA_DmBleObserve(FALSE, 0, 0);
            break;

        case BTIF_GATTC_OPEN:
        {
            // Ensure device is in inquiry database
            int addr_type = 0;
            int device_type = 0;
            tBTA_GATT_TRANSPORT transport = BTA_GATT_TRANSPORT_LE;

            if (btif_get_device_type(p_cb->bd_addr.address, &addr_type, &device_type) == TRUE
                  && device_type != BT_DEVICE_TYPE_BREDR)
                BTA_DmAddBleDevice(p_cb->bd_addr.address, addr_type, device_type);

            // Mark background connections
            if (!p_cb->is_direct)
                BTA_DmBleSetBgConnType(BTM_BLE_CONN_AUTO, NULL);

            switch(device_type)
            {
                case BT_DEVICE_TYPE_BREDR:
                    transport = BTA_GATT_TRANSPORT_BR_EDR;
                    break;

                case BT_DEVICE_TYPE_BLE:
                    transport = BTA_GATT_TRANSPORT_LE;
                    break;

                case BT_DEVICE_TYPE_DUMO:
                    if ((p_cb->transport == GATT_TRANSPORT_LE) &&
                        (btif_storage_is_dmt_supported_device(&(p_cb->bd_addr)) == TRUE))
                        transport = BTA_GATT_TRANSPORT_LE;
                    else
                        transport = BTA_GATT_TRANSPORT_BR_EDR;
                    break;
            }

            // Connect!
            BTIF_TRACE_DEBUG2 ("BTA_GATTC_Open Transport  = %d, dev type = %d",
                                transport, device_type);
            BTA_GATTC_Open(p_cb->client_if, p_cb->bd_addr.address, p_cb->is_direct, transport);
            break;
        }

        case BTIF_GATTC_CLOSE:
            // Disconnect established connections
            if (p_cb->conn_id != 0)
                BTA_GATTC_Close(p_cb->conn_id);
            else
                BTA_GATTC_CancelOpen(p_cb->client_if, p_cb->bd_addr.address, TRUE);

            // Cancel pending background connections (remove from whitelist)
            BTA_GATTC_CancelOpen(p_cb->client_if, p_cb->bd_addr.address, FALSE);
            break;

        case BTIF_GATTC_SEARCH_SERVICE:
        {
            if (p_cb->search_all)
            {
                BTA_GATTC_ServiceSearchRequest(p_cb->conn_id, NULL);
            } else {
                btif_to_bta_uuid(&uuid, &p_cb->uuid);
                BTA_GATTC_ServiceSearchRequest(p_cb->conn_id, &uuid);
            }
            break;
        }

        case BTIF_GATTC_GET_FIRST_CHAR:
        {
            btgatt_gatt_id_t char_id;
            btif_to_bta_srvc_id(&srvc_id, &p_cb->srvc_id);
            status = BTA_GATTC_GetFirstChar(p_cb->conn_id, &srvc_id, NULL,
                                            &out_char_id, &out_char_prop);

            if (status == 0)
                bta_to_btif_gatt_id(&char_id, &out_char_id.char_id);

            HAL_CBACK(bt_gatt_callbacks, client->get_characteristic_cb,
                p_cb->conn_id, status, &p_cb->srvc_id,
                &char_id, out_char_prop);
            break;
        }

        case BTIF_GATTC_GET_NEXT_CHAR:
        {
            btgatt_gatt_id_t char_id;
            btif_to_bta_srvc_id(&in_char_id.srvc_id, &p_cb->srvc_id);
            btif_to_bta_gatt_id(&in_char_id.char_id, &p_cb->char_id);

            status = BTA_GATTC_GetNextChar(p_cb->conn_id, &in_char_id, NULL,
                                            &out_char_id, &out_char_prop);

            if (status == 0)
                bta_to_btif_gatt_id(&char_id, &out_char_id.char_id);

            HAL_CBACK(bt_gatt_callbacks, client->get_characteristic_cb,
                p_cb->conn_id, status, &p_cb->srvc_id,
                &char_id, out_char_prop);
            break;
        }

        case BTIF_GATTC_GET_FIRST_CHAR_DESCR:
        {
            btgatt_gatt_id_t descr_id;
            btif_to_bta_srvc_id(&in_char_id.srvc_id, &p_cb->srvc_id);
            btif_to_bta_gatt_id(&in_char_id.char_id, &p_cb->char_id);

            status = BTA_GATTC_GetFirstCharDescr(p_cb->conn_id, &in_char_id, NULL,
                                                    &out_char_descr_id);

            if (status == 0)
                bta_to_btif_gatt_id(&descr_id, &out_char_descr_id.descr_id);

            HAL_CBACK(bt_gatt_callbacks, client->get_descriptor_cb,
                p_cb->conn_id, status, &p_cb->srvc_id,
                &p_cb->char_id, &descr_id);
            break;
        }

        case BTIF_GATTC_GET_NEXT_CHAR_DESCR:
        {
            btgatt_gatt_id_t descr_id;
            btif_to_bta_srvc_id(&in_char_descr_id.char_id.srvc_id, &p_cb->srvc_id);
            btif_to_bta_gatt_id(&in_char_descr_id.char_id.char_id, &p_cb->char_id);
            btif_to_bta_gatt_id(&in_char_descr_id.descr_id, &p_cb->descr_id);

            status = BTA_GATTC_GetNextCharDescr(p_cb->conn_id, &in_char_descr_id
                                        , NULL, &out_char_descr_id);

            if (status == 0)
                bta_to_btif_gatt_id(&descr_id, &out_char_descr_id.descr_id);

            HAL_CBACK(bt_gatt_callbacks, client->get_descriptor_cb,
                p_cb->conn_id, status, &p_cb->srvc_id,
                &p_cb->char_id, &descr_id);
            break;
        }

        case BTIF_GATTC_GET_FIRST_INCL_SERVICE:
        {
            btgatt_srvc_id_t incl_srvc_id;
            btif_to_bta_srvc_id(&srvc_id, &p_cb->srvc_id);

            status = BTA_GATTC_GetFirstIncludedService(p_cb->conn_id,
                        &srvc_id, NULL, &out_incl_svc_id);

            bta_to_btif_srvc_id(&incl_srvc_id, &out_incl_svc_id.incl_svc_id);

            HAL_CBACK(bt_gatt_callbacks, client->get_included_service_cb,
                p_cb->conn_id, status, &p_cb->srvc_id,
                &incl_srvc_id);
            break;
        }

        case BTIF_GATTC_GET_NEXT_INCL_SERVICE:
        {
            btgatt_srvc_id_t incl_srvc_id;
            btif_to_bta_srvc_id(&in_incl_svc_id.srvc_id, &p_cb->srvc_id);
            btif_to_bta_srvc_id(&in_incl_svc_id.incl_svc_id, &p_cb->incl_srvc_id);

            status = BTA_GATTC_GetNextIncludedService(p_cb->conn_id,
                        &in_incl_svc_id, NULL, &out_incl_svc_id);

            bta_to_btif_srvc_id(&incl_srvc_id, &out_incl_svc_id.incl_svc_id);

            HAL_CBACK(bt_gatt_callbacks, client->get_included_service_cb,
                p_cb->conn_id, status, &p_cb->srvc_id,
                &incl_srvc_id);
            break;
        }

        case BTIF_GATTC_READ_CHAR:
            btif_to_bta_srvc_id(&in_char_id.srvc_id, &p_cb->srvc_id);
            btif_to_bta_gatt_id(&in_char_id.char_id, &p_cb->char_id);

            BTA_GATTC_ReadCharacteristic(p_cb->conn_id, &in_char_id, p_cb->auth_req);
            break;

        case BTIF_GATTC_READ_CHAR_DESCR:
            btif_to_bta_srvc_id(&in_char_descr_id.char_id.srvc_id, &p_cb->srvc_id);
            btif_to_bta_gatt_id(&in_char_descr_id.char_id.char_id, &p_cb->char_id);
            btif_to_bta_gatt_id(&in_char_descr_id.descr_id, &p_cb->descr_id);

            BTA_GATTC_ReadCharDescr(p_cb->conn_id, &in_char_descr_id, p_cb->auth_req);
            break;

        case BTIF_GATTC_WRITE_CHAR:
            btif_to_bta_srvc_id(&in_char_id.srvc_id, &p_cb->srvc_id);
            btif_to_bta_gatt_id(&in_char_id.char_id, &p_cb->char_id);

            BTA_GATTC_WriteCharValue(p_cb->conn_id, &in_char_id,
                                     p_cb->write_type,
                                     p_cb->len,
                                     p_cb->value,
                                     p_cb->auth_req);
            break;

        case BTIF_GATTC_WRITE_CHAR_DESCR:
            btif_to_bta_srvc_id(&in_char_descr_id.char_id.srvc_id, &p_cb->srvc_id);
            btif_to_bta_gatt_id(&in_char_descr_id.char_id.char_id, &p_cb->char_id);
            btif_to_bta_gatt_id(&in_char_descr_id.descr_id, &p_cb->descr_id);

            descr_val.len = p_cb->len;
            descr_val.p_value = p_cb->value;

            BTA_GATTC_WriteCharDescr(p_cb->conn_id, &in_char_descr_id,
                                     p_cb->write_type, &descr_val,
                                     p_cb->auth_req);
            break;

        case BTIF_GATTC_EXECUTE_WRITE:
            BTA_GATTC_ExecuteWrite(p_cb->conn_id, p_cb->action);
            break;

        case BTIF_GATTC_REG_FOR_NOTIFICATION:
            btif_to_bta_srvc_id(&in_char_id.srvc_id, &p_cb->srvc_id);
            btif_to_bta_gatt_id(&in_char_id.char_id, &p_cb->char_id);

            status = BTA_GATTC_RegisterForNotifications(p_cb->client_if,
                                    p_cb->bd_addr.address, &in_char_id);

            HAL_CBACK(bt_gatt_callbacks, client->register_for_notification_cb,
                p_cb->conn_id, 1, status, &p_cb->srvc_id,
                &p_cb->char_id);
            break;

        case BTIF_GATTC_DEREG_FOR_NOTIFICATION:
            btif_to_bta_srvc_id(&in_char_id.srvc_id, &p_cb->srvc_id);
            btif_to_bta_gatt_id(&in_char_id.char_id, &p_cb->char_id);

            status = BTA_GATTC_DeregisterForNotifications(p_cb->client_if,
                                        p_cb->bd_addr.address, &in_char_id);

            HAL_CBACK(bt_gatt_callbacks, client->register_for_notification_cb,
                p_cb->conn_id, 0, status, &p_cb->srvc_id,
                &p_cb->char_id);
            break;

        case BTIF_GATTC_REFRESH:
            BTA_GATTC_Refresh(p_cb->bd_addr.address);
            break;

        case BTIF_GATTC_READ_RSSI:
            rssi_request_client_if = p_cb->client_if;
            BTM_ReadRSSI (p_cb->bd_addr.address, (tBTM_CMPL_CB *)btm_read_rssi_cb);
            break;

        case BTIF_GATTC_SCAN_FILTER_ENABLE:
            BTA_DmBleEnableFilterCondition(p_cb->action, NULL, bta_scan_filter_cmpl_cb);
            break;

        case BTIF_GATTC_SCAN_FILTER_CONFIG:
        {
            tBTA_DM_BLE_PF_COND_PARAM cond;
            memset(&cond, 0, sizeof(cond));

            switch (p_cb->action)
            {
                case BTA_DM_BLE_PF_ADDR_FILTER: // 0
                    bdcpy(cond.target_addr.bda, p_cb->bd_addr.address);
                    cond.target_addr.type = p_cb->addr_type;
                    BTA_DmBleCfgFilterCondition(BTA_DM_BLE_SCAN_COND_ADD,
                                              p_cb->action, &cond,
                                              bta_scan_filter_cmpl_cb);
                    break;

                case BTA_DM_BLE_PF_SRVC_DATA: // 1
                    BTA_DmBleCfgFilterCondition(BTA_DM_BLE_SCAN_COND_ADD,
                                              p_cb->action, NULL,
                                              bta_scan_filter_cmpl_cb);
                    break;

                case BTA_DM_BLE_PF_SRVC_UUID: // 2
                {
                    tBTA_DM_BLE_PF_COND_MASK uuid_mask;

                    cond.srvc_uuid.p_target_addr = NULL;
                    cond.srvc_uuid.cond_logic = BTA_DM_BLE_PF_LOGIC_AND;
                    btif_to_bta_uuid(&cond.srvc_uuid.uuid, &p_cb->uuid);

                    cond.srvc_uuid.p_uuid_mask = NULL;
                    if (p_cb->has_mask)
                    {
                        btif_to_bta_uuid_mask(&uuid_mask, &p_cb->uuid_mask);
                        cond.srvc_uuid.p_uuid_mask = &uuid_mask;
                    }
                    BTA_DmBleCfgFilterCondition(BTA_DM_BLE_SCAN_COND_ADD,
                                              p_cb->action, &cond,
                                              bta_scan_filter_cmpl_cb);
                    break;
                }

                case BTA_DM_BLE_PF_SRVC_SOL_UUID: // 3
                {
                    cond.solicitate_uuid.p_target_addr = NULL;
                    cond.solicitate_uuid.cond_logic = BTA_DM_BLE_PF_LOGIC_AND;
                    btif_to_bta_uuid(&cond.solicitate_uuid.uuid, &p_cb->uuid);
                    BTA_DmBleCfgFilterCondition(BTA_DM_BLE_SCAN_COND_ADD,
                                              p_cb->action, &cond,
                                              bta_scan_filter_cmpl_cb);
                    break;
                }

                case BTA_DM_BLE_PF_LOCAL_NAME: // 4
                {
                    cond.local_name.data_len = p_cb->len;
                    cond.local_name.p_data = p_cb->value;
                    BTA_DmBleCfgFilterCondition(BTA_DM_BLE_SCAN_COND_ADD,
                                              p_cb->action, &cond,
                                              bta_scan_filter_cmpl_cb);
                    break;
                }

                case BTA_DM_BLE_PF_MANU_DATA: // 5
                {
                    cond.manu_data.company_id = p_cb->conn_id;
                    cond.manu_data.company_id_mask = p_cb->mask;
                    cond.manu_data.data_len = p_cb->len;
                    cond.manu_data.p_pattern = p_cb->value;
                    cond.manu_data.p_pattern_mask = &p_cb->value[p_cb->len];
                    BTA_DmBleCfgFilterCondition(BTA_DM_BLE_SCAN_COND_ADD,
                                              p_cb->action, &cond,
                                              bta_scan_filter_cmpl_cb);
                    break;
                }

                default:
                    ALOGE("%s: Unknown filter type (%d)!", __FUNCTION__, p_cb->action);
                    break;
            }
            break;
        }

        case BTIF_GATTC_SCAN_FILTER_CLEAR:
        {
            BTA_DmBleCfgFilterCondition(BTA_DM_BLE_SCAN_COND_CLEAR, BTA_DM_BLE_PF_TYPE_ALL,
                                      NULL, bta_scan_filter_cmpl_cb);
            break;
        }

        case BTIF_GATTC_LISTEN:
#if (defined(BLE_PERIPHERAL_MODE_SUPPORT) && (BLE_PERIPHERAL_MODE_SUPPORT == TRUE))
            BTA_GATTC_Listen(p_cb->client_if, p_cb->start, NULL);
#else
            BTA_GATTC_Broadcast(p_cb->client_if, p_cb->start);
#endif
            break;

        case BTIF_GATTC_SET_ADV_DATA:
        {
            if (p_cb->start == 0)
                BTA_DmBleSetAdvConfig(p_cb->adv_data.mask, &p_cb->adv_data.data);
            else
                BTA_DmBleSetScanRsp(p_cb->adv_data.mask, &p_cb->adv_data.data);

            // Cleanup ...

            // ... manufacturer data
            if (p_cb->adv_data.data.manu.p_val != NULL)
                GKI_freebuf(p_cb->adv_data.data.manu.p_val);

            // ... service data
            if (p_cb->adv_data.data.p_proprietary != NULL)
            {
                int i = 0;
                tBTA_BLE_PROP_ELEM *p_elem = p_cb->adv_data.data.p_proprietary->p_elem;
                while (i++ != p_cb->adv_data.data.p_proprietary->num_elem && p_elem)
                {
                    if (p_elem->p_val != NULL)
                        GKI_freebuf(p_elem->p_val);
                    ++p_elem;
                }
                if (p_cb->adv_data.data.p_proprietary->p_elem != NULL)
                    GKI_freebuf(p_cb->adv_data.data.p_proprietary->p_elem);
                GKI_freebuf(p_cb->adv_data.data.p_proprietary);
            }

            // ... service list
            if (p_cb->adv_data.data.services.p_uuid != NULL)
                GKI_freebuf(p_cb->adv_data.data.services.p_uuid);

            break;
        }
        case BTIF_GATTC_CONFIGURE_MTU:
            BTA_GATTC_ConfigureMTU(p_cb->conn_id, p_cb->len);
            break;

        default:
            ALOGE("%s: Unknown event (%d)!", __FUNCTION__, event);
            break;
    }
}

/*******************************************************************************
**  Client API Functions
********************************************************************************/

static bt_status_t btif_gattc_register_app(bt_uuid_t *uuid)
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    memcpy(&btif_cb.uuid, uuid, sizeof(bt_uuid_t));
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_REGISTER_APP,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_unregister_app(int client_if )
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    btif_cb.client_if = (uint8_t) client_if;
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_UNREGISTER_APP,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_scan( int client_if, bool start )
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    btif_cb.client_if = (uint8_t) client_if;
    return btif_transfer_context(btgattc_handle_event, start ? BTIF_GATTC_SCAN_START : BTIF_GATTC_SCAN_STOP,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_open(int client_if, const bt_bdaddr_t *bd_addr,
                                        bool is_direct,int transport)
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    btif_cb.client_if = (uint8_t) client_if;
    btif_cb.is_direct = is_direct ? 1 : 0;
    btif_cb.transport = (btgatt_transport_t)transport;
    bdcpy(btif_cb.bd_addr.address, bd_addr->address);
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_OPEN,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_close( int client_if, const bt_bdaddr_t *bd_addr, int conn_id)
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    btif_cb.client_if = (uint8_t) client_if;
    btif_cb.conn_id = (uint16_t) conn_id;
    bdcpy(btif_cb.bd_addr.address, bd_addr->address);
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_CLOSE,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_listen(int client_if, bool start)
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    btif_cb.client_if = (uint8_t) client_if;
    btif_cb.start = start ? 1 : 0;
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_LISTEN,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_set_adv_data(int client_if, bool set_scan_rsp, bool include_name,
                bool include_txpower, int min_interval, int max_interval, int appearance,
                uint16_t manufacturer_len, char* manufacturer_data,
                uint16_t service_data_len, char* service_data,
                uint16_t service_uuid_len, char* service_uuid)
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    memset(&btif_cb, 0, sizeof(btif_gattc_cb_t));
    memset(&btif_cb.adv_data, 0, sizeof(btgatt_adv_data));

    btif_cb.client_if = (uint8_t) client_if;
    btif_cb.start = set_scan_rsp ? 1 : 0;

    if (!set_scan_rsp)
    {
        btif_cb.adv_data.mask = BTM_BLE_AD_BIT_FLAGS;
        btif_cb.adv_data.data.flag = ADV_FLAGS;
    }

    if (include_name)
        btif_cb.adv_data.mask |= BTM_BLE_AD_BIT_DEV_NAME;

    if (include_txpower)
        btif_cb.adv_data.mask |= BTM_BLE_AD_BIT_TX_PWR;

    if (min_interval > 0 && max_interval > 0 && max_interval > min_interval)
    {
        btif_cb.adv_data.mask |= BTM_BLE_AD_BIT_INT_RANGE;
        btif_cb.adv_data.data.int_range.low = min_interval;
        btif_cb.adv_data.data.int_range.hi = max_interval;
    }

    if (appearance != 0)
    {
        btif_cb.adv_data.mask |= BTM_BLE_AD_BIT_APPEARANCE;
        btif_cb.adv_data.data.appearance = appearance;
    }

    if (manufacturer_len > 0 && manufacturer_data != NULL)
    {
        btif_cb.adv_data.data.manu.p_val = GKI_getbuf(manufacturer_len);
        if (btif_cb.adv_data.data.manu.p_val != NULL)
        {
            btif_cb.adv_data.mask |= BTM_BLE_AD_BIT_MANU;
            btif_cb.adv_data.data.manu.len = manufacturer_len;
            memcpy(btif_cb.adv_data.data.manu.p_val, manufacturer_data, manufacturer_len);
        }
    }

    tBTA_BLE_PROP_ELEM *p_elem_service_data = NULL;
    tBTA_BLE_PROP_ELEM *p_elem_service_128 = NULL;

    if (service_data_len > 0 && service_data != NULL)
    {
        p_elem_service_data = GKI_getbuf(sizeof(tBTA_BLE_PROP_ELEM));
        if (p_elem_service_data != NULL)
        {
            p_elem_service_data->p_val = GKI_getbuf(service_data_len);
            if (p_elem_service_data->p_val != NULL)
            {
                p_elem_service_data->adv_type = BTM_BLE_AD_TYPE_SERVICE_DATA;
                p_elem_service_data->len = service_data_len;
                memcpy(p_elem_service_data->p_val, service_data, service_data_len);

            } else {
                GKI_freebuf(p_elem_service_data);
                p_elem_service_data = NULL;
            }
        }
    }

    if (service_uuid_len > 0 && service_uuid != NULL)
    {
        btif_cb.adv_data.data.services.list_cmpl = FALSE;
        btif_cb.adv_data.data.services.num_service = 0;

        btif_cb.adv_data.data.services.p_uuid =
            GKI_getbuf(service_uuid_len / LEN_UUID_128 * LEN_UUID_16);
        if (btif_cb.adv_data.data.services.p_uuid != NULL)
        {
            UINT16 *p_uuid_out = btif_cb.adv_data.data.services.p_uuid;
            while (service_uuid_len >= LEN_UUID_128)
            {
                bt_uuid_t uuid;
                memset(&uuid, 0, sizeof(bt_uuid_t));
                memcpy(&uuid.uu, service_uuid, LEN_UUID_128);

                tBT_UUID bt_uuid;
                memset(&bt_uuid, 0, sizeof(tBT_UUID));
                btif_to_bta_uuid(&bt_uuid, &uuid);

                if (bt_uuid.len == LEN_UUID_16)
                {
                    btif_cb.adv_data.mask |= BTM_BLE_AD_BIT_SERVICE;
                    ++btif_cb.adv_data.data.services.num_service;
                    *p_uuid_out++ = bt_uuid.uu.uuid16;

                } else if (bt_uuid.len == LEN_UUID_128 && p_elem_service_128 == NULL) {
                    /* Currently, only one 128-bit UUID is supported */
                    p_elem_service_128 = GKI_getbuf(sizeof(tBTA_BLE_PROP_ELEM));
                    if (p_elem_service_128 != NULL)
                    {
                        p_elem_service_128->p_val = GKI_getbuf(LEN_UUID_128);
                        if (p_elem_service_128->p_val != NULL)
                        {
                            p_elem_service_128->adv_type = BTM_BLE_AD_TYPE_128SRV_PART;
                            p_elem_service_128->len = LEN_UUID_128;
                            memcpy(p_elem_service_128->p_val, bt_uuid.uu.uuid128, LEN_UUID_128);

                        } else {
                            GKI_freebuf(p_elem_service_128);
                            p_elem_service_128 = NULL;
                        }
                    }
                }

                service_uuid += LEN_UUID_128;
                service_uuid_len -= LEN_UUID_128;
            }
        }
    }

    if (p_elem_service_data != NULL || p_elem_service_128 != NULL)
    {
        btif_cb.adv_data.data.p_proprietary = GKI_getbuf(sizeof(tBTA_BLE_PROPRIETARY));
        if (btif_cb.adv_data.data.p_proprietary != NULL)
        {
            tBTA_BLE_PROPRIETARY *p_prop = btif_cb.adv_data.data.p_proprietary;
            tBTA_BLE_PROP_ELEM *p_elem = NULL;
            p_prop->num_elem = 0;
            btif_cb.adv_data.mask |= BTM_BLE_AD_BIT_PROPRIETARY;

            if (p_elem_service_128 != NULL)
                ++p_prop->num_elem;

            if (p_elem_service_data != NULL)
                ++p_prop->num_elem;

            p_prop->p_elem = GKI_getbuf(sizeof(tBTA_BLE_PROP_ELEM) * p_prop->num_elem);
            p_elem = p_prop->p_elem;

            if (p_elem_service_128 != NULL)
            {
                memcpy(p_elem++, p_elem_service_128, sizeof(tBTA_BLE_PROP_ELEM));
                GKI_freebuf(p_elem_service_128);
            }

            if (p_elem_service_data != NULL)
            {
                memcpy(p_elem++, p_elem_service_data, sizeof(tBTA_BLE_PROP_ELEM));
                GKI_freebuf(p_elem_service_data);
            }
        }
    }

#if (defined(BLE_PERIPHERAL_ADV_NAME) && (BLE_PERIPHERAL_ADV_NAME == TRUE))
    btif_cb.adv_data.mask |= BTM_BLE_AD_BIT_DEV_NAME;
#endif

    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_SET_ADV_DATA,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_refresh( int client_if, const bt_bdaddr_t *bd_addr )
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    btif_cb.client_if = (uint8_t) client_if;
    bdcpy(btif_cb.bd_addr.address, bd_addr->address);
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_REFRESH,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_search_service(int conn_id, bt_uuid_t *filter_uuid )
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    btif_cb.conn_id = (uint16_t) conn_id;
    btif_cb.search_all = filter_uuid ? 0 : 1;
    if (filter_uuid)
        memcpy(&btif_cb.uuid, filter_uuid, sizeof(bt_uuid_t));
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_SEARCH_SERVICE,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_get_characteristic( int conn_id
        , btgatt_srvc_id_t *srvc_id, btgatt_gatt_id_t *start_char_id)
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    btif_cb.conn_id = (uint16_t) conn_id;
    memcpy(&btif_cb.srvc_id, srvc_id, sizeof(btgatt_srvc_id_t));
    if (start_char_id)
    {
        memcpy(&btif_cb.char_id, start_char_id, sizeof(btgatt_gatt_id_t));
        return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_GET_NEXT_CHAR,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
    }
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_GET_FIRST_CHAR,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_get_descriptor( int conn_id
        , btgatt_srvc_id_t *srvc_id, btgatt_gatt_id_t *char_id
        , btgatt_gatt_id_t *start_descr_id)
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    btif_cb.conn_id = (uint16_t) conn_id;
    memcpy(&btif_cb.srvc_id, srvc_id, sizeof(btgatt_srvc_id_t));
    memcpy(&btif_cb.char_id, char_id, sizeof(btgatt_gatt_id_t));
    if (start_descr_id)
    {
        memcpy(&btif_cb.descr_id, start_descr_id, sizeof(btgatt_gatt_id_t));
        return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_GET_NEXT_CHAR_DESCR,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
    }

    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_GET_FIRST_CHAR_DESCR,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_get_included_service(int conn_id, btgatt_srvc_id_t *srvc_id,
                                                   btgatt_srvc_id_t *start_incl_srvc_id)
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    btif_cb.conn_id = (uint16_t) conn_id;
    memcpy(&btif_cb.srvc_id, srvc_id, sizeof(btgatt_srvc_id_t));
    if (start_incl_srvc_id)
    {
        memcpy(&btif_cb.incl_srvc_id, start_incl_srvc_id, sizeof(btgatt_srvc_id_t));
        return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_GET_NEXT_INCL_SERVICE,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
    }
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_GET_FIRST_INCL_SERVICE,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_read_char(int conn_id, btgatt_srvc_id_t* srvc_id,
                                        btgatt_gatt_id_t* char_id, int auth_req )
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    btif_cb.conn_id = (uint16_t) conn_id;
    btif_cb.auth_req = (uint8_t) auth_req;
    memcpy(&btif_cb.srvc_id, srvc_id, sizeof(btgatt_srvc_id_t));
    memcpy(&btif_cb.char_id, char_id, sizeof(btgatt_gatt_id_t));
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_READ_CHAR,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_read_char_descr(int conn_id, btgatt_srvc_id_t* srvc_id,
                                              btgatt_gatt_id_t* char_id,
                                              btgatt_gatt_id_t* descr_id,
                                              int auth_req )
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    btif_cb.conn_id = (uint16_t) conn_id;
    btif_cb.auth_req = (uint8_t) auth_req;
    memcpy(&btif_cb.srvc_id, srvc_id, sizeof(btgatt_srvc_id_t));
    memcpy(&btif_cb.char_id, char_id, sizeof(btgatt_gatt_id_t));
    memcpy(&btif_cb.descr_id, descr_id, sizeof(btgatt_gatt_id_t));
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_READ_CHAR_DESCR,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_write_char(int conn_id, btgatt_srvc_id_t* srvc_id,
                                         btgatt_gatt_id_t* char_id, int write_type,
                                         int len, int auth_req, char* p_value)
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    btif_cb.conn_id = (uint16_t) conn_id;
    btif_cb.auth_req = (uint8_t) auth_req;
    btif_cb.write_type = (uint8_t) write_type;
    btif_cb.len = len > BTGATT_MAX_ATTR_LEN ? BTGATT_MAX_ATTR_LEN : len;
    memcpy(&btif_cb.srvc_id, srvc_id, sizeof(btgatt_srvc_id_t));
    memcpy(&btif_cb.char_id, char_id, sizeof(btgatt_gatt_id_t));
    memcpy(btif_cb.value, p_value, btif_cb.len);
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_WRITE_CHAR,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_write_char_descr(int conn_id, btgatt_srvc_id_t* srvc_id,
                                               btgatt_gatt_id_t* char_id,
                                               btgatt_gatt_id_t* descr_id,
                                               int write_type, int len, int auth_req,
                                               char* p_value)
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    btif_cb.conn_id = (uint16_t) conn_id;
    btif_cb.auth_req = (uint8_t) auth_req;
    btif_cb.write_type = (uint8_t) write_type;
    btif_cb.len = len > BTGATT_MAX_ATTR_LEN ? BTGATT_MAX_ATTR_LEN : len;
    memcpy(&btif_cb.srvc_id, srvc_id, sizeof(btgatt_srvc_id_t));
    memcpy(&btif_cb.char_id, char_id, sizeof(btgatt_gatt_id_t));
    memcpy(&btif_cb.descr_id, descr_id, sizeof(btgatt_gatt_id_t));
    memcpy(btif_cb.value, p_value, btif_cb.len);
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_WRITE_CHAR_DESCR,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_execute_write(int conn_id, int execute)
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    btif_cb.conn_id = (uint16_t) conn_id;
    btif_cb.action = (uint8_t) execute;
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_EXECUTE_WRITE,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_reg_for_notification(int client_if, const bt_bdaddr_t *bd_addr,
                                                   btgatt_srvc_id_t* srvc_id,
                                                   btgatt_gatt_id_t* char_id)
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    btif_cb.client_if = (uint8_t) client_if;
    bdcpy(btif_cb.bd_addr.address, bd_addr->address);
    memcpy(&btif_cb.srvc_id, srvc_id, sizeof(btgatt_srvc_id_t));
    memcpy(&btif_cb.char_id, char_id, sizeof(btgatt_gatt_id_t));
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_REG_FOR_NOTIFICATION,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_dereg_for_notification(int client_if, const bt_bdaddr_t *bd_addr,
                                                     btgatt_srvc_id_t* srvc_id,
                                                     btgatt_gatt_id_t* char_id)
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    btif_cb.client_if = (uint8_t) client_if;
    bdcpy(btif_cb.bd_addr.address, bd_addr->address);
    memcpy(&btif_cb.srvc_id, srvc_id, sizeof(btgatt_srvc_id_t));
    memcpy(&btif_cb.char_id, char_id, sizeof(btgatt_gatt_id_t));
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_DEREG_FOR_NOTIFICATION,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_read_remote_rssi(int client_if, const bt_bdaddr_t *bd_addr)
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    btif_cb.client_if = (uint8_t) client_if;
    bdcpy(btif_cb.bd_addr.address, bd_addr->address);
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_READ_RSSI,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_configure_mtu(int conn_id, int mtu)
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    btif_cb.conn_id = conn_id;
    btif_cb.len = mtu; // Re-use len field
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_CONFIGURE_MTU,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_scan_filter_enable(int enable )
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    btif_cb.action = enable;
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_SCAN_FILTER_ENABLE,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_scan_filter_add(int type, int company_id, int company_mask,
                              int len, const bt_uuid_t *p_uuid, const bt_uuid_t *p_uuid_mask,
                              const bt_bdaddr_t *bd_addr, char addr_type, const char* p_value)
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;

    if (len > (BTGATT_MAX_ATTR_LEN / 2))
        len = BTGATT_MAX_ATTR_LEN / 2;

    btif_cb.action = type;
    btif_cb.len = len;
    btif_cb.conn_id = company_id;
    btif_cb.mask = company_mask ? company_mask : 0xFFFF;
    if(bd_addr)
      bdcpy(btif_cb.bd_addr.address, bd_addr->address);
    btif_cb.addr_type = addr_type;
    btif_cb.has_mask = (p_uuid_mask != NULL);

    if (p_uuid != NULL)
        memcpy(&btif_cb.uuid, p_uuid, sizeof(bt_uuid_t));
    if (p_uuid_mask != NULL)
        memcpy(&btif_cb.uuid_mask, p_uuid_mask, sizeof(bt_uuid_t));
    if (p_value != NULL && len != 0)
        memcpy(btif_cb.value, p_value, len * 2 /* PATTERN CONTAINS MASK */);
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_SCAN_FILTER_CONFIG,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static bt_status_t btif_gattc_scan_filter_clear()
{
    CHECK_BTGATT_INIT();
    btif_gattc_cb_t btif_cb;
    return btif_transfer_context(btgattc_handle_event, BTIF_GATTC_SCAN_FILTER_CLEAR,
                                 (char*) &btif_cb, sizeof(btif_gattc_cb_t), NULL);
}

static int btif_gattc_get_device_type( const bt_bdaddr_t *bd_addr )
{
    int device_type = 0;
    char bd_addr_str[18] = {0};

    bd2str(bd_addr, &bd_addr_str);
    if (btif_config_get_int("Remote", bd_addr_str, "DevType", &device_type))
        return device_type;
    return 0;
}

extern bt_status_t btif_gattc_test_command_impl(int command, btgatt_test_params_t* params);

static bt_status_t btif_gattc_test_command(int command, btgatt_test_params_t* params)
{
    return btif_gattc_test_command_impl(command, params);
}


const btgatt_client_interface_t btgattClientInterface = {
    btif_gattc_register_app,
    btif_gattc_unregister_app,
    btif_gattc_scan,
    btif_gattc_open,
    btif_gattc_close,
    btif_gattc_listen,
    btif_gattc_refresh,
    btif_gattc_search_service,
    btif_gattc_get_included_service,
    btif_gattc_get_characteristic,
    btif_gattc_get_descriptor,
    btif_gattc_read_char,
    btif_gattc_write_char,
    btif_gattc_read_char_descr,
    btif_gattc_write_char_descr,
    btif_gattc_execute_write,
    btif_gattc_reg_for_notification,
    btif_gattc_dereg_for_notification,
    btif_gattc_read_remote_rssi,
    btif_gattc_scan_filter_enable,
    btif_gattc_scan_filter_add,
    btif_gattc_scan_filter_clear,
    btif_gattc_get_device_type,
    btif_gattc_set_adv_data,
    btif_gattc_configure_mtu,
    btif_gattc_test_command
};

#endif
