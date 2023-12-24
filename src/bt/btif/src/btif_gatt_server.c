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


/************************************************************************************
 *
 *  Filename:      btif_gatt_server.c
 *
 *  Description:   GATT server implementation
 *
 ***********************************************************************************/

#include <hardware/bluetooth.h>
#include <hardware/bt_gatt.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define LOG_TAG "BtGatt.btif"

#include "btif_common.h"
#include "btif_util.h"

#if (defined(BLE_INCLUDED) && (BLE_INCLUDED == TRUE))

#include "gki.h"
#include "bta_api.h"
#include "bta_gatt_api.h"
#include "bd.h"
#include "btif_dm.h"
#include "btif_storage.h"

#include "btif_gatt.h"
#include "btif_gatt_util.h"

/************************************************************************************
**  Constants & Macros
************************************************************************************/

#define CHECK_BTGATT_INIT() if (bt_gatt_callbacks == NULL)\
    {\
        ALOGW("%s: BTGATT not initialized", __FUNCTION__);\
        return BT_STATUS_NOT_READY;\
    } else {\
        ALOGD("%s", __FUNCTION__);\
    }


typedef enum {
    BTIF_GATTS_REGISTER_APP = 2000,
    BTIF_GATTS_UNREGISTER_APP,
    BTIF_GATTS_OPEN,
    BTIF_GATTS_CLOSE,
    BTIF_GATTS_CREATE_SERVICE,
    BTIF_GATTS_ADD_INCLUDED_SERVICE,
    BTIF_GATTS_ADD_CHARACTERISTIC,
    BTIF_GATTS_ADD_DESCRIPTOR,
    BTIF_GATTS_START_SERVICE,
    BTIF_GATTS_STOP_SERVICE,
    BTIF_GATTS_DELETE_SERVICE,
    BTIF_GATTS_SEND_INDICATION,
    BTIF_GATTS_SEND_RESPONSE
} btif_gatts_event_t;

/************************************************************************************
**  Local type definitions
************************************************************************************/

typedef struct
{
    uint8_t             value[BTGATT_MAX_ATTR_LEN];
    btgatt_response_t   response;
    btgatt_srvc_id_t    srvc_id;
    bt_bdaddr_t         bd_addr;
    bt_uuid_t           uuid;
    uint32_t            trans_id;
    uint16_t            conn_id;
    uint16_t            srvc_handle;
    uint16_t            incl_handle;
    uint16_t            attr_handle;
    uint16_t            permissions;
    uint16_t            len;
    uint8_t             server_if;
    uint8_t             is_direct;
    uint8_t             num_handles;
    uint8_t             properties;
    uint8_t             confirm;
    uint8_t             status;
    btgatt_transport_t  transport;

} __attribute__((packed)) btif_gatts_cb_t;


/************************************************************************************
**  Static variables
************************************************************************************/

extern const btgatt_callbacks_t *bt_gatt_callbacks;


/************************************************************************************
**  Static functions
************************************************************************************/

static void btapp_gatts_copy_req_data(UINT16 event, char *p_dest, char *p_src)
{
    tBTA_GATTS *p_dest_data = (tBTA_GATTS*) p_dest;
    tBTA_GATTS *p_src_data = (tBTA_GATTS*) p_src;

    if (!p_src_data || !p_dest_data)
        return;

    // Copy basic structure first
    memcpy(p_dest_data, p_src_data, sizeof(tBTA_GATTS));

    // Allocate buffer for request data if necessary
    switch (event)
    {
        case BTA_GATTS_READ_EVT:
        case BTA_GATTS_WRITE_EVT:
        case BTA_GATTS_EXEC_WRITE_EVT:
        case BTA_GATTS_MTU_EVT:
            p_dest_data->req_data.p_data = GKI_getbuf(sizeof(tBTA_GATTS_REQ_DATA));
            if (p_dest_data->req_data.p_data != NULL)
            {
                memcpy(p_dest_data->req_data.p_data, p_src_data->req_data.p_data,
                    sizeof(tBTA_GATTS_REQ_DATA));
            }
            break;

        default:
            break;
    }
}

static void btapp_gatts_free_req_data(UINT16 event, tBTA_GATTS *p_data)
{
    switch (event)
    {
        case BTA_GATTS_READ_EVT:
        case BTA_GATTS_WRITE_EVT:
        case BTA_GATTS_EXEC_WRITE_EVT:
        case BTA_GATTS_MTU_EVT:
            if (p_data && p_data->req_data.p_data)
                GKI_freebuf(p_data->req_data.p_data);
            break;

        default:
            break;
    }
}

static void btapp_gatts_handle_cback(uint16_t event, char* p_param)
{
    ALOGD("%s: Event %d", __FUNCTION__, event);

    tBTA_GATTS *p_data = (tBTA_GATTS*)p_param;
    switch (event)
    {
        case BTA_GATTS_REG_EVT:
        {
            bt_uuid_t app_uuid;
            bta_to_btif_uuid(&app_uuid, &p_data->reg_oper.uuid);
            HAL_CBACK(bt_gatt_callbacks, server->register_server_cb
                , p_data->reg_oper.status
                , p_data->reg_oper.server_if
                , &app_uuid
            );
            break;
        }

        case BTA_GATTS_DEREG_EVT:
            break;

        case BTA_GATTS_CONNECT_EVT:
        {
            bt_bdaddr_t bda;
            bdcpy(bda.address, p_data->conn.remote_bda);

            btif_gatt_check_encrypted_link(p_data->conn.remote_bda);

            HAL_CBACK(bt_gatt_callbacks, server->connection_cb,
                      p_data->conn.conn_id, p_data->conn.server_if, TRUE, &bda);
            break;
        }

        case BTA_GATTS_DISCONNECT_EVT:
        {
            bt_bdaddr_t bda;
            bdcpy(bda.address, p_data->conn.remote_bda);

            HAL_CBACK(bt_gatt_callbacks, server->connection_cb,
                      p_data->conn.conn_id, p_data->conn.server_if, FALSE, &bda);
            break;
        }

        case BTA_GATTS_CREATE_EVT:
        {
            btgatt_srvc_id_t srvc_id;
            srvc_id.is_primary = p_data->create.is_primary;
            srvc_id.id.inst_id = p_data->create.svc_instance;
            bta_to_btif_uuid(&srvc_id.id.uuid, &p_data->create.uuid);

            HAL_CBACK(bt_gatt_callbacks, server->service_added_cb,
                      p_data->create.status, p_data->create.server_if, &srvc_id,
                      p_data->create.service_id
            );
        }
        break;

        case BTA_GATTS_ADD_INCL_SRVC_EVT:
            HAL_CBACK(bt_gatt_callbacks, server->included_service_added_cb,
                      p_data->add_result.status,
                      p_data->add_result.server_if,
                      p_data->add_result.service_id,
                      p_data->add_result.attr_id);
            break;

        case BTA_GATTS_ADD_CHAR_EVT:
        {
            bt_uuid_t uuid;
            bta_to_btif_uuid(&uuid, &p_data->add_result.char_uuid);

            HAL_CBACK(bt_gatt_callbacks, server->characteristic_added_cb,
                      p_data->add_result.status,
                      p_data->add_result.server_if,
                      &uuid,
                      p_data->add_result.service_id,
                      p_data->add_result.attr_id);
            break;
        }

        case BTA_GATTS_ADD_CHAR_DESCR_EVT:
        {
            bt_uuid_t uuid;
            bta_to_btif_uuid(&uuid, &p_data->add_result.char_uuid);

            HAL_CBACK(bt_gatt_callbacks, server->descriptor_added_cb,
                      p_data->add_result.status,
                      p_data->add_result.server_if,
                      &uuid,
                      p_data->add_result.service_id,
                      p_data->add_result.attr_id);
            break;
        }

        case BTA_GATTS_START_EVT:
            HAL_CBACK(bt_gatt_callbacks, server->service_started_cb,
                      p_data->srvc_oper.status,
                      p_data->srvc_oper.server_if,
                      p_data->srvc_oper.service_id);
            break;

        case BTA_GATTS_STOP_EVT:
            HAL_CBACK(bt_gatt_callbacks, server->service_stopped_cb,
                      p_data->srvc_oper.status,
                      p_data->srvc_oper.server_if,
                      p_data->srvc_oper.service_id);
            break;

        case BTA_GATTS_DELELTE_EVT:
            HAL_CBACK(bt_gatt_callbacks, server->service_deleted_cb,
                      p_data->srvc_oper.status,
                      p_data->srvc_oper.server_if,
                      p_data->srvc_oper.service_id);
            break;

        case BTA_GATTS_READ_EVT:
        {
            bt_bdaddr_t bda;
            bdcpy(bda.address, p_data->req_data.remote_bda);

            HAL_CBACK(bt_gatt_callbacks, server->request_read_cb,
                      p_data->req_data.conn_id,p_data->req_data.trans_id, &bda,
                      p_data->req_data.p_data->read_req.handle,
                      p_data->req_data.p_data->read_req.offset,
                      p_data->req_data.p_data->read_req.is_long);
            break;
        }

        case BTA_GATTS_WRITE_EVT:
        {
            bt_bdaddr_t bda;
            bdcpy(bda.address, p_data->req_data.remote_bda);

            HAL_CBACK(bt_gatt_callbacks, server->request_write_cb,
                      p_data->req_data.conn_id,p_data->req_data.trans_id, &bda,
                      p_data->req_data.p_data->write_req.handle,
                      p_data->req_data.p_data->write_req.offset,
                      p_data->req_data.p_data->write_req.len,
                      p_data->req_data.p_data->write_req.need_rsp,
                      p_data->req_data.p_data->write_req.is_prep,
                      p_data->req_data.p_data->write_req.value);
            break;
        }

        case BTA_GATTS_EXEC_WRITE_EVT:
        {
            bt_bdaddr_t bda;
            bdcpy(bda.address, p_data->req_data.remote_bda);

            HAL_CBACK(bt_gatt_callbacks, server->request_exec_write_cb,
                      p_data->req_data.conn_id,p_data->req_data.trans_id, &bda,
                      p_data->req_data.p_data->exec_write);
            break;
        }

        case BTA_GATTS_MTU_EVT:
        case BTA_GATTS_OPEN_EVT:
        case BTA_GATTS_CANCEL_OPEN_EVT:
        case BTA_GATTS_CLOSE_EVT:
            ALOGD("%s: Empty event (%d)!", __FUNCTION__, event);
            break;

        default:
            ALOGE("%s: Unhandled event (%d)!", __FUNCTION__, event);
            break;
    }

    btapp_gatts_free_req_data(event, p_data);
}

static void btapp_gatts_cback(tBTA_GATTS_EVT event, tBTA_GATTS *p_data)
{
    bt_status_t status;
    status = btif_transfer_context(btapp_gatts_handle_cback, (uint16_t) event,
        (void*)p_data, sizeof(tBTA_GATTS), btapp_gatts_copy_req_data);
    ASSERTC(status == BT_STATUS_SUCCESS, "Context transfer failed!", status);
}

static void btgatts_handle_event(uint16_t event, char* p_param)
{
    btif_gatts_cb_t* p_cb = (btif_gatts_cb_t*)p_param;
    if (!p_cb) return;

    ALOGD("%s: Event %d", __FUNCTION__, event);

    switch (event)
    {
        case BTIF_GATTS_REGISTER_APP:
        {
            tBT_UUID uuid;
            btif_to_bta_uuid(&uuid, &p_cb->uuid);
            BTA_GATTS_AppRegister(&uuid, btapp_gatts_cback);
            break;
        }

        case BTIF_GATTS_UNREGISTER_APP:
            BTA_GATTS_AppDeregister(p_cb->server_if);
            break;

        case BTIF_GATTS_OPEN:
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

                default:
                    BTIF_TRACE_ERROR1 (" GATT Open :Invalid device type %d",device_type);
                    return;
            }

            // Connect!
            BTA_GATTS_Open(p_cb->server_if, p_cb->bd_addr.address,
                           p_cb->is_direct, transport);
            break;
        }

        case BTIF_GATTS_CLOSE:
            // Cancel pending foreground/background connections
            BTA_GATTS_CancelOpen(p_cb->server_if, p_cb->bd_addr.address, TRUE);
            BTA_GATTS_CancelOpen(p_cb->server_if, p_cb->bd_addr.address, FALSE);

            // Close active connection
            if (p_cb->conn_id != 0)
                BTA_GATTS_Close(p_cb->conn_id);
            break;

        case BTIF_GATTS_CREATE_SERVICE:
        {
            tBTA_GATT_SRVC_ID srvc_id;
            btif_to_bta_srvc_id(&srvc_id, &p_cb->srvc_id);
            BTA_GATTS_CreateService(p_cb->server_if, &srvc_id.id.uuid,
                                    srvc_id.id.inst_id, p_cb->num_handles,
                                    srvc_id.is_primary);
            break;
        }

        case BTIF_GATTS_ADD_INCLUDED_SERVICE:
            BTA_GATTS_AddIncludeService(p_cb->srvc_handle, p_cb->incl_handle);
            break;

        case BTIF_GATTS_ADD_CHARACTERISTIC:
        {
            tBT_UUID uuid;
            btif_to_bta_uuid(&uuid, &p_cb->uuid);

            BTA_GATTS_AddCharacteristic(p_cb->srvc_handle, &uuid,
                                        p_cb->permissions, p_cb->properties);
            break;
        }

        case BTIF_GATTS_ADD_DESCRIPTOR:
        {
            tBT_UUID uuid;
            btif_to_bta_uuid(&uuid, &p_cb->uuid);

            BTA_GATTS_AddCharDescriptor(p_cb->srvc_handle, p_cb->permissions,
                                         &uuid);
            break;
        }

        case BTIF_GATTS_START_SERVICE:
            BTA_GATTS_StartService(p_cb->srvc_handle, p_cb->transport);
            break;

        case BTIF_GATTS_STOP_SERVICE:
            BTA_GATTS_StopService(p_cb->srvc_handle);
            break;

        case BTIF_GATTS_DELETE_SERVICE:
            BTA_GATTS_DeleteService(p_cb->srvc_handle);
            break;

        case BTIF_GATTS_SEND_INDICATION:
            BTA_GATTS_HandleValueIndication(p_cb->conn_id, p_cb->attr_handle,
                                        p_cb->len, p_cb->value, p_cb->confirm);
            // TODO: Might need to send an ACK if handle value indication is
            //       invoked without need for confirmation.
            break;

        case BTIF_GATTS_SEND_RESPONSE:
        {
            tBTA_GATTS_RSP rsp_struct;
            btgatt_response_t *p_rsp = &p_cb->response;
            btif_to_bta_response(&rsp_struct, p_rsp);

            BTA_GATTS_SendRsp(p_cb->conn_id, p_cb->trans_id,
                              p_cb->status, &rsp_struct);

            HAL_CBACK(bt_gatt_callbacks, server->response_confirmation_cb,
                      0, rsp_struct.attr_value.handle);
            break;
        }

        default:
            ALOGE("%s: Unknown event (%d)!", __FUNCTION__, event);
            break;
    }
}

/************************************************************************************
**  Server API Functions
************************************************************************************/

static bt_status_t btif_gatts_register_app(bt_uuid_t *uuid)
{
    CHECK_BTGATT_INIT();
    btif_gatts_cb_t btif_cb;
    memcpy(&btif_cb.uuid, uuid, sizeof(bt_uuid_t));
    return btif_transfer_context(btgatts_handle_event, BTIF_GATTS_REGISTER_APP,
                                 (char*) &btif_cb, sizeof(btif_gatts_cb_t), NULL);
}

static bt_status_t btif_gatts_unregister_app( int server_if )
{
    CHECK_BTGATT_INIT();
    btif_gatts_cb_t btif_cb;
    btif_cb.server_if = (uint8_t) server_if;
    return btif_transfer_context(btgatts_handle_event, BTIF_GATTS_UNREGISTER_APP,
                                 (char*) &btif_cb, sizeof(btif_gatts_cb_t), NULL);
}

static bt_status_t btif_gatts_open( int server_if, const bt_bdaddr_t *bd_addr,
                                      bool is_direct, int transport )
{
    CHECK_BTGATT_INIT();
    btif_gatts_cb_t btif_cb;
    btif_cb.server_if = (uint8_t) server_if;
    btif_cb.is_direct = is_direct ? 1 : 0;
    btif_cb.transport = (btgatt_transport_t)transport;
    bdcpy(btif_cb.bd_addr.address, bd_addr->address);
    return btif_transfer_context(btgatts_handle_event, BTIF_GATTS_OPEN,
                                 (char*) &btif_cb, sizeof(btif_gatts_cb_t), NULL);
}

static bt_status_t btif_gatts_close(int server_if, const bt_bdaddr_t *bd_addr, int conn_id)
{
    CHECK_BTGATT_INIT();
    btif_gatts_cb_t btif_cb;
    btif_cb.server_if = (uint8_t) server_if;
    btif_cb.conn_id = (uint16_t) conn_id;
    bdcpy(btif_cb.bd_addr.address, bd_addr->address);
    return btif_transfer_context(btgatts_handle_event, BTIF_GATTS_CLOSE,
                                 (char*) &btif_cb, sizeof(btif_gatts_cb_t), NULL);
}

static bt_status_t btif_gatts_add_service(int server_if, btgatt_srvc_id_t *srvc_id,
                                          int num_handles)
{
    CHECK_BTGATT_INIT();
    btif_gatts_cb_t btif_cb;
    btif_cb.server_if = (uint8_t) server_if;
    btif_cb.num_handles = (uint8_t) num_handles;
    memcpy(&btif_cb.srvc_id, srvc_id, sizeof(btgatt_srvc_id_t));
    return btif_transfer_context(btgatts_handle_event, BTIF_GATTS_CREATE_SERVICE,
                                 (char*) &btif_cb, sizeof(btif_gatts_cb_t), NULL);
}

static bt_status_t btif_gatts_add_included_service(int server_if, int service_handle,
                                                   int included_handle)
{
    CHECK_BTGATT_INIT();
    btif_gatts_cb_t btif_cb;
    btif_cb.server_if = (uint8_t) server_if;
    btif_cb.srvc_handle = (uint16_t) service_handle;
    btif_cb.incl_handle = (uint16_t) included_handle;
    return btif_transfer_context(btgatts_handle_event, BTIF_GATTS_ADD_INCLUDED_SERVICE,
                                 (char*) &btif_cb, sizeof(btif_gatts_cb_t), NULL);
}

static bt_status_t btif_gatts_add_characteristic(int server_if, int service_handle,
                                                 bt_uuid_t *uuid, int properties,
                                                 int permissions)
{
    CHECK_BTGATT_INIT();
    btif_gatts_cb_t btif_cb;
    btif_cb.server_if = (uint8_t) server_if;
    btif_cb.srvc_handle = (uint16_t) service_handle;
    btif_cb.properties = (uint8_t) properties;
    btif_cb.permissions = (uint16_t) permissions;
    memcpy(&btif_cb.uuid, uuid, sizeof(bt_uuid_t));
    return btif_transfer_context(btgatts_handle_event, BTIF_GATTS_ADD_CHARACTERISTIC,
                                 (char*) &btif_cb, sizeof(btif_gatts_cb_t), NULL);
}

static bt_status_t btif_gatts_add_descriptor(int server_if, int service_handle, bt_uuid_t *uuid,
                                             int permissions)
{
    CHECK_BTGATT_INIT();
    btif_gatts_cb_t btif_cb;
    btif_cb.server_if = (uint8_t) server_if;
    btif_cb.srvc_handle = (uint16_t) service_handle;
    btif_cb.permissions = (uint16_t) permissions;
    memcpy(&btif_cb.uuid, uuid, sizeof(bt_uuid_t));
    return btif_transfer_context(btgatts_handle_event, BTIF_GATTS_ADD_DESCRIPTOR,
                                 (char*) &btif_cb, sizeof(btif_gatts_cb_t), NULL);
}

static bt_status_t btif_gatts_start_service(int server_if, int service_handle, int transport)
{
    CHECK_BTGATT_INIT();
    btif_gatts_cb_t btif_cb;
    btif_cb.server_if = (uint8_t) server_if;
    btif_cb.srvc_handle = (uint16_t) service_handle;
    btif_cb.transport = (uint8_t) transport;
    return btif_transfer_context(btgatts_handle_event, BTIF_GATTS_START_SERVICE,
                                 (char*) &btif_cb, sizeof(btif_gatts_cb_t), NULL);
}

static bt_status_t btif_gatts_stop_service(int server_if, int service_handle)
{
    CHECK_BTGATT_INIT();
    btif_gatts_cb_t btif_cb;
    btif_cb.server_if = (uint8_t) server_if;
    btif_cb.srvc_handle = (uint16_t) service_handle;
    return btif_transfer_context(btgatts_handle_event, BTIF_GATTS_STOP_SERVICE,
                                 (char*) &btif_cb, sizeof(btif_gatts_cb_t), NULL);
}

static bt_status_t btif_gatts_delete_service(int server_if, int service_handle)
{
    CHECK_BTGATT_INIT();
    btif_gatts_cb_t btif_cb;
    btif_cb.server_if = (uint8_t) server_if;
    btif_cb.srvc_handle = (uint16_t) service_handle;
    return btif_transfer_context(btgatts_handle_event, BTIF_GATTS_DELETE_SERVICE,
                                 (char*) &btif_cb, sizeof(btif_gatts_cb_t), NULL);
}

static bt_status_t btif_gatts_send_indication(int server_if, int attribute_handle, int conn_id,
                                              int len, int confirm, char* p_value)
{
    CHECK_BTGATT_INIT();
    btif_gatts_cb_t btif_cb;
    btif_cb.server_if = (uint8_t) server_if;
    btif_cb.conn_id = (uint16_t) conn_id;
    btif_cb.attr_handle = attribute_handle;
    btif_cb.confirm = confirm;
    btif_cb.len = len;
    memcpy(btif_cb.value, p_value, len > BTGATT_MAX_ATTR_LEN ? BTGATT_MAX_ATTR_LEN : len);
    return btif_transfer_context(btgatts_handle_event, BTIF_GATTS_SEND_INDICATION,
                                 (char*) &btif_cb, sizeof(btif_gatts_cb_t), NULL);
}

static bt_status_t btif_gatts_send_response(int conn_id, int trans_id,
                                            int status, btgatt_response_t *response)
{
    CHECK_BTGATT_INIT();
    btif_gatts_cb_t btif_cb;
    btif_cb.conn_id = (uint16_t) conn_id;
    btif_cb.trans_id = (uint32_t) trans_id;
    btif_cb.status = (uint8_t) status;
    memcpy(&btif_cb.response, response, sizeof(btgatt_response_t));
    return btif_transfer_context(btgatts_handle_event, BTIF_GATTS_SEND_RESPONSE,
                                 (char*) &btif_cb, sizeof(btif_gatts_cb_t), NULL);
}

const btgatt_server_interface_t btgattServerInterface = {
    btif_gatts_register_app,
    btif_gatts_unregister_app,
    btif_gatts_open,
    btif_gatts_close,
    btif_gatts_add_service,
    btif_gatts_add_included_service,
    btif_gatts_add_characteristic,
    btif_gatts_add_descriptor,
    btif_gatts_start_service,
    btif_gatts_stop_service,
    btif_gatts_delete_service,
    btif_gatts_send_indication,
    btif_gatts_send_response
};

#endif
