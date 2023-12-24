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
 *  Filename:      btif_gatt.c
 *
 *  Description:   GATT Profile Bluetooth Interface
 *
 *******************************************************************************/

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

#include "bta_api.h"
#include "bta_gatt_api.h"
#include "bd.h"
#include "btif_storage.h"

#include "btif_gatt.h"
#include "btif_gatt_util.h"

const btgatt_callbacks_t *bt_gatt_callbacks = NULL;

extern btgatt_client_interface_t btgattClientInterface;
extern btgatt_server_interface_t btgattServerInterface;

/*******************************************************************************
**
** Function         btif_gatt_init
**
** Description      Initializes the GATT interface
**
** Returns          bt_status_t
**
*******************************************************************************/
static bt_status_t btif_gatt_init( const btgatt_callbacks_t* callbacks )
{
    bt_gatt_callbacks = callbacks;

    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         btif_gatt_cleanup
**
** Description      Closes the GATT interface
**
** Returns          void
**
*******************************************************************************/
static void  btif_gatt_cleanup( void )
{
    if (bt_gatt_callbacks)
        bt_gatt_callbacks = NULL;

    BTA_GATTC_Disable();
    BTA_GATTS_Disable();
}

static const btgatt_interface_t btgattInterface = {
    sizeof(btgattInterface),

    btif_gatt_init,
    btif_gatt_cleanup,

    &btgattClientInterface,
    &btgattServerInterface,
};

/*******************************************************************************
**
** Function         btif_gatt_get_interface
**
** Description      Get the gatt callback interface
**
** Returns          btgatt_interface_t
**
*******************************************************************************/
const btgatt_interface_t *btif_gatt_get_interface()
{
    return &btgattInterface;
}

#endif
