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
 *  Filename:      btif_storage.c
 *
 *  Description:   Stores the local BT adapter and remote device properties in
 *                 NVRAM storage, typically as xml file in the
 *                 mobile's filesystem
 *
 *
 */
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <alloca.h>


#include <hardware/bluetooth.h>
#include "btif_config.h"
#define LOG_TAG "BTIF_STORAGE"

#include "btif_api.h"
#include "btif_storage.h"
#include "btif_util.h"
#include "bd.h"
#include "gki.h"
#include "bta_hh_api.h"
#include "btif_hh.h"

#include <cutils/log.h>

/************************************************************************************
**  Constants & Macros
************************************************************************************/

#define BTIF_STORAGE_PATH_BLUEDROID "/data/misc/bluedroid"

//#define BTIF_STORAGE_PATH_ADAPTER_INFO "adapter_info"
//#define BTIF_STORAGE_PATH_REMOTE_DEVICES "remote_devices"
#define BTIF_STORAGE_PATH_REMOTE_DEVTIME "Timestamp"
#define BTIF_STORAGE_PATH_REMOTE_DEVCLASS "DevClass"
#define BTIF_STORAGE_PATH_REMOTE_DEVTYPE "DevType"
#define BTIF_STORAGE_PATH_REMOTE_NAME "Name"
#define BTIF_STORAGE_PATH_REMOTE_VER_MFCT "Manufacturer"
#define BTIF_STORAGE_PATH_REMOTE_VER_VER "LmpVer"
#define BTIF_STORAGE_PATH_REMOTE_VER_SUBVER "LmpSubVer"

//#define BTIF_STORAGE_PATH_REMOTE_LINKKEYS "remote_linkkeys"
#define BTIF_STORAGE_PATH_REMOTE_ALIASE "Aliase"
#define BTIF_STORAGE_PATH_REMOTE_SERVICE "Service"
#define BTIF_STORAGE_PATH_REMOTE_HIDINFO "HidInfo"
#define BTIF_STORAGE_KEY_ADAPTER_NAME "Name"
#define BTIF_STORAGE_KEY_ADAPTER_SCANMODE "ScanMode"
#define BTIF_STORAGE_KEY_ADAPTER_DISC_TIMEOUT "DiscoveryTimeout"


#define BTIF_AUTO_PAIR_CONF_FILE  "/etc/bluetooth/auto_pair_devlist.conf"
#define BTIF_STORAGE_PATH_AUTOPAIR_BLACKLIST "AutoPairBlacklist"
#define BTIF_STORAGE_KEY_AUTOPAIR_BLACKLIST_ADDR "AddressBlacklist"
#define BTIF_STORAGE_KEY_AUTOPAIR_BLACKLIST_EXACTNAME "ExactNameBlacklist"
#define BTIF_STORAGE_KEY_AUTOPAIR_BLACKLIST_PARTIALNAME "PartialNameBlacklist"
#define BTIF_STORAGE_KEY_AUTOPAIR_FIXPIN_KBLIST "FixedPinZerosKeyboardBlacklist"
#define BTIF_STORAGE_KEY_AUTOPAIR_DYNAMIC_BLACKLIST_ADDR "DynamicAddressBlacklist"

#define BTIF_AUTO_PAIR_CONF_VALUE_SEPARATOR ","
#define BTIF_AUTO_PAIR_CONF_SPACE ' '
#define BTIF_AUTO_PAIR_CONF_COMMENT '#'
#define BTIF_AUTO_PAIR_CONF_KEY_VAL_DELIMETER "="


/* This is a local property to add a device found */
#define BT_PROPERTY_REMOTE_DEVICE_TIMESTAMP 0xFF

#define BTIF_STORAGE_GET_ADAPTER_PROP(t,v,l,p) \
      {p.type=t;p.val=v;p.len=l; btif_storage_get_adapter_property(&p);}

#define BTIF_STORAGE_GET_REMOTE_PROP(b,t,v,l,p) \
      {p.type=t;p.val=v;p.len=l;btif_storage_get_remote_device_property(b,&p);}

#define STORAGE_BDADDR_STRING_SZ           (18)      /* 00:11:22:33:44:55 */
#define STORAGE_UUID_STRING_SIZE           (36+1)    /* 00001200-0000-1000-8000-00805f9b34fb; */
#define STORAGE_PINLEN_STRING_MAX_SIZE     (2)       /* ascii pinlen max chars */
#define STORAGE_KEYTYPE_STRING_MAX_SIZE    (1)       /* ascii keytype max chars */

#define STORAGE_KEY_TYPE_MAX               (10)

#define STORAGE_HID_ATRR_MASK_SIZE           (4)
#define STORAGE_HID_SUB_CLASS_SIZE           (2)
#define STORAGE_HID_APP_ID_SIZE              (2)
#define STORAGE_HID_VENDOR_ID_SIZE           (4)
#define STORAGE_HID_PRODUCT_ID_SIZE          (4)
#define STORAGE_HID_VERSION_SIZE             (4)
#define STORAGE_HID_CTRY_CODE_SIZE           (2)
#define STORAGE_HID_DESC_LEN_SIZE            (4)
#define STORAGE_HID_DESC_MAX_SIZE            (2*512)

/* <18 char bd addr> <space> LIST< <36 char uuid> <;> > <keytype (dec)> <pinlen> */
#define BTIF_REMOTE_SERVICES_ENTRY_SIZE_MAX (STORAGE_BDADDR_STRING_SZ + 1 +\
                                             STORAGE_UUID_STRING_SIZE*BT_MAX_NUM_UUIDS + \
                                             STORAGE_PINLEN_STRING_MAX_SIZE +\
                                             STORAGE_KEYTYPE_STRING_MAX_SIZE)

#define STORAGE_REMOTE_LINKKEYS_ENTRY_SIZE (LINK_KEY_LEN*2 + 1 + 2 + 1 + 2)

/* <18 char bd addr> <space>LIST <attr_mask> <space> > <sub_class> <space> <app_id> <space>
                                <vendor_id> <space> > <product_id> <space> <version> <space>
                                <ctry_code> <space> > <desc_len> <space> <desc_list> <space> */
#define BTIF_HID_INFO_ENTRY_SIZE_MAX    (STORAGE_BDADDR_STRING_SZ + 1 +\
                                         STORAGE_HID_ATRR_MASK_SIZE + 1 +\
                                         STORAGE_HID_SUB_CLASS_SIZE + 1 +\
                                         STORAGE_HID_APP_ID_SIZE+ 1 +\
                                         STORAGE_HID_VENDOR_ID_SIZE+ 1 +\
                                         STORAGE_HID_PRODUCT_ID_SIZE+ 1 +\
                                         STORAGE_HID_VERSION_SIZE+ 1 +\
                                         STORAGE_HID_CTRY_CODE_SIZE+ 1 +\
                                         STORAGE_HID_DESC_LEN_SIZE+ 1 +\
                                         STORAGE_HID_DESC_MAX_SIZE+ 1 )


/* currently remote services is the potentially largest entry */
#define BTIF_STORAGE_MAX_LINE_SZ BTIF_REMOTE_SERVICES_ENTRY_SIZE_MAX


/* check against unv max entry size at compile time */
#if (BTIF_STORAGE_ENTRY_MAX_SIZE > UNV_MAXLINE_LENGTH)
    #error "btif storage entry size exceeds unv max line size"
#endif


#define BTIF_STORAGE_HL_APP          "hl_app"
#define BTIF_STORAGE_HL_APP_CB       "hl_app_cb"
#define BTIF_STORAGE_HL_APP_DATA     "hl_app_data_"
#define BTIF_STORAGE_HL_APP_MDL_DATA "hl_app_mdl_data_"

/************************************************************************************
**  Local type definitions
************************************************************************************/
typedef struct
{
    uint32_t num_devices;
    bt_bdaddr_t devices[BTM_SEC_MAX_DEVICE_RECORDS];
} btif_bonded_devices_t;

/************************************************************************************
**  External variables
************************************************************************************/
extern UINT16 bta_service_id_to_uuid_lkup_tbl [BTA_MAX_SERVICE_ID];
extern bt_bdaddr_t btif_local_bd_addr;

/************************************************************************************
**  External functions
************************************************************************************/

extern void btif_gatts_add_bonded_dev_from_nv(BD_ADDR bda);

/************************************************************************************
**  Internal Functions
************************************************************************************/

bt_status_t btif_in_fetch_bonded_ble_device(char *remote_bd_addr,int add,
                                              btif_bonded_devices_t *p_bonded_devices);
bt_status_t btif_storage_get_remote_addr_type(bt_bdaddr_t *remote_bd_addr,
                                              int *addr_type);

/************************************************************************************
**  Static functions
************************************************************************************/

/*******************************************************************************
**
** Function         btif_in_make_filename
**
** Description      Internal helper function to create NVRAM file path
**                  from address and filename
**
** Returns          NVRAM file path if successfull, NULL otherwise
**
*******************************************************************************/
static char* btif_in_make_filename(bt_bdaddr_t *bd_addr, char *fname)
{
    static char path[256];
    bdstr_t bdstr;

    if (fname == NULL)return NULL;
    if (bd_addr)
    {
        sprintf(path, "%s/%s/%s", BTIF_STORAGE_PATH_BLUEDROID,
                bd2str(bd_addr, &bdstr), fname);
    }
    else
    {
        /* local adapter */
        sprintf(path, "%s/LOCAL/%s", BTIF_STORAGE_PATH_BLUEDROID, fname);
    }

    return(char*)path;
}
/*******************************************************************************
**
** Function         btif_in_split_uuids_string_to_list
**
** Description      Internal helper function to split the string of UUIDs
**                  read from the NVRAM to an array
**
** Returns          None
**
*******************************************************************************/
static void btif_in_split_uuids_string_to_list(char *str, bt_uuid_t *p_uuid,
                                               uint32_t *p_num_uuid)
{
    char buf[64];
    char *p_start = str;
    char *p_needle;
    uint32_t num = 0;
    do
    {
        //p_needle = strchr(p_start, ';');
        p_needle = strchr(p_start, ' ');
        if (p_needle < p_start) break;
        memset(buf, 0, sizeof(buf));
        strncpy(buf, p_start, (p_needle-p_start));
        string_to_uuid(buf, p_uuid + num);
        num++;
        p_start = ++p_needle;

    } while (*p_start != 0);
    *p_num_uuid = num;
}
static int prop2cfg(bt_bdaddr_t *remote_bd_addr, bt_property_t *prop)
{
    bdstr_t bdstr = {0};
    if(remote_bd_addr)
        bd2str(remote_bd_addr, &bdstr);
    BTIF_TRACE_DEBUG3("in, bd addr:%s, prop type:%d, len:%d", bdstr, prop->type, prop->len);
    char value[1024];
    if(prop->len <= 0 || prop->len > (int)sizeof(value) - 1)
    {
        BTIF_TRACE_ERROR2("property type:%d, len:%d is invalid", prop->type, prop->len);
        return FALSE;
    }
    switch(prop->type)
    {
       case BT_PROPERTY_REMOTE_DEVICE_TIMESTAMP:
            btif_config_set_int("Remote", bdstr,
                                BTIF_STORAGE_PATH_REMOTE_DEVTIME, (int)time(NULL));
            static const char* exclude_filter[] =
                        {"LinkKey", "LE_KEY_PENC", "LE_KEY_PID", "LE_KEY_PCSRK", "LE_KEY_LENC", "LE_KEY_LCSRK"};
            btif_config_filter_remove("Remote", exclude_filter, sizeof(exclude_filter)/sizeof(char*),
                        BTIF_STORAGE_MAX_ALLOWED_REMOTE_DEVICE);
            break;
        case BT_PROPERTY_BDNAME:
            strncpy(value, (char*)prop->val, prop->len);
            value[prop->len]='\0';
            if(remote_bd_addr)
                btif_config_set_str("Remote", bdstr,
                                BTIF_STORAGE_PATH_REMOTE_NAME, value);
            else btif_config_set_str("Local", "Adapter",
                                BTIF_STORAGE_KEY_ADAPTER_NAME, value);
            break;
        case BT_PROPERTY_REMOTE_FRIENDLY_NAME:
            strncpy(value, (char*)prop->val, prop->len);
            value[prop->len]='\0';
            btif_config_set_str("Remote", bdstr, BTIF_STORAGE_PATH_REMOTE_ALIASE, value);
            break;
        case BT_PROPERTY_ADAPTER_SCAN_MODE:
            btif_config_set_int("Local", "Adapter",
                                BTIF_STORAGE_KEY_ADAPTER_SCANMODE, *(int*)prop->val);
            break;
        case BT_PROPERTY_ADAPTER_DISCOVERY_TIMEOUT:
            btif_config_set_int("Local", "Adapter",
                                BTIF_STORAGE_KEY_ADAPTER_DISC_TIMEOUT, *(int*)prop->val);
            break;
        case BT_PROPERTY_CLASS_OF_DEVICE:
            btif_config_set_int("Remote", bdstr,
                                BTIF_STORAGE_PATH_REMOTE_DEVCLASS, *(int*)prop->val);
            break;
        case BT_PROPERTY_TYPE_OF_DEVICE:
            btif_config_set_int("Remote", bdstr,
                                BTIF_STORAGE_PATH_REMOTE_DEVTYPE, *(int*)prop->val);
            break;
        case BT_PROPERTY_UUIDS:
        {
            uint32_t i;
            char buf[64];
            value[0] = 0;
            for (i=0; i < (prop->len)/sizeof(bt_uuid_t); i++)
            {
                bt_uuid_t *p_uuid = (bt_uuid_t*)prop->val + i;
                memset(buf, 0, sizeof(buf));
                uuid_to_string(p_uuid, buf);
                strcat(value, buf);
                //strcat(value, ";");
                strcat(value, " ");
            }
            btif_config_set_str("Remote", bdstr, BTIF_STORAGE_PATH_REMOTE_SERVICE, value);
            btif_config_save();
            break;
        }
        case BT_PROPERTY_REMOTE_VERSION_INFO:
        {
            bt_remote_version_t *info = (bt_remote_version_t *)prop->val;

            if (!info)
                return FALSE;

            btif_config_set_int("Remote", bdstr,
                                BTIF_STORAGE_PATH_REMOTE_VER_MFCT, info->manufacturer);
            btif_config_set_int("Remote", bdstr,
                                BTIF_STORAGE_PATH_REMOTE_VER_VER, info->version);
            btif_config_set_int("Remote", bdstr,
                                BTIF_STORAGE_PATH_REMOTE_VER_SUBVER, info->sub_ver);
            btif_config_save();
         } break;

        default:
             BTIF_TRACE_ERROR1("Unknow prop type:%d", prop->type);
             return FALSE;
    }
    return TRUE;
}
static int cfg2prop(bt_bdaddr_t *remote_bd_addr, bt_property_t *prop)
{
    bdstr_t bdstr = {0};
    if(remote_bd_addr)
        bd2str(remote_bd_addr, &bdstr);
    BTIF_TRACE_DEBUG3("in, bd addr:%s, prop type:%d, len:%d", bdstr, prop->type, prop->len);
    if(prop->len <= 0)
    {
        BTIF_TRACE_ERROR2("property type:%d, len:%d is invalid", prop->type, prop->len);
        return FALSE;
    }
    int ret = FALSE;
    switch(prop->type)
    {
       case BT_PROPERTY_REMOTE_DEVICE_TIMESTAMP:
            if(prop->len >= (int)sizeof(int))
                ret = btif_config_get_int("Remote", bdstr,
                                        BTIF_STORAGE_PATH_REMOTE_DEVTIME, (int*)prop->val);
            break;
        case BT_PROPERTY_BDNAME:
        {
            int len = prop->len;
            if(remote_bd_addr)
                ret = btif_config_get_str("Remote", bdstr,
                                        BTIF_STORAGE_PATH_REMOTE_NAME, (char*)prop->val, &len);
            else ret = btif_config_get_str("Local", "Adapter",
                                        BTIF_STORAGE_KEY_ADAPTER_NAME, (char*)prop->val, &len);
            if(ret && len && len <= prop->len)
                prop->len = len - 1;
            else
            {
                prop->len = 0;
                ret = FALSE;
            }
            break;
        }
        case BT_PROPERTY_REMOTE_FRIENDLY_NAME:
        {
            int len = prop->len;
            ret = btif_config_get_str("Remote", bdstr,
                                       BTIF_STORAGE_PATH_REMOTE_ALIASE, (char*)prop->val, &len);
            if(ret && len && len <= prop->len)
                prop->len = len - 1;
            else
            {
                prop->len = 0;
                ret = FALSE;
            }
            break;
        }
        case BT_PROPERTY_ADAPTER_SCAN_MODE:
           if(prop->len >= (int)sizeof(int))
                ret = btif_config_get_int("Local", "Adapter",
                                          BTIF_STORAGE_KEY_ADAPTER_SCANMODE, (int*)prop->val);
           break;
        case BT_PROPERTY_ADAPTER_DISCOVERY_TIMEOUT:
           if(prop->len >= (int)sizeof(int))
                ret = btif_config_get_int("Local", "Adapter",
                                          BTIF_STORAGE_KEY_ADAPTER_DISC_TIMEOUT, (int*)prop->val);
            break;
        case BT_PROPERTY_CLASS_OF_DEVICE:
            if(prop->len >= (int)sizeof(int))
                ret = btif_config_get_int("Remote", bdstr,
                                BTIF_STORAGE_PATH_REMOTE_DEVCLASS, (int*)prop->val);
            break;
        case BT_PROPERTY_TYPE_OF_DEVICE:
            if(prop->len >= (int)sizeof(int))
                ret = btif_config_get_int("Remote",
                                    bdstr, BTIF_STORAGE_PATH_REMOTE_DEVTYPE, (int*)prop->val);
            break;
        case BT_PROPERTY_UUIDS:
        {
            char value[1280];
            int size = sizeof(value);
            if(btif_config_get_str("Remote", bdstr,
                                    BTIF_STORAGE_PATH_REMOTE_SERVICE, value, &size))
            {
                bt_uuid_t *p_uuid = (bt_uuid_t*)prop->val;
                uint32_t num_uuids = 0;
                btif_in_split_uuids_string_to_list(value, p_uuid, &num_uuids);
                prop->len = num_uuids * sizeof(bt_uuid_t);
                ret = TRUE;
            }
            else
            {
                prop->val = NULL;
                prop->len = 0;
            }
        } break;

        case BT_PROPERTY_REMOTE_VERSION_INFO:
        {
            bt_remote_version_t *info = (bt_remote_version_t *)prop->val;

            if(prop->len >= (int)sizeof(bt_remote_version_t))
            {
                ret = btif_config_get_int("Remote", bdstr,
                                BTIF_STORAGE_PATH_REMOTE_VER_MFCT, &info->manufacturer);

                if (ret == TRUE)
                    ret = btif_config_get_int("Remote", bdstr,
                                BTIF_STORAGE_PATH_REMOTE_VER_VER, &info->version);

                if (ret == TRUE)
                    ret = btif_config_get_int("Remote", bdstr,
                                BTIF_STORAGE_PATH_REMOTE_VER_SUBVER, &info->sub_ver);
            }
         } break;

        default:
            BTIF_TRACE_ERROR1("Unknow prop type:%d", prop->type);
            return FALSE;
    }
    return ret;
}


/*******************************************************************************
**
** Function         btif_in_fetch_bonded_devices
**
** Description      Internal helper function to fetch the bonded devices
**                  from NVRAM
**
** Returns          BT_STATUS_SUCCESS if successful, BT_STATUS_FAIL otherwise
**
*******************************************************************************/
static bt_status_t btif_in_fetch_bonded_devices(btif_bonded_devices_t *p_bonded_devices, int add)
{
    BTIF_TRACE_DEBUG1("in add:%d", add);
    memset(p_bonded_devices, 0, sizeof(btif_bonded_devices_t));

    char kname[128], vname[128];
    short kpos;
    int kname_size;
    kname_size = sizeof(kname);
    kname[0] = 0;
    kpos = 0;
    BOOLEAN bt_linkkey_file_found=FALSE;
    int device_type;

    do
    {
        kpos = btif_config_next_key(kpos, "Remote", kname, &kname_size);
        BTIF_TRACE_DEBUG2("Remote device:%s, size:%d", kname, kname_size);
        int type = BTIF_CFG_TYPE_BIN;
        LINK_KEY link_key;
        int size = sizeof(link_key);
        if(btif_config_get("Remote", kname, "LinkKey", (char*)link_key, &size, &type))
        {
            int linkkey_type;
            if(btif_config_get_int("Remote", kname, "LinkKeyType", &linkkey_type))
            {
                //int pin_len;
                //btif_config_get_int("Remote", kname, "PinLength", &pin_len))
                bt_bdaddr_t bd_addr;
                str2bd(kname, &bd_addr);
                if(add)
                {
                    DEV_CLASS dev_class = {0, 0, 0};
                    int cod;
                    if(btif_config_get_int("Remote", kname, "DevClass", &cod))
                        uint2devclass((UINT32)cod, dev_class);
                    BTA_DmAddDevice(bd_addr.address, dev_class, link_key, 0, 0, (UINT8)linkkey_type, 0);

#if BLE_INCLUDED == TRUE
                    if (btif_config_get_int("Remote", kname, "DevType", &device_type) &&
                       (device_type == BT_DEVICE_TYPE_DUMO) )
                    {
                        btif_gatts_add_bonded_dev_from_nv(bd_addr.address);
                    }
#endif
                }
                bt_linkkey_file_found = TRUE;
                memcpy(&p_bonded_devices->devices[p_bonded_devices->num_devices++], &bd_addr, sizeof(bt_bdaddr_t));
            }
            else
            {
#if (BLE_INCLUDED == TRUE)
                bt_linkkey_file_found = FALSE;
#else
                BTIF_TRACE_ERROR1("bounded device:%s, LinkKeyType or PinLength is invalid", kname);
#endif
            }
        }
#if (BLE_INCLUDED == TRUE)
            if(!(btif_in_fetch_bonded_ble_device(kname,add, p_bonded_devices)) && (!bt_linkkey_file_found))
            {
                BTIF_TRACE_DEBUG1("Remote device:%s, no link key or ble key found", kname);
            }
#else
            if(!bt_linkkey_file_found)
                BTIF_TRACE_DEBUG1("Remote device:%s, no link key", kname);
#endif
        kname_size = sizeof(kname);
        kname[0] = 0;
    } while(kpos != -1);
    BTIF_TRACE_DEBUG0("out");
    return BT_STATUS_SUCCESS;
}

static int hex_str_to_int(const char* str, int size)
{
    int  n = 0;
    char c = *str++;
    while (size-- != 0)
    {
        n <<= 4;
        if (c >= '0' && c <= '9') {
            n |= c - '0';
        }
        else if (c >= 'a' && c <= 'z') {
            n |= c - 'a' + 10;
        }
        else // (c >= 'A' && c <= 'Z')
        {
            n |= c - 'A' + 10;
        }

        c = *str++;
    }
    return n;
}

/************************************************************************************
**  Externs
************************************************************************************/

/************************************************************************************
**  Functions
************************************************************************************/

/** functions are synchronous.
 * functions can be called by both internal modules such as BTIF_DM and by external entiries from HAL via BTIF_context_switch
 * For OUT parameters,  caller is expected to provide the memory.
 * Caller is expected to provide a valid pointer to 'property->value' based on the property->type
 */
/*******************************************************************************
**
** Function         btif_storage_get_adapter_property
**
** Description      BTIF storage API - Fetches the adapter property->type
**                  from NVRAM and fills property->val.
**                  Caller should provide memory for property->val and
**                  set the property->val
**
** Returns          BT_STATUS_SUCCESS if the fetch was successful,
**                  BT_STATUS_FAIL otherwise
**
*******************************************************************************/
bt_status_t btif_storage_get_adapter_property(bt_property_t *property)
{

    /* Special handling for adapter BD_ADDR and BONDED_DEVICES */
    if (property->type == BT_PROPERTY_BDADDR)
    {
        BD_ADDR addr;
        bt_bdaddr_t *bd_addr = (bt_bdaddr_t*)property->val;
        /* This has been cached in btif. Just fetch it from there */
        memcpy(bd_addr, &btif_local_bd_addr, sizeof(bt_bdaddr_t));
        property->len = sizeof(bt_bdaddr_t);
        return BT_STATUS_SUCCESS;
    }
    else if (property->type == BT_PROPERTY_ADAPTER_BONDED_DEVICES)
    {
        btif_bonded_devices_t bonded_devices;

        btif_in_fetch_bonded_devices(&bonded_devices, 0);

        BTIF_TRACE_DEBUG2("%s: Number of bonded devices: %d Property:BT_PROPERTY_ADAPTER_BONDED_DEVICES", __FUNCTION__, bonded_devices.num_devices);

        if (bonded_devices.num_devices > 0)
        {
            property->len = bonded_devices.num_devices * sizeof(bt_bdaddr_t);
            memcpy(property->val, bonded_devices.devices, property->len);
        }

        /* if there are no bonded_devices, then length shall be 0 */
        return BT_STATUS_SUCCESS;
    }
    else if (property->type == BT_PROPERTY_UUIDS)
    {
        /* publish list of local supported services */
        bt_uuid_t *p_uuid = (bt_uuid_t*)property->val;
        uint32_t num_uuids = 0;
        uint32_t i;

        tBTA_SERVICE_MASK service_mask = btif_get_enabled_services_mask();
        BTIF_TRACE_ERROR2("%s service_mask:0x%x", __FUNCTION__, service_mask);
        for (i=0; i < BTA_MAX_SERVICE_ID; i++)
        {
            /* This should eventually become a function when more services are enabled */
            if (service_mask
                &(tBTA_SERVICE_MASK)(1 << i))
            {
                switch (i)
                {
                    case BTA_HFP_SERVICE_ID:
                        {
                            uuid16_to_uuid128(UUID_SERVCLASS_AG_HANDSFREE,
                                              p_uuid+num_uuids);
                            num_uuids++;
                        }
                    /* intentional fall through: Send both BFP & HSP UUIDs if HFP is enabled */
                    case BTA_HSP_SERVICE_ID:
                        {
                            uuid16_to_uuid128(UUID_SERVCLASS_HEADSET_AUDIO_GATEWAY,
                                              p_uuid+num_uuids);
                            num_uuids++;
                        }break;
                    case BTA_A2DP_SERVICE_ID:
                        {
                            uuid16_to_uuid128(UUID_SERVCLASS_AUDIO_SOURCE,
                                              p_uuid+num_uuids);
                            num_uuids++;
                        }break;
                }
            }
        }
        property->len = (num_uuids)*sizeof(bt_uuid_t);
        return BT_STATUS_SUCCESS;
    }

    /* fall through for other properties */
    if(!cfg2prop(NULL, property))
    {
        return btif_dm_get_adapter_property(property);
    }
    return BT_STATUS_SUCCESS;
 }

/*******************************************************************************
**
** Function         btif_storage_set_adapter_property
**
** Description      BTIF storage API - Stores the adapter property
**                  to NVRAM
**
** Returns          BT_STATUS_SUCCESS if the store was successful,
**                  BT_STATUS_FAIL otherwise
**
*******************************************************************************/
bt_status_t btif_storage_set_adapter_property(bt_property_t *property)
{
    return prop2cfg(NULL, property) ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;
}

/*******************************************************************************
**
** Function         btif_storage_get_remote_device_property
**
** Description      BTIF storage API - Fetches the remote device property->type
**                  from NVRAM and fills property->val.
**                  Caller should provide memory for property->val and
**                  set the property->val
**
** Returns          BT_STATUS_SUCCESS if the fetch was successful,
**                  BT_STATUS_FAIL otherwise
**
*******************************************************************************/
bt_status_t btif_storage_get_remote_device_property(bt_bdaddr_t *remote_bd_addr,
                                                    bt_property_t *property)
{
    return cfg2prop(remote_bd_addr, property) ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;
}
/*******************************************************************************
**
** Function         btif_storage_set_remote_device_property
**
** Description      BTIF storage API - Stores the remote device property
**                  to NVRAM
**
** Returns          BT_STATUS_SUCCESS if the store was successful,
**                  BT_STATUS_FAIL otherwise
**
*******************************************************************************/
bt_status_t btif_storage_set_remote_device_property(bt_bdaddr_t *remote_bd_addr,
                                                    bt_property_t *property)
{
    return prop2cfg(remote_bd_addr, property) ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;
}

/*******************************************************************************
**
** Function         btif_storage_add_remote_device
**
** Description      BTIF storage API - Adds a newly discovered device to NVRAM
**                  along with the timestamp. Also, stores the various
**                  properties - RSSI, BDADDR, NAME (if found in EIR)
**
** Returns          BT_STATUS_SUCCESS if the store was successful,
**                  BT_STATUS_FAIL otherwise
**
*******************************************************************************/
bt_status_t btif_storage_add_remote_device(bt_bdaddr_t *remote_bd_addr,
                                           uint32_t num_properties,
                                           bt_property_t *properties)
{
    uint32_t i = 0;
    /* TODO: If writing a property, fails do we go back undo the earlier
     * written properties? */
    for (i=0; i < num_properties; i++)
    {
        /* Ignore the RSSI as this is not stored in DB */
        if (properties[i].type == BT_PROPERTY_REMOTE_RSSI)
            continue;

        /* BD_ADDR for remote device needs special handling as we also store timestamp */
        if (properties[i].type == BT_PROPERTY_BDADDR)
        {
            bt_property_t addr_prop;
            memcpy(&addr_prop, &properties[i], sizeof(bt_property_t));
            addr_prop.type = BT_PROPERTY_REMOTE_DEVICE_TIMESTAMP;
            btif_storage_set_remote_device_property(remote_bd_addr,
                                                    &addr_prop);
        }
        else
        {
            btif_storage_set_remote_device_property(remote_bd_addr,
                                                    &properties[i]);
        }
    }
    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         btif_storage_add_bonded_device
**
** Description      BTIF storage API - Adds the newly bonded device to NVRAM
**                  along with the link-key, Key type and Pin key length
**
** Returns          BT_STATUS_SUCCESS if the store was successful,
**                  BT_STATUS_FAIL otherwise
**
*******************************************************************************/

bt_status_t btif_storage_add_bonded_device(bt_bdaddr_t *remote_bd_addr,
                                           LINK_KEY link_key,
                                           uint8_t key_type,
                                           uint8_t pin_length)
{
    bdstr_t bdstr;
    bd2str(remote_bd_addr, &bdstr);
    int ret = btif_config_set_int("Remote", bdstr, "LinkKeyType", (int)key_type);
    ret &= btif_config_set_int("Remote", bdstr, "PinLength", (int)pin_length);
    ret &= btif_config_set("Remote", bdstr, "LinkKey", (const char*)link_key, sizeof(LINK_KEY), BTIF_CFG_TYPE_BIN);
    /* write bonded info immediately */
    btif_config_flush();
    return ret ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;
}

/*******************************************************************************
**
** Function         btif_storage_remove_bonded_device
**
** Description      BTIF storage API - Deletes the bonded device from NVRAM
**
** Returns          BT_STATUS_SUCCESS if the deletion was successful,
**                  BT_STATUS_FAIL otherwise
**
*******************************************************************************/
bt_status_t btif_storage_remove_bonded_device(bt_bdaddr_t *remote_bd_addr)
{
    bdstr_t bdstr;
    bd2str(remote_bd_addr, &bdstr);
    BTIF_TRACE_DEBUG1("in bd addr:%s", bdstr);
    int ret = 1;
    if(btif_config_exist("Remote", bdstr, "LinkKeyType"))
        ret &= btif_config_remove("Remote", bdstr, "LinkKeyType");
    if(btif_config_exist("Remote", bdstr, "PinLength"))
        ret &= btif_config_remove("Remote", bdstr, "PinLength");
    if(btif_config_exist("Remote", bdstr, "LinkKey"))
        ret &= btif_config_remove("Remote", bdstr, "LinkKey");
    /* write bonded info immediately */
    btif_config_flush();
    return ret ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;

}

/*******************************************************************************
**
** Function         btif_storage_load_bonded_devices
**
** Description      BTIF storage API - Loads all the bonded devices from NVRAM
**                  and adds to the BTA.
**                  Additionally, this API also invokes the adaper_properties_cb
**                  and remote_device_properties_cb for each of the bonded devices.
**
** Returns          BT_STATUS_SUCCESS if successful, BT_STATUS_FAIL otherwise
**
*******************************************************************************/
bt_status_t btif_storage_load_bonded_devices(void)
{
    char *fname;
    btif_bonded_devices_t bonded_devices;
    uint32_t i = 0;
    bt_property_t adapter_props[6];
    uint32_t num_props = 0;
    bt_property_t remote_properties[8];
    bt_bdaddr_t addr;
    bt_bdname_t name, alias;
    bt_scan_mode_t mode;
    uint32_t disc_timeout;
    bt_bdaddr_t *devices_list;
    bt_uuid_t local_uuids[BT_MAX_NUM_UUIDS];
    bt_uuid_t remote_uuids[BT_MAX_NUM_UUIDS];
    uint32_t cod, devtype;

    btif_in_fetch_bonded_devices(&bonded_devices, 1);

    /* Now send the adapter_properties_cb with all adapter_properties */
    {
        memset(adapter_props, 0, sizeof(adapter_props));

        /* BD_ADDR */
        BTIF_STORAGE_GET_ADAPTER_PROP(BT_PROPERTY_BDADDR, &addr, sizeof(addr),
                                      adapter_props[num_props]);
        num_props++;

        /* BD_NAME */
        BTIF_STORAGE_GET_ADAPTER_PROP(BT_PROPERTY_BDNAME, &name, sizeof(name),
                                      adapter_props[num_props]);
        num_props++;

        /* SCAN_MODE */
        /* TODO: At the time of BT on, always report the scan mode as 0 irrespective
         of the scan_mode during the previous enable cycle.
         This needs to be re-visited as part of the app/stack enable sequence
         synchronization */
        mode = BT_SCAN_MODE_NONE;
        adapter_props[num_props].type = BT_PROPERTY_ADAPTER_SCAN_MODE;
        adapter_props[num_props].len = sizeof(mode);
        adapter_props[num_props].val = &mode;
        num_props++;

        /* DISC_TIMEOUT */
        BTIF_STORAGE_GET_ADAPTER_PROP(BT_PROPERTY_ADAPTER_DISCOVERY_TIMEOUT,
                                      &disc_timeout, sizeof(disc_timeout),
                                      adapter_props[num_props]);
        num_props++;

        /* BONDED_DEVICES */
        devices_list = (bt_bdaddr_t*)malloc(sizeof(bt_bdaddr_t)*bonded_devices.num_devices);
        adapter_props[num_props].type = BT_PROPERTY_ADAPTER_BONDED_DEVICES;
        adapter_props[num_props].len = bonded_devices.num_devices * sizeof(bt_bdaddr_t);
        adapter_props[num_props].val = devices_list;
        for (i=0; i < bonded_devices.num_devices; i++)
        {
            memcpy(devices_list + i, &bonded_devices.devices[i], sizeof(bt_bdaddr_t));
        }
        num_props++;

        /* LOCAL UUIDs */
        BTIF_STORAGE_GET_ADAPTER_PROP(BT_PROPERTY_UUIDS,
                                      local_uuids, sizeof(local_uuids),
                                      adapter_props[num_props]);
        num_props++;

        btif_adapter_properties_evt(BT_STATUS_SUCCESS, num_props, adapter_props);

        free(devices_list);
    }

    BTIF_TRACE_EVENT2("%s: %d bonded devices found", __FUNCTION__, bonded_devices.num_devices);

    {
        for (i = 0; i < bonded_devices.num_devices; i++)
        {
            bt_bdaddr_t *p_remote_addr;

            num_props = 0;
            p_remote_addr = &bonded_devices.devices[i];
            memset(remote_properties, 0, sizeof(remote_properties));
            BTIF_STORAGE_GET_REMOTE_PROP(p_remote_addr, BT_PROPERTY_BDNAME,
                                         &name, sizeof(name),
                                         remote_properties[num_props]);
            num_props++;

            BTIF_STORAGE_GET_REMOTE_PROP(p_remote_addr, BT_PROPERTY_REMOTE_FRIENDLY_NAME,
                                         &alias, sizeof(alias),
                                         remote_properties[num_props]);
            num_props++;

            BTIF_STORAGE_GET_REMOTE_PROP(p_remote_addr, BT_PROPERTY_CLASS_OF_DEVICE,
                                         &cod, sizeof(cod),
                                         remote_properties[num_props]);
            num_props++;

            BTIF_STORAGE_GET_REMOTE_PROP(p_remote_addr, BT_PROPERTY_TYPE_OF_DEVICE,
                                         &devtype, sizeof(devtype),
                                         remote_properties[num_props]);
            num_props++;

            BTIF_STORAGE_GET_REMOTE_PROP(p_remote_addr, BT_PROPERTY_UUIDS,
                                         remote_uuids, sizeof(remote_uuids),
                                         remote_properties[num_props]);
            num_props++;

            btif_remote_properties_evt(BT_STATUS_SUCCESS, p_remote_addr,
                                       num_props, remote_properties);
        }
    }
    return BT_STATUS_SUCCESS;
}

#if (BLE_INCLUDED == TRUE)

/*******************************************************************************
**
** Function         btif_storage_add_ble_bonding_key
**
** Description      BTIF storage API - Adds the newly bonded device to NVRAM
**                  along with the ble-key, Key type and Pin key length
**
** Returns          BT_STATUS_SUCCESS if the store was successful,
**                  BT_STATUS_FAIL otherwise
**
*******************************************************************************/

bt_status_t btif_storage_add_ble_bonding_key(bt_bdaddr_t *remote_bd_addr,
                                           char *key,
                                           UINT8 key_type,
                                           UINT8 key_length)
{
    bdstr_t bdstr;
    bd2str(remote_bd_addr, &bdstr);
    const char* name;
    switch(key_type)
    {
        case BTIF_DM_LE_KEY_PENC:
            name = "LE_KEY_PENC";
            break;
        case BTIF_DM_LE_KEY_PID:
            name = "LE_KEY_PID";
            break;
        case BTIF_DM_LE_KEY_PCSRK:
            name = "LE_KEY_PCSRK";
            break;
        case BTIF_DM_LE_KEY_LENC:
            name = "LE_KEY_LENC";
            break;
        case BTIF_DM_LE_KEY_LCSRK:
            name = "LE_KEY_LCSRK";
            break;
        default:
            return BT_STATUS_FAIL;
    }
    int ret = btif_config_set("Remote", bdstr, name, (const char*)key, (int)key_length, BTIF_CFG_TYPE_BIN);
    btif_config_save();
    return ret ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;
}

/*******************************************************************************
**
** Function         btif_storage_get_ble_bonding_key
**
** Description
**
** Returns          BT_STATUS_SUCCESS if the fetch was successful,
**                  BT_STATUS_FAIL otherwise
**
*******************************************************************************/
bt_status_t btif_storage_get_ble_bonding_key(bt_bdaddr_t *remote_bd_addr,
                                             UINT8 key_type,
                                             char *key_value,
                                             int key_length)
{
    bdstr_t bdstr;
    bd2str(remote_bd_addr, &bdstr);
    const char* name;
    int type = BTIF_CFG_TYPE_BIN;
    switch(key_type)
    {
        case BTIF_DM_LE_KEY_PENC:
            name = "LE_KEY_PENC";
            break;
        case BTIF_DM_LE_KEY_PID:
            name = "LE_KEY_PID";
            break;
        case BTIF_DM_LE_KEY_PCSRK:
            name = "LE_KEY_PCSRK";
            break;
        case BTIF_DM_LE_KEY_LENC:
            name = "LE_KEY_LENC";
            break;
        case BTIF_DM_LE_KEY_LCSRK:
            name = "LE_KEY_LCSRK";
            break;
        default:
            return BT_STATUS_FAIL;
    }
    int ret = btif_config_get("Remote", bdstr, name, key_value, &key_length, &type);
    return ret ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;

}

/*******************************************************************************
**
** Function         btif_storage_remove_ble_keys
**
** Description      BTIF storage API - Deletes the bonded device from NVRAM
**
** Returns          BT_STATUS_SUCCESS if the deletion was successful,
**                  BT_STATUS_FAIL otherwise
**
*******************************************************************************/
bt_status_t btif_storage_remove_ble_bonding_keys(bt_bdaddr_t *remote_bd_addr)
{
    bdstr_t bdstr;
    bd2str(remote_bd_addr, &bdstr);
    BTIF_TRACE_DEBUG2(" %s in bd addr:%s",__FUNCTION__, bdstr);
    int ret = 1;
    if(btif_config_exist("Remote", bdstr, "LE_KEY_PENC"))
        ret &= btif_config_remove("Remote", bdstr, "LE_KEY_PENC");
    if(btif_config_exist("Remote", bdstr, "LE_KEY_PID"))
        ret &= btif_config_remove("Remote", bdstr, "LE_KEY_PID");
    if(btif_config_exist("Remote", bdstr, "LE_KEY_PCSRK"))
        ret &= btif_config_remove("Remote", bdstr, "LE_KEY_PCSRK");
    if(btif_config_exist("Remote", bdstr, "LE_KEY_LENC"))
        ret &= btif_config_remove("Remote", bdstr, "LE_KEY_LENC");
    if(btif_config_exist("Remote", bdstr, "LE_KEY_LCSRK"))
        ret &= btif_config_remove("Remote", bdstr, "LE_KEY_LCSRK");
    btif_config_save();
    return ret ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;
}

/*******************************************************************************
**
** Function         btif_storage_add_ble_local_key
**
** Description      BTIF storage API - Adds the ble key to NVRAM
**
** Returns          BT_STATUS_SUCCESS if the store was successful,
**                  BT_STATUS_FAIL otherwise
**
*******************************************************************************/
bt_status_t btif_storage_add_ble_local_key(char *key,
                                           uint8_t key_type,
                                           uint8_t key_length)
{
    const char* name;
    switch(key_type)
    {
        case BTIF_DM_LE_LOCAL_KEY_IR:
            name = "LE_LOCAL_KEY_IR";
            break;
        case BTIF_DM_LE_LOCAL_KEY_IRK:
            name = "LE_LOCAL_KEY_IRK";
            break;
        case BTIF_DM_LE_LOCAL_KEY_DHK:
            name = "LE_LOCAL_KEY_DHK";
            break;
        case BTIF_DM_LE_LOCAL_KEY_ER:
            name = "LE_LOCAL_KEY_ER";
            break;
        default:
            return BT_STATUS_FAIL;
    }
    int ret = btif_config_set("Local", "Adapter", name, (const char*)key, key_length, BTIF_CFG_TYPE_BIN);
    btif_config_save();
    return ret ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;
}

/*******************************************************************************
**
** Function         btif_storage_get_ble_local_key
**
** Description
**
** Returns          BT_STATUS_SUCCESS if the fetch was successful,
**                  BT_STATUS_FAIL otherwise
**
*******************************************************************************/
bt_status_t btif_storage_get_ble_local_key(UINT8 key_type,
                                           char *key_value,
                                           int key_length)
{
    const char* name;
    int type = BTIF_CFG_TYPE_BIN;
    switch(key_type)
    {
        case BTIF_DM_LE_LOCAL_KEY_IR:
            name = "LE_LOCAL_KEY_IR";
            break;
        case BTIF_DM_LE_LOCAL_KEY_IRK:
            name = "LE_LOCAL_KEY_IRK";
            break;
        case BTIF_DM_LE_LOCAL_KEY_DHK:
            name = "LE_LOCAL_KEY_DHK";
            break;
        case BTIF_DM_LE_LOCAL_KEY_ER:
            name = "LE_LOCAL_KEY_ER";
            break;
        default:
            return BT_STATUS_FAIL;
    }
    int ret = btif_config_get("Local", "Adapter", name, key_value, &key_length, &type);
    return ret ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;

}

/*******************************************************************************
**
** Function         btif_storage_remove_ble_local_keys
**
** Description      BTIF storage API - Deletes the bonded device from NVRAM
**
** Returns          BT_STATUS_SUCCESS if the deletion was successful,
**                  BT_STATUS_FAIL otherwise
**
*******************************************************************************/
bt_status_t btif_storage_remove_ble_local_keys(void)
{
    int ret = 1;
    if(btif_config_exist("Local", "Adapter", "LE_LOCAL_KEY_IR"))
        ret &= btif_config_remove("Local", "Adapter", "LE_LOCAL_KEY_IR");
    if(btif_config_exist("Local", "Adapter", "LE_LOCAL_KEY_IRK"))
        ret &= btif_config_remove("Local", "Adapter", "LE_LOCAL_KEY_IRK");
    if(btif_config_exist("Local", "Adapter", "LE_LOCAL_KEY_DHK"))
        ret &= btif_config_remove("Local", "Adapter", "LE_LOCAL_KEY_DHK");
    if(btif_config_exist("Local", "Adapter", "LE_LOCAL_KEY_ER"))
        ret &= btif_config_remove("Local", "Adapter", "LE_LOCAL_KEY_ER");
    btif_config_save();
    return ret ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;
}

bt_status_t btif_in_fetch_bonded_ble_device(char *remote_bd_addr,int add, btif_bonded_devices_t *p_bonded_devices)
{
    int device_type;
    int addr_type;
    char buf[100];
    UINT32 i;
    bt_bdaddr_t bd_addr;
    BD_ADDR bta_bd_addr;
    BOOLEAN is_device_added =FALSE;
    tBTA_LE_KEY_VALUE *p;

    if(!btif_config_get_int("Remote", remote_bd_addr,"DevType", &device_type))
        return BT_STATUS_FAIL;
    if(device_type == BT_DEVICE_TYPE_BLE)
    {
            BTIF_TRACE_DEBUG2("%s %s found a BLE device", __FUNCTION__,remote_bd_addr);
            str2bd(remote_bd_addr, &bd_addr);
            bdcpy(bta_bd_addr, bd_addr.address);
            if (btif_storage_get_remote_addr_type(&bd_addr, &addr_type) != BT_STATUS_SUCCESS)
            {
                return BT_STATUS_FAIL;
            }

            memset(buf, 0, sizeof(buf));
            if (btif_storage_get_ble_bonding_key(&bd_addr,
                                                 BTIF_DM_LE_KEY_PENC,
                                                 buf,
                                                 sizeof(btif_dm_ble_penc_keys_t)) == BT_STATUS_SUCCESS)
            {
                if(add)
                {
                    if (!is_device_added)
                    {
                        BTA_DmAddBleDevice(bta_bd_addr, addr_type, BT_DEVICE_TYPE_BLE);
                        is_device_added = TRUE;
                    }
                    p = (tBTA_LE_KEY_VALUE *)buf;
                    for (i=0; i<16; i++)
                    {
                        BTIF_TRACE_DEBUG2("penc_key.ltk[%d]=0x%02x",i,p->penc_key.ltk[i]);
                    }
                    for (i=0; i<8; i++)
                    {
                        BTIF_TRACE_DEBUG2("penc_key.rand[%d]=0x%02x",i,p->penc_key.rand[i]);
                    }
                    BTIF_TRACE_DEBUG1("p->penc_key.ediv=0x%04x",p->penc_key.ediv);
                    BTIF_TRACE_DEBUG1("p->penc_key.sec_level=0x%02x",p->penc_key.sec_level);
                    BTIF_TRACE_DEBUG1("p->penc_key.key_size=0x%02x",p->penc_key.key_size);
                    BTA_DmAddBleKey (bta_bd_addr, (tBTA_LE_KEY_VALUE *)buf, BTIF_DM_LE_KEY_PENC);
                }
            }

            memset(buf, 0, sizeof(buf));
            if (btif_storage_get_ble_bonding_key(&bd_addr,
                                                 BTIF_DM_LE_KEY_PID,
                                                 buf,
                                                 sizeof(btif_dm_ble_pcsrk_keys_t)) == BT_STATUS_SUCCESS)
            {
                if(add)
                {
                    if (!is_device_added)
                    {
                        BTA_DmAddBleDevice(bta_bd_addr, addr_type, BT_DEVICE_TYPE_BLE);
                        is_device_added = TRUE;
                    }
                    p = (tBTA_LE_KEY_VALUE *)buf;
                    for (i=0; i<16; i++)
                    {
                        BTIF_TRACE_DEBUG2("p->pid_key[%d]=0x%02x",i,p->pid_key.irk[i]);
                    }

                    BTA_DmAddBleKey (bta_bd_addr, (tBTA_LE_KEY_VALUE *)buf, BTIF_DM_LE_KEY_PID);
                }
            }

            memset(buf, 0, sizeof(buf));
            if (btif_storage_get_ble_bonding_key(&bd_addr,
                                                 BTIF_DM_LE_KEY_PCSRK,
                                                 buf,
                                                 sizeof(btif_dm_ble_pcsrk_keys_t)) == BT_STATUS_SUCCESS)
            {
                if(add)
                {
                    if (!is_device_added)
                    {
                        BTA_DmAddBleDevice(bta_bd_addr, addr_type, BT_DEVICE_TYPE_BLE);
                        is_device_added = TRUE;
                    }

                    p = (tBTA_LE_KEY_VALUE *)buf;
                    for (i=0; i<16; i++)
                    {
                        BTIF_TRACE_DEBUG2("p->pcsrk_key.csrk[%d]=0x%02x",i, p->psrk_key.csrk[i]);
                    }
                    BTIF_TRACE_DEBUG1("p->pcsrk_key.counter=0x%08x",p->psrk_key.counter);
                    BTIF_TRACE_DEBUG1("p->pcsrk_key.sec_level=0x%02x",p->psrk_key.sec_level);

                    BTA_DmAddBleKey (bta_bd_addr, (tBTA_LE_KEY_VALUE *)buf, BTIF_DM_LE_KEY_PCSRK);
                }
            }

            memset(buf, 0, sizeof(buf));
            if (btif_storage_get_ble_bonding_key(&bd_addr,
                                                 BTIF_DM_LE_KEY_LENC,
                                                 buf,
                                                 sizeof(btif_dm_ble_lenc_keys_t)) == BT_STATUS_SUCCESS)
            {
                if(add)
                {
                    if (!is_device_added)
                    {
                        BTA_DmAddBleDevice(bta_bd_addr, addr_type, BT_DEVICE_TYPE_BLE);
                        is_device_added = TRUE;
                    }
                    p = (tBTA_LE_KEY_VALUE *)buf;
                    BTIF_TRACE_DEBUG1("p->lenc_key.div=0x%04x",p->lenc_key.div);
                    BTIF_TRACE_DEBUG1("p->lenc_key.key_size=0x%02x",p->lenc_key.key_size);
                    BTIF_TRACE_DEBUG1("p->lenc_key.sec_level=0x%02x",p->lenc_key.sec_level);

                    BTA_DmAddBleKey (bta_bd_addr, (tBTA_LE_KEY_VALUE *)buf, BTIF_DM_LE_KEY_LENC);
                }
            }

            memset(buf, 0, sizeof(buf));
            if (btif_storage_get_ble_bonding_key(&bd_addr,
                                                 BTIF_DM_LE_KEY_LCSRK,
                                                 buf,
                                                 sizeof(btif_dm_ble_lcsrk_keys_t)) == BT_STATUS_SUCCESS)
            {
                if(add)
                {
                    if (!is_device_added)
                    {
                        BTA_DmAddBleDevice(bta_bd_addr, addr_type, BT_DEVICE_TYPE_BLE);
                        is_device_added = TRUE;
                    }
                    p = (tBTA_LE_KEY_VALUE *)buf;
                    BTIF_TRACE_DEBUG1("p->lcsrk_key.div=0x%04x",p->lcsrk_key.div);
                    BTIF_TRACE_DEBUG1("p->lcsrk_key.counter=0x%08x",p->lcsrk_key.counter);
                    BTIF_TRACE_DEBUG1("p->lcsrk_key.sec_level=0x%02x",p->lcsrk_key.sec_level);

                    BTA_DmAddBleKey (bta_bd_addr, (tBTA_LE_KEY_VALUE *)buf, BTIF_DM_LE_KEY_LCSRK);
                }
            }

            /* Fill in the bonded devices */
            if (is_device_added)
            {
                memcpy(&p_bonded_devices->devices[p_bonded_devices->num_devices++], &bd_addr, sizeof(bt_bdaddr_t));
                btif_gatts_add_bonded_dev_from_nv(bta_bd_addr);
            }

            return BT_STATUS_SUCCESS;
    }
    return BT_STATUS_FAIL;
}

bt_status_t btif_storage_set_remote_addr_type(bt_bdaddr_t *remote_bd_addr,
                                              UINT8 addr_type)
{
    bdstr_t bdstr;
    bd2str(remote_bd_addr, &bdstr);
    int ret = btif_config_set_int("Remote", bdstr, "AddrType", (int)addr_type);
    btif_config_save();
    return ret ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;
}

/*******************************************************************************
**
** Function         btif_storage_get_remote_addr_type
**
** Description      BTIF storage API - Fetches the remote addr type
**
** Returns          BT_STATUS_SUCCESS if the fetch was successful,
**                  BT_STATUS_FAIL otherwise
**
*******************************************************************************/
bt_status_t btif_storage_get_remote_addr_type(bt_bdaddr_t *remote_bd_addr,
                                              int*addr_type)
{
    bdstr_t bdstr;
    bd2str(remote_bd_addr, &bdstr);
    int ret = btif_config_get_int("Remote", bdstr, "AddrType", addr_type);
    return ret ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;
}
#endif
/*******************************************************************************
**
** Function         btif_storage_add_hid_device_info
**
** Description      BTIF storage API - Adds the hid information of bonded hid devices-to NVRAM
**
** Returns          BT_STATUS_SUCCESS if the store was successful,
**                  BT_STATUS_FAIL otherwise
**
*******************************************************************************/

bt_status_t btif_storage_add_hid_device_info(bt_bdaddr_t *remote_bd_addr,
                                                    UINT16 attr_mask, UINT8 sub_class,
                                                    UINT8 app_id, UINT16 vendor_id,
                                                    UINT16 product_id, UINT16 version,
                                                    UINT8 ctry_code, UINT16 ssr_max_latency,
                                                    UINT16 ssr_min_tout, UINT16 dl_len, UINT8 *dsc_list)
{
    bdstr_t bdstr;
    BTIF_TRACE_DEBUG0("btif_storage_add_hid_device_info:");
    bd2str(remote_bd_addr, &bdstr);
    btif_config_set_int("Remote", bdstr, "HidAttrMask", attr_mask);
    btif_config_set_int("Remote", bdstr, "HidSubClass", sub_class);
    btif_config_set_int("Remote", bdstr, "HidAppId", app_id);
    btif_config_set_int("Remote", bdstr, "HidVendorId", vendor_id);
    btif_config_set_int("Remote", bdstr, "HidProductId", product_id);
    btif_config_set_int("Remote", bdstr, "HidVersion", version);
    btif_config_set_int("Remote", bdstr, "HidCountryCode", ctry_code);
    btif_config_set_int("Remote", bdstr, "HidSSRMaxLatency", ssr_max_latency);
    btif_config_set_int("Remote", bdstr, "HidSSRMinTimeout", ssr_min_tout);
    if(dl_len > 0)
        btif_config_set("Remote", bdstr, "HidDescriptor", (const char*)dsc_list, dl_len,
                        BTIF_CFG_TYPE_BIN);
    btif_config_save();
    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         btif_storage_load_bonded_hid_info
**
** Description      BTIF storage API - Loads hid info for all the bonded devices from NVRAM
**                  and adds those devices  to the BTA_HH.
**
** Returns          BT_STATUS_SUCCESS if successful, BT_STATUS_FAIL otherwise
**
*******************************************************************************/
bt_status_t btif_storage_load_bonded_hid_info(void)
{
    bt_bdaddr_t bd_addr;
    tBTA_HH_DEV_DSCP_INFO dscp_info;
    uint32_t i;
    uint16_t attr_mask;
    uint8_t  sub_class;
    uint8_t  app_id;

    char kname[128], vname[128];
    short kpos;
    int kname_size;
    kname_size = sizeof(kname);
    kname[0] = 0;
    kpos = 0;
    memset(&dscp_info, 0, sizeof(dscp_info));
    do
    {
        kpos = btif_config_next_key(kpos, "Remote", kname, &kname_size);
        BTIF_TRACE_DEBUG2("Remote device:%s, size:%d", kname, kname_size);
        int value;
        if(btif_config_get_int("Remote", kname, "HidAttrMask", &value))
        {
            attr_mask = (uint16_t)value;

            btif_config_get_int("Remote", kname, "HidSubClass", &value);
            sub_class = (uint8_t)value;

            btif_config_get_int("Remote", kname, "HidAppId", &value);
            app_id = (uint8_t)value;

            btif_config_get_int("Remote", kname, "HidVendorId", &value);
            dscp_info.vendor_id = (uint16_t) value;

            btif_config_get_int("Remote", kname, "HidProductId", &value);
            dscp_info.product_id = (uint16_t) value;

            btif_config_get_int("Remote", kname, "HidVersion", &value);
            dscp_info.version = (uint8_t) value;

            btif_config_get_int("Remote", kname, "HidCountryCode", &value);
            dscp_info.ctry_code = (uint8_t) value;

            value = 0;
            btif_config_get_int("Remote", kname, "HidSSRMaxLatency", &value);
            dscp_info.ssr_max_latency = (uint16_t) value;

            value = 0;
            btif_config_get_int("Remote", kname, "HidSSRMinTimeout", &value);
            dscp_info.ssr_min_tout = (uint16_t) value;

            int len = 0;
            int type;
            btif_config_get("Remote", kname, "HidDescriptor", NULL, &len, &type);
            if(len > 0)
            {
                dscp_info.descriptor.dl_len = (uint16_t)len;
                dscp_info.descriptor.dsc_list = (uint8_t*)alloca(len);
                btif_config_get("Remote", kname, "HidDescriptor", (char*)dscp_info.descriptor.dsc_list, &len, &type);
            }
            str2bd(kname, &bd_addr);
            // add extracted information to BTA HH
            if (btif_hh_add_added_dev(bd_addr,attr_mask))
            {
                BTA_HhAddDev(bd_addr.address, attr_mask, sub_class,
                        app_id, dscp_info);
            }
        }
    } while(kpos != -1);

    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         btif_storage_remove_hid_info
**
** Description      BTIF storage API - Deletes the bonded hid device info from NVRAM
**
** Returns          BT_STATUS_SUCCESS if the deletion was successful,
**                  BT_STATUS_FAIL otherwise
**
*******************************************************************************/
bt_status_t btif_storage_remove_hid_info(bt_bdaddr_t *remote_bd_addr)
{
    char *fname;
    int ret;
    bdstr_t bdstr;
    bd2str(remote_bd_addr, &bdstr);

    btif_config_remove("Remote", bdstr, "HidAttrMask");
    btif_config_remove("Remote", bdstr, "HidSubClass");
    btif_config_remove("Remote", bdstr, "HidAppId");
    btif_config_remove("Remote", bdstr, "HidVendorId");
    btif_config_remove("Remote", bdstr, "HidProductId");
    btif_config_remove("Remote", bdstr, "HidVersion");
    btif_config_remove("Remote", bdstr, "HidCountryCode");
    btif_config_remove("Remote", bdstr, "HidSSRMaxLatency");
    btif_config_remove("Remote", bdstr, "HidSSRMinTimeout");
    btif_config_remove("Remote", bdstr, "HidDescriptor");
    btif_config_save();
    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         btif_storage_read_hl_apps_cb
**
** Description      BTIF storage API - Read HL application control block from NVRAM
**
** Returns          BT_STATUS_SUCCESS if the operation was successful,
**                  BT_STATUS_FAIL otherwise
**
*******************************************************************************/
bt_status_t btif_storage_read_hl_apps_cb(char *value, int value_size)
{
    bt_status_t bt_status = BT_STATUS_SUCCESS;
    int read_size=value_size, read_type=BTIF_CFG_TYPE_BIN;

    if (!btif_config_exist("Local", BTIF_STORAGE_HL_APP, BTIF_STORAGE_HL_APP_CB))
    {
        memset(value, 0, value_size);
        if (!btif_config_set("Local", BTIF_STORAGE_HL_APP,BTIF_STORAGE_HL_APP_CB,
                             value, value_size, BTIF_CFG_TYPE_BIN))
        {
            bt_status = BT_STATUS_FAIL;
        }
        else
        {
            btif_config_save();
        }
    }
    else
    {
        if (!btif_config_get("Local", BTIF_STORAGE_HL_APP, BTIF_STORAGE_HL_APP_CB,
                             value, &read_size, &read_type))
        {
            bt_status = BT_STATUS_FAIL;
        }
        else
        {
            if ((read_size != value_size) || (read_type != BTIF_CFG_TYPE_BIN) )
            {
                BTIF_TRACE_ERROR4("%s  value_size=%d read_size=%d read_type=%d",
                                  __FUNCTION__, value_size, read_size, read_type);
                bt_status = BT_STATUS_FAIL;
            }
        }

    }

    BTIF_TRACE_DEBUG3("%s  status=%d value_size=%d", __FUNCTION__, bt_status, value_size);
    return bt_status;
}


/*******************************************************************************
**
** Function         btif_storage_load_autopair_device_list
**
** Description      BTIF storage API - Populates auto pair device list
**
** Returns          BT_STATUS_SUCCESS if the auto pair blacklist is successfully populated
**                  BT_STATUS_FAIL otherwise
**
*******************************************************************************/

bt_status_t btif_storage_load_autopair_device_list()
{
    char *key_name, *key_value;
    int i=0;
    char linebuf[BTIF_STORAGE_MAX_LINE_SZ];
    char *line;
    FILE *fp;

    if(!btif_config_exist("Local", BTIF_STORAGE_PATH_AUTOPAIR_BLACKLIST, NULL))
    {
        /* first time loading of auto pair blacklist configuration  */

        fp = fopen (BTIF_AUTO_PAIR_CONF_FILE, "r");

        if (fp == NULL)
        {
            ALOGE("%s: Failed to open auto pair blacklist conf file at %s", __FUNCTION__,BTIF_AUTO_PAIR_CONF_FILE );
            return BT_STATUS_FAIL;
        }

        /* read through auto_pairing.conf file and create the key value pairs specific to  auto pair blacklist devices */
        while (fgets(linebuf, BTIF_STORAGE_MAX_LINE_SZ, fp) != NULL)
        {
            /* trip  leading white spaces */
            while (linebuf[i] == BTIF_AUTO_PAIR_CONF_SPACE)
                i++;

            /* skip  commented lines */
            if (linebuf[i] == BTIF_AUTO_PAIR_CONF_COMMENT)
                continue;

            line = (char*)&(linebuf[i]);

            if (line == NULL)
                continue;

            key_name = strtok(line, BTIF_AUTO_PAIR_CONF_KEY_VAL_DELIMETER);

            if (key_name == NULL)
                continue;
            else if((strcmp(key_name, BTIF_STORAGE_KEY_AUTOPAIR_BLACKLIST_ADDR) == 0) ||
                    (strcmp(key_name, BTIF_STORAGE_KEY_AUTOPAIR_BLACKLIST_EXACTNAME) ==0) ||
                    (strcmp(key_name, BTIF_STORAGE_KEY_AUTOPAIR_FIXPIN_KBLIST) ==0 ) ||
                    (strcmp(key_name, BTIF_STORAGE_KEY_AUTOPAIR_BLACKLIST_PARTIALNAME) == 0) ||
                    (strcmp(key_name, BTIF_STORAGE_KEY_AUTOPAIR_DYNAMIC_BLACKLIST_ADDR) == 0))
            {
                key_value = strtok(NULL, BTIF_AUTO_PAIR_CONF_KEY_VAL_DELIMETER);
                btif_config_set_str("Local", BTIF_STORAGE_PATH_AUTOPAIR_BLACKLIST, key_name, key_value);
            }
        }
        fclose(fp);
    }
    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         btif_storage_is_device_autopair_blacklisted
**
** Description      BTIF storage API  Checks if the given device is blacklisted for auto pairing
**
** Returns          TRUE if the device is found in the auto pair blacklist
**                  FALSE otherwise
**
*******************************************************************************/
BOOLEAN  btif_storage_is_device_autopair_blacklisted(bt_bdaddr_t *remote_bd_addr)
{
    char *token;
    int ret;
    bdstr_t bdstr;
    char *dev_name_str;
    uint8_t i = 0;
    char value[BTIF_STORAGE_MAX_LINE_SZ];
    int value_size = sizeof(value);

    bd2str(remote_bd_addr, &bdstr);

    /* Consider only  Lower Address Part from BD Address */
    bdstr[8] = '\0';

    if(btif_config_get_str("Local", BTIF_STORAGE_PATH_AUTOPAIR_BLACKLIST,
                BTIF_STORAGE_KEY_AUTOPAIR_BLACKLIST_ADDR, value, &value_size))
    {
        if (strcasestr(value,bdstr) != NULL)
            return TRUE;
    }

    dev_name_str = BTM_SecReadDevName((remote_bd_addr->address));

    if (dev_name_str != NULL)
    {
        value_size = sizeof(value);
        if(btif_config_get_str("Local", BTIF_STORAGE_PATH_AUTOPAIR_BLACKLIST,
                    BTIF_STORAGE_KEY_AUTOPAIR_BLACKLIST_EXACTNAME, value, &value_size))
        {
            if (strstr(value,dev_name_str) != NULL)
                return TRUE;
        }
        value_size = sizeof(value);
        if(btif_config_get_str("Local", BTIF_STORAGE_PATH_AUTOPAIR_BLACKLIST,
                    BTIF_STORAGE_KEY_AUTOPAIR_BLACKLIST_PARTIALNAME, value, &value_size))
        {
            token = strtok(value, BTIF_AUTO_PAIR_CONF_VALUE_SEPARATOR);
            while (token != NULL)
            {
                if (strstr(dev_name_str, token) != NULL)
                    return TRUE;

                token = strtok(NULL, BTIF_AUTO_PAIR_CONF_VALUE_SEPARATOR);
            }
        }
    }
    if(btif_config_get_str("Local", BTIF_STORAGE_PATH_AUTOPAIR_BLACKLIST,
                BTIF_STORAGE_KEY_AUTOPAIR_DYNAMIC_BLACKLIST_ADDR, value, &value_size))
    {
        if (strstr(value,bdstr) != NULL)
            return TRUE;
    }
    return FALSE;
}

/*******************************************************************************
**
** Function         btif_storage_add_device_to_autopair_blacklist
**
** Description      BTIF storage API - Add a remote device to the auto pairing blacklist
**
** Returns          BT_STATUS_SUCCESS if the device is successfully added to the auto pair blacklist
**                  BT_STATUS_FAIL otherwise
**
*******************************************************************************/
bt_status_t btif_storage_add_device_to_autopair_blacklist(bt_bdaddr_t *remote_bd_addr)
{
    int ret;
    bdstr_t bdstr;
    char linebuf[BTIF_STORAGE_MAX_LINE_SZ+20];
    char input_value [20];

    bd2str(remote_bd_addr, &bdstr);
    strlcpy(input_value, (char*)bdstr, sizeof(input_value));
    strlcat(input_value,BTIF_AUTO_PAIR_CONF_VALUE_SEPARATOR, sizeof(input_value));

    int line_size = sizeof(linebuf);
    if(btif_config_get_str("Local", BTIF_STORAGE_PATH_AUTOPAIR_BLACKLIST,
                            BTIF_STORAGE_KEY_AUTOPAIR_DYNAMIC_BLACKLIST_ADDR, linebuf, &line_size))
    {
         /* Append this address to the dynamic List of BD address  */
        strncat (linebuf, input_value, BTIF_STORAGE_MAX_LINE_SZ);
    }
    else
    {
        strncpy( linebuf,input_value, BTIF_STORAGE_MAX_LINE_SZ);
    }

    /* Write back the key value */
    ret = btif_config_set_str("Local", BTIF_STORAGE_PATH_AUTOPAIR_BLACKLIST,
                        BTIF_STORAGE_KEY_AUTOPAIR_DYNAMIC_BLACKLIST_ADDR, linebuf);

    return ret ? BT_STATUS_SUCCESS:BT_STATUS_FAIL;
}

/*******************************************************************************
**
** Function         btif_storage_is_fixed_pin_zeros_keyboard
**
** Description      BTIF storage API - checks if this device has fixed PIN key device list
**
** Returns          TRUE   if the device is found in the fixed pin keyboard device list
**                  FALSE otherwise
**
*******************************************************************************/
BOOLEAN btif_storage_is_fixed_pin_zeros_keyboard(bt_bdaddr_t *remote_bd_addr)
{
    int ret;
    bdstr_t bdstr;
    char *dev_name_str;
    uint8_t i = 0;
    char linebuf[BTIF_STORAGE_MAX_LINE_SZ];

    bd2str(remote_bd_addr, &bdstr);

    /*consider on LAP part of BDA string*/
    bdstr[8] = '\0';

    int line_size = sizeof(linebuf);
    if(btif_config_get_str("Local", BTIF_STORAGE_PATH_AUTOPAIR_BLACKLIST,
                            BTIF_STORAGE_KEY_AUTOPAIR_FIXPIN_KBLIST, linebuf, &line_size))
    {
        if (strcasestr(linebuf,bdstr) != NULL)
            return TRUE;
    }
    return FALSE;

}

/*******************************************************************************
**
** Function         btif_storage_set_dmt_support_type
**
** Description      Sets DMT support status for a remote device
**
** Returns          BT_STATUS_SUCCESS if config update is successful
**                  BT_STATUS_FAIL otherwise
**
*******************************************************************************/

bt_status_t btif_storage_set_dmt_support_type(const bt_bdaddr_t *remote_bd_addr,
                                                   BOOLEAN dmt_supported)
{
    int ret;
    bdstr_t bdstr = {0};
    if(remote_bd_addr)
    {
        bd2str(remote_bd_addr, &bdstr);
    }
    else
    {
        BTIF_TRACE_ERROR1("%s  NULL BD Address", __FUNCTION__);
        return BT_STATUS_FAIL;
    }

   ret = btif_config_set_int("Remote", bdstr,"DMTSupported", (int)dmt_supported);
   return ret ? BT_STATUS_SUCCESS:BT_STATUS_FAIL;

}

/*******************************************************************************
**
** Function         btif_storage_is_dmt_supported_device
**
** Description      checks if a device supports Dual mode topology
**
** Returns         TRUE if remote address is valid and supports DMT else FALSE
**
*******************************************************************************/

BOOLEAN btif_storage_is_dmt_supported_device(const bt_bdaddr_t *remote_bd_addr)
{
    int    dmt_supported = 0;
    bdstr_t bdstr = {0};
    if(remote_bd_addr)
        bd2str(remote_bd_addr, &bdstr);

    if(remote_bd_addr)
    {
        bd2str(remote_bd_addr, &bdstr);
    }
    else
    {
        BTIF_TRACE_ERROR1("%s  NULL BD Address", __FUNCTION__);
        return FALSE;
    }

    btif_config_get_int("Remote", bdstr,"DMTSupported", &dmt_supported);

    return dmt_supported == 1 ? TRUE:FALSE;
}


