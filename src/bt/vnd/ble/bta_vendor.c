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
**  Name:           bta_vendor.c
**
**  Description:    This is the implementation VENDOR custom Ble APIs
**
*****************************************************************************/

#include "bta_api.h"
#include "bta_vendor_api.h"
#include "bta_sys_int.h"
#include "bta_dm_int.h"
#include "vendor_api.h"
#include "vendor_ble.h"
#include <string.h>

#if (BLE_INCLUDED == TRUE && BLE_ANDROID_CONTROLLER_SCAN_FILTER == TRUE)

static tBTA_DM_SCAN_PF_CBACK *bta_vendor_ble_scan_pf_cmpl_cback = NULL;

/*******************************************************************************
**
** Function         bta_vendor_ble_scan_pf_cmpl
**
** Description      ADV payload filtering operation complete callback
**
**
** Returns         TRUE if handled, otherwise FALSE.
**
*******************************************************************************/
static void bta_vendor_ble_scan_pf_cmpl(tBTM_BLE_PF_ACTION action, tBTM_BLE_PF_COND_TYPE cfg_cond, tBTM_STATUS status)
{
    tBTA_STATUS st = (status == BTM_SUCCESS) ? BTA_SUCCESS: BTA_FAILURE;

    if (bta_vendor_ble_scan_pf_cmpl_cback)
        ((tBTA_DM_SCAN_PF_CBACK *) bta_vendor_ble_scan_pf_cmpl_cback)(action, cfg_cond, st);

}
/*******************************************************************************
**
** Function         bta_vendor_ble_scan_pf_enable
**
** Description      This function processes events for enabling adv payload filtering
**                  feature
**
** Returns         TRUE if handled, otherwise FALSE.
**
*******************************************************************************/
BOOLEAN bta_vendor_ble_scan_pf_enable(tBTA_SYS_VS_BLE_SCAN_PF_ENABLE *p_data)
{
    tBTM_STATUS st;
    tBTA_STATUS status;

    if ((st = BTM_BleEnableFilterCondition(p_data->enable,
                                     p_data->p_target,
                                     (tBTM_BLE_PF_CMPL_CBACK *)p_data->p_cmpl_cback))
            == BTM_CMD_STARTED)
    {
        bta_vendor_ble_scan_pf_cmpl_cback = (tBTA_DM_SCAN_PF_CBACK *)p_data->p_cmpl_cback;
    }
    else
    {
        status = (st == BTM_SUCCESS) ? BTA_SUCCESS: BTA_FAILURE;
        if (p_data->p_cmpl_cback)
            ((tBTA_DM_SCAN_PF_CBACK *) p_data->p_cmpl_cback)(BTA_DM_BLE_PF_CONFIG_EVT, 0, status);
    }

    return TRUE;
}


/*******************************************************************************
**
** Function         bta_vendor_ble_scan_pf_condition
**
** Description      This function processes events for configuring the ADV filtering
**                  condition
**
**
** Returns         TRUE if handled, otherwise FALSE.
**
*******************************************************************************/
BOOLEAN bta_vendor_ble_scan_pf_condition(tBTA_SYS_VS_BLE_SCAN_PF_COND *p_data)
{
    tBTM_STATUS st;
    tBTA_STATUS status;

    if ((st = BTM_BleCfgFilterCondition(p_data->action,
                              p_data->cond_type,
                                        (tBTM_BLE_PF_COND_PARAM *)p_data->p_cond,
                                        bta_vendor_ble_scan_pf_cmpl))
            == BTM_CMD_STARTED)
    {
        bta_vendor_ble_scan_pf_cmpl_cback = (tBTA_DM_SCAN_PF_CBACK *)p_data->p_cmpl_cback;
    }
    else
    {
        status = (st == BTM_SUCCESS) ? BTA_SUCCESS: BTA_FAILURE;
        if (p_data->p_cmpl_cback)
            ((tBTA_DM_SCAN_PF_CBACK *) p_data->p_cmpl_cback)(BTA_DM_BLE_PF_CONFIG_EVT, p_data->cond_type, status);
    }
    return TRUE;
}
#endif
/*******************************************************************************
**
** Function         bta_vendor_evt_hdlr
**
** Description      This function processes events for Broadcom specific features.
**
** Returns         TRUE if handled, otherwise FALSE.
**
*******************************************************************************/
BOOLEAN bta_vendor_evt_hdlr(UINT16 event, void *p)
{
    BOOLEAN   st = TRUE;

    APPL_TRACE_EVENT1("bta_vendor_evt_hdlr :0x%04x", event);

    switch (event)
    {
#if BLE_INCLUDED == TRUE && BLE_ANDROID_CONTROLLER_SCAN_FILTER == TRUE
    case BTA_VS_BLE_SCAN_PF_ENABLE_EVT:
        st = bta_vendor_ble_scan_pf_enable((tBTA_SYS_VS_BLE_SCAN_PF_ENABLE *)p);
        break;

    case BTA_VS_BLE_SCAN_PF_COND_EVT:
        bta_vendor_ble_scan_pf_condition((tBTA_SYS_VS_BLE_SCAN_PF_COND*)p);
        break;
#endif

    default:
        APPL_TRACE_EVENT1("Unknown BTA VS event: %d", event);
        st = FALSE;
        break;
    }

    return st;
}



/*******************************************************************************
**
** Function         BTA_DmBleCfgFilterCondition
**
** Description      This function is called to configure the adv data payload filter
**                  condition.
**
** Parameters       action: to read/write/clear
**                  cond_type: filter condition type.
**                  p_cond: filter condition paramter
**
** Returns          void
**
*******************************************************************************/
void BTA_DmBleCfgFilterCondition(tBTA_DM_BLE_SCAN_COND_OP action,
                                 tBTA_DM_BLE_PF_COND_TYPE cond_type,
                                 tBTA_DM_BLE_PF_COND_PARAM *p_cond,
                                 tBTA_DM_SCAN_PF_CBACK *p_cmpl_cback)
{
#if BLE_INCLUDED == TRUE && BLE_ANDROID_CONTROLLER_SCAN_FILTER == TRUE
    tBTA_DM_API_CFG_FILTER_COND *p_msg;
    UINT16  len = sizeof(tBTA_DM_API_CFG_FILTER_COND) + sizeof(tBTA_DM_BLE_PF_COND_PARAM) + \
                BTM_BLE_PF_STR_LEN_MAX + BTM_BLE_PF_STR_LEN_MAX + sizeof(tBTA_DM_BLE_PF_COND_MASK);

    UINT8 *p;

    if ((p_msg = (tBTA_DM_API_CFG_FILTER_COND *) GKI_getbuf(len)) != NULL)
    {
        memset (p_msg, 0, len);

        p_msg->hdr.event        = BTA_DM_API_CFG_FILTER_COND_EVT;
        p_msg->action           = action;
        p_msg->cond_type        = cond_type;
        p_msg->p_cmpl_cback     = (void *) p_cmpl_cback;

        if (p_cond)
        {
            p_msg->p_cond_param = (tBTA_DM_BLE_PF_COND_PARAM *)(p_msg + 1);
            memcpy(p_msg->p_cond_param, p_cond, sizeof(tBTA_DM_BLE_PF_COND_PARAM));

            p = (UINT8 *)(p_msg->p_cond_param + 1);

            if (cond_type == BTA_DM_BLE_PF_SRVC_DATA_PATTERN ||cond_type == BTA_DM_BLE_PF_MANU_DATA)
            {
                p_msg->p_cond_param->manu_data.p_pattern = p;
                p_msg->p_cond_param->manu_data.data_len = p_cond->manu_data.data_len;
                memcpy(p_msg->p_cond_param->manu_data.p_pattern, p_cond->manu_data.p_pattern, p_cond->manu_data.data_len);
                p += p_cond->manu_data.data_len;

                if (cond_type == BTA_DM_BLE_PF_MANU_DATA)
                {
                    p_msg->p_cond_param->manu_data.company_id_mask = p_cond->manu_data.company_id_mask;
                    if ( p_cond->manu_data.p_pattern_mask != NULL)
                    {
                        p_msg->p_cond_param->manu_data.p_pattern_mask = p;
                        memcpy(p_msg->p_cond_param->manu_data.p_pattern_mask, p_cond->manu_data.p_pattern_mask, p_cond->manu_data.data_len);
                    }
                }
            }
            else if (cond_type == BTA_DM_BLE_PF_LOCAL_NAME)
            {
                p_msg->p_cond_param->local_name.p_data = p;
                memcpy(p_msg->p_cond_param->local_name.p_data, p_cond->local_name.p_data, p_cond->local_name.data_len);

            }
            else if ((cond_type == BTM_BLE_PF_SRVC_UUID || cond_type == BTM_BLE_PF_SRVC_SOL_UUID))
            {
                if (p_cond->srvc_uuid.p_target_addr != NULL)
                {
                    p_msg->p_cond_param->srvc_uuid.p_target_addr = (tBLE_BD_ADDR *)(p);
                    p_msg->p_cond_param->srvc_uuid.p_target_addr->type = p_cond->srvc_uuid.p_target_addr->type;
                    memcpy(p_msg->p_cond_param->srvc_uuid.p_target_addr->bda, p_cond->srvc_uuid.p_target_addr->bda, BD_ADDR_LEN);
                    p = (UINT8*)( p_msg->p_cond_param->srvc_uuid.p_target_addr + 1);
                }
                if (p_cond->srvc_uuid.p_uuid_mask)
                {
                    p_msg->p_cond_param->srvc_uuid.p_uuid_mask = (tBTA_DM_BLE_PF_COND_MASK *)p;
                    memcpy(p_msg->p_cond_param->srvc_uuid.p_uuid_mask, p_cond->srvc_uuid.p_uuid_mask, sizeof(tBTA_DM_BLE_PF_COND_MASK));
                }
            }
        }

        bta_sys_sendmsg(p_msg);
    }
#endif
}

/*******************************************************************************
**
** Function         BTA_DmBleEnableFilterCondition
**
** Description      This function is called to enable the adv data payload filter
**                  condition.
**
** Parameters       p_target: enabble the filter condition on a target device; if NULL
**                            enable the generic scan condition.
**                  enable: enable or disable the filter condition
**
** Returns          void
**
*******************************************************************************/
void BTA_DmBleEnableFilterCondition(BOOLEAN enable, tBLE_BD_ADDR *p_target, tBTA_DM_SCAN_PF_CBACK *p_cmpl_cback)
{
#if BLE_INCLUDED == TRUE && BLE_ANDROID_CONTROLLER_SCAN_FILTER == TRUE
    tBTA_DM_API_ENABLE_SCAN_FILTER *p_msg;
    UINT16  len = sizeof(tBTA_DM_API_ENABLE_SCAN_FILTER) + sizeof(tBLE_BD_ADDR);

    if ((p_msg = (tBTA_DM_API_ENABLE_SCAN_FILTER *) GKI_getbuf(len)) != NULL)
    {
        memset (p_msg, 0, len);

        p_msg->hdr.event        = BTA_DM_API_ENABLE_SCAN_FILTER_EVT;
        p_msg->enable       = enable;
        p_msg->p_cmpl_cback     = (void *) p_cmpl_cback;

        if (p_target)
        {
            p_msg->p_target = (tBLE_BD_ADDR *)(p_msg + 1);
            memcpy(p_msg->p_target, p_target, sizeof(tBLE_BD_ADDR));
        }

        bta_sys_sendmsg(p_msg);
    }
#endif
}

/*******************************************************************************
**
** Function         BTA_BrcmInit
**
** Description      This function initializes Broadcom specific
**
** Returns          void
**
*******************************************************************************/
void BTA_BrcmInit (void)
{
    APPL_TRACE_API0("BTA_BrcmInit");
    bta_sys_cb.p_vs_evt_hdlr = bta_vendor_evt_hdlr;
#if BLE_INCLUDED == TRUE && BLE_ANDROID_CONTROLLER_SCAN_FILTER == TRUE
    btm_ble_vendor_init();
#endif
}


