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
 *  Filename:      btif_sock.c
 *
 *  Description:   Bluetooth Socket Interface
 *
 *
 ***********************************************************************************/

#include <hardware/bluetooth.h>
#include <hardware/bt_sock.h>

#define LOG_TAG "BTIF_SOCK"
#include "btif_common.h"
#include "btif_util.h"

#include "bd.h"

#include "bta_api.h"
#include "btif_sock_thread.h"
#include "btif_sock_rfc.h"

static bt_status_t btsock_listen(btsock_type_t type, const char* service_name,
                                const uint8_t* uuid, int channel, int* sock_fd, int flags);
static bt_status_t btsock_connect(const bt_bdaddr_t *bd_addr, btsock_type_t type,
                                  const uint8_t* uuid, int channel, int* sock_fd, int flags);

static void btsock_signaled(int fd, int type, int flags, uint32_t user_id);

/*******************************************************************************
**
** Function         btsock_ini
**
** Description     initializes the bt socket interface
**
** Returns         bt_status_t
**
*******************************************************************************/
static btsock_interface_t sock_if = {
                sizeof(sock_if),
                btsock_listen,
                btsock_connect
       };
btsock_interface_t *btif_sock_get_interface()
{
    return &sock_if;
}
bt_status_t btif_sock_init()
{
    static volatile int binit;
    if(!binit)
    {
        //fix me, the process doesn't exit right now. don't set the init flag for now
        //binit = 1;
        BTIF_TRACE_DEBUG0("btsock initializing...");
        btsock_thread_init();
        int handle = btsock_thread_create(btsock_signaled, NULL);
        if(handle >= 0 && btsock_rfc_init(handle) == BT_STATUS_SUCCESS)
        {
            BTIF_TRACE_DEBUG0("btsock successfully initialized");
            return BT_STATUS_SUCCESS;
        }
    }
    else BTIF_TRACE_ERROR0("btsock interface already initialized");
    return BT_STATUS_FAIL;
}
void btif_sock_cleanup()
{
    btsock_rfc_cleanup();
    BTIF_TRACE_DEBUG0("leaving");
}

static bt_status_t btsock_listen(btsock_type_t type, const char* service_name,
        const uint8_t* service_uuid, int channel, int* sock_fd, int flags)
{
    if((service_uuid == NULL && channel <= 0) || sock_fd == NULL)
    {
        BTIF_TRACE_ERROR3("invalid parameters, uuid:%p, channel:%d, sock_fd:%p", service_uuid, channel, sock_fd);
        return BT_STATUS_PARM_INVALID;
    }
    *sock_fd = -1;
    bt_status_t status = BT_STATUS_FAIL;
    switch(type)
    {
        case BTSOCK_RFCOMM:
            status = btsock_rfc_listen(service_name, service_uuid, channel, sock_fd, flags);
            break;
        case BTSOCK_L2CAP:
            BTIF_TRACE_ERROR1("bt l2cap socket type not supported, type:%d", type);
            status = BT_STATUS_UNSUPPORTED;
            break;
        case BTSOCK_SCO:
            BTIF_TRACE_ERROR1("bt sco socket not supported, type:%d", type);
            status = BT_STATUS_UNSUPPORTED;
            break;
        default:
            BTIF_TRACE_ERROR1("unknown bt socket type:%d", type);
            status = BT_STATUS_UNSUPPORTED;
            break;
    }
    return status;
}
static bt_status_t btsock_connect(const bt_bdaddr_t *bd_addr, btsock_type_t type,
        const uint8_t* uuid, int channel, int* sock_fd, int flags)
{
    if((uuid == NULL && channel <= 0) || bd_addr == NULL || sock_fd == NULL)
    {
        BTIF_TRACE_ERROR4("invalid parameters, bd_addr:%p, uuid:%p, channel:%d, sock_fd:%p",
                bd_addr, uuid, channel, sock_fd);
        return BT_STATUS_PARM_INVALID;
    }
    *sock_fd = -1;
    bt_status_t status = BT_STATUS_FAIL;
    switch(type)
    {
        case BTSOCK_RFCOMM:
            status = btsock_rfc_connect(bd_addr, uuid, channel, sock_fd, flags);
            break;
        case BTSOCK_L2CAP:
            BTIF_TRACE_ERROR1("bt l2cap socket type not supported, type:%d", type);
            status = BT_STATUS_UNSUPPORTED;
            break;
        case BTSOCK_SCO:
            BTIF_TRACE_ERROR1("bt sco socket not supported, type:%d", type);
            status = BT_STATUS_UNSUPPORTED;
            break;
        default:
            BTIF_TRACE_ERROR1("unknown bt socket type:%d", type);
            status = BT_STATUS_UNSUPPORTED;
            break;
    }
    return status;
}
static void btsock_signaled(int fd, int type, int flags, uint32_t user_id)
{
    switch(type)
    {
        case BTSOCK_RFCOMM:
            btsock_rfc_signaled(fd, flags, user_id);
            break;
        case BTSOCK_L2CAP:
            BTIF_TRACE_ERROR2("bt l2cap socket type not supported, fd:%d, flags:%d", fd, flags);
            break;
        case BTSOCK_SCO:
            BTIF_TRACE_ERROR2("bt sco socket type not supported, fd:%d, flags:%d", fd, flags);
            break;
        default:
            BTIF_TRACE_ERROR3("unknown socket type:%d, fd:%d, flags:%d", type, fd, flags);
            break;
    }
}



