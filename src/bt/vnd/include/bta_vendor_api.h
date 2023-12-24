
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
**  Name:           bta_vendor_api.h
**
**  Description:       VENDOR custom Ble API Bluetooth application definitions
**
*****************************************************************************/
#ifndef BTA_VENDOR_API_H
#define BTA_VENDOR_API_H

#include "bta_api.h"
#include "bta_sys.h"
#include "vendor_api.h"


#define BTA_DM_BLE_PF_ENABLE_EVT       BTM_BLE_PF_ENABLE
#define BTA_DM_BLE_PF_CONFIG_EVT       BTM_BLE_PF_CONFIG
typedef UINT8 tBTA_DM_BLE_PF_EVT;

/* Search callback */
typedef void (tBTA_DM_SCAN_PF_CBACK)(tBTA_DM_BLE_PF_EVT event, tBTA_DM_BLE_PF_COND_TYPE cfg_cond, tBTA_STATUS status);;


#if (BLE_INCLUDED == TRUE && BLE_ANDROID_CONTROLLER_SCAN_FILTER == TRUE)
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
BTA_API extern void BTA_DmBleEnableFilterCondition(BOOLEAN enable,
                                                   tBLE_BD_ADDR *p_target,
                                                   tBTA_DM_SCAN_PF_CBACK *p_cmpl_cback);

/*******************************************************************************
**
** Function         BTA_BrcmInit
**
** Description      This function initializes Broadcom specific VS handler in BTA
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_BrcmInit (void);


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
BTA_API extern void BTA_DmBleCfgFilterCondition(tBTA_DM_BLE_SCAN_COND_OP action,
                                                 tBTA_DM_BLE_PF_COND_TYPE cond_type,
                                                 tBTA_DM_BLE_PF_COND_PARAM *p_cond,
                                                 tBTA_DM_SCAN_PF_CBACK *p_cmpl_cback);
#endif

#ifdef __cplusplus
}
#endif

#endif



