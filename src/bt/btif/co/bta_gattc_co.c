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


#include "gki.h"
#include "bta_gattc_co.h"
#include "bta_gattc_ci.h"
#include "btif_util.h"

#if( defined BLE_INCLUDED ) && (BLE_INCLUDED == TRUE)
#if( defined BTA_GATT_INCLUDED ) && (BTA_GATT_INCLUDED == TRUE)


/*****************************************************************************
**  Function Declarations
*****************************************************************************/

/*******************************************************************************
**
** Function         bta_gattc_co_cache_open
**
** Description      This callout function is executed by GATTC when a GATT server
**                  cache is ready to be sent.
**
** Parameter        server_bda: server bd address of this cache belongs to
**                  evt: call in event to be passed in when cache open is done.
**                  conn_id: connection ID of this cache operation attach to.
**                  to_save: open cache to save or to load.
**
** Returns          void.
**
*******************************************************************************/
void bta_gattc_co_cache_open(BD_ADDR server_bda, UINT16 evt, UINT16 conn_id, BOOLEAN to_save)
{
    tBTA_GATT_STATUS    status = BTA_GATT_OK;
    UNUSED(to_save);

    /* open NV cache and send call in */
    bta_gattc_ci_cache_open(server_bda, evt, status, conn_id);
}

/*******************************************************************************
**
** Function         bta_gattc_co_cache_load
**
** Description      This callout function is executed by GATT when server cache
**                  is required to load.
**
** Parameter        server_bda: server bd address of this cache belongs to
**                  evt: call in event to be passed in when cache save is done.
**                  num_attr: number of attribute to be save.
**                  attr_index: starting attribute index of the save operation.
**                  conn_id: connection ID of this cache operation attach to.
** Returns
**
*******************************************************************************/
void bta_gattc_co_cache_load(BD_ADDR server_bda, UINT16 evt, UINT16 start_index, UINT16 conn_id)
{
    UINT16              num_attr = 0;
    tBTA_GATTC_NV_ATTR  attr[BTA_GATTC_NV_LOAD_MAX];
    tBTA_GATT_STATUS    status = BTA_GATT_MORE;
    UNUSED(start_index);

    bta_gattc_ci_cache_load(server_bda, evt, num_attr, attr, status, conn_id);
}
/*******************************************************************************
**
** Function         bta_gattc_co_cache_save
**
** Description      This callout function is executed by GATT when a server cache
**                  is available to save.
**
** Parameter        server_bda: server bd address of this cache belongs to
**                  evt: call in event to be passed in when cache save is done.
**                  num_attr: number of attribute to be save.
**                  p_attr: pointer to the list of attributes to save.
**                  attr_index: starting attribute index of the save operation.
**                  conn_id: connection ID of this cache operation attach to.
** Returns
**
*******************************************************************************/
void bta_gattc_co_cache_save (BD_ADDR server_bda, UINT16 evt, UINT16 num_attr,
                              tBTA_GATTC_NV_ATTR *p_attr_list, UINT16 attr_index, UINT16 conn_id)
{
    tBTA_GATT_STATUS    status = BTA_GATT_OK;
    UNUSED(num_attr);
    UNUSED(p_attr_list);
    UNUSED(attr_index);

    bta_gattc_ci_cache_save(server_bda, evt, status, conn_id);
}

/*******************************************************************************
**
** Function         bta_gattc_co_cache_close
**
** Description      This callout function is executed by GATTC when a GATT server
**                  cache is written completely.
**
** Parameter        server_bda: server bd address of this cache belongs to
**                  conn_id: connection ID of this cache operation attach to.
**
** Returns          void.
**
*******************************************************************************/
void bta_gattc_co_cache_close(BD_ADDR server_bda, UINT16 conn_id)
{
    UNUSED(server_bda);
    UNUSED(conn_id);
    /* close NV when server cache is done saving or loading,
       does not need to do anything for now on Insight */
}

/*******************************************************************************
**
** Function         bta_gattc_co_cache_reset
**
** Description      This callout function is executed by GATTC to reset cache in
**                  application
**
** Parameter        server_bda: server bd address of this cache belongs to
**
** Returns          void.
**
*******************************************************************************/
void bta_gattc_co_cache_reset(BD_ADDR server_bda)
{
    UNUSED(server_bda);
}

#endif
#endif

