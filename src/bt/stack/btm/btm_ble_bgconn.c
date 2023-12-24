/******************************************************************************
 *
 *  Copyright (C) 1999-2012 Broadcom Corporation
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

/******************************************************************************
 *
 *  This file contains functions for BLE whitelist operation.
 *
 ******************************************************************************/

#include <string.h>

#include "bt_types.h"
#include "btu.h"
#include "btm_int.h"
#include "l2c_int.h"
#include "hcimsgs.h"
#include "bt_utils.h"

#ifndef BTM_BLE_SCAN_PARAM_TOUT
#define BTM_BLE_SCAN_PARAM_TOUT      50    /* 50 seconds */
#endif

#if (BLE_INCLUDED == TRUE)

static void btm_suspend_wl_activity(tBTM_BLE_WL_STATE wl_state);
static void btm_resume_wl_activity(tBTM_BLE_WL_STATE wl_state);

/*******************************************************************************
**
** Function         btm_update_scanner_filter_policy
**
** Description      This function update the filter policy of scnner or advertiser.
*******************************************************************************/
void btm_update_scanner_filter_policy(tBTM_BLE_SFP scan_policy)
{
    tBTM_BLE_INQ_CB *p_inq = &btm_cb.ble_ctr_cb.inq_var;
    BTM_TRACE_EVENT0 ("btm_update_scanner_filter_policy");

    p_inq->sfp = scan_policy;
    p_inq->scan_type = (p_inq->scan_type == BTM_BLE_SCAN_MODE_NONE) ? BTM_BLE_SCAN_MODE_ACTI: p_inq->scan_type;

    btsnd_hcic_ble_set_scan_params (p_inq->scan_type,
                                    (UINT16)(!p_inq->scan_interval ? BTM_BLE_GAP_DISC_SCAN_INT : p_inq->scan_interval),
                                    (UINT16)(!p_inq->scan_window ? BTM_BLE_GAP_DISC_SCAN_WIN : p_inq->scan_window),
                                     btm_cb.ble_ctr_cb.addr_mgnt_cb.own_addr_type,
                                     scan_policy);
}
/*******************************************************************************
**
** Function         btm_add_dev_to_controller
**
** Description      This function load the device into controller white list
*******************************************************************************/
BOOLEAN btm_add_dev_to_controller (BOOLEAN to_add, BD_ADDR bd_addr, UINT8 attr)
{
    tBTM_SEC_DEV_REC    *p_dev_rec = btm_find_dev (bd_addr);
    tBLE_ADDR_TYPE  addr_type = BLE_ADDR_PUBLIC;
    BOOLEAN             started = FALSE;
    BD_ADDR             dummy_bda = {0};
    tBT_DEVICE_TYPE dev_type;
    UNUSED(attr);

    if (p_dev_rec != NULL &&
        p_dev_rec->device_type == BT_DEVICE_TYPE_BLE)
    {

        if (to_add)
        {
            if (p_dev_rec->ble.ble_addr_type == BLE_ADDR_PUBLIC || !BTM_BLE_IS_RESOLVE_BDA(bd_addr))
            {
                started = btsnd_hcic_ble_add_white_list (p_dev_rec->ble.ble_addr_type, bd_addr);
            }
            if (memcmp(p_dev_rec->ble.static_addr, bd_addr, BD_ADDR_LEN) != 0 &&
                memcmp(p_dev_rec->ble.static_addr, dummy_bda, BD_ADDR_LEN) != 0)
            {
                started = btsnd_hcic_ble_add_white_list (p_dev_rec->ble.static_addr_type,
                                                         p_dev_rec->ble.static_addr);
            }
        }
        else
        {
            if (p_dev_rec->ble.ble_addr_type == BLE_ADDR_PUBLIC || !BTM_BLE_IS_RESOLVE_BDA(bd_addr))
            {
                    started = btsnd_hcic_ble_remove_from_white_list (p_dev_rec->ble.ble_addr_type, bd_addr);
            }
            if (memcmp(p_dev_rec->ble.static_addr, dummy_bda, BD_ADDR_LEN) != 0 &&
                memcmp(p_dev_rec->ble.static_addr, bd_addr, BD_ADDR_LEN) != 0)
            {
                    started = btsnd_hcic_ble_remove_from_white_list (p_dev_rec->ble.static_addr_type, p_dev_rec->ble.static_addr);
            }
        }
    }    /* if not a known device, shall we add it? */
    else
    {
        BTM_ReadDevInfo(bd_addr, &dev_type, &addr_type);

        if (to_add)
            started = btsnd_hcic_ble_add_white_list (addr_type, bd_addr);
        else
            started = btsnd_hcic_ble_remove_from_white_list (addr_type, bd_addr);
    }

    return started;

}
/*******************************************************************************
**
** Function         btm_execute_wl_dev_operation
**
** Description      execute the pending whitelist device operation(loading or removing)
*******************************************************************************/
BOOLEAN btm_execute_wl_dev_operation(void)
{
    tBTM_BLE_WL_OP *p_dev_op = btm_cb.ble_ctr_cb.wl_op_q;
    UINT8   i = 0;
    BOOLEAN rt = TRUE;

    for (i = 0; i < BTM_BLE_MAX_BG_CONN_DEV_NUM && rt; i ++, p_dev_op ++)
    {
        if (p_dev_op->in_use)
        {
            rt = btm_add_dev_to_controller(p_dev_op->to_add, p_dev_op->bd_addr, p_dev_op->attr);
            memset(p_dev_op, 0, sizeof(tBTM_BLE_WL_OP));
        }
        else
            break;
    }
    return rt;
}
/*******************************************************************************
**
** Function         btm_enq_wl_dev_operation
**
** Description      enqueue the pending whitelist device operation(loading or removing).
*******************************************************************************/
void btm_enq_wl_dev_operation(BOOLEAN to_add, BD_ADDR bd_addr, UINT8 attr)
{
    tBTM_BLE_WL_OP *p_dev_op = btm_cb.ble_ctr_cb.wl_op_q;
    UINT8   i = 0;

    for (i = 0; i < BTM_BLE_MAX_BG_CONN_DEV_NUM; i ++, p_dev_op ++)
    {
        if (p_dev_op->in_use && !memcmp(p_dev_op->bd_addr, bd_addr, BD_ADDR_LEN))
        {
            p_dev_op->to_add = to_add;
            p_dev_op->attr = attr;
            return;
        }
        else if (!p_dev_op->in_use)
            break;
    }
    if (i != BTM_BLE_MAX_BG_CONN_DEV_NUM)
    {
        p_dev_op->in_use = TRUE;
        p_dev_op->to_add = to_add;
        p_dev_op->attr  = attr;
        memcpy(p_dev_op->bd_addr, bd_addr, BD_ADDR_LEN);
    }
    else
    {
        BTM_TRACE_ERROR0("max pending WL operation reached, discard");
    }
    return;
}
/*******************************************************************************
**
** Function         btm_update_dev_to_white_list
**
** Description      This function adds a device into white list.
*******************************************************************************/
BOOLEAN btm_update_dev_to_white_list(BOOLEAN to_add, BD_ADDR bd_addr, UINT8 attr)
{
    /* look up the sec device record, and find the address */
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    BOOLEAN     started = FALSE;
    UINT8       wl_state = p_cb->wl_state;

    if ((to_add && p_cb->num_empty_filter == 0) ||
        (!to_add && p_cb->num_empty_filter == p_cb->max_filter_entries))
    {
        BTM_TRACE_ERROR1("WL full or empty, unable to update to WL. num_entry available: %d",
                          p_cb->num_empty_filter);
        return started;
    }

    btm_suspend_wl_activity(wl_state);

    /* enq pending WL device operation */
    btm_enq_wl_dev_operation(to_add, bd_addr, attr);

    btm_resume_wl_activity(wl_state);

    return started;
}
/*******************************************************************************
**
** Function         btm_ble_clear_white_list
**
** Description      This function clears the white list.
*******************************************************************************/
void btm_ble_clear_white_list (void)
{
    BTM_TRACE_EVENT0 ("btm_ble_clear_white_list");
    btsnd_hcic_ble_clear_white_list();
}

/*******************************************************************************
**
** Function         btm_ble_clear_white_list_complete
**
** Description      This function clears the white list complete.
*******************************************************************************/
void btm_ble_clear_white_list_complete(UINT8 *p_data, UINT16 evt_len)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    UINT8       status;
    UNUSED(evt_len);

    BTM_TRACE_EVENT0 ("btm_ble_clear_white_list_complete");
    STREAM_TO_UINT8  (status, p_data);

    if (status == HCI_SUCCESS)
        p_cb->num_empty_filter = p_cb->max_filter_entries;

}
/*******************************************************************************
**
** Function         btm_ble_add_2_white_list_complete
**
** Description      This function read the current white list size.
*******************************************************************************/
void btm_ble_add_2_white_list_complete(UINT8 status)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    BTM_TRACE_EVENT0 ("btm_ble_add_2_white_list_complete");

    if (status == HCI_SUCCESS)
    {
        p_cb->num_empty_filter --;
    }
}
/*******************************************************************************
**
** Function         btm_ble_remove_from_white_list_complete
**
** Description      This function remove the white list element complete.
*******************************************************************************/
void btm_ble_remove_from_white_list_complete(UINT8 *p, UINT16 evt_len)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    UNUSED(evt_len);

    BTM_TRACE_EVENT0 ("btm_ble_remove_from_white_list_complete");
    if (*p == HCI_SUCCESS)
    {
        p_cb->num_empty_filter ++;
    }
}
/*******************************************************************************
**
** Function         btm_ble_count_unconn_dev_in_whitelist
**
** Description      This function find the number of un-connected background device
*******************************************************************************/
UINT8 btm_ble_count_unconn_dev_in_whitelist(void)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    UINT8 i, count = 0;

    for (i = 0; i < BTM_BLE_MAX_BG_CONN_DEV_NUM; i ++)
    {
        if (p_cb->bg_dev_list[i].in_use &&
            !BTM_IsAclConnectionUp(p_cb->bg_dev_list[i].bd_addr, BT_TRANSPORT_LE))
        {
            count ++;
        }
    }
    return count;

}
/*******************************************************************************
**
** Function         btm_update_bg_conn_list
**
** Description      This function update the local background connection device list.
*******************************************************************************/
BOOLEAN btm_update_bg_conn_list(BOOLEAN to_add, BD_ADDR bd_addr, UINT8 *p_attr_tag)
{
    tBTM_BLE_CB             *p_cb = &btm_cb.ble_ctr_cb;
    tBTM_LE_BG_CONN_DEV     *p_bg_dev = &p_cb->bg_dev_list[0], *p_next, *p_cur;
    UINT8                   i, j;
    BOOLEAN             ret = FALSE;
    UNUSED(p_attr_tag);

    BTM_TRACE_EVENT0 ("btm_update_bg_conn_list");

    if ((to_add && (p_cb->bg_dev_num == BTM_BLE_MAX_BG_CONN_DEV_NUM || p_cb->num_empty_filter == 0)))
    {
        BTM_TRACE_DEBUG1("num_empty_filter = %d", p_cb->num_empty_filter);
        return ret;
    }

    for (i = 0; i < BTM_BLE_MAX_BG_CONN_DEV_NUM; i ++, p_bg_dev ++)
    {
        if (p_bg_dev->in_use && memcmp(p_bg_dev->bd_addr, bd_addr, BD_ADDR_LEN) == 0)
        {
            if (!to_add)
            {
                memset(p_bg_dev, 0, sizeof(tBTM_LE_BG_CONN_DEV));
                p_cb->bg_dev_num --;
                p_cur = p_bg_dev;
                p_next = p_bg_dev + 1;
                for (j = i + 1 ;j < BTM_BLE_MAX_BG_CONN_DEV_NUM && p_next->in_use ; j ++, p_cur ++, p_next ++ )
                    memcpy(p_cur, p_next, sizeof(tBTM_LE_BG_CONN_DEV));
            }
            ret = TRUE;
            break;
        }
        else if (!p_bg_dev->in_use && to_add)
        {
            BTM_TRACE_DEBUG0("add new WL entry in bg_dev_list");

            memcpy(p_bg_dev->bd_addr, bd_addr, BD_ADDR_LEN);
            p_bg_dev->in_use = TRUE;
            p_cb->bg_dev_num ++;

            ret = TRUE;
            break;
        }
    }


    return ret;
}

/*******************************************************************************
**
** Function         btm_ble_start_auto_conn
**
** Description      This function is to start/stop auto connection procedure.
**
** Parameters       start: TRUE to start; FALSE to stop.
**
** Returns          void
**
*******************************************************************************/
BOOLEAN btm_ble_start_auto_conn(BOOLEAN start)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    BD_ADDR dummy_bda = {0};
    BOOLEAN exec = TRUE;
    UINT16 scan_int, scan_win;

    if (start)
    {
        if ((p_cb->conn_state == BLE_CONN_IDLE && btm_ble_count_unconn_dev_in_whitelist() > 0)
            && btm_ble_topology_check(BTM_BLE_STATE_INIT))
        {
            btm_execute_wl_dev_operation();

            scan_int = (p_cb->scan_int == BTM_BLE_CONN_PARAM_UNDEF) ? BTM_BLE_SCAN_SLOW_INT_1 : p_cb->scan_int;
            scan_win = (p_cb->scan_win == BTM_BLE_CONN_PARAM_UNDEF) ? BTM_BLE_SCAN_SLOW_WIN_1 : p_cb->scan_win;

            if (!btsnd_hcic_ble_create_ll_conn (scan_int,  /* UINT16 scan_int      */
                                                scan_win,    /* UINT16 scan_win      */
                                                0x01,                   /* UINT8 white_list     */
                                                BLE_ADDR_PUBLIC,        /* UINT8 addr_type_peer */
                                                dummy_bda,              /* BD_ADDR bda_peer     */
                                                p_cb->addr_mgnt_cb.own_addr_type,
                                                   /* UINT8 addr_type_own,
                                                   not allow random address for central  */
                                                BTM_BLE_CONN_INT_MIN_DEF,   /* UINT16 conn_int_min  */
                                                BTM_BLE_CONN_INT_MAX_DEF,   /* UINT16 conn_int_max  */
                                                BTM_BLE_CONN_SLAVE_LATENCY_DEF,  /* UINT16 conn_latency  */
                                                BTM_BLE_CONN_TIMEOUT_DEF,        /* UINT16 conn_timeout  */
                                                0,                       /* UINT16 min_len       */
                                                0))                      /* UINT16 max_len       */
            {
                /* start auto connection failed */
                exec =  FALSE;
            }
            else
            {
                btm_ble_set_conn_st (BLE_BG_CONN);

            }
        }
        else
        {
            exec = FALSE;
        }
    }
    else
    {
        if (p_cb->conn_state == BLE_BG_CONN)
        {
            btsnd_hcic_ble_create_conn_cancel();
            btm_ble_set_conn_st (BLE_CONN_CANCEL);

        }
        else
        {
#if 0
            BTM_TRACE_ERROR1("conn_st = %d, not in auto conn state, can not stop.", p_cb->conn_state);
            exec = FALSE;
#endif
        }
    }
    return exec;
}

/*******************************************************************************
**
** Function         btm_ble_start_select_conn
**
** Description      This function is to start/stop selective connection procedure.
**
** Parameters       start: TRUE to start; FALSE to stop.
**                  p_select_cback: callback function to return application
**                                  selection.
**
** Returns          BOOLEAN: selective connectino procedure is started.
**
*******************************************************************************/
BOOLEAN btm_ble_start_select_conn(BOOLEAN start,tBTM_BLE_SEL_CBACK   *p_select_cback)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    UINT16 scan_int, scan_win;

    BTM_TRACE_EVENT0 ("btm_ble_start_select_conn");

    scan_int = (p_cb->scan_int == BTM_BLE_CONN_PARAM_UNDEF) ? BTM_BLE_SCAN_FAST_INT : p_cb->scan_int;
    scan_win = (p_cb->scan_win == BTM_BLE_CONN_PARAM_UNDEF) ? BTM_BLE_SCAN_FAST_WIN : p_cb->scan_win;

    if (start)
    {
        if (!BTM_BLE_IS_SCAN_ACTIVE(p_cb->scan_activity))
        {
            if (p_select_cback != NULL)
                btm_cb.ble_ctr_cb.p_select_cback = p_select_cback;

            btm_execute_wl_dev_operation();

            btm_update_scanner_filter_policy(SP_ADV_WL);
            btm_cb.ble_ctr_cb.inq_var.scan_type = BTM_BLE_SCAN_MODE_PASS;

            if (!btsnd_hcic_ble_set_scan_params(BTM_BLE_SCAN_MODE_PASS,  /* use passive scan by default */
                                                scan_int, /* scan interval */
                                                scan_win,    /* scan window */
                                                p_cb->addr_mgnt_cb.own_addr_type,
                                                SP_ADV_WL)              /* process advertising packets only from devices in the White List */
                )
                return FALSE;

            if (!btm_ble_topology_check(BTM_BLE_STATE_PASSIVE_SCAN))
            {
                BTM_TRACE_ERROR0("peripheral device cannot initiate passive scan for a selective connection");
                return FALSE;
            }
            else if (p_cb->bg_dev_num > 0 && btm_ble_count_unconn_dev_in_whitelist() > 0 )
            {

                if (!btsnd_hcic_ble_set_scan_enable(TRUE, TRUE)) /* duplicate filtering enabled */
                    return FALSE;

                /* mark up inquiry status flag */
                p_cb->scan_activity |= BTM_LE_SELECT_CONN_ACTIVE;
            }
        }
        else
        {
            BTM_TRACE_ERROR0("scan active, can not start selective connection procedure");
            return FALSE;
        }
    }
    else /* disable selective connection mode */
    {
        p_cb->scan_activity &= ~BTM_LE_SELECT_CONN_ACTIVE;
        p_cb->p_select_cback = NULL;


        /* stop scanning */
        if (!BTM_BLE_IS_SCAN_ACTIVE(p_cb->scan_activity))
            btm_ble_stop_scan(); /* duplicate filtering enabled */
        btm_update_scanner_filter_policy(SP_ADV_ALL);
    }
    return TRUE;
}
/*******************************************************************************
**
** Function         btm_ble_initiate_select_conn
**
** Description      This function is to start/stop selective connection procedure.
**
** Parameters       start: TRUE to start; FALSE to stop.
**                  p_select_cback: callback function to return application
**                                  selection.
**
** Returns          BOOLEAN: selective connectino procedure is started.
**
*******************************************************************************/
void btm_ble_initiate_select_conn(BD_ADDR bda)
{
    BTM_TRACE_EVENT0 ("btm_ble_initiate_select_conn");

    /* use direct connection procedure to initiate connection */
    if (!L2CA_ConnectFixedChnl(L2CAP_ATT_CID, bda))
    {
        BTM_TRACE_ERROR0("btm_ble_initiate_select_conn failed");
    }
}
/*******************************************************************************
**
** Function         btm_ble_suspend_bg_conn
**
** Description      This function is to suspend an active background connection
**                  procedure.
**
** Parameters       none.
**
** Returns          none.
**
*******************************************************************************/
void btm_ble_suspend_bg_conn(void)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    BTM_TRACE_EVENT0 ("btm_ble_suspend_bg_conn");

    if (p_cb->bg_conn_type == BTM_BLE_CONN_AUTO)
    {
        btm_ble_start_auto_conn(FALSE);
    }
    else if (p_cb->bg_conn_type == BTM_BLE_CONN_SELECTIVE)
    {
        btm_ble_start_select_conn(FALSE, NULL);
    }
}
/*******************************************************************************
**
** Function         btm_suspend_wl_activity
**
** Description      This function is to suspend white list related activity
**
** Returns          none.
**
*******************************************************************************/
static void btm_suspend_wl_activity(tBTM_BLE_WL_STATE wl_state)
{
    if (wl_state & BTM_BLE_WL_INIT)
    {
        btm_ble_start_auto_conn(FALSE);
    }
    if (wl_state & BTM_BLE_WL_SCAN)
    {
        btm_ble_start_select_conn(FALSE, NULL);
    }
    if (wl_state & BTM_BLE_WL_ADV)
    {
        btm_ble_stop_adv();
    }

}
/*******************************************************************************
**
** Function         btm_resume_wl_activity
**
** Description      This function is to resume white list related activity
**
** Returns          none.
**
*******************************************************************************/
static void btm_resume_wl_activity(tBTM_BLE_WL_STATE wl_state)
{
    btm_ble_resume_bg_conn();

    if (wl_state & BTM_BLE_WL_ADV)
    {
       btm_ble_start_adv();
    }

}
/*******************************************************************************
**
** Function         btm_ble_resume_bg_conn
**
** Description      This function is to resume a background auto connection
**                  procedure.
**
** Parameters       none.
**
** Returns          none.
**
*******************************************************************************/
BOOLEAN btm_ble_resume_bg_conn(void)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    BOOLEAN ret = FALSE;

    if (p_cb->bg_conn_type != BTM_BLE_CONN_NONE)
    {
        if (p_cb->bg_conn_type == BTM_BLE_CONN_AUTO)
            ret = btm_ble_start_auto_conn(TRUE);

        if (p_cb->bg_conn_type == BTM_BLE_CONN_SELECTIVE)
            ret = btm_ble_start_select_conn(TRUE, btm_cb.ble_ctr_cb.p_select_cback);
    }

    return ret;
}
/*******************************************************************************
**
** Function         btm_ble_get_conn_st
**
** Description      This function get BLE connection state
**
** Returns          connection state
**
*******************************************************************************/
tBTM_BLE_CONN_ST btm_ble_get_conn_st(void)
{
    return btm_cb.ble_ctr_cb.conn_state;
}
/*******************************************************************************
**
** Function         btm_ble_set_conn_st
**
** Description      This function set BLE connection state
**
** Returns          None.
**
*******************************************************************************/
void btm_ble_set_conn_st(tBTM_BLE_CONN_ST new_st)
{
    btm_cb.ble_ctr_cb.conn_state = new_st;
    if (new_st == BLE_BG_CONN || new_st == BLE_DIR_CONN)
        btm_ble_set_topology_mask(BTM_BLE_STATE_INIT_BIT);
    else
        btm_ble_clear_topology_mask(BTM_BLE_STATE_INIT_BIT);
}

/*******************************************************************************
**
** Function         btm_ble_enqueue_direct_conn_req
**
** Description      This function enqueue the direct connection request
**
** Returns          None.
**
*******************************************************************************/
void btm_ble_enqueue_direct_conn_req(void *p_param)
{
    tBTM_BLE_CONN_REQ   *p = (tBTM_BLE_CONN_REQ *)GKI_getbuf(sizeof(tBTM_BLE_CONN_REQ));

    p->p_param = p_param;

    GKI_enqueue (&btm_cb.ble_ctr_cb.conn_pending_q, p);
}
/*******************************************************************************
**
** Function         btm_send_pending_direct_conn
**
** Description      This function send the pending direct connection request in queue
**
** Returns          TRUE if started, FALSE otherwise
**
*******************************************************************************/
BOOLEAN btm_send_pending_direct_conn(void )
{
    tBTM_BLE_CONN_REQ *p_req;
    BOOLEAN     rt = FALSE;

    if ( btm_cb.ble_ctr_cb.conn_pending_q.count )
    {
        p_req = (tBTM_BLE_CONN_REQ*)GKI_dequeue (&btm_cb.ble_ctr_cb.conn_pending_q);

        rt = l2cble_init_direct_conn((tL2C_LCB *)(p_req->p_param));

        GKI_freebuf((void *)p_req);
    }

    return rt;
}

#endif


