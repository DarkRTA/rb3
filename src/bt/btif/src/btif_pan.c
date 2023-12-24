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
 *  Filename:      btif_pan.c
 *
 *  Description:   PAN Profile Bluetooth Interface
 *
 *
 ***********************************************************************************/
#include <hardware/bluetooth.h>
#include <hardware/bt_pan.h>
#include <assert.h>
#include <signal.h>
#include <ctype.h>
#include <sys/select.h>
#include <sys/poll.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <net/if.h>
#include <linux/sockios.h>
#include <sys/prctl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <linux/if_ether.h>

#define LOG_TAG "BTIF_PAN"
#include "btif_common.h"
#include "btif_util.h"
#include "btm_api.h"
#include "bd.h"

#include "bta_api.h"
#include "bta_pan_api.h"
#include "btif_sock_thread.h"
#include "btif_sock_util.h"
#include "btif_pan_internal.h"
#include "gki.h"

#define FORWARD_IGNORE        1
#define FORWARD_SUCCESS       0
#define FORWARD_FAILURE     (-1)
#define FORWARD_CONGEST     (-2)
//#define PANU_DISABLED TRUE

#if (PAN_NAP_DISABLED == TRUE) && (PANU_DISABLED == TRUE)
#define BTPAN_LOCAL_ROLE BTPAN_ROLE_NONE
#elif PAN_NAP_DISABLED == TRUE
#define BTPAN_LOCAL_ROLE BTPAN_ROLE_PANU
#elif PANU_DISABLED == TRUE
#define BTPAN_LOCAL_ROLE BTPAN_ROLE_PANNAP
#else
#define BTPAN_LOCAL_ROLE (BTPAN_ROLE_PANU | BTPAN_ROLE_PANNAP)
#endif

#define asrt(s) if(!(s)) BTIF_TRACE_ERROR3("btif_pan: ## %s assert %s failed at line:%d ##",__FUNCTION__, #s, __LINE__)

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

btpan_cb_t btpan_cb;

BD_ADDR local_addr;
static int jni_initialized, stack_initialized;
static bt_status_t btpan_jni_init(const btpan_callbacks_t* callbacks);
static void btpan_jni_cleanup();
static bt_status_t btpan_connect(const bt_bdaddr_t *bd_addr, int local_role, int remote_role);
static bt_status_t btpan_disconnect(const bt_bdaddr_t *bd_addr);
static bt_status_t btpan_enable(int local_role);
static int btpan_get_local_role(void);

static void btpan_tap_fd_signaled(int fd, int type, int flags, uint32_t user_id);
static void btpan_cleanup_conn(btpan_conn_t* conn);
static void bta_pan_callback(tBTA_PAN_EVT event, tBTA_PAN *p_data);
static void btu_exec_tap_fd_read(void *p_param);

static btpan_interface_t pan_if = {
    sizeof(pan_if),
    btpan_jni_init,
    btpan_enable,
    btpan_get_local_role,
    btpan_connect,
    btpan_disconnect,
    btpan_jni_cleanup
};

btpan_interface_t *btif_pan_get_interface()
{
    return &pan_if;
}

/*******************************************************************************
 **
 ** Function        btif_pan_init
 **
 ** Description     initializes the pan interface
 **
 ** Returns         bt_status_t
 **
 *******************************************************************************/
void btif_pan_init()
{
    BTIF_TRACE_DEBUG2("jni_initialized = %d, btpan_cb.enabled:%d", jni_initialized, btpan_cb.enabled);
    stack_initialized = TRUE;
    if (jni_initialized && !btpan_cb.enabled)
    {
        BTIF_TRACE_DEBUG0("Enabling PAN....");
        memset(&btpan_cb, 0, sizeof(btpan_cb));
        btpan_cb.tap_fd = -1;
        btpan_cb.flow = 1;
        int i;
        for(i = 0; i < MAX_PAN_CONNS; i++)
            btpan_cleanup_conn(&btpan_cb.conns[i]);
        BTA_PanEnable(bta_pan_callback);
        btpan_cb.enabled = 1;
        btpan_enable(BTPAN_LOCAL_ROLE);
    }
}

static void pan_disable()
{
    if(btpan_cb.enabled)
    {
        btpan_cb.enabled = 0;
        BTA_PanDisable();
        if(btpan_cb.tap_fd != -1)
        {
            btpan_tap_close(btpan_cb.tap_fd);
            btpan_cb.tap_fd = -1;
        }
    }
}

void btif_pan_cleanup()
{
    if(stack_initialized)
    {
        //bt is shuting down, invalid all bta pan handles
        int i;
        for(i = 0; i < MAX_PAN_CONNS; i++)
            btpan_cleanup_conn(&btpan_cb.conns[i]);
        pan_disable();
    }
    stack_initialized = FALSE;
}

static btpan_callbacks_t callback;
static bt_status_t btpan_jni_init(const btpan_callbacks_t* callbacks)
{
    BTIF_TRACE_DEBUG2("stack_initialized = %d, btpan_cb.enabled:%d", stack_initialized, btpan_cb.enabled);
    jni_initialized = TRUE;
    if(stack_initialized && !btpan_cb.enabled)
        btif_pan_init();
    callback = *callbacks;
    return BT_STATUS_SUCCESS;
}

static void btpan_jni_cleanup()
{
    pan_disable();
    jni_initialized = FALSE;
}

static inline int bta_role_to_btpan(int bta_pan_role)
{
    int btpan_role = 0;
    BTIF_TRACE_DEBUG1("bta_pan_role:0x%x", bta_pan_role);
    if(bta_pan_role & PAN_ROLE_NAP_SERVER)
    {
        btpan_role |= BTPAN_ROLE_PANNAP;
    }
    if(bta_pan_role & PAN_ROLE_CLIENT)
    {
        btpan_role |= BTPAN_ROLE_PANU;
    }
    return btpan_role;
}

static inline int btpan_role_to_bta(int btpan_role)
{
    int bta_pan_role = PAN_ROLE_INACTIVE;
    BTIF_TRACE_DEBUG1("btpan_role:0x%x", btpan_role);
    if(btpan_role & BTPAN_ROLE_PANNAP)
    {
        bta_pan_role |= PAN_ROLE_NAP_SERVER;
    }
    if(btpan_role & BTPAN_ROLE_PANU)
    {
        bta_pan_role |= PAN_ROLE_CLIENT;
    }
    return bta_pan_role;
}

static volatile int btpan_dev_local_role;
static tBTA_PAN_ROLE_INFO bta_panu_info = {PANU_SERVICE_NAME, 0, PAN_SECURITY};
static tBTA_PAN_ROLE_INFO bta_pan_nap_info = {PAN_NAP_SERVICE_NAME, 1, PAN_SECURITY};

static bt_status_t btpan_enable(int local_role)
{
    int bta_pan_role;
    BTIF_TRACE_DEBUG1("local_role:%d", local_role);
    bta_pan_role = btpan_role_to_bta(local_role);
#if BTA_PAN_INCLUDED == TRUE
    BTA_PanSetRole(bta_pan_role, &bta_panu_info, NULL, &bta_pan_nap_info);
    btpan_dev_local_role = local_role;
    return BT_STATUS_SUCCESS;
#else
    return BT_STATUS_FAIL;
#endif
}

static int btpan_get_local_role()
{
    BTIF_TRACE_DEBUG1("btpan_dev_local_role:%d", btpan_dev_local_role);
    return btpan_dev_local_role;
}

static bt_status_t btpan_connect(const bt_bdaddr_t *bd_addr, int local_role, int remote_role)
{
    BTIF_TRACE_DEBUG2("local_role:%d, remote_role:%d", local_role, remote_role);
    int bta_local_role = btpan_role_to_bta(local_role);
    int bta_remote_role = btpan_role_to_bta(remote_role);
    btpan_new_conn(-1, bd_addr->address, bta_local_role, bta_remote_role);
    BTA_PanOpen((UINT8*)bd_addr->address, bta_local_role, bta_remote_role);
    return BT_STATUS_SUCCESS;
}

static void btif_in_pan_generic_evt(UINT16 event, char *p_param)
{
    BTIF_TRACE_EVENT2("%s: event=%d", __FUNCTION__, event);
    switch (event) {
        case BTIF_PAN_CB_DISCONNECTING:
        {
            bt_bdaddr_t *bd_addr = (bt_bdaddr_t*)p_param;
            btpan_conn_t* conn = btpan_find_conn_addr(bd_addr->address);
            int btpan_conn_local_role;
            int btpan_remote_role;
            asrt(conn != NULL);
            if (conn) {
                btpan_conn_local_role = bta_role_to_btpan(conn->local_role);
                btpan_remote_role = bta_role_to_btpan(conn->remote_role);
                callback.connection_state_cb(BTPAN_STATE_DISCONNECTING, BT_STATUS_SUCCESS,
                        (const bt_bdaddr_t*)conn->peer, btpan_conn_local_role, btpan_remote_role);
            }
        } break;
        default:
        {
            BTIF_TRACE_WARNING2("%s : Unknown event 0x%x", __FUNCTION__, event);
        }
        break;
    }
}

static bt_status_t btpan_disconnect(const bt_bdaddr_t *bd_addr)
{
    btpan_conn_t* conn = btpan_find_conn_addr(bd_addr->address);
    if(conn && conn->handle >= 0)
    {
        BTA_PanClose(conn->handle);
        /* Inform the application that the disconnect has been initiated successfully */
        btif_transfer_context(btif_in_pan_generic_evt, BTIF_PAN_CB_DISCONNECTING,
                              (char *)bd_addr, sizeof(bt_bdaddr_t), NULL);
        return BT_STATUS_SUCCESS;
    }
    return BT_STATUS_FAIL;
}

static int pan_pth = -1;
void create_tap_read_thread(int tap_fd)
{
    if(pan_pth < 0)
        pan_pth = btsock_thread_create(btpan_tap_fd_signaled, NULL);
    if(pan_pth >= 0)
        btsock_thread_add_fd(pan_pth, tap_fd, 0, SOCK_THREAD_FD_RD, 0);
}

void destroy_tap_read_thread(void)
{
    if(pan_pth >= 0)
    {
        btsock_thread_exit(pan_pth);
        pan_pth = -1;
    }
}

static int tap_if_up(const char *devname, BD_ADDR addr)
{
    struct ifreq ifr;
    int sk, err;

    sk = socket(AF_INET, SOCK_DGRAM, 0);

    //set mac addr
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, devname, IFNAMSIZ - 1);
    err = ioctl(sk, SIOCGIFHWADDR, &ifr);
    if(err < 0)
    {
        BTIF_TRACE_ERROR2("Could not get network hardware for interface:%s, errno:%s", devname, strerror(errno));
        close(sk);
        return -1;
    }
    /* debug("found mac address for interface:%s = %02x:%02x:%02x:%02x:%02x:%02x", devname, */
    /*         ifr.ifr_hwaddr.sa_data[0], ifr.ifr_hwaddr.sa_data[1], ifr.ifr_hwaddr.sa_data[2], */
    /*         ifr.ifr_hwaddr.sa_data[3], ifr.ifr_hwaddr.sa_data[4], ifr.ifr_hwaddr.sa_data[5]); */
    strncpy(ifr.ifr_name, devname, IFNAMSIZ - 1);
    memcpy(ifr.ifr_hwaddr.sa_data, addr, 6);
    /* debug("setting bt address for interface:%s = %02x:%02x:%02x:%02x:%02x:%02x", devname, */
    /*         ifr.ifr_hwaddr.sa_data[0], ifr.ifr_hwaddr.sa_data[1], ifr.ifr_hwaddr.sa_data[2], */
    /*         ifr.ifr_hwaddr.sa_data[3], ifr.ifr_hwaddr.sa_data[4], ifr.ifr_hwaddr.sa_data[5]); */

    err = ioctl(sk, SIOCSIFHWADDR, (caddr_t)&ifr);

    if (err < 0) {
        BTIF_TRACE_ERROR2("Could not set bt address for interface:%s, errno:%s", devname, strerror(errno));
        close(sk);
        return -1;
    }

    //bring it up
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, devname, IF_NAMESIZE - 1);

    ifr.ifr_flags |= IFF_UP;
    ifr.ifr_flags |= IFF_MULTICAST;

    err = ioctl(sk, SIOCSIFFLAGS, (caddr_t) &ifr);


    if (err < 0) {
        BTIF_TRACE_ERROR2("Could not bring up network interface:%s, errno:%d", devname, errno);
        close(sk);
        return -1;
    }
    close(sk);
    BTIF_TRACE_DEBUG1("network interface: %s is up", devname);
    return 0;
}

static int tap_if_down(const char *devname)
{
    struct ifreq ifr;
    int sk, err;

    sk = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, devname, IF_NAMESIZE - 1);

    ifr.ifr_flags &= ~IFF_UP;

    err = ioctl(sk, SIOCSIFFLAGS, (caddr_t) &ifr);

    close(sk);

    return 0;
}

void btpan_set_flow_control(BOOLEAN enable) {
    if (btpan_cb.tap_fd == -1)
        return;

    btpan_cb.flow = enable;
    if (enable) {
        btsock_thread_add_fd(pan_pth, btpan_cb.tap_fd, 0, SOCK_THREAD_FD_RD, 0);
        bta_dmexecutecallback(btu_exec_tap_fd_read, (void *)btpan_cb.tap_fd);
    }
}

int btpan_tap_open()
{
    struct ifreq ifr;
    int fd, err;
    const char *clonedev = "/dev/tun";

    /* open the clone device */

    //system("insmod /system/lib/modules/tun.ko");
    if( (fd = open(clonedev, O_RDWR)) < 0 ) {

        BTIF_TRACE_DEBUG2("could not open %s, err:%d", clonedev, errno);
        return fd;
    }

    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;

    strncpy(ifr.ifr_name, TAP_IF_NAME, IFNAMSIZ);

    /* try to create the device */
    if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 )//|| tap_setup_ip(TAP_IF_NAME) == FALSE)
    {
        BTIF_TRACE_DEBUG2("ioctl error:%d, errno:%s", err, strerror(errno));
        close(fd);
        return err;
    }
    BTM_GetLocalDeviceAddr (local_addr);
    if(tap_if_up(TAP_IF_NAME, local_addr) == 0)
    {
        return fd;
    }
    BTIF_TRACE_ERROR1("can not bring up tap interface:%s", TAP_IF_NAME);
    close(fd);
    return -1;
}

int btpan_tap_send(int tap_fd, const BD_ADDR src, const BD_ADDR dst, UINT16 proto, const char* buf,
                    UINT16 len, BOOLEAN ext, BOOLEAN forward)
{
    UNUSED(ext);
    UNUSED(forward);
    if(tap_fd != -1)
    {
        tETH_HDR eth_hdr;
        //if(is_empty_eth_addr(dst))
        //    memcpy(&eth_hdr.h_dest, local_addr, ETH_ADDR_LEN);
        //else
        memcpy(&eth_hdr.h_dest, dst, ETH_ADDR_LEN);
        memcpy(&eth_hdr.h_src, src, ETH_ADDR_LEN);
        eth_hdr.h_proto = htons(proto);
        char packet[2000];
        memcpy(packet, &eth_hdr, sizeof(tETH_HDR));
        if(len > 2000)
        {
            ALOGE("btpan_tap_send eth packet size:%d is exceeded limit!", len);
            return -1;
        }
        memcpy(packet + sizeof(tETH_HDR), buf, len);

        /* Send data to network interface */
        //btnet_send(btpan_cb.conn[i].sock.sock, &buffer, (len + sizeof(tETH_HDR)));
        //dump_bin("packet to network", packet, len + sizeof(tETH_HDR));
        int ret = write(tap_fd, packet, len + sizeof(tETH_HDR));
        BTIF_TRACE_DEBUG1("ret:%d", ret);
        return ret;
    }
    return -1;

}

int btpan_tap_close(int fd)
{
    tap_if_down(TAP_IF_NAME);
    close(fd);
    if(pan_pth >= 0)
        btsock_thread_wakeup(pan_pth);
    return 0;
}

btpan_conn_t * btpan_find_conn_handle(UINT16 handle)
{
    int i;
    for(i = 0; i < MAX_PAN_CONNS; i++)
        if(btpan_cb.conns[i].handle == handle)
            return &btpan_cb.conns[i];
    return NULL;
}

btpan_conn_t* btpan_find_conn_addr(const BD_ADDR addr)
{
    int i;
    for(i = 0; i < MAX_PAN_CONNS; i++)
        if(memcmp(btpan_cb.conns[i].peer, addr, sizeof(BD_ADDR)) == 0)
            return &btpan_cb.conns[i];
    return NULL;
}

static void btpan_cleanup_conn(btpan_conn_t* conn)
{
    if(conn)
    {
        conn->handle = -1;
        conn->state = -1;
        memset(&conn->peer, 0, sizeof(conn->peer));
        memset(&conn->eth_addr, 0, sizeof(conn->eth_addr));
        conn->local_role = conn->remote_role = 0;
    }
}

btpan_conn_t* btpan_new_conn(int handle, const BD_ADDR addr, int local_role, int remote_role )
{
    int i;
    for(i = 0; i < MAX_PAN_CONNS; i++)
    {
        BTIF_TRACE_DEBUG2("conns[%d]:%d", i, btpan_cb.conns[i].handle);
        if(btpan_cb.conns[i].handle == -1)
        {
            BTIF_TRACE_DEBUG3("handle:%d, local_role:%d, remote_role:%d", handle, local_role, remote_role);

            btpan_cb.conns[i].handle = handle;
            bdcpy(btpan_cb.conns[i].peer, addr);
            btpan_cb.conns[i].local_role = local_role;
            btpan_cb.conns[i].remote_role = remote_role;
            return &btpan_cb.conns[i];
        }
    }
    BTIF_TRACE_DEBUG1("MAX_PAN_CONNS:%d exceeded, return NULL as failed", MAX_PAN_CONNS);
    return NULL;
}

void btpan_close_handle(btpan_conn_t *p)
{
    BTIF_TRACE_DEBUG1("btpan_close_handle : close handle %d", p->handle);
    p->handle = -1;
    p->local_role = -1;
    p->remote_role = -1;
    memset(&p->peer, 0, 6);
}

static inline int should_forward(tETH_HDR* hdr)
{
    if(ntohs(hdr->h_proto) == ETH_P_IP || ntohs(hdr->h_proto) == ETH_P_ARP)
        return TRUE;
    BTIF_TRACE_DEBUG1("unknown proto:%x", ntohs(hdr->h_proto));
    return FALSE;
}

static int forward_bnep(tETH_HDR* eth_hdr, BT_HDR *hdr) {
    int broadcast = eth_hdr->h_dest[0] & 1;
    int i;

    // Find the right connection to send this frame over.
    for (i = 0; i < MAX_PAN_CONNS; i++) {
        UINT16 handle = btpan_cb.conns[i].handle;
        if (handle != (UINT16)-1 &&
                (broadcast || memcmp(btpan_cb.conns[i].eth_addr, eth_hdr->h_dest, sizeof(BD_ADDR)) == 0
                 || memcmp(btpan_cb.conns[i].peer, eth_hdr->h_dest, sizeof(BD_ADDR)) == 0)) {
            int result = PAN_WriteBuf(handle, eth_hdr->h_dest, eth_hdr->h_src, ntohs(eth_hdr->h_proto), hdr, 0);
            switch (result) {
                case PAN_Q_SIZE_EXCEEDED:
                    return FORWARD_CONGEST;
                case PAN_SUCCESS:
                    return FORWARD_SUCCESS;
                default:
                    return FORWARD_FAILURE;
            }
        }
    }
    GKI_freebuf(hdr);
    return FORWARD_IGNORE;
}

static void bta_pan_callback_transfer(UINT16 event, char *p_param)
{
    tBTA_PAN *p_data = (tBTA_PAN *)p_param;
    switch(event)
    {
        case BTA_PAN_ENABLE_EVT:
            BTIF_TRACE_DEBUG0("BTA_PAN_ENABLE_EVT");
            break;
        case BTA_PAN_SET_ROLE_EVT:
            {
                int btpan_role = bta_role_to_btpan(p_data->set_role.role);
                bt_status_t status = p_data->set_role.status == BTA_PAN_SUCCESS ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;
                btpan_control_state_t state = btpan_role == 0 ? BTPAN_STATE_DISABLED : BTPAN_STATE_ENABLED;
                callback.control_state_cb(state, btpan_role, status, TAP_IF_NAME);
                break;
            }
        case BTA_PAN_OPENING_EVT:
            {
                btpan_conn_t* conn;
                bdstr_t bds;
                bd2str((bt_bdaddr_t*)p_data->opening.bd_addr, &bds);
                BTIF_TRACE_DEBUG2("BTA_PAN_OPENING_EVT handle %d, addr: %s", p_data->opening.handle, bds);
                conn = btpan_find_conn_addr(p_data->opening.bd_addr);

                asrt(conn != NULL);
                if (conn)
                {
                    conn->handle = p_data->opening.handle;
                    int btpan_conn_local_role = bta_role_to_btpan(conn->local_role);
                    int btpan_remote_role = bta_role_to_btpan(conn->remote_role);
                    callback.connection_state_cb(BTPAN_STATE_CONNECTING, BT_STATUS_SUCCESS,
                            (const bt_bdaddr_t*)p_data->opening.bd_addr, btpan_conn_local_role, btpan_remote_role);
                }
                else
                    BTIF_TRACE_ERROR0("connection not found");
                break;
            }
        case BTA_PAN_OPEN_EVT:
            {
                /* debug("BTA_PAN_OPEN_EVT, open status:%d, bd_addr = [%02X:%02X:%02X:%02X:%02X:%02X]", */
                /*         p_data->open.status, */
                /*         p_data->open.bd_addr[0], p_data->open.bd_addr[1], p_data->open.bd_addr[2], */
                /*         p_data->open.bd_addr[3], p_data->open.bd_addr[4], p_data->open.bd_addr[5]); */
                btpan_connection_state_t state;
                bt_status_t status;
                if(p_data->open.status == BTA_PAN_SUCCESS)
                {
                    state = BTPAN_STATE_CONNECTED;
                    status = BT_STATUS_SUCCESS;
                }
                else
                {
                    state = BTPAN_STATE_DISCONNECTED;
                    status = BT_STATUS_FAIL;
                }
                btpan_conn_t* conn = btpan_find_conn_handle(p_data->open.handle);
                /* debug("BTA_PAN_OPEN_EVT handle:%d, conn:%p",  p_data->open.handle, conn); */
                /* debug("conn bta local_role:%d, bta remote role:%d", conn->local_role, conn->remote_role); */
                int btpan_conn_local_role = bta_role_to_btpan(p_data->open.local_role);
                /* debug("bta local_role:%d, bta remote role:%d", p_data->open.local_role, p_data->open.peer_role); */
                int btpan_remote_role = bta_role_to_btpan(p_data->open.peer_role);
                callback.connection_state_cb(state, status, (const bt_bdaddr_t*)p_data->open.bd_addr,
                        btpan_conn_local_role, btpan_remote_role);
                break;
            }
        case BTA_PAN_CLOSE_EVT:
            {
                btpan_conn_t* conn = btpan_find_conn_handle(p_data->close.handle);

                ALOGI("%s: event = BTA_PAN_CLOSE_EVT handle %d", __FUNCTION__, p_data->close.handle);

                if(conn && conn->handle >= 0)
                {
                    /* debug("BTA_PAN_CLOSE_EVT, conn local_role:%d, remote_role:%d", conn->local_role, conn->remote_role); */
                    int btpan_conn_local_role = bta_role_to_btpan(conn->local_role);
                    int btpan_remote_role = bta_role_to_btpan(conn->remote_role);
                    callback.connection_state_cb(BTPAN_STATE_DISCONNECTED, 0, (const bt_bdaddr_t*)conn->peer,
                            btpan_conn_local_role, btpan_remote_role);
                    btpan_cleanup_conn(conn);
                }
                else
                    BTIF_TRACE_ERROR1("pan handle not found (%d)", p_data->close.handle);
                break;
            }
        default:
            BTIF_TRACE_WARNING1("Unknown pan event %d", event);
            break;
    }
}

static void bta_pan_callback(tBTA_PAN_EVT event, tBTA_PAN *p_data)
{
    btif_transfer_context(bta_pan_callback_transfer, event, (char*)p_data, sizeof(tBTA_PAN), NULL);
}

#define IS_EXCEPTION(e) ((e) & (POLLHUP | POLLRDHUP | POLLERR | POLLNVAL))
static void btu_exec_tap_fd_read(void *p_param) {
    struct pollfd ufd;
    int fd = (int)p_param;

    if (fd == -1 || fd != btpan_cb.tap_fd)
        return;

    // Keep sending until someone either turns off BTIF or disables data the flow.
    while (btif_is_enabled() && btpan_cb.flow) {
        BT_HDR *buffer = (BT_HDR *)GKI_getpoolbuf(PAN_POOL_ID);
        if (!buffer) {
            BTIF_TRACE_WARNING1("%s unable to allocate buffer for packet.", __func__);
            break;
        }
        buffer->offset = PAN_MINIMUM_OFFSET;
        buffer->len = GKI_get_buf_size(buffer) - sizeof(BT_HDR) - buffer->offset;

        UINT8 *packet = (UINT8 *)buffer + sizeof(BT_HDR) + buffer->offset;

        // If we don't have an undelivered packet left over, pull one from the TAP driver.
        // We save it in the congest_packet right away in case we can't deliver it in this
        // attempt.
        if (!btpan_cb.congest_packet_size) {
            ssize_t ret = read(fd, btpan_cb.congest_packet, sizeof(btpan_cb.congest_packet));
            switch (ret) {
                case -1:
                    BTIF_TRACE_ERROR2("%s unable to read from driver: %s", __func__, strerror(errno));
                    GKI_freebuf(buffer);
                    return;
                case 0:
                    BTIF_TRACE_WARNING1("%s end of file reached.", __func__);
                    GKI_freebuf(buffer);
                    return;
                default:
                    btpan_cb.congest_packet_size = ret;
                    break;
            }
        }

        memcpy(packet, btpan_cb.congest_packet, MIN(btpan_cb.congest_packet_size, buffer->len));
        buffer->len = MIN(btpan_cb.congest_packet_size, buffer->len);

        if (buffer->len > sizeof(tETH_HDR) && should_forward((tETH_HDR *)packet)) {
            // Extract the ethernet header from the buffer since the PAN_WriteBuf inside
            // forward_bnep can't handle two pointers that point inside the same GKI buffer.
            tETH_HDR hdr;
            memcpy(&hdr, packet, sizeof(tETH_HDR));

            // Skip the ethernet header.
            buffer->len -= sizeof(tETH_HDR);
            buffer->offset += sizeof(tETH_HDR);
            if (forward_bnep(&hdr, buffer) != FORWARD_CONGEST)
                btpan_cb.congest_packet_size = 0;
        } else {
            BTIF_TRACE_WARNING2("%s dropping packet of length %d", __func__, buffer->len);
            btpan_cb.congest_packet_size = 0;
            GKI_freebuf(buffer);
        }

        // Bail out of the loop if reading from the TAP fd would block.
        ufd.fd = fd;
        ufd.events = POLLIN;
        ufd.revents = 0;
        if(poll(&ufd, 1, 0) <= 0 || IS_EXCEPTION(ufd.revents)) {
            btsock_thread_add_fd(pan_pth, fd, 0, SOCK_THREAD_FD_RD, 0);
            return;
        }
    }
}

static void btif_pan_close_all_conns() {
    int i;
    if (!stack_initialized)
        return;

    for (i = 0; i < MAX_PAN_CONNS; ++i)
        if (btpan_cb.conns[i].handle != -1)
            BTA_PanClose(btpan_cb.conns[i].handle);
}

static void btpan_tap_fd_signaled(int fd, int type, int flags, uint32_t user_id) {
    assert(btpan_cb.tap_fd == fd);

    if (btpan_cb.tap_fd != fd)
        return;

    if(flags & SOCK_THREAD_FD_EXCEPTION) {
        btpan_cb.tap_fd = -1;
        btpan_tap_close(fd);
        btif_pan_close_all_conns();
    } else if(flags & SOCK_THREAD_FD_RD)
        bta_dmexecutecallback(btu_exec_tap_fd_read, (void *)fd);
}
