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
**  Name        vendor_hcidefs.h
**
**  Function    This file contains Broadcom Specific Host Controller Interface
**              definitions.
**
******************************************************************************/

#ifndef VENDOR_HCIDEFS_H
#define VENDOR_HCIDEFS_H

/* advertising data payload filter VSC */
#define HCI_VENDOR_BLE_PCF_VSC                (0x0138 | HCI_GRP_VENDOR_SPECIFIC)

/* BLE PCF VSC sub code */
#define BTM_BLE_META_PF_ENABLE          0x00
#define BTM_BLE_META_PF_FEAT_SEL        0x01
#define BTM_BLE_META_PF_ADDR            0x02
#define BTM_BLE_META_PF_UUID            0x03
#define BTM_BLE_META_PF_SOL_UUID        0x04
#define BTM_BLE_META_PF_LOCAL_NAME      0x05
#define BTM_BLE_META_PF_MANU_DATA       0x06
#define BTM_BLE_META_PF_SRVC_DATA       0x07

#endif

