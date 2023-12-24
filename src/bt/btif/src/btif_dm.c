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

/************************************************************************************
 *
 *  Filename:      btif_dm.c
 *
 *  Description:   Contains Device Management (DM) related functionality
 *
 *
 ***********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <hardware/bluetooth.h>

#include <utils/Log.h>
#include <cutils/properties.h>
#include "gki.h"
#include "btu.h"
#include "bd.h"
#include "bta_api.h"
#include "btif_api.h"
#include "btif_util.h"
#include "btif_dm.h"
#include "btif_storage.h"
#include "btif_hh.h"
#include "btif_config.h"

#include "bta_gatt_api.h"
/******************************************************************************
**  Constants & Macros
******************************************************************************/

#define COD_UNCLASSIFIED ((0x1F) << 8)
#define COD_HID_KEYBOARD                    0x0540
#define COD_HID_POINTING                    0x0580
#define COD_HID_COMBO                       0x05C0
#define COD_HID_MAJOR                       0x0500
#define COD_AV_HEADSETS                     0x0404
#define COD_AV_HANDSFREE                    0x0408
#define COD_AV_HEADPHONES                   0x0418
#define COD_AV_PORTABLE_AUDIO               0x041C
#define COD_AV_HIFI_AUDIO                   0x0428


#define BTIF_DM_DEFAULT_INQ_MAX_RESULTS     0
#define BTIF_DM_DEFAULT_INQ_MAX_DURATION    10
#define BTIF_DM_MAX_SDP_ATTEMPTS_AFTER_PAIRING 2

#define PROPERTY_PRODUCT_MODEL "ro.product.model"
#define DEFAULT_LOCAL_NAME_MAX  31
#if (DEFAULT_LOCAL_NAME_MAX > BTM_MAX_LOC_BD_NAME_LEN)
    #error "default btif local name size exceeds stack supported length"
#endif

#if (defined(BTA_HOST_INTERLEAVE_SEARCH) && BTA_HOST_INTERLEAVE_SEARCH == TRUE)
#define BTIF_DM_INTERLEAVE_DURATION_BR_ONE    2
#define BTIF_DM_INTERLEAVE_DURATION_LE_ONE    2
#define BTIF_DM_INTERLEAVE_DURATION_BR_TWO    3
#define BTIF_DM_INTERLEAVE_DURATION_LE_TWO    4
#endif

typedef struct
{
    bt_bond_state_t state;
    BD_ADDR bd_addr;
    UINT8   is_temp;
    UINT8   pin_code_len;
    UINT8   is_ssp;
    UINT8   autopair_attempts;
    UINT8   is_local_initiated;
    UINT8   sdp_attempts;
#if (defined(BLE_INCLUDED) && (BLE_INCLUDED == TRUE))
    BOOLEAN          is_le_only;
    btif_dm_ble_cb_t ble;
#endif
} btif_dm_pairing_cb_t;


typedef struct
{
    UINT8       ir[BT_OCTET16_LEN];
    UINT8       irk[BT_OCTET16_LEN];
    UINT8       dhk[BT_OCTET16_LEN];
}btif_dm_local_key_id_t;

typedef struct
{
    BOOLEAN                 is_er_rcvd;
    UINT8                   er[BT_OCTET16_LEN];
    BOOLEAN                 is_id_keys_rcvd;
    btif_dm_local_key_id_t  id_keys;  /* ID kyes */

}btif_dm_local_key_cb_t;

typedef struct
{
    BD_ADDR bd_addr;
    BD_NAME bd_name;
} btif_dm_remote_name_t;

typedef struct
{
    BT_OCTET16 sp_c;
    BT_OCTET16 sp_r;
    BD_ADDR  oob_bdaddr;  /* peer bdaddr*/
} btif_dm_oob_cb_t;
#define BTA_SERVICE_ID_TO_SERVICE_MASK(id)       (1 << (id))

/* This flag will be true if HCI_Inquiry is in progress */
static BOOLEAN btif_dm_inquiry_in_progress = FALSE;

/************************************************************************************
**  Static variables
************************************************************************************/
static char btif_default_local_name[DEFAULT_LOCAL_NAME_MAX+1] = {'\0'};

/******************************************************************************
**  Static functions
******************************************************************************/
static btif_dm_pairing_cb_t pairing_cb;
static btif_dm_oob_cb_t     oob_cb;
static void btif_dm_generic_evt(UINT16 event, char* p_param);
static void btif_dm_cb_create_bond(bt_bdaddr_t *bd_addr);
static void btif_dm_cb_hid_remote_name(tBTM_REMOTE_DEV_NAME *p_remote_name);
static void btif_update_remote_properties(BD_ADDR bd_addr, BD_NAME bd_name,
                                          DEV_CLASS dev_class, tBT_DEVICE_TYPE dev_type);
#if (defined(BLE_INCLUDED) && (BLE_INCLUDED == TRUE))
static btif_dm_local_key_cb_t ble_local_key_cb;
static void btif_dm_ble_key_notif_evt(tBTA_DM_SP_KEY_NOTIF *p_ssp_key_notif);
static void btif_dm_ble_auth_cmpl_evt (tBTA_DM_AUTH_CMPL *p_auth_cmpl);
static void btif_dm_ble_passkey_req_evt(tBTA_DM_PIN_REQ *p_pin_req);
#endif
static char* btif_get_default_local_name();
/******************************************************************************
**  Externs
******************************************************************************/
extern UINT16 bta_service_id_to_uuid_lkup_tbl [BTA_MAX_SERVICE_ID];
extern bt_status_t btif_hf_execute_service(BOOLEAN b_enable);
extern bt_status_t btif_av_execute_service(BOOLEAN b_enable);
extern bt_status_t btif_hh_execute_service(BOOLEAN b_enable);
extern int btif_hh_connect(bt_bdaddr_t *bd_addr);
extern void bta_gatt_convert_uuid16_to_uuid128(UINT8 uuid_128[LEN_UUID_128], UINT16 uuid_16);


/******************************************************************************
**  Functions
******************************************************************************/

bt_status_t btif_in_execute_service_request(tBTA_SERVICE_ID service_id,
                                                BOOLEAN b_enable)
{
    /* Check the service_ID and invoke the profile's BT state changed API */
    switch (service_id)
    {
         case BTA_HFP_SERVICE_ID:
         case BTA_HSP_SERVICE_ID:
         {
              btif_hf_execute_service(b_enable);
         }break;
         case BTA_A2DP_SERVICE_ID:
         {
              btif_av_execute_service(b_enable);
         }break;
         case BTA_HID_SERVICE_ID:
         {
              btif_hh_execute_service(b_enable);
         }break;

         default:
              BTIF_TRACE_ERROR1("%s: Unknown service being enabled", __FUNCTION__);
              return BT_STATUS_FAIL;
    }
    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         check_eir_remote_name
**
** Description      Check if remote name is in the EIR data
**
** Returns          TRUE if remote name found
**                  Populate p_remote_name, if provided and remote name found
**
*******************************************************************************/
static BOOLEAN check_eir_remote_name(tBTA_DM_SEARCH *p_search_data,
                            UINT8 *p_remote_name, UINT8 *p_remote_name_len)
{
    UINT8 *p_eir_remote_name = NULL;
    UINT8 remote_name_len = 0;

    /* Check EIR for remote name and services */
    if (p_search_data->inq_res.p_eir)
    {
        p_eir_remote_name = BTA_CheckEirData(p_search_data->inq_res.p_eir,
                BTM_EIR_COMPLETE_LOCAL_NAME_TYPE, &remote_name_len);
        if (!p_eir_remote_name)
        {
            p_eir_remote_name = BTA_CheckEirData(p_search_data->inq_res.p_eir,
                    BTM_EIR_SHORTENED_LOCAL_NAME_TYPE, &remote_name_len);
        }

        if (p_eir_remote_name)
        {
            if (remote_name_len > BD_NAME_LEN)
                remote_name_len = BD_NAME_LEN;

            if (p_remote_name && p_remote_name_len)
            {
                memcpy(p_remote_name, p_eir_remote_name, remote_name_len);
                *(p_remote_name + remote_name_len) = 0;
                *p_remote_name_len = remote_name_len;
            }

            return TRUE;
        }
    }

    return FALSE;

}

/*******************************************************************************
**
** Function         check_cached_remote_name
**
** Description      Check if remote name is in the NVRAM cache
**
** Returns          TRUE if remote name found
**                  Populate p_remote_name, if provided and remote name found
**
*******************************************************************************/
static BOOLEAN check_cached_remote_name(tBTA_DM_SEARCH *p_search_data,
                                UINT8 *p_remote_name, UINT8 *p_remote_name_len)
{
    bt_bdname_t bdname;
    bt_bdaddr_t remote_bdaddr;
    bt_property_t prop_name;

    /* check if we already have it in our btif_storage cache */
    bdcpy(remote_bdaddr.address, p_search_data->inq_res.bd_addr);
    BTIF_STORAGE_FILL_PROPERTY(&prop_name, BT_PROPERTY_BDNAME,
                               sizeof(bt_bdname_t), &bdname);
    if (btif_storage_get_remote_device_property(
        &remote_bdaddr, &prop_name) == BT_STATUS_SUCCESS)
    {
        if (p_remote_name && p_remote_name_len)
        {
            strcpy((char *)p_remote_name, (char *)bdname.name);
            *p_remote_name_len = strlen((char *)p_remote_name);
        }
        return TRUE;
    }

    return FALSE;
}

BOOLEAN check_cod(const bt_bdaddr_t *remote_bdaddr, uint32_t cod)
{
    uint32_t    remote_cod;
    bt_property_t prop_name;

    /* check if we already have it in our btif_storage cache */
    BTIF_STORAGE_FILL_PROPERTY(&prop_name, BT_PROPERTY_CLASS_OF_DEVICE,
                               sizeof(uint32_t), &remote_cod);
    if (btif_storage_get_remote_device_property((bt_bdaddr_t *)remote_bdaddr, &prop_name) == BT_STATUS_SUCCESS)
    {
        BTIF_TRACE_ERROR2("%s: remote_cod = 0x%06x", __FUNCTION__, remote_cod);
        if ((remote_cod & 0x7ff) == cod)
            return TRUE;
    }

    return FALSE;
}

BOOLEAN check_cod_hid(const bt_bdaddr_t *remote_bdaddr, uint32_t cod)
{
    uint32_t    remote_cod;
    bt_property_t prop_name;

    /* check if we already have it in our btif_storage cache */
    BTIF_STORAGE_FILL_PROPERTY(&prop_name, BT_PROPERTY_CLASS_OF_DEVICE,
                               sizeof(uint32_t), &remote_cod);
    if (btif_storage_get_remote_device_property((bt_bdaddr_t *)remote_bdaddr,
                                &prop_name) == BT_STATUS_SUCCESS)
    {
        BTIF_TRACE_DEBUG2("%s: remote_cod = 0x%06x", __FUNCTION__, remote_cod);
        if ((remote_cod & 0x700) == cod)
            return TRUE;
    }
    return FALSE;
}

BOOLEAN check_hid_le(const bt_bdaddr_t *remote_bdaddr)
{
    uint32_t    remote_dev_type;
    bt_property_t prop_name;

    /* check if we already have it in our btif_storage cache */
    BTIF_STORAGE_FILL_PROPERTY(&prop_name,BT_PROPERTY_TYPE_OF_DEVICE,
                               sizeof(uint32_t), &remote_dev_type);
    if (btif_storage_get_remote_device_property((bt_bdaddr_t *)remote_bdaddr,
                                &prop_name) == BT_STATUS_SUCCESS)
    {
        if (remote_dev_type == BT_DEVICE_DEVTYPE_BLE)
        {
            bdstr_t bdstr;
            bd2str(remote_bdaddr, &bdstr);
            if(btif_config_exist("Remote", bdstr, "HidAppId"))
                return TRUE;
        }
    }
    return FALSE;
}

static void bond_state_changed(bt_status_t status, bt_bdaddr_t *bd_addr, bt_bond_state_t state)
{
    /* Send bonding state only once - based on outgoing/incoming we may receive duplicates */
    if ( (pairing_cb.state == state) && (state == BT_BOND_STATE_BONDING) )
        return;

    if (pairing_cb.is_temp)
    {
       state = BT_BOND_STATE_NONE;
    }
    BTIF_TRACE_DEBUG3("%s: state=%d prev_state=%d", __FUNCTION__, state, pairing_cb.state);

    HAL_CBACK(bt_hal_cbacks, bond_state_changed_cb, status, bd_addr, state);

    if (state == BT_BOND_STATE_BONDING)
    {
        pairing_cb.state = state;
        bdcpy(pairing_cb.bd_addr, bd_addr->address);
    }
    else
    {
        memset(&pairing_cb, 0, sizeof(pairing_cb));
    }

}

/* store remote version in bt config to always have access
   to it post pairing*/
static void btif_update_remote_version_property(bt_bdaddr_t *p_bd)
{
    bt_property_t property;
    UINT8 lmp_ver = 0;
    UINT16 lmp_subver = 0;
    UINT16 mfct_set = 0;
    tBTM_STATUS btm_status;
    bt_remote_version_t info;
    bt_status_t status;
    bdstr_t bdstr;

    btm_status = BTM_ReadRemoteVersion(*(BD_ADDR*)p_bd, &lmp_ver,
                          &mfct_set, &lmp_subver);

    ALOGD("remote version info [%s]: %x, %x, %x", bd2str(p_bd, &bdstr),
               lmp_ver, mfct_set, lmp_subver);

    if (btm_status == BTM_SUCCESS)
    {
        /* always update cache to ensure we have availability whenever BTM API
           is not populated */
        info.manufacturer = mfct_set;
        info.sub_ver = lmp_subver;
        info.version = lmp_ver;
        BTIF_STORAGE_FILL_PROPERTY(&property,
                            BT_PROPERTY_REMOTE_VERSION_INFO, sizeof(bt_remote_version_t),
                            &info);
        status = btif_storage_set_remote_device_property(p_bd, &property);
        ASSERTC(status == BT_STATUS_SUCCESS, "failed to save remote version", status);
    }
}


static void btif_update_remote_properties(BD_ADDR bd_addr, BD_NAME bd_name,
                                          DEV_CLASS dev_class, tBT_DEVICE_TYPE device_type)
{
    int num_properties = 0;
    bt_property_t properties[3];
    bt_bdaddr_t bdaddr;
    bt_status_t status;
    UINT32 cod;
    bt_device_type_t dev_type;

    memset(properties, 0, sizeof(properties));
    bdcpy(bdaddr.address, bd_addr);

    /* remote name */
    if (strlen((const char *) bd_name))
    {
        BTIF_STORAGE_FILL_PROPERTY(&properties[num_properties],
                            BT_PROPERTY_BDNAME, strlen((char *)bd_name), bd_name);
        status = btif_storage_set_remote_device_property(&bdaddr, &properties[num_properties]);
        ASSERTC(status == BT_STATUS_SUCCESS, "failed to save remote device name", status);
        num_properties++;
    }

    /* class of device */
    cod = devclass2uint(dev_class);
    BTIF_TRACE_DEBUG2("%s():cod is 0x%06x", __FUNCTION__, cod);
    if ( cod == 0) {
       /* Try to retrieve cod from storage */
        BTIF_TRACE_DEBUG1("%s():cod is 0, checking cod from storage", __FUNCTION__);
        BTIF_STORAGE_FILL_PROPERTY(&properties[num_properties],
            BT_PROPERTY_CLASS_OF_DEVICE, sizeof(cod), &cod);
        status = btif_storage_get_remote_device_property(&bdaddr, &properties[num_properties]);
        BTIF_TRACE_DEBUG2("%s():cod retreived from storage is 0x%06x", __FUNCTION__, cod);
        if ( cod == 0) {
            BTIF_TRACE_DEBUG1("%s():cod is again 0, set as unclassified", __FUNCTION__);
            cod = COD_UNCLASSIFIED;
        }
    }

    BTIF_STORAGE_FILL_PROPERTY(&properties[num_properties],
                        BT_PROPERTY_CLASS_OF_DEVICE, sizeof(cod), &cod);
    status = btif_storage_set_remote_device_property(&bdaddr, &properties[num_properties]);
    ASSERTC(status == BT_STATUS_SUCCESS, "failed to save remote device class", status);
    num_properties++;

    /* device type */
    dev_type = device_type;
    BTIF_STORAGE_FILL_PROPERTY(&properties[num_properties],
                        BT_PROPERTY_TYPE_OF_DEVICE, sizeof(dev_type), &dev_type);
    status = btif_storage_set_remote_device_property(&bdaddr, &properties[num_properties]);
    ASSERTC(status == BT_STATUS_SUCCESS, "failed to save remote device type", status);
    num_properties++;

    HAL_CBACK(bt_hal_cbacks, remote_device_properties_cb,
                     status, &bdaddr, num_properties, properties);
}
/*******************************************************************************
**
** Function         hid_remote_name_cback
**
** Description      Remote name callback for HID device. Called in stack context
**                  Special handling for HID devices
**
** Returns          void
**
*******************************************************************************/
static void hid_remote_name_cback(void *p_param)
{
    BTIF_TRACE_DEBUG1("%s", __FUNCTION__);

    btif_transfer_context(btif_dm_generic_evt, BTIF_DM_CB_HID_REMOTE_NAME,
        (char *)p_param, sizeof(tBTM_REMOTE_DEV_NAME), NULL);
}

/*******************************************************************************
**
** Function         btif_dm_cb_hid_remote_name
**
** Description      Remote name callback for HID device. Called in btif context
**                  Special handling for HID devices
**
** Returns          void
**
*******************************************************************************/
static void btif_dm_cb_hid_remote_name(tBTM_REMOTE_DEV_NAME *p_remote_name)
{
    BTIF_TRACE_DEBUG3("%s: status=%d pairing_cb.state=%d", __FUNCTION__, p_remote_name->status, pairing_cb.state);
    if (pairing_cb.state == BT_BOND_STATE_BONDING)
    {
        bt_bdaddr_t remote_bd;

        bdcpy(remote_bd.address, pairing_cb.bd_addr);

        if (p_remote_name->status == BTM_SUCCESS)
        {
            bond_state_changed(BT_STATUS_SUCCESS, &remote_bd, BT_BOND_STATE_BONDED);
        }
        else
            bond_state_changed(BT_STATUS_FAIL, &remote_bd, BT_BOND_STATE_NONE);
    }
}

/*******************************************************************************
**
** Function         btif_dm_cb_create_bond
**
** Description      Create bond initiated from the BTIF thread context
**                  Special handling for HID devices
**
** Returns          void
**
*******************************************************************************/
static void btif_dm_cb_create_bond(bt_bdaddr_t *bd_addr)
{
    BOOLEAN is_hid = check_cod(bd_addr, COD_HID_POINTING);


    bond_state_changed(BT_STATUS_SUCCESS, bd_addr, BT_BOND_STATE_BONDING);

    if (is_hid){

            int status;
            status = btif_hh_connect(bd_addr);
            if(status != BT_STATUS_SUCCESS)
                bond_state_changed(status, bd_addr, BT_BOND_STATE_NONE);
    }
    else
    {
#if BLE_INCLUDED == TRUE
        int device_type;
        int addr_type;
        bdstr_t bdstr;
        bd2str(bd_addr, &bdstr);
        if(btif_config_get_int("Remote", (char const *)&bdstr,"DevType", &device_type) &&
           (btif_storage_get_remote_addr_type(bd_addr, &addr_type) == BT_STATUS_SUCCESS) &&
           (device_type == BT_DEVICE_TYPE_BLE))
        {
            BTA_DmAddBleDevice(bd_addr->address, addr_type, BT_DEVICE_TYPE_BLE);
        }
#endif
        BTA_DmBond ((UINT8 *)bd_addr->address);
    }
    /*  Track  originator of bond creation  */
    pairing_cb.is_local_initiated = TRUE;

}

/*******************************************************************************
**
** Function         btif_dm_cb_remove_bond
**
** Description      remove bond initiated from the BTIF thread context
**                  Special handling for HID devices
**
** Returns          void
**
*******************************************************************************/
void btif_dm_cb_remove_bond(bt_bdaddr_t *bd_addr)
{
     bdstr_t bdstr;
     /*special handling for HID devices */
     /*  VUP needs to be sent if its a HID Device. The HID HOST module will check if there
     is a valid hid connection with this bd_addr. If yes VUP will be issued.*/
#if (defined(BTA_HH_INCLUDED) && (BTA_HH_INCLUDED == TRUE))
    if (btif_hh_virtual_unplug(bd_addr) != BT_STATUS_SUCCESS)
#endif
    {
         BTA_DmRemoveDevice((UINT8 *)bd_addr->address);
    }
}

/*******************************************************************************
**
** Function         search_devices_copy_cb
**
** Description      Deep copy callback for search devices event
**
** Returns          void
**
*******************************************************************************/
static void search_devices_copy_cb(UINT16 event, char *p_dest, char *p_src)
{
    tBTA_DM_SEARCH *p_dest_data =  (tBTA_DM_SEARCH *) p_dest;
    tBTA_DM_SEARCH *p_src_data =  (tBTA_DM_SEARCH *) p_src;

    if (!p_src)
        return;

    BTIF_TRACE_DEBUG2("%s: event=%s", __FUNCTION__, dump_dm_search_event(event));
    memcpy(p_dest_data, p_src_data, sizeof(tBTA_DM_SEARCH));
    switch (event)
    {
        case BTA_DM_INQ_RES_EVT:
        {
            if (p_src_data->inq_res.p_eir)
            {
                p_dest_data->inq_res.p_eir = (UINT8 *)(p_dest + sizeof(tBTA_DM_SEARCH));
                memcpy(p_dest_data->inq_res.p_eir, p_src_data->inq_res.p_eir, HCI_EXT_INQ_RESPONSE_LEN);
            }
        }
        break;

        case BTA_DM_DISC_RES_EVT:
        {
            if (p_src_data->disc_res.raw_data_size && p_src_data->disc_res.p_raw_data)
            {
                p_dest_data->disc_res.p_raw_data = (UINT8 *)(p_dest + sizeof(tBTA_DM_SEARCH));
                memcpy(p_dest_data->disc_res.p_raw_data,
                    p_src_data->disc_res.p_raw_data, p_src_data->disc_res.raw_data_size);
            }
        }
        break;
    }
}

static void search_services_copy_cb(UINT16 event, char *p_dest, char *p_src)
{
    tBTA_DM_SEARCH *p_dest_data =  (tBTA_DM_SEARCH *) p_dest;
    tBTA_DM_SEARCH *p_src_data =  (tBTA_DM_SEARCH *) p_src;

    if (!p_src)
        return;
    memcpy(p_dest_data, p_src_data, sizeof(tBTA_DM_SEARCH));
    switch (event)
    {
         case BTA_DM_DISC_RES_EVT:
         {
              if (p_src_data->disc_res.result == BTA_SUCCESS)
              {
                  if (p_src_data->disc_res.num_uuids > 0)
                  {
                       p_dest_data->disc_res.p_uuid_list =
                                                        (UINT8*)(p_dest + sizeof(tBTA_DM_SEARCH));
                       memcpy(p_dest_data->disc_res.p_uuid_list, p_src_data->disc_res.p_uuid_list,
                              p_src_data->disc_res.num_uuids*MAX_UUID_SIZE);
                       GKI_freebuf(p_src_data->disc_res.p_uuid_list);
                  }
                  if (p_src_data->disc_res.p_raw_data != NULL)
                  {
                      GKI_freebuf(p_src_data->disc_res.p_raw_data);
                  }
              }
         } break;
    }
}
/******************************************************************************
**
**  BTIF DM callback events
**
*****************************************************************************/

/*******************************************************************************
**
** Function         btif_dm_pin_req_evt
**
** Description      Executes pin request event in btif context
**
** Returns          void
**
*******************************************************************************/
static void btif_dm_pin_req_evt(tBTA_DM_PIN_REQ *p_pin_req)
{
    bt_bdaddr_t bd_addr;
    bt_bdname_t bd_name;
    UINT32 cod;
    bt_pin_code_t pin_code;

    /* Remote properties update */
    btif_update_remote_properties(p_pin_req->bd_addr, p_pin_req->bd_name,
                                  p_pin_req->dev_class, BT_DEVICE_TYPE_BREDR);

    bdcpy(bd_addr.address, p_pin_req->bd_addr);
    memcpy(bd_name.name, p_pin_req->bd_name, BD_NAME_LEN);

    bond_state_changed(BT_STATUS_SUCCESS, &bd_addr, BT_BOND_STATE_BONDING);

    cod = devclass2uint(p_pin_req->dev_class);

    if ( cod == 0) {
        BTIF_TRACE_DEBUG1("%s():cod is 0, set as unclassified", __FUNCTION__);
        cod = COD_UNCLASSIFIED;
    }

    /* check for auto pair possiblity only if bond was initiated by local device */
    if (pairing_cb.is_local_initiated)
    {
        if (check_cod(&bd_addr, COD_AV_HEADSETS) ||
            check_cod(&bd_addr, COD_AV_HANDSFREE) ||
            check_cod(&bd_addr, COD_AV_HEADPHONES) ||
            check_cod(&bd_addr, COD_AV_PORTABLE_AUDIO) ||
            check_cod(&bd_addr, COD_AV_HIFI_AUDIO) ||
            check_cod(&bd_addr, COD_HID_POINTING))
        {
            BTIF_TRACE_DEBUG1("%s()cod matches for auto pair", __FUNCTION__);
            /*  Check if this device can be auto paired  */
            if ((btif_storage_is_device_autopair_blacklisted(&bd_addr) == FALSE) &&
                (pairing_cb.autopair_attempts == 0))
            {
                BTIF_TRACE_DEBUG1("%s() Attempting auto pair", __FUNCTION__);
                pin_code.pin[0] = 0x30;
                pin_code.pin[1] = 0x30;
                pin_code.pin[2] = 0x30;
                pin_code.pin[3] = 0x30;

                pairing_cb.autopair_attempts++;
                BTA_DmPinReply( (UINT8*)bd_addr.address, TRUE, 4, pin_code.pin);
                return;
            }
        }
        else if (check_cod(&bd_addr, COD_HID_KEYBOARD) ||
                 check_cod(&bd_addr, COD_HID_COMBO))
        {
            if(( btif_storage_is_fixed_pin_zeros_keyboard (&bd_addr) == TRUE) &&
               (pairing_cb.autopair_attempts == 0))
            {
                BTIF_TRACE_DEBUG1("%s() Attempting auto pair", __FUNCTION__);
                pin_code.pin[0] = 0x30;
                pin_code.pin[1] = 0x30;
                pin_code.pin[2] = 0x30;
                pin_code.pin[3] = 0x30;

                pairing_cb.autopair_attempts++;
                BTA_DmPinReply( (UINT8*)bd_addr.address, TRUE, 4, pin_code.pin);
                return;
            }
        }
    }
    HAL_CBACK(bt_hal_cbacks, pin_request_cb,
                     &bd_addr, &bd_name, cod);
}

/*******************************************************************************
**
** Function         btif_dm_ssp_cfm_req_evt
**
** Description      Executes SSP confirm request event in btif context
**
** Returns          void
**
*******************************************************************************/
static void btif_dm_ssp_cfm_req_evt(tBTA_DM_SP_CFM_REQ *p_ssp_cfm_req)
{
    bt_bdaddr_t bd_addr;
    bt_bdname_t bd_name;
    UINT32 cod;
    BOOLEAN is_incoming = !(pairing_cb.state == BT_BOND_STATE_BONDING);

    BTIF_TRACE_DEBUG1("%s", __FUNCTION__);

    /* Remote properties update */
    btif_update_remote_properties(p_ssp_cfm_req->bd_addr, p_ssp_cfm_req->bd_name,
                                  p_ssp_cfm_req->dev_class, BT_DEVICE_TYPE_BREDR);

    bdcpy(bd_addr.address, p_ssp_cfm_req->bd_addr);
    memcpy(bd_name.name, p_ssp_cfm_req->bd_name, BD_NAME_LEN);

    /* Set the pairing_cb based on the local & remote authentication requirements */
    bond_state_changed(BT_STATUS_SUCCESS, &bd_addr, BT_BOND_STATE_BONDING);

    /* if just_works and bonding bit is not set treat this as temporary */
    if (p_ssp_cfm_req->just_works && !(p_ssp_cfm_req->loc_auth_req & BTM_AUTH_BONDS) &&
        !(p_ssp_cfm_req->rmt_auth_req & BTM_AUTH_BONDS) &&
        !(check_cod((bt_bdaddr_t*)&p_ssp_cfm_req->bd_addr, COD_HID_POINTING)))
        pairing_cb.is_temp = TRUE;
    else
        pairing_cb.is_temp = FALSE;

    pairing_cb.is_ssp = TRUE;

    /* If JustWorks auto-accept */
    if (p_ssp_cfm_req->just_works)
    {
        /* Pairing consent for JustWorks needed if:
         * 1. Incoming pairing is detected AND
         * 2. local IO capabilities are DisplayYesNo AND
         * 3. remote IO capabiltiies are DisplayOnly or NoInputNoOutput;
         */
        if ((is_incoming) && ((p_ssp_cfm_req->loc_io_caps == 0x01) &&
                (p_ssp_cfm_req->rmt_io_caps == 0x00 || p_ssp_cfm_req->rmt_io_caps == 0x03)))
        {
            BTIF_TRACE_EVENT3("%s: User consent needed for incoming pairing request. loc_io_caps: %d, rmt_io_caps: %d",
                __FUNCTION__, p_ssp_cfm_req->loc_io_caps, p_ssp_cfm_req->rmt_io_caps);
        }
        else
        {
            BTIF_TRACE_EVENT1("%s: Auto-accept JustWorks pairing", __FUNCTION__);
            btif_dm_ssp_reply(&bd_addr, BT_SSP_VARIANT_CONSENT, TRUE, 0);
            return;
        }
    }

    cod = devclass2uint(p_ssp_cfm_req->dev_class);

    if ( cod == 0) {
        ALOGD("cod is 0, set as unclassified");
        cod = COD_UNCLASSIFIED;
    }

    pairing_cb.sdp_attempts = 0;
    HAL_CBACK(bt_hal_cbacks, ssp_request_cb, &bd_addr, &bd_name, cod,
                     (p_ssp_cfm_req->just_works ? BT_SSP_VARIANT_CONSENT : BT_SSP_VARIANT_PASSKEY_CONFIRMATION),
                     p_ssp_cfm_req->num_val);
}

static void btif_dm_ssp_key_notif_evt(tBTA_DM_SP_KEY_NOTIF *p_ssp_key_notif)
{
    bt_bdaddr_t bd_addr;
    bt_bdname_t bd_name;
    UINT32 cod;

    BTIF_TRACE_DEBUG1("%s", __FUNCTION__);

    /* Remote properties update */
    btif_update_remote_properties(p_ssp_key_notif->bd_addr, p_ssp_key_notif->bd_name,
                                  p_ssp_key_notif->dev_class, BT_DEVICE_TYPE_BREDR);

    bdcpy(bd_addr.address, p_ssp_key_notif->bd_addr);
    memcpy(bd_name.name, p_ssp_key_notif->bd_name, BD_NAME_LEN);

    bond_state_changed(BT_STATUS_SUCCESS, &bd_addr, BT_BOND_STATE_BONDING);
    pairing_cb.is_ssp = TRUE;
    cod = devclass2uint(p_ssp_key_notif->dev_class);

    if ( cod == 0) {
        ALOGD("cod is 0, set as unclassified");
        cod = COD_UNCLASSIFIED;
    }

    HAL_CBACK(bt_hal_cbacks, ssp_request_cb, &bd_addr, &bd_name,
                     cod, BT_SSP_VARIANT_PASSKEY_NOTIFICATION,
                     p_ssp_key_notif->passkey);
}
/*******************************************************************************
**
** Function         btif_dm_auth_cmpl_evt
**
** Description      Executes authentication complete event in btif context
**
** Returns          void
**
*******************************************************************************/
static void btif_dm_auth_cmpl_evt (tBTA_DM_AUTH_CMPL *p_auth_cmpl)
{
    /* Save link key, if not temporary */
    bt_bdaddr_t bd_addr;
    bt_status_t status = BT_STATUS_FAIL;
    bt_bond_state_t state = BT_BOND_STATE_NONE;

    bdcpy(bd_addr.address, p_auth_cmpl->bd_addr);
    if ( (p_auth_cmpl->success == TRUE) && (p_auth_cmpl->key_present) )
    {
        if ((p_auth_cmpl->key_type < HCI_LKEY_TYPE_DEBUG_COMB)  || (p_auth_cmpl->key_type == HCI_LKEY_TYPE_AUTH_COMB) ||
            (p_auth_cmpl->key_type == HCI_LKEY_TYPE_CHANGED_COMB) || (!pairing_cb.is_temp))
        {
            bt_status_t ret;
            BTIF_TRACE_DEBUG3("%s: Storing link key. key_type=0x%x, is_temp=%d",
                __FUNCTION__, p_auth_cmpl->key_type, pairing_cb.is_temp);
            ret = btif_storage_add_bonded_device(&bd_addr,
                                p_auth_cmpl->key, p_auth_cmpl->key_type,
                                pairing_cb.pin_code_len);
            ASSERTC(ret == BT_STATUS_SUCCESS, "storing link key failed", ret);
        }
        else
        {
            BTIF_TRACE_DEBUG3("%s: Temporary key. Not storing. key_type=0x%x, is_temp=%d",
                __FUNCTION__, p_auth_cmpl->key_type, pairing_cb.is_temp);
            if(pairing_cb.is_temp)
            {
                BTIF_TRACE_DEBUG1("%s: sending BT_BOND_STATE_NONE for Temp pairing",
                        __FUNCTION__);
                bond_state_changed(BT_STATUS_SUCCESS, &bd_addr, BT_BOND_STATE_NONE);
                return;
            }
        }
    }
    if (p_auth_cmpl->success)
    {
        status = BT_STATUS_SUCCESS;
        state = BT_BOND_STATE_BONDED;

        /* Trigger SDP on the device */
        pairing_cb.sdp_attempts = 1;;

        if(btif_dm_inquiry_in_progress)
            btif_dm_cancel_discovery();

        btif_dm_get_remote_services(&bd_addr);
        /* Do not call bond_state_changed_cb yet. Wait till fetch remote service is complete */
    }
    else
    {
         /*Map the HCI fail reason  to  bt status  */
        switch(p_auth_cmpl->fail_reason)
        {
            case HCI_ERR_PAGE_TIMEOUT:
            case HCI_ERR_CONNECTION_TOUT:
                status =  BT_STATUS_RMT_DEV_DOWN;
                break;

            /* map the auth failure codes, so we can retry pairing if necessary */
            case HCI_ERR_AUTH_FAILURE:
                btif_storage_remove_bonded_device(&bd_addr);
            case HCI_ERR_HOST_REJECT_SECURITY:
            case HCI_ERR_ENCRY_MODE_NOT_ACCEPTABLE:
            case HCI_ERR_UNIT_KEY_USED:
            case HCI_ERR_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED:
            case HCI_ERR_INSUFFCIENT_SECURITY:
            case HCI_ERR_PEER_USER:
            case HCI_ERR_UNSPECIFIED:
                BTIF_TRACE_DEBUG2(" %s() Authentication fail reason %d",
                    __FUNCTION__, p_auth_cmpl->fail_reason);
                if (pairing_cb.autopair_attempts  == 1)
                {
                    BTIF_TRACE_DEBUG1("%s(): Adding device to blacklist ", __FUNCTION__);

                    /* Add the device to dynamic black list only if this device belongs to Audio/pointing dev class  */
                    if (check_cod(&bd_addr, COD_AV_HEADSETS) ||
                        check_cod(&bd_addr, COD_AV_HANDSFREE) ||
                        check_cod(&bd_addr, COD_AV_HEADPHONES) ||
                        check_cod(&bd_addr, COD_AV_PORTABLE_AUDIO) ||
                        check_cod(&bd_addr, COD_AV_HIFI_AUDIO) ||
                        check_cod(&bd_addr, COD_HID_POINTING))
                    {
                        btif_storage_add_device_to_autopair_blacklist (&bd_addr);
                    }
                    pairing_cb.autopair_attempts++;

                    /* Create the Bond once again */
                    BTIF_TRACE_DEBUG1("%s() auto pair failed. Reinitiate Bond", __FUNCTION__);
                    btif_dm_cb_create_bond (&bd_addr);
                    return;
                }
                else
                {
                    /* if autopair attempts are more than 1, or not attempted */
                    status =  BT_STATUS_AUTH_FAILURE;
                }
                break;

            default:
                status =  BT_STATUS_FAIL;
        }
        /* Special Handling for HID Devices */
        if (check_cod(&bd_addr, COD_HID_POINTING)) {
            /* Remove Device as bonded in nvram as authentication failed */
            BTIF_TRACE_DEBUG1("%s(): removing hid pointing device from nvram", __FUNCTION__);
            btif_storage_remove_bonded_device(&bd_addr);
        }
        bond_state_changed(status, &bd_addr, state);
    }
}

/******************************************************************************
**
** Function         btif_dm_search_devices_evt
**
** Description      Executes search devices callback events in btif context
**
** Returns          void
**
******************************************************************************/
static void btif_dm_search_devices_evt (UINT16 event, char *p_param)
{
    tBTA_DM_SEARCH *p_search_data;
    BTIF_TRACE_EVENT2("%s event=%s", __FUNCTION__, dump_dm_search_event(event));

    switch (event)
    {
        case BTA_DM_DISC_RES_EVT:
        {
            p_search_data = (tBTA_DM_SEARCH *)p_param;
            /* Remote name update */
            if (strlen((const char *) p_search_data->disc_res.bd_name))
            {
                bt_property_t properties[1];
                bt_bdaddr_t bdaddr;
                bt_status_t status;

                properties[0].type = BT_PROPERTY_BDNAME;
                properties[0].val = p_search_data->disc_res.bd_name;
                properties[0].len = strlen((char *)p_search_data->disc_res.bd_name);
                bdcpy(bdaddr.address, p_search_data->disc_res.bd_addr);

                status = btif_storage_set_remote_device_property(&bdaddr, &properties[0]);
                ASSERTC(status == BT_STATUS_SUCCESS, "failed to save remote device property", status);
                HAL_CBACK(bt_hal_cbacks, remote_device_properties_cb,
                                 status, &bdaddr, 1, properties);
            }
            /* TODO: Services? */
        }
        break;

        case BTA_DM_INQ_RES_EVT:
        {
            /* inquiry result */
            UINT32 cod;
            UINT8 *p_eir_remote_name = NULL;
            bt_bdname_t bdname;
            bt_bdaddr_t bdaddr;
            UINT8 remote_name_len;
            UINT8 *p_cached_name = NULL;
            tBTA_SERVICE_MASK services = 0;
            bdstr_t bdstr;

            p_search_data = (tBTA_DM_SEARCH *)p_param;
            bdcpy(bdaddr.address, p_search_data->inq_res.bd_addr);

            BTIF_TRACE_DEBUG3("%s() %s device_type = 0x%x\n", __FUNCTION__, bd2str(&bdaddr, &bdstr),
#if (BLE_INCLUDED == TRUE)
                    p_search_data->inq_res.device_type);
#else
                    BT_DEVICE_TYPE_BREDR);
#endif
            bdname.name[0] = 0;

            cod = devclass2uint (p_search_data->inq_res.dev_class);

            if ( cod == 0) {
                ALOGD("cod is 0, set as unclassified");
                cod = COD_UNCLASSIFIED;
            }

            if (!check_eir_remote_name(p_search_data, bdname.name, &remote_name_len))
                check_cached_remote_name(p_search_data, bdname.name, &remote_name_len);

            /* Check EIR for remote name and services */
            if (p_search_data->inq_res.p_eir)
            {
                BTA_GetEirService(p_search_data->inq_res.p_eir, &services);
                BTIF_TRACE_DEBUG2("%s()EIR BTA services = %08X", __FUNCTION__, (UINT32)services);
                /* TODO:  Get the service list and check to see which uuids we got and send it back to the client. */
            }


            {
                bt_property_t properties[5];
                bt_device_type_t dev_type;
                UINT8 addr_type;
                uint32_t num_properties = 0;
                bt_status_t status;

                memset(properties, 0, sizeof(properties));
                /* BD_ADDR */
                BTIF_STORAGE_FILL_PROPERTY(&properties[num_properties],
                                    BT_PROPERTY_BDADDR, sizeof(bdaddr), &bdaddr);
                num_properties++;
                /* BD_NAME */
                /* Don't send BDNAME if it is empty */
                if (bdname.name[0])
                {
                    BTIF_STORAGE_FILL_PROPERTY(&properties[num_properties],
                                               BT_PROPERTY_BDNAME,
                                               strlen((char *)bdname.name), &bdname);
                    num_properties++;
                }

                /* DEV_CLASS */
                BTIF_STORAGE_FILL_PROPERTY(&properties[num_properties],
                                    BT_PROPERTY_CLASS_OF_DEVICE, sizeof(cod), &cod);
                num_properties++;
                /* DEV_TYPE */
#if (defined(BLE_INCLUDED) && (BLE_INCLUDED == TRUE))
                /* FixMe: Assumption is that bluetooth.h and BTE enums match */
                dev_type = p_search_data->inq_res.device_type;
                addr_type = p_search_data->inq_res.ble_addr_type;
#else
                dev_type = BT_DEVICE_TYPE_BREDR;
#endif
                BTIF_STORAGE_FILL_PROPERTY(&properties[num_properties],
                                    BT_PROPERTY_TYPE_OF_DEVICE, sizeof(dev_type), &dev_type);
                num_properties++;
                /* RSSI */
                BTIF_STORAGE_FILL_PROPERTY(&properties[num_properties],
                                    BT_PROPERTY_REMOTE_RSSI, sizeof(int8_t),
                                    &(p_search_data->inq_res.rssi));
                num_properties++;

                status = btif_storage_add_remote_device(&bdaddr, num_properties, properties);
                ASSERTC(status == BT_STATUS_SUCCESS, "failed to save remote device (inquiry)", status);
#if (defined(BLE_INCLUDED) && (BLE_INCLUDED == TRUE))
                status = btif_storage_set_remote_addr_type(&bdaddr, addr_type);
                if (( dev_type == BT_DEVICE_TYPE_DUMO)&&
                   (p_search_data->inq_res.flag & BTA_BLE_DMT_CONTROLLER_SPT) &&
                   (p_search_data->inq_res.flag & BTA_BLE_DMT_HOST_SPT))
                 {
                    btif_storage_set_dmt_support_type (&bdaddr, TRUE);
                 }
                ASSERTC(status == BT_STATUS_SUCCESS, "failed to save remote addr type (inquiry)", status);
#endif
                /* Callback to notify upper layer of device */
                HAL_CBACK(bt_hal_cbacks, device_found_cb,
                                 num_properties, properties);
            }
        }
        break;

        case BTA_DM_INQ_CMPL_EVT:
        {
        }
        break;
        case BTA_DM_DISC_CMPL_EVT:
        {
            HAL_CBACK(bt_hal_cbacks, discovery_state_changed_cb, BT_DISCOVERY_STOPPED);
        }
        break;
        case BTA_DM_SEARCH_CANCEL_CMPL_EVT:
        {
           /* if inquiry is not in progress and we get a cancel event, then
            * it means we are done with inquiry, but remote_name fetches are in
            * progress
            *
            * if inquiry  is in progress, then we don't want to act on this cancel_cmpl_evt
            * but instead wait for the cancel_cmpl_evt via the Busy Level
            *
            */
           if (btif_dm_inquiry_in_progress == FALSE)
           {
               HAL_CBACK(bt_hal_cbacks, discovery_state_changed_cb, BT_DISCOVERY_STOPPED);
           }
        }
        break;
    }
}

/*******************************************************************************
**
** Function         btif_dm_search_services_evt
**
** Description      Executes search services event in btif context
**
** Returns          void
**
*******************************************************************************/
static void btif_dm_search_services_evt(UINT16 event, char *p_param)
{
    tBTA_DM_SEARCH *p_data = (tBTA_DM_SEARCH*)p_param;

    BTIF_TRACE_EVENT2("%s:  event = %d", __FUNCTION__, event);
    switch (event)
    {
        case BTA_DM_DISC_RES_EVT:
        {
            bt_uuid_t uuid_arr[BT_MAX_NUM_UUIDS]; /* Max 32 services */
            bt_property_t prop;
            uint32_t i = 0,  j = 0;
            bt_bdaddr_t bd_addr;
            bt_status_t ret;

            bdcpy(bd_addr.address, p_data->disc_res.bd_addr);

            BTIF_TRACE_DEBUG3("%s:(result=0x%x, services 0x%x)", __FUNCTION__,
                    p_data->disc_res.result, p_data->disc_res.services);
            if  ((p_data->disc_res.result != BTA_SUCCESS) &&
                 (pairing_cb.state == BT_BOND_STATE_BONDING ) &&
                 (pairing_cb.sdp_attempts < BTIF_DM_MAX_SDP_ATTEMPTS_AFTER_PAIRING))
            {
                BTIF_TRACE_WARNING1("%s:SDP failed after bonding re-attempting", __FUNCTION__);
                pairing_cb.sdp_attempts++;
                btif_dm_get_remote_services(&bd_addr);
                return;
            }
            prop.type = BT_PROPERTY_UUIDS;
            prop.len = 0;
            if ((p_data->disc_res.result == BTA_SUCCESS) && (p_data->disc_res.num_uuids > 0))
            {
                 prop.val = p_data->disc_res.p_uuid_list;
                 prop.len = p_data->disc_res.num_uuids * MAX_UUID_SIZE;
                 for (i=0; i < p_data->disc_res.num_uuids; i++)
                 {
                      char temp[256];
                      uuid_to_string((bt_uuid_t*)(p_data->disc_res.p_uuid_list + (i*MAX_UUID_SIZE)), temp);
                      BTIF_TRACE_ERROR2("Index: %d uuid:%s", i, temp);
                 }
            }

            /* onUuidChanged requires getBondedDevices to be populated.
            ** bond_state_changed needs to be sent prior to remote_device_property
            */
            if ((pairing_cb.state == BT_BOND_STATE_BONDING) &&
                (bdcmp(p_data->disc_res.bd_addr, pairing_cb.bd_addr) == 0)&&
                pairing_cb.sdp_attempts > 0)
            {
                 BTIF_TRACE_DEBUG1("%s Remote Service SDP done. Call bond_state_changed_cb BONDED",
                                   __FUNCTION__);
                 pairing_cb.sdp_attempts  = 0;
                 bond_state_changed(BT_STATUS_SUCCESS, &bd_addr, BT_BOND_STATE_BONDED);
            }

            if(p_data->disc_res.num_uuids != 0)
            {
                /* Also write this to the NVRAM */
                ret = btif_storage_set_remote_device_property(&bd_addr, &prop);
                ASSERTC(ret == BT_STATUS_SUCCESS, "storing remote services failed", ret);
                /* Send the event to the BTIF */
                HAL_CBACK(bt_hal_cbacks, remote_device_properties_cb,
                                 BT_STATUS_SUCCESS, &bd_addr, 1, &prop);
            }
        }
        break;

        case BTA_DM_DISC_CMPL_EVT:
            /* fixme */
        break;

#if (defined(BLE_INCLUDED) && (BLE_INCLUDED == TRUE))
        case BTA_DM_DISC_BLE_RES_EVT:
             BTIF_TRACE_DEBUG2("%s:, services 0x%x)", __FUNCTION__,
                                p_data->disc_ble_res.service.uu.uuid16);
             bt_uuid_t  uuid;
             int i = 0;
             int j = 15;
             if (p_data->disc_ble_res.service.uu.uuid16 == UUID_SERVCLASS_LE_HID)
             {
                BTIF_TRACE_DEBUG1("%s: Found HOGP UUID",__FUNCTION__);
                bt_property_t prop;
                bt_bdaddr_t bd_addr;
                char temp[256];
                bt_status_t ret;

                bta_gatt_convert_uuid16_to_uuid128(uuid.uu,p_data->disc_ble_res.service.uu.uuid16);

                while(i < j )
                {
                    unsigned char c = uuid.uu[j];
                    uuid.uu[j] = uuid.uu[i];
                    uuid.uu[i] = c;
                    i++;
                    j--;
                }

                uuid_to_string(&uuid, temp);
                BTIF_TRACE_ERROR1(" uuid:%s", temp);

                bdcpy(bd_addr.address, p_data->disc_ble_res.bd_addr);
                prop.type = BT_PROPERTY_UUIDS;
                prop.val = uuid.uu;
                prop.len = MAX_UUID_SIZE;

                /* Also write this to the NVRAM */
                ret = btif_storage_set_remote_device_property(&bd_addr, &prop);
                ASSERTC(ret == BT_STATUS_SUCCESS, "storing remote services failed", ret);

                /* Send the event to the BTIF */
                HAL_CBACK(bt_hal_cbacks, remote_device_properties_cb,
                                 BT_STATUS_SUCCESS, &bd_addr, 1, &prop);

            }
        break;
#endif /* BLE_INCLUDED */

        default:
        {
            ASSERTC(0, "unhandled search services event", event);
        }
        break;
    }
}

/*******************************************************************************
**
** Function         btif_dm_remote_service_record_evt
**
** Description      Executes search service record event in btif context
**
** Returns          void
**
*******************************************************************************/
static void btif_dm_remote_service_record_evt(UINT16 event, char *p_param)
{
    tBTA_DM_SEARCH *p_data = (tBTA_DM_SEARCH*)p_param;

    BTIF_TRACE_EVENT2("%s:  event = %d", __FUNCTION__, event);
    switch (event)
    {
        case BTA_DM_DISC_RES_EVT:
        {
            bt_service_record_t rec;
            bt_property_t prop;
            uint32_t i = 0;
            bt_bdaddr_t bd_addr;

            memset(&rec, 0, sizeof(bt_service_record_t));
            bdcpy(bd_addr.address, p_data->disc_res.bd_addr);

            BTIF_TRACE_DEBUG3("%s:(result=0x%x, services 0x%x)", __FUNCTION__,
                    p_data->disc_res.result, p_data->disc_res.services);
            prop.type = BT_PROPERTY_SERVICE_RECORD;
            prop.val = (void*)&rec;
            prop.len = sizeof(rec);

            /* disc_res.result is overloaded with SCN. Cannot check result */
            p_data->disc_res.services &= ~BTA_USER_SERVICE_MASK;
            /* TODO: Get the UUID as well */
            rec.channel = p_data->disc_res.result - 3;
            /* TODO: Need to get the service name using p_raw_data */
            rec.name[0] = 0;

            HAL_CBACK(bt_hal_cbacks, remote_device_properties_cb,
                             BT_STATUS_SUCCESS, &bd_addr, 1, &prop);
        }
        break;

        default:
        {
           ASSERTC(0, "unhandled remote service record event", event);
        }
        break;
    }
}

/*******************************************************************************
**
** Function         btif_dm_upstreams_cback
**
** Description      Executes UPSTREAMS events in btif context
**
** Returns          void
**
*******************************************************************************/
static void btif_dm_upstreams_evt(UINT16 event, char* p_param)
{
    tBTA_DM_SEC_EVT dm_event = (tBTA_DM_SEC_EVT)event;
    tBTA_DM_SEC *p_data = (tBTA_DM_SEC*)p_param;
    tBTA_SERVICE_MASK service_mask;
    uint32_t i;
    bt_bdaddr_t bd_addr;

    BTIF_TRACE_EVENT1("btif_dm_upstreams_cback  ev: %s", dump_dm_event(event));

    switch (event)
    {
        case BTA_DM_ENABLE_EVT:
        {
             BD_NAME bdname;
             bt_status_t status;
             bt_property_t prop;
             prop.type = BT_PROPERTY_BDNAME;
             prop.len = BD_NAME_LEN;
             prop.val = (void*)bdname;

             status = btif_storage_get_adapter_property(&prop);
             if (status == BT_STATUS_SUCCESS)
             {
                 /* A name exists in the storage. Make this the device name */
                 BTA_DmSetDeviceName((char*)prop.val);
             }
             else
             {
                 /* Storage does not have a name yet.
                  * Use the default name and write it to the chip
                  */
                 BTA_DmSetDeviceName(btif_get_default_local_name());
             }

             /* for each of the enabled services in the mask, trigger the profile
              * enable */
             service_mask = btif_get_enabled_services_mask();
             for (i=0; i <= BTA_MAX_SERVICE_ID; i++)
             {
                 if (service_mask &
                     (tBTA_SERVICE_MASK)(BTA_SERVICE_ID_TO_SERVICE_MASK(i)))
                 {
                     btif_in_execute_service_request(i, TRUE);
                 }
             }
             /* clear control blocks */
             memset(&pairing_cb, 0, sizeof(btif_dm_pairing_cb_t));

             /* This function will also trigger the adapter_properties_cb
             ** and bonded_devices_info_cb
             */
             btif_storage_load_bonded_devices();

             btif_storage_load_autopair_device_list();

             btif_enable_bluetooth_evt(p_data->enable.status, p_data->enable.bd_addr);
        }
        break;

        case BTA_DM_DISABLE_EVT:
            /* for each of the enabled services in the mask, trigger the profile
             * disable */
            service_mask = btif_get_enabled_services_mask();
            for (i=0; i <= BTA_MAX_SERVICE_ID; i++)
            {
                if (service_mask &
                    (tBTA_SERVICE_MASK)(BTA_SERVICE_ID_TO_SERVICE_MASK(i)))
                {
                    btif_in_execute_service_request(i, FALSE);
                }
            }
            btif_disable_bluetooth_evt();
            break;

        case BTA_DM_PIN_REQ_EVT:
            btif_dm_pin_req_evt(&p_data->pin_req);
            break;

        case BTA_DM_AUTH_CMPL_EVT:
            btif_dm_auth_cmpl_evt(&p_data->auth_cmpl);
            break;

        case BTA_DM_BOND_CANCEL_CMPL_EVT:
            if (pairing_cb.state == BT_BOND_STATE_BONDING)
            {
                bdcpy(bd_addr.address, pairing_cb.bd_addr);
                bond_state_changed(p_data->bond_cancel_cmpl.result, &bd_addr, BT_BOND_STATE_NONE);
            }
            break;

        case BTA_DM_SP_CFM_REQ_EVT:
            btif_dm_ssp_cfm_req_evt(&p_data->cfm_req);
            break;
        case BTA_DM_SP_KEY_NOTIF_EVT:
            btif_dm_ssp_key_notif_evt(&p_data->key_notif);
            break;

        case BTA_DM_DEV_UNPAIRED_EVT:
            bdcpy(bd_addr.address, p_data->link_down.bd_addr);

            /*special handling for HID devices */
            #if (defined(BTA_HH_INCLUDED) && (BTA_HH_INCLUDED == TRUE))
            btif_hh_remove_device(bd_addr);
            #endif
            #if (defined(BLE_INCLUDED) && (BLE_INCLUDED == TRUE))
            btif_storage_remove_ble_bonding_keys(&bd_addr);
            #endif
            btif_storage_remove_bonded_device(&bd_addr);
            bond_state_changed(BT_STATUS_SUCCESS, &bd_addr, BT_BOND_STATE_NONE);
            break;

        case BTA_DM_BUSY_LEVEL_EVT:
        {

            if (p_data->busy_level.level_flags & BTM_BL_INQUIRY_PAGING_MASK)
            {
                if (p_data->busy_level.level_flags == BTM_BL_INQUIRY_STARTED)
                {
                       HAL_CBACK(bt_hal_cbacks, discovery_state_changed_cb,
                                                BT_DISCOVERY_STARTED);
                       btif_dm_inquiry_in_progress = TRUE;
                }
                else if (p_data->busy_level.level_flags == BTM_BL_INQUIRY_CANCELLED)
                {
                       HAL_CBACK(bt_hal_cbacks, discovery_state_changed_cb,
                                                BT_DISCOVERY_STOPPED);
                       btif_dm_inquiry_in_progress = FALSE;
                }
                else if (p_data->busy_level.level_flags == BTM_BL_INQUIRY_COMPLETE)
                {
                       btif_dm_inquiry_in_progress = FALSE;
                }
            }
        }break;

        case BTA_DM_LINK_UP_EVT:
            bdcpy(bd_addr.address, p_data->link_up.bd_addr);
            BTIF_TRACE_DEBUG0("BTA_DM_LINK_UP_EVT. Sending BT_ACL_STATE_CONNECTED");

            btif_update_remote_version_property(&bd_addr);

            HAL_CBACK(bt_hal_cbacks, acl_state_changed_cb, BT_STATUS_SUCCESS,
                      &bd_addr, BT_ACL_STATE_CONNECTED);
            break;

        case BTA_DM_LINK_DOWN_EVT:
            bdcpy(bd_addr.address, p_data->link_down.bd_addr);
            BTIF_TRACE_DEBUG0("BTA_DM_LINK_DOWN_EVT. Sending BT_ACL_STATE_DISCONNECTED");
            HAL_CBACK(bt_hal_cbacks, acl_state_changed_cb, BT_STATUS_SUCCESS,
                      &bd_addr, BT_ACL_STATE_DISCONNECTED);
            break;

        case BTA_DM_HW_ERROR_EVT:
            BTIF_TRACE_ERROR0("Received H/W Error. ");
            /* Flush storage data */
            btif_config_flush();
            usleep(100000); /* 100milliseconds */
            /* Killing the process to force a restart as part of fault tolerance */
            kill(getpid(), SIGKILL);
            break;

#if (defined(BLE_INCLUDED) && (BLE_INCLUDED == TRUE))
        case BTA_DM_BLE_KEY_EVT:
            BTIF_TRACE_DEBUG1("BTA_DM_BLE_KEY_EVT key_type=0x%02x ", p_data->ble_key.key_type);

            /* If this pairing is by-product of local initiated GATT client Read or Write,
            BTA would not have sent BTA_DM_BLE_SEC_REQ_EVT event and Bond state would not
            have setup properly. Setup pairing_cb and notify App about Bonding state now*/
            if (pairing_cb.state != BT_BOND_STATE_BONDING)
            {
                BTIF_TRACE_DEBUG0("Bond state not sent to App so far.Notify the app now");
                bond_state_changed(BT_STATUS_SUCCESS, (bt_bdaddr_t*)p_data->ble_key.bd_addr,
                                   BT_BOND_STATE_BONDING);
            }
            else if (memcmp (pairing_cb.bd_addr, p_data->ble_key.bd_addr, BD_ADDR_LEN)!=0)
            {
                BTIF_TRACE_ERROR1("BD mismatch discard BLE key_type=%d ",p_data->ble_key.key_type);
                break;
            }

            switch (p_data->ble_key.key_type)
            {
                case BTA_LE_KEY_PENC:
                    BTIF_TRACE_DEBUG0("Rcv BTA_LE_KEY_PENC");
                    pairing_cb.ble.is_penc_key_rcvd = TRUE;
                    memcpy(pairing_cb.ble.penc_key.ltk,p_data->ble_key.key_value.penc_key.ltk, 16);
                    memcpy(pairing_cb.ble.penc_key.rand, p_data->ble_key.key_value.penc_key.rand,8);
                    pairing_cb.ble.penc_key.ediv = p_data->ble_key.key_value.penc_key.ediv;
                    pairing_cb.ble.penc_key.sec_level = p_data->ble_key.key_value.penc_key.sec_level;

                    for (i=0; i<16; i++)
                    {
                        BTIF_TRACE_DEBUG2("pairing_cb.ble.penc_key.ltk[%d]=0x%02x",i,pairing_cb.ble.penc_key.ltk[i]);
                    }
                    for (i=0; i<8; i++)
                    {
                        BTIF_TRACE_DEBUG2("pairing_cb.ble.penc_key.rand[%d]=0x%02x",i,pairing_cb.ble.penc_key.rand[i]);
                    }
                    BTIF_TRACE_DEBUG1("pairing_cb.ble.penc_key.ediv=0x%04x",pairing_cb.ble.penc_key.ediv);
                    BTIF_TRACE_DEBUG1("pairing_cb.ble.penc_key.sec_level=0x%02x",pairing_cb.ble.penc_key.sec_level);
                    BTIF_TRACE_DEBUG1("pairing_cb.ble.penc_key.key_size=0x%02x",pairing_cb.ble.penc_key.key_size);
                    break;

                case BTA_LE_KEY_PID:
                    BTIF_TRACE_DEBUG0("Rcv BTA_LE_KEY_PID");
                    pairing_cb.ble.is_pid_key_rcvd = TRUE;
                    memcpy(pairing_cb.ble.pid_key, p_data->ble_key.key_value.pid_key.irk, 16);
                    for (i=0; i<16; i++)
                    {
                        BTIF_TRACE_DEBUG2("pairing_cb.ble.pid_key[%d]=0x%02x",i,pairing_cb.ble.pid_key[i]);
                    }
                    break;

                case BTA_LE_KEY_PCSRK:
                    BTIF_TRACE_DEBUG0("Rcv BTA_LE_KEY_PCSRK");
                    pairing_cb.ble.is_pcsrk_key_rcvd = TRUE;
                    pairing_cb.ble.pcsrk_key.counter = p_data->ble_key.key_value.pcsrk_key.counter;
                    pairing_cb.ble.pcsrk_key.sec_level = p_data->ble_key.key_value.pcsrk_key.sec_level;
                    memcpy(pairing_cb.ble.pcsrk_key.csrk,p_data->ble_key.key_value.pcsrk_key.csrk,16);

                    for (i=0; i<16; i++)
                    {
                        BTIF_TRACE_DEBUG2("pairing_cb.ble.pcsrk_key.csrk[%d]=0x%02x",i,pairing_cb.ble.pcsrk_key.csrk[i]);
                    }
                    BTIF_TRACE_DEBUG1("pairing_cb.ble.pcsrk_key.counter=0x%08x",pairing_cb.ble.pcsrk_key.counter);
                    BTIF_TRACE_DEBUG1("pairing_cb.ble.pcsrk_key.sec_level=0x%02x",pairing_cb.ble.pcsrk_key.sec_level);
                    break;

                case BTA_LE_KEY_LENC:
                    BTIF_TRACE_DEBUG0("Rcv BTA_LE_KEY_LENC");
                    pairing_cb.ble.is_lenc_key_rcvd = TRUE;
                    pairing_cb.ble.lenc_key.div = p_data->ble_key.key_value.lenc_key.div;
                    pairing_cb.ble.lenc_key.key_size = p_data->ble_key.key_value.lenc_key.key_size;
                    pairing_cb.ble.lenc_key.sec_level = p_data->ble_key.key_value.lenc_key.sec_level;

                    BTIF_TRACE_DEBUG1("pairing_cb.ble.lenc_key.div=0x%04x",pairing_cb.ble.lenc_key.div);
                    BTIF_TRACE_DEBUG1("pairing_cb.ble.lenc_key.key_size=0x%02x",pairing_cb.ble.lenc_key.key_size);
                    BTIF_TRACE_DEBUG1("pairing_cb.ble.lenc_key.sec_level=0x%02x",pairing_cb.ble.lenc_key.sec_level);
                    break;



                case BTA_LE_KEY_LCSRK:
                    BTIF_TRACE_DEBUG0("Rcv BTA_LE_KEY_LCSRK");
                    pairing_cb.ble.is_lcsrk_key_rcvd = TRUE;
                    pairing_cb.ble.lcsrk_key.counter = p_data->ble_key.key_value.lcsrk_key.counter;
                    pairing_cb.ble.lcsrk_key.div = p_data->ble_key.key_value.lcsrk_key.div;
                    pairing_cb.ble.lcsrk_key.sec_level = p_data->ble_key.key_value.lcsrk_key.sec_level;

                    BTIF_TRACE_DEBUG1("pairing_cb.ble.lcsrk_key.div=0x%04x",pairing_cb.ble.lcsrk_key.div);
                    BTIF_TRACE_DEBUG1("pairing_cb.ble.lcsrk_key.counter=0x%08x",pairing_cb.ble.lcsrk_key.counter);
                    BTIF_TRACE_DEBUG1("pairing_cb.ble.lcsrk_key.sec_level=0x%02x",pairing_cb.ble.lcsrk_key.sec_level);

                    break;

                default:
                    BTIF_TRACE_ERROR1("unknown BLE key type (0x%02x)", p_data->ble_key.key_type);
                    break;
            }

            break;
        case BTA_DM_BLE_SEC_REQ_EVT:
            BTIF_TRACE_DEBUG0("BTA_DM_BLE_SEC_REQ_EVT. ");
            btif_dm_ble_sec_req_evt(&p_data->ble_req);
            break;
        case BTA_DM_BLE_PASSKEY_NOTIF_EVT:
            BTIF_TRACE_DEBUG0("BTA_DM_BLE_PASSKEY_NOTIF_EVT. ");
            btif_dm_ble_key_notif_evt(&p_data->key_notif);
            break;
        case BTA_DM_BLE_PASSKEY_REQ_EVT:
            BTIF_TRACE_DEBUG0("BTA_DM_BLE_PASSKEY_REQ_EVT. ");
            btif_dm_ble_passkey_req_evt(&p_data->pin_req);
            break;
        case BTA_DM_BLE_OOB_REQ_EVT:
            BTIF_TRACE_DEBUG0("BTA_DM_BLE_OOB_REQ_EVT. ");
            break;
        case BTA_DM_BLE_LOCAL_IR_EVT:
            BTIF_TRACE_DEBUG0("BTA_DM_BLE_LOCAL_IR_EVT. ");
            ble_local_key_cb.is_id_keys_rcvd = TRUE;
            memcpy(&ble_local_key_cb.id_keys.irk[0], &p_data->ble_id_keys.irk[0], sizeof(BT_OCTET16));
            memcpy(&ble_local_key_cb.id_keys.ir[0], &p_data->ble_id_keys.ir[0], sizeof(BT_OCTET16));
            memcpy(&ble_local_key_cb.id_keys.dhk[0], &p_data->ble_id_keys.dhk[0], sizeof(BT_OCTET16));
            btif_storage_add_ble_local_key( (char *)&ble_local_key_cb.id_keys.irk[0],
                                            BTIF_DM_LE_LOCAL_KEY_IR,
                                            BT_OCTET16_LEN);
            btif_storage_add_ble_local_key( (char *)&ble_local_key_cb.id_keys.ir[0],
                                            BTIF_DM_LE_LOCAL_KEY_IRK,
                                            BT_OCTET16_LEN);
            btif_storage_add_ble_local_key( (char *)&ble_local_key_cb.id_keys.dhk[0],
                                            BTIF_DM_LE_LOCAL_KEY_DHK,
                                            BT_OCTET16_LEN);
            break;
        case BTA_DM_BLE_LOCAL_ER_EVT:
            BTIF_TRACE_DEBUG0("BTA_DM_BLE_LOCAL_ER_EVT. ");
            ble_local_key_cb.is_er_rcvd = TRUE;
            memcpy(&ble_local_key_cb.er[0], &p_data->ble_er[0], sizeof(BT_OCTET16));
            btif_storage_add_ble_local_key( (char *)&ble_local_key_cb.er[0],
                                            BTIF_DM_LE_LOCAL_KEY_ER,
                                            BT_OCTET16_LEN);
            break;

        case BTA_DM_BLE_AUTH_CMPL_EVT:
            BTIF_TRACE_DEBUG0("BTA_DM_BLE_KEY_EVT. ");
            btif_dm_ble_auth_cmpl_evt(&p_data->auth_cmpl);
            break;
#endif

        case BTA_DM_AUTHORIZE_EVT:
        case BTA_DM_SIG_STRENGTH_EVT:
        case BTA_DM_SP_RMT_OOB_EVT:
        case BTA_DM_SP_KEYPRESS_EVT:
        case BTA_DM_ROLE_CHG_EVT:

        default:
            BTIF_TRACE_WARNING1( "btif_dm_cback : unhandled event (%d)", event );
            break;
    }
} /* btui_security_cback() */


/*******************************************************************************
**
** Function         btif_dm_generic_evt
**
** Description      Executes non-BTA upstream events in BTIF context
**
** Returns          void
**
*******************************************************************************/
static void btif_dm_generic_evt(UINT16 event, char* p_param)
{
    BTIF_TRACE_EVENT2("%s: event=%d", __FUNCTION__, event);
    switch(event)
    {
        case BTIF_DM_CB_DISCOVERY_STARTED:
        {
            HAL_CBACK(bt_hal_cbacks, discovery_state_changed_cb, BT_DISCOVERY_STARTED);
        }
        break;

        case BTIF_DM_CB_CREATE_BOND:
        {
            btif_dm_cb_create_bond((bt_bdaddr_t *)p_param);
        }
        break;

        case BTIF_DM_CB_REMOVE_BOND:
        {
            btif_dm_cb_remove_bond((bt_bdaddr_t *)p_param);
        }
        break;

        case BTIF_DM_CB_HID_REMOTE_NAME:
        {
            btif_dm_cb_hid_remote_name((tBTM_REMOTE_DEV_NAME *)p_param);
        }
        break;

        case BTIF_DM_CB_BOND_STATE_BONDING:
            {
                bond_state_changed(BT_STATUS_SUCCESS, (bt_bdaddr_t *)p_param, BT_BOND_STATE_BONDING);
            }
            break;
        case BTIF_DM_CB_LE_TX_TEST:
        case BTIF_DM_CB_LE_RX_TEST:
            {
                uint8_t status;
                STREAM_TO_UINT8(status, p_param);
                HAL_CBACK(bt_hal_cbacks, le_test_mode_cb,
                      (status == 0) ? BT_STATUS_SUCCESS : BT_STATUS_FAIL, 0);
            }
            break;
        case BTIF_DM_CB_LE_TEST_END:
            {
                uint8_t status;
                uint16_t count = 0;
                STREAM_TO_UINT8(status, p_param);
                if (status == 0)
                    STREAM_TO_UINT16(count, p_param);
                HAL_CBACK(bt_hal_cbacks, le_test_mode_cb,
                      (status == 0) ? BT_STATUS_SUCCESS : BT_STATUS_FAIL, count);
            }
            break;
        default:
        {
            BTIF_TRACE_WARNING2("%s : Unknown event 0x%x", __FUNCTION__, event);
        }
        break;
    }
}

/*******************************************************************************
**
** Function         bte_dm_evt
**
** Description      Switches context from BTE to BTIF for all DM events
**
** Returns          void
**
*******************************************************************************/

void bte_dm_evt(tBTA_DM_SEC_EVT event, tBTA_DM_SEC *p_data)
{
    bt_status_t status;

    /* switch context to btif task context (copy full union size for convenience) */
    status = btif_transfer_context(btif_dm_upstreams_evt, (uint16_t)event, (void*)p_data, sizeof(tBTA_DM_SEC), NULL);

    /* catch any failed context transfers */
    ASSERTC(status == BT_STATUS_SUCCESS, "context transfer failed", status);
}

/*******************************************************************************
**
** Function         bte_search_devices_evt
**
** Description      Switches context from BTE to BTIF for DM search events
**
** Returns          void
**
*******************************************************************************/
static void bte_search_devices_evt(tBTA_DM_SEARCH_EVT event, tBTA_DM_SEARCH *p_data)
{
    UINT16 param_len = 0;

    if (p_data)
        param_len += sizeof(tBTA_DM_SEARCH);
    /* Allocate buffer to hold the pointers (deep copy). The pointers will point to the end of the tBTA_DM_SEARCH */
    switch (event)
    {
        case BTA_DM_INQ_RES_EVT:
        {
            if (p_data->inq_res.p_eir)
                param_len += HCI_EXT_INQ_RESPONSE_LEN;
        }
        break;

        case BTA_DM_DISC_RES_EVT:
        {
            if (p_data->disc_res.raw_data_size && p_data->disc_res.p_raw_data)
                param_len += p_data->disc_res.raw_data_size;
        }
        break;
    }
    BTIF_TRACE_DEBUG3("%s event=%s param_len=%d", __FUNCTION__, dump_dm_search_event(event), param_len);

    /* if remote name is available in EIR, set teh flag so that stack doesnt trigger RNR */
    if (event == BTA_DM_INQ_RES_EVT)
        p_data->inq_res.remt_name_not_required = check_eir_remote_name(p_data, NULL, NULL);

    btif_transfer_context (btif_dm_search_devices_evt , (UINT16) event, (void *)p_data, param_len,
        (param_len > sizeof(tBTA_DM_SEARCH)) ? search_devices_copy_cb : NULL);
}

/*******************************************************************************
**
** Function         bte_dm_search_services_evt
**
** Description      Switches context from BTE to BTIF for DM search services
**                  event
**
** Returns          void
**
*******************************************************************************/
static void bte_dm_search_services_evt(tBTA_DM_SEARCH_EVT event, tBTA_DM_SEARCH *p_data)
{
    UINT16 param_len = 0;
   if (p_data)
       param_len += sizeof(tBTA_DM_SEARCH);
   switch (event)
   {
         case BTA_DM_DISC_RES_EVT:
         {
             if ((p_data->disc_res.result == BTA_SUCCESS) && (p_data->disc_res.num_uuids > 0)) {
                  param_len += (p_data->disc_res.num_uuids * MAX_UUID_SIZE);
             }
         } break;
   }
   /* TODO: The only other member that needs a deep copy is the p_raw_data. But not sure
    * if raw_data is needed. */
   btif_transfer_context(btif_dm_search_services_evt, event, (char*)p_data, param_len,
         (param_len > sizeof(tBTA_DM_SEARCH)) ? search_services_copy_cb : NULL);
}

/*******************************************************************************
**
** Function         bte_dm_remote_service_record_evt
**
** Description      Switches context from BTE to BTIF for DM search service
**                  record event
**
** Returns          void
**
*******************************************************************************/
static void bte_dm_remote_service_record_evt(tBTA_DM_SEARCH_EVT event, tBTA_DM_SEARCH *p_data)
{
   /* TODO: The only member that needs a deep copy is the p_raw_data. But not sure yet if this is needed. */
   btif_transfer_context(btif_dm_remote_service_record_evt, event, (char*)p_data, sizeof(tBTA_DM_SEARCH), NULL);
}

/*****************************************************************************
**
**   btif api functions (no context switch)
**
*****************************************************************************/

/*******************************************************************************
**
** Function         btif_dm_start_discovery
**
** Description      Start device discovery/inquiry
**
** Returns          bt_status_t
**
*******************************************************************************/
bt_status_t btif_dm_start_discovery(void)
{
    tBTA_DM_INQ inq_params;
    tBTA_SERVICE_MASK services = 0;

    BTIF_TRACE_EVENT1("%s", __FUNCTION__);
    /* TODO: Do we need to handle multiple inquiries at the same time? */

    /* Set inquiry params and call API */
#if (defined(BLE_INCLUDED) && (BLE_INCLUDED == TRUE))
    inq_params.mode = BTA_DM_GENERAL_INQUIRY|BTA_BLE_GENERAL_INQUIRY;
#if (defined(BTA_HOST_INTERLEAVE_SEARCH) && BTA_HOST_INTERLEAVE_SEARCH == TRUE)
    inq_params.intl_duration[0]= BTIF_DM_INTERLEAVE_DURATION_BR_ONE;
    inq_params.intl_duration[1]= BTIF_DM_INTERLEAVE_DURATION_LE_ONE;
    inq_params.intl_duration[2]= BTIF_DM_INTERLEAVE_DURATION_BR_TWO;
    inq_params.intl_duration[3]= BTIF_DM_INTERLEAVE_DURATION_LE_TWO;
#endif
#else
    inq_params.mode = BTA_DM_GENERAL_INQUIRY;
#endif
    inq_params.duration = BTIF_DM_DEFAULT_INQ_MAX_DURATION;

    inq_params.max_resps = BTIF_DM_DEFAULT_INQ_MAX_RESULTS;
    inq_params.report_dup = TRUE;

    inq_params.filter_type = BTA_DM_INQ_CLR;
    /* TODO: Filter device by BDA needs to be implemented here */

    /* Will be enabled to TRUE once inquiry busy level has been received */
    btif_dm_inquiry_in_progress = FALSE;
    /* find nearby devices */
    BTA_DmSearch(&inq_params, services, bte_search_devices_evt);

    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         btif_dm_cancel_discovery
**
** Description      Cancels search
**
** Returns          bt_status_t
**
*******************************************************************************/
bt_status_t btif_dm_cancel_discovery(void)
{
    BTIF_TRACE_EVENT1("%s", __FUNCTION__);
    BTA_DmSearchCancel();
    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         btif_dm_create_bond
**
** Description      Initiate bonding with the specified device
**
** Returns          bt_status_t
**
*******************************************************************************/
bt_status_t btif_dm_create_bond(const bt_bdaddr_t *bd_addr)
{
    bdstr_t bdstr;

    BTIF_TRACE_EVENT2("%s: bd_addr=%s", __FUNCTION__, bd2str((bt_bdaddr_t *) bd_addr, &bdstr));
    if (pairing_cb.state != BT_BOND_STATE_NONE)
        return BT_STATUS_BUSY;

    btif_transfer_context(btif_dm_generic_evt, BTIF_DM_CB_CREATE_BOND,
                          (char *)bd_addr, sizeof(bt_bdaddr_t), NULL);

    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         btif_dm_cancel_bond
**
** Description      Initiate bonding with the specified device
**
** Returns          bt_status_t
**
*******************************************************************************/

bt_status_t btif_dm_cancel_bond(const bt_bdaddr_t *bd_addr)
{
    bdstr_t bdstr;

    BTIF_TRACE_EVENT2("%s: bd_addr=%s", __FUNCTION__, bd2str((bt_bdaddr_t *)bd_addr, &bdstr));

    /* TODO:
    **  1. Restore scan modes
    **  2. special handling for HID devices
    */
    if (pairing_cb.state == BT_BOND_STATE_BONDING)
    {

#if (defined(BLE_INCLUDED) && (BLE_INCLUDED == TRUE))

        if (pairing_cb.is_ssp)
        {
            if (pairing_cb.is_le_only)
            {
                BTA_DmBleSecurityGrant((UINT8 *)bd_addr->address,BTA_DM_SEC_PAIR_NOT_SPT);
            }
            else
                BTA_DmConfirm( (UINT8 *)bd_addr->address, FALSE);
        }
        else
        {
            if (pairing_cb.is_le_only)
            {
                BTA_DmBondCancel ((UINT8 *)bd_addr->address);
            }
            else
            {
                BTA_DmPinReply( (UINT8 *)bd_addr->address, FALSE, 0, NULL);
            }
        /* Cancel bonding, in case it is in ACL connection setup state */
        BTA_DmBondCancel ((UINT8 *)bd_addr->address);
        }

#else
        if (pairing_cb.is_ssp)
        {
            BTA_DmConfirm( (UINT8 *)bd_addr->address, FALSE);
        }
        else
        {
            BTA_DmPinReply( (UINT8 *)bd_addr->address, FALSE, 0, NULL);
        }
        /* Cancel bonding, in case it is in ACL connection setup state */
        BTA_DmBondCancel ((UINT8 *)bd_addr->address);
        btif_storage_remove_bonded_device((bt_bdaddr_t *)bd_addr);
#endif
    }

    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         btif_dm_hh_open_failed
**
** Description      informs the upper layers if the HH have failed during bonding
**
** Returns          none
**
*******************************************************************************/

void btif_dm_hh_open_failed(bt_bdaddr_t *bdaddr)
{
    if (pairing_cb.state == BT_BOND_STATE_BONDING &&
            bdcmp(bdaddr->address, pairing_cb.bd_addr) == 0)
    {
        bond_state_changed(BT_STATUS_FAIL, bdaddr, BT_BOND_STATE_NONE);
    }
}

/*******************************************************************************
**
** Function         btif_dm_remove_bond
**
** Description      Removes bonding with the specified device
**
** Returns          bt_status_t
**
*******************************************************************************/

bt_status_t btif_dm_remove_bond(const bt_bdaddr_t *bd_addr)
{
    bdstr_t bdstr;

    BTIF_TRACE_EVENT2("%s: bd_addr=%s", __FUNCTION__, bd2str((bt_bdaddr_t *)bd_addr, &bdstr));
    btif_transfer_context(btif_dm_generic_evt, BTIF_DM_CB_REMOVE_BOND,
                          (char *)bd_addr, sizeof(bt_bdaddr_t), NULL);

    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         btif_dm_pin_reply
**
** Description      BT legacy pairing - PIN code reply
**
** Returns          bt_status_t
**
*******************************************************************************/

bt_status_t btif_dm_pin_reply( const bt_bdaddr_t *bd_addr, uint8_t accept,
                               uint8_t pin_len, bt_pin_code_t *pin_code)
{
    BTIF_TRACE_EVENT2("%s: accept=%d", __FUNCTION__, accept);
#if (defined(BLE_INCLUDED) && (BLE_INCLUDED == TRUE))

    if (pairing_cb.is_le_only)
    {
        int i;
        UINT32 passkey = 0;
        int multi[] = {100000, 10000, 1000, 100, 10,1};
        BD_ADDR remote_bd_addr;
        bdcpy(remote_bd_addr, bd_addr->address);
        for (i = 0; i < 6; i++)
        {
            passkey += (multi[i] * (pin_code->pin[i] - '0'));
        }
        BTIF_TRACE_DEBUG1("btif_dm_pin_reply: passkey: %d", passkey);
        BTA_DmBlePasskeyReply(remote_bd_addr, accept, passkey);

    }
    else
    {
        BTA_DmPinReply( (UINT8 *)bd_addr->address, accept, pin_len, pin_code->pin);
        if (accept)
            pairing_cb.pin_code_len = pin_len;
    }
#else
    BTA_DmPinReply( (UINT8 *)bd_addr->address, accept, pin_len, pin_code->pin);

    if (accept)
        pairing_cb.pin_code_len = pin_len;
#endif
    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         btif_dm_ssp_reply
**
** Description      BT SSP Reply - Just Works, Numeric Comparison & Passkey Entry
**
** Returns          bt_status_t
**
*******************************************************************************/
bt_status_t btif_dm_ssp_reply(const bt_bdaddr_t *bd_addr,
                                 bt_ssp_variant_t variant, uint8_t accept,
                                 uint32_t passkey)
{
    UNUSED(passkey);

    if (variant == BT_SSP_VARIANT_PASSKEY_ENTRY)
    {
        /* This is not implemented in the stack.
         * For devices with display, this is not needed
        */
        BTIF_TRACE_WARNING1("%s: Not implemented", __FUNCTION__);
        return BT_STATUS_FAIL;
    }
    /* BT_SSP_VARIANT_CONSENT & BT_SSP_VARIANT_PASSKEY_CONFIRMATION supported */
    BTIF_TRACE_EVENT2("%s: accept=%d", __FUNCTION__, accept);
#if (defined(BLE_INCLUDED) && (BLE_INCLUDED == TRUE))
    if (pairing_cb.is_le_only)
    {
        if (accept)
            BTA_DmBleSecurityGrant((UINT8 *)bd_addr->address,BTA_DM_SEC_GRANTED);
        else
            BTA_DmBleSecurityGrant((UINT8 *)bd_addr->address,BTA_DM_SEC_PAIR_NOT_SPT);
    }
    else
        BTA_DmConfirm( (UINT8 *)bd_addr->address, accept);

#else
    BTA_DmConfirm( (UINT8 *)bd_addr->address, accept);
#endif
    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         btif_dm_get_adapter_property
**
** Description     Queries the BTA for the adapter property
**
** Returns          bt_status_t
**
*******************************************************************************/
bt_status_t btif_dm_get_adapter_property(bt_property_t *prop)
{
    bt_status_t status;

    BTIF_TRACE_EVENT2("%s: type=0x%x", __FUNCTION__, prop->type);
    switch (prop->type)
    {
        case BT_PROPERTY_BDNAME:
        {
            bt_bdname_t *bd_name = (bt_bdname_t*)prop->val;
            strcpy((char *)bd_name->name, btif_get_default_local_name());
            prop->len = strlen((char *)bd_name->name);
        }
        break;

        case BT_PROPERTY_ADAPTER_SCAN_MODE:
        {
            /* if the storage does not have it. Most likely app never set it. Default is NONE */
            bt_scan_mode_t *mode = (bt_scan_mode_t*)prop->val;
            *mode = BT_SCAN_MODE_NONE;
            prop->len = sizeof(bt_scan_mode_t);
        }
        break;

        case BT_PROPERTY_ADAPTER_DISCOVERY_TIMEOUT:
        {
            uint32_t *tmt = (uint32_t*)prop->val;
            *tmt = 120; /* default to 120s, if not found in NV */
            prop->len = sizeof(uint32_t);
        }
        break;

        default:
            prop->len = 0;
            return BT_STATUS_FAIL;
    }
    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         btif_dm_get_remote_services
**
** Description      Start SDP to get remote services
**
** Returns          bt_status_t
**
*******************************************************************************/
bt_status_t btif_dm_get_remote_services(bt_bdaddr_t *remote_addr)
{
    bdstr_t bdstr;

    BTIF_TRACE_EVENT2("%s: remote_addr=%s", __FUNCTION__, bd2str(remote_addr, &bdstr));

    BTA_DmDiscover(remote_addr->address, BTA_ALL_SERVICE_MASK,
                   bte_dm_search_services_evt, TRUE);

    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         btif_dm_get_remote_service_record
**
** Description      Start SDP to get remote service record
**
**
** Returns          bt_status_t
*******************************************************************************/
bt_status_t btif_dm_get_remote_service_record(bt_bdaddr_t *remote_addr,
                                                    bt_uuid_t *uuid)
{
    tSDP_UUID sdp_uuid;
    bdstr_t bdstr;

    BTIF_TRACE_EVENT2("%s: remote_addr=%s", __FUNCTION__, bd2str(remote_addr, &bdstr));

    sdp_uuid.len = MAX_UUID_SIZE;
    memcpy(sdp_uuid.uu.uuid128, uuid->uu, MAX_UUID_SIZE);

    BTA_DmDiscoverUUID(remote_addr->address, &sdp_uuid,
                       bte_dm_remote_service_record_evt, TRUE);

    return BT_STATUS_SUCCESS;
}

void btif_dm_execute_service_request(UINT16 event, char *p_param)
{
    BOOLEAN b_enable = FALSE;
    bt_status_t status;
    if (event == BTIF_DM_ENABLE_SERVICE)
    {
        b_enable = TRUE;
    }
    status = btif_in_execute_service_request(*((tBTA_SERVICE_ID*)p_param), b_enable);
    if (status == BT_STATUS_SUCCESS)
    {
        bt_property_t property;
        bt_uuid_t local_uuids[BT_MAX_NUM_UUIDS];

        /* Now send the UUID_PROPERTY_CHANGED event to the upper layer */
        BTIF_STORAGE_FILL_PROPERTY(&property, BT_PROPERTY_UUIDS,
                                    sizeof(local_uuids), local_uuids);
        btif_storage_get_adapter_property(&property);
        HAL_CBACK(bt_hal_cbacks, adapter_properties_cb,
                          BT_STATUS_SUCCESS, 1, &property);
    }
    return;
}

#if (BTM_OOB_INCLUDED == TRUE)
void btif_dm_set_oob_for_io_req(tBTA_OOB_DATA  *p_oob_data)
{
    if (oob_cb.sp_c[0] == 0 && oob_cb.sp_c[1] == 0 &&
        oob_cb.sp_c[2] == 0 && oob_cb.sp_c[3] == 0 )
    {
        *p_oob_data = FALSE;
    }
    else
    {
        *p_oob_data = TRUE;
    }
    BTIF_TRACE_DEBUG1("btif_dm_set_oob_for_io_req *p_oob_data=%d", *p_oob_data);
}
#endif /* BTM_OOB_INCLUDED */

#ifdef BTIF_DM_OOB_TEST
void btif_dm_load_local_oob(void)
{
    char prop_oob[PROPERTY_VALUE_MAX];
    property_get("service.brcm.bt.oob", prop_oob, "3");
    BTIF_TRACE_DEBUG1("btif_dm_load_local_oob prop_oob = %s",prop_oob);
    if (prop_oob[0] != '3')
    {
#if (BTM_OOB_INCLUDED == TRUE)
        if (oob_cb.sp_c[0] == 0 && oob_cb.sp_c[1] == 0 &&
            oob_cb.sp_c[2] == 0 && oob_cb.sp_c[3] == 0 )
        {
            BTIF_TRACE_DEBUG0("btif_dm_load_local_oob: read OOB, call BTA_DmLocalOob()");
            BTA_DmLocalOob();
        }
#else
        BTIF_TRACE_ERROR0("BTM_OOB_INCLUDED is FALSE!!(btif_dm_load_local_oob)");
#endif
    }
}

void btif_dm_proc_loc_oob(BOOLEAN valid, BT_OCTET16 c, BT_OCTET16 r)
{
    FILE *fp;
    char *path_a = "/data/misc/bluedroid/LOCAL/a.key";
    char *path_b = "/data/misc/bluedroid/LOCAL/b.key";
    char *path = NULL;
    char prop_oob[PROPERTY_VALUE_MAX];
    BTIF_TRACE_DEBUG1("btif_dm_proc_loc_oob: valid=%d", valid);
    if (oob_cb.sp_c[0] == 0 && oob_cb.sp_c[1] == 0 &&
        oob_cb.sp_c[2] == 0 && oob_cb.sp_c[3] == 0 &&
        valid)
    {
        BTIF_TRACE_DEBUG0("save local OOB data in memory");
        memcpy(oob_cb.sp_c, c, BT_OCTET16_LEN);
        memcpy(oob_cb.sp_r, r, BT_OCTET16_LEN);
        property_get("service.brcm.bt.oob", prop_oob, "3");
        BTIF_TRACE_DEBUG1("btif_dm_proc_loc_oob prop_oob = %s",prop_oob);
        if (prop_oob[0] == '1')
            path = path_a;
        else if (prop_oob[0] == '2')
            path = path_b;
        if (path)
        {
            fp = fopen(path, "wb+");
            if (fp == NULL)
            {
                BTIF_TRACE_DEBUG1("btif_dm_proc_loc_oob: failed to save local OOB data to %s", path);
            }
            else
            {
                BTIF_TRACE_DEBUG1("btif_dm_proc_loc_oob: save local OOB data into file %s",path);
                fwrite (c , 1 , BT_OCTET16_LEN , fp );
                fwrite (r , 1 , BT_OCTET16_LEN , fp );
                fclose(fp);
            }
        }
    }
}
BOOLEAN btif_dm_proc_rmt_oob(BD_ADDR bd_addr,  BT_OCTET16 p_c, BT_OCTET16 p_r)
{
    char t[128];
    FILE *fp;
    char *path_a = "/data/misc/bluedroid/LOCAL/a.key";
    char *path_b = "/data/misc/bluedroid/LOCAL/b.key";
    char *path = NULL;
    char prop_oob[PROPERTY_VALUE_MAX];
    BOOLEAN result = FALSE;
    bt_bdaddr_t bt_bd_addr;
    bdcpy(oob_cb.oob_bdaddr, bd_addr);
    property_get("service.brcm.bt.oob", prop_oob, "3");
    BTIF_TRACE_DEBUG1("btif_dm_proc_rmt_oob prop_oob = %s",prop_oob);
    if (prop_oob[0] == '1')
        path = path_b;
    else if (prop_oob[0] == '2')
        path = path_a;
    if (path)
    {
        fp = fopen(path, "rb");
        if (fp == NULL)
        {
            BTIF_TRACE_DEBUG1("btapp_dm_rmt_oob_reply: failed to read OOB keys from %s",path);
            return FALSE;
        }
        else
        {
            BTIF_TRACE_DEBUG1("btif_dm_proc_rmt_oob: read OOB data from %s",path);
            fread (p_c , 1 , BT_OCTET16_LEN , fp );
            fread (p_r , 1 , BT_OCTET16_LEN , fp );
            fclose(fp);
        }
        BTIF_TRACE_DEBUG0("----btif_dm_proc_rmt_oob: TRUE");
        sprintf(t, "%02x:%02x:%02x:%02x:%02x:%02x",
                oob_cb.oob_bdaddr[0], oob_cb.oob_bdaddr[1], oob_cb.oob_bdaddr[2],
                oob_cb.oob_bdaddr[3], oob_cb.oob_bdaddr[4], oob_cb.oob_bdaddr[5]);
        BTIF_TRACE_DEBUG1("----btif_dm_proc_rmt_oob: peer_bdaddr = %s", t);
        sprintf(t, "%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
                p_c[0], p_c[1], p_c[2],  p_c[3],  p_c[4],  p_c[5],  p_c[6],  p_c[7],
                p_c[8], p_c[9], p_c[10], p_c[11], p_c[12], p_c[13], p_c[14], p_c[15]);
        BTIF_TRACE_DEBUG1("----btif_dm_proc_rmt_oob: c = %s",t);
        sprintf(t, "%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
                p_r[0], p_r[1], p_r[2],  p_r[3],  p_r[4],  p_r[5],  p_r[6],  p_r[7],
                p_r[8], p_r[9], p_r[10], p_r[11], p_r[12], p_r[13], p_r[14], p_r[15]);
        BTIF_TRACE_DEBUG1("----btif_dm_proc_rmt_oob: r = %s",t);
        bdcpy(bt_bd_addr.address, bd_addr);
        btif_transfer_context(btif_dm_generic_evt, BTIF_DM_CB_BOND_STATE_BONDING,
                              (char *)&bt_bd_addr, sizeof(bt_bdaddr_t), NULL);
        result = TRUE;
    }
    BTIF_TRACE_DEBUG1("btif_dm_proc_rmt_oob result=%d",result);
    return result;
}
#endif /*  BTIF_DM_OOB_TEST */
#if (defined(BLE_INCLUDED) && (BLE_INCLUDED == TRUE))

static void btif_dm_ble_key_notif_evt(tBTA_DM_SP_KEY_NOTIF *p_ssp_key_notif)
{
    bt_bdaddr_t bd_addr;
    bt_bdname_t bd_name;
    UINT32 cod;

    BTIF_TRACE_DEBUG1("%s", __FUNCTION__);

    /* Remote name update */
    btif_update_remote_properties(p_ssp_key_notif->bd_addr , p_ssp_key_notif->bd_name,
                                          NULL, BT_DEVICE_TYPE_BLE);
    bdcpy(bd_addr.address, p_ssp_key_notif->bd_addr);
    memcpy(bd_name.name, p_ssp_key_notif->bd_name, BD_NAME_LEN);

    bond_state_changed(BT_STATUS_SUCCESS, &bd_addr, BT_BOND_STATE_BONDING);
    pairing_cb.is_ssp = FALSE;
    cod = COD_UNCLASSIFIED;

    HAL_CBACK(bt_hal_cbacks, ssp_request_cb, &bd_addr, &bd_name,
              cod, BT_SSP_VARIANT_PASSKEY_NOTIFICATION,
              p_ssp_key_notif->passkey);
}

/*******************************************************************************
**
** Function         btif_dm_ble_auth_cmpl_evt
**
** Description      Executes authentication complete event in btif context
**
** Returns          void
**
*******************************************************************************/
static void btif_dm_ble_auth_cmpl_evt (tBTA_DM_AUTH_CMPL *p_auth_cmpl)
{
    /* Save link key, if not temporary */
    bt_bdaddr_t bd_addr;
    bt_status_t status = BT_STATUS_FAIL;
    bt_bond_state_t state = BT_BOND_STATE_NONE;

    bdcpy(bd_addr.address, p_auth_cmpl->bd_addr);
    if ( (p_auth_cmpl->success == TRUE) && (p_auth_cmpl->key_present) )
    {
        /* store keys */
    }
    if (p_auth_cmpl->success)
    {
        status = BT_STATUS_SUCCESS;
        state = BT_BOND_STATE_BONDED;

        btif_dm_save_ble_bonding_keys();
        BTA_GATTC_Refresh(bd_addr.address);
        btif_dm_get_remote_services(&bd_addr);
    }
    else
    {
        /*Map the HCI fail reason  to  bt status  */
        switch (p_auth_cmpl->fail_reason)
        {
            default:
                btif_dm_remove_ble_bonding_keys();
                status =  BT_STATUS_FAIL;
                break;
        }
    }
    bond_state_changed(status, &bd_addr, state);
}



void    btif_dm_load_ble_local_keys(void)
{
    bt_status_t bt_status;

    memset(&ble_local_key_cb, 0, sizeof(btif_dm_local_key_cb_t));

    if (btif_storage_get_ble_local_key(BTIF_DM_LE_LOCAL_KEY_ER,(char*)&ble_local_key_cb.er[0],
                                       BT_OCTET16_LEN)== BT_STATUS_SUCCESS)
    {
        ble_local_key_cb.is_er_rcvd = TRUE;
        BTIF_TRACE_DEBUG1("%s BLE ER key loaded",__FUNCTION__ );
    }

    if ((btif_storage_get_ble_local_key(BTIF_DM_LE_LOCAL_KEY_IR,(char*)&ble_local_key_cb.id_keys.ir[0],
                                        BT_OCTET16_LEN)== BT_STATUS_SUCCESS )&&
        (btif_storage_get_ble_local_key(BTIF_DM_LE_LOCAL_KEY_IRK, (char*)&ble_local_key_cb.id_keys.irk[0],
                                        BT_OCTET16_LEN)== BT_STATUS_SUCCESS)&&
        (btif_storage_get_ble_local_key(BTIF_DM_LE_LOCAL_KEY_DHK,(char*)&ble_local_key_cb.id_keys.dhk[0],
                                        BT_OCTET16_LEN)== BT_STATUS_SUCCESS))
    {
        ble_local_key_cb.is_id_keys_rcvd = TRUE;
        BTIF_TRACE_DEBUG1("%s BLE ID keys loaded",__FUNCTION__ );
    }

}
void    btif_dm_get_ble_local_keys(tBTA_DM_BLE_LOCAL_KEY_MASK *p_key_mask, BT_OCTET16 er,
                                   tBTA_BLE_LOCAL_ID_KEYS *p_id_keys)
{
    if (ble_local_key_cb.is_er_rcvd )
    {
        memcpy(&er[0], &ble_local_key_cb.er[0], sizeof(BT_OCTET16));
        *p_key_mask |= BTA_BLE_LOCAL_KEY_TYPE_ER;
    }

    if (ble_local_key_cb.is_id_keys_rcvd)
    {
        memcpy(&p_id_keys->ir[0], &ble_local_key_cb.id_keys.ir[0], sizeof(BT_OCTET16));
        memcpy(&p_id_keys->irk[0],  &ble_local_key_cb.id_keys.irk[0], sizeof(BT_OCTET16));
        memcpy(&p_id_keys->dhk[0],  &ble_local_key_cb.id_keys.dhk[0], sizeof(BT_OCTET16));
        *p_key_mask |= BTA_BLE_LOCAL_KEY_TYPE_ID;
    }
    BTIF_TRACE_DEBUG2("%s  *p_key_mask=0x%02x",__FUNCTION__,   *p_key_mask);
}

void btif_dm_save_ble_bonding_keys(void)
{

    bt_bdaddr_t bd_addr;

    BTIF_TRACE_DEBUG1("%s",__FUNCTION__ );

    bdcpy(bd_addr.address, pairing_cb.bd_addr);

    if (pairing_cb.ble.is_penc_key_rcvd)
    {
        btif_storage_add_ble_bonding_key(&bd_addr,
                                         (char *) &pairing_cb.ble.penc_key,
                                         BTIF_DM_LE_KEY_PENC,
                                         sizeof(btif_dm_ble_penc_keys_t));
    }

    if (pairing_cb.ble.is_pid_key_rcvd)
    {
        btif_storage_add_ble_bonding_key(&bd_addr,
                                         (char *) &pairing_cb.ble.pid_key[0],
                                         BTIF_DM_LE_KEY_PID,
                                         BT_OCTET16_LEN);
    }


    if (pairing_cb.ble.is_pcsrk_key_rcvd)
    {
        btif_storage_add_ble_bonding_key(&bd_addr,
                                         (char *) &pairing_cb.ble.pcsrk_key,
                                         BTIF_DM_LE_KEY_PCSRK,
                                         sizeof(btif_dm_ble_pcsrk_keys_t));
    }


    if (pairing_cb.ble.is_lenc_key_rcvd)
    {
        btif_storage_add_ble_bonding_key(&bd_addr,
                                         (char *) &pairing_cb.ble.lenc_key,
                                         BTIF_DM_LE_KEY_LENC,
                                         sizeof(btif_dm_ble_lenc_keys_t));
    }

    if (pairing_cb.ble.is_lcsrk_key_rcvd)
    {
        btif_storage_add_ble_bonding_key(&bd_addr,
                                         (char *) &pairing_cb.ble.lcsrk_key,
                                         BTIF_DM_LE_KEY_LCSRK,
                                         sizeof(btif_dm_ble_lcsrk_keys_t));
    }

}


void btif_dm_remove_ble_bonding_keys(void)
{
    bt_bdaddr_t bd_addr;

    BTIF_TRACE_DEBUG1("%s",__FUNCTION__ );

    bdcpy(bd_addr.address, pairing_cb.bd_addr);
    btif_storage_remove_ble_bonding_keys(&bd_addr);
}


/*******************************************************************************
**
** Function         btif_dm_ble_sec_req_evt
**
** Description      Eprocess security request event in btif context
**
** Returns          void
**
*******************************************************************************/
void btif_dm_ble_sec_req_evt(tBTA_DM_BLE_SEC_REQ *p_ble_req)
{
    bt_bdaddr_t bd_addr;
    bt_bdname_t bd_name;
    UINT32 cod;
    BTIF_TRACE_DEBUG1("%s", __FUNCTION__);

    if (pairing_cb.state == BT_BOND_STATE_BONDING)
    {
        BTIF_TRACE_DEBUG1("%s Discard security request", __FUNCTION__);
        return;
    }

    /* Remote name update */
    btif_update_remote_properties(p_ble_req->bd_addr,p_ble_req->bd_name,NULL,BT_DEVICE_TYPE_BLE);

    bdcpy(bd_addr.address, p_ble_req->bd_addr);
    memcpy(bd_name.name, p_ble_req->bd_name, BD_NAME_LEN);

    bond_state_changed(BT_STATUS_SUCCESS, &bd_addr, BT_BOND_STATE_BONDING);

    pairing_cb.is_temp = FALSE;
    pairing_cb.is_le_only = TRUE;
    pairing_cb.is_ssp = TRUE;

    cod = COD_UNCLASSIFIED;

    HAL_CBACK(bt_hal_cbacks, ssp_request_cb, &bd_addr, &bd_name, cod,
              BT_SSP_VARIANT_CONSENT, 0);
}



/*******************************************************************************
**
** Function         btif_dm_ble_passkey_req_evt
**
** Description      Executes pin request event in btif context
**
** Returns          void
**
*******************************************************************************/
static void btif_dm_ble_passkey_req_evt(tBTA_DM_PIN_REQ *p_pin_req)
{
    bt_bdaddr_t bd_addr;
    bt_bdname_t bd_name;
    UINT32 cod;

    /* Remote name update */
    btif_update_remote_properties(p_pin_req->bd_addr,p_pin_req->bd_name,NULL,BT_DEVICE_TYPE_BLE);

    bdcpy(bd_addr.address, p_pin_req->bd_addr);
    memcpy(bd_name.name, p_pin_req->bd_name, BD_NAME_LEN);

    bond_state_changed(BT_STATUS_SUCCESS, &bd_addr, BT_BOND_STATE_BONDING);
    pairing_cb.is_le_only = TRUE;

    cod = COD_UNCLASSIFIED;

    HAL_CBACK(bt_hal_cbacks, pin_request_cb,
              &bd_addr, &bd_name, cod);
}


void btif_dm_update_ble_remote_properties( BD_ADDR bd_addr, BD_NAME bd_name,
                                           tBT_DEVICE_TYPE dev_type)
{
   btif_update_remote_properties(bd_addr,bd_name,NULL,dev_type);
}

static void btif_dm_ble_tx_test_cback(void *p)
{
    btif_transfer_context(btif_dm_generic_evt, BTIF_DM_CB_LE_TX_TEST,
                          (char *)p, 1, NULL);
}

static void btif_dm_ble_rx_test_cback(void *p)
{
    btif_transfer_context(btif_dm_generic_evt, BTIF_DM_CB_LE_RX_TEST,
                          (char *)p, 1, NULL);
}

static void btif_dm_ble_test_end_cback(void *p)
{
    btif_transfer_context(btif_dm_generic_evt, BTIF_DM_CB_LE_TEST_END,
                          (char *)p, 3, NULL);
}
/*******************************************************************************
**
** Function         btif_le_test_mode
**
** Description     Sends a HCI BLE Test command to the Controller
**
** Returns          BT_STATUS_SUCCESS on success
**
*******************************************************************************/
bt_status_t btif_le_test_mode(uint16_t opcode, uint8_t *buf, uint8_t len)
{
     switch (opcode) {
         case HCI_BLE_TRANSMITTER_TEST:
             if (len != 3) return BT_STATUS_PARM_INVALID;
             BTM_BleTransmitterTest(buf[0],buf[1],buf[2], btif_dm_ble_tx_test_cback);
             break;
         case HCI_BLE_RECEIVER_TEST:
             if (len != 1) return BT_STATUS_PARM_INVALID;
             BTM_BleReceiverTest(buf[0], btif_dm_ble_rx_test_cback);
             break;
         case HCI_BLE_TEST_END:
             BTM_BleTestEnd((tBTM_CMPL_CB*) btif_dm_ble_test_end_cback);
             break;
         default:
             BTIF_TRACE_ERROR2("%s: Unknown LE Test Mode Command 0x%x", __FUNCTION__, opcode);
             return BT_STATUS_UNSUPPORTED;
     }
     return BT_STATUS_SUCCESS;
}

#endif

void btif_dm_on_disable()
{
    /* cancel any pending pairing requests */
    if (pairing_cb.state == BT_BOND_STATE_BONDING)
    {
        bt_bdaddr_t bd_addr;

        BTIF_TRACE_DEBUG1("%s: Cancel pending pairing request", __FUNCTION__);
        bdcpy(bd_addr.address, pairing_cb.bd_addr);
        btif_dm_cancel_bond(&bd_addr);
    }
}

static char* btif_get_default_local_name() {
    if (btif_default_local_name[0] == '\0')
    {
        int max_len = sizeof(btif_default_local_name) - 1;
        if (BTM_DEF_LOCAL_NAME[0] != '\0')
        {
            strncpy(btif_default_local_name, BTM_DEF_LOCAL_NAME, max_len);
        }
        else
        {
            char prop_model[PROPERTY_VALUE_MAX];
            property_get(PROPERTY_PRODUCT_MODEL, prop_model, "");
            strncpy(btif_default_local_name, prop_model, max_len);
        }
        btif_default_local_name[max_len] = '\0';
    }
    return btif_default_local_name;
}
