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

//#if (defined(BTA_HH_INCLUDED) && (BTA_HH_INCLUDED == TRUE))

#include <ctype.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <linux/uhid.h>
#include "btif_hh.h"
#include "bta_api.h"
#include "bta_hh_api.h"
#include "btif_util.h"


const char *dev_path = "/dev/uhid";


/*Internal function to perform UHID write and error checking*/
static int uhid_write(int fd, const struct uhid_event *ev)
{
    ssize_t ret;
    ret = write(fd, ev, sizeof(*ev));
    if (ret < 0){
        int rtn = -errno;
        APPL_TRACE_ERROR2("%s: Cannot write to uhid:%s", __FUNCTION__, strerror(errno));
        return rtn;
    } else if (ret != sizeof(*ev)) {
        APPL_TRACE_ERROR3("%s: Wrong size written to uhid: %ld != %lu",
                                                    __FUNCTION__, ret, sizeof(*ev));
        return -EFAULT;
    } else {
        return 0;
    }
}

/* Internal function to parse the events received from UHID driver*/
static int uhid_event(btif_hh_device_t *p_dev)
{
    struct uhid_event ev;
    ssize_t ret;
    memset(&ev, 0, sizeof(ev));
    if(!p_dev)
    {
        APPL_TRACE_ERROR1("%s: Device not found",__FUNCTION__)
        return -1;
    }
    ret = read(p_dev->fd, &ev, sizeof(ev));
    if (ret == 0) {
        APPL_TRACE_ERROR2("%s: Read HUP on uhid-cdev %s", __FUNCTION__,
                                                 strerror(errno));
        return -EFAULT;
    } else if (ret < 0) {
        APPL_TRACE_ERROR2("%s:Cannot read uhid-cdev: %s", __FUNCTION__,
                                                strerror(errno));
        return -errno;
    } else if (ret != sizeof(ev)) {
        APPL_TRACE_ERROR3("%s:Invalid size read from uhid-dev: %ld != %lu",
                            __FUNCTION__, ret, sizeof(ev));
        return -EFAULT;
    }

    switch (ev.type) {
    case UHID_START:
        APPL_TRACE_DEBUG0("UHID_START from uhid-dev\n");
        break;
    case UHID_STOP:
        APPL_TRACE_DEBUG0("UHID_STOP from uhid-dev\n");
        break;
    case UHID_OPEN:
        APPL_TRACE_DEBUG0("UHID_OPEN from uhid-dev\n");
        break;
    case UHID_CLOSE:
        APPL_TRACE_DEBUG0("UHID_CLOSE from uhid-dev\n");
        break;
    case UHID_OUTPUT:
        APPL_TRACE_DEBUG2("UHID_OUTPUT: Report type = %d, report_size = %d"
                            ,ev.u.output.rtype, ev.u.output.size);
        //Send SET_REPORT with feature report if the report type in output event is FEATURE
        if(ev.u.output.rtype == UHID_FEATURE_REPORT)
            btif_hh_setreport(p_dev,BTHH_FEATURE_REPORT,ev.u.output.size,ev.u.output.data);
        else if(ev.u.output.rtype == UHID_OUTPUT_REPORT)
            btif_hh_setreport(p_dev,BTHH_OUTPUT_REPORT,ev.u.output.size,ev.u.output.data);
        else
            btif_hh_setreport(p_dev,BTHH_INPUT_REPORT,ev.u.output.size,ev.u.output.data);
           break;
    case UHID_OUTPUT_EV:
        APPL_TRACE_DEBUG0("UHID_OUTPUT_EV from uhid-dev\n");
        break;
    case UHID_FEATURE:
        APPL_TRACE_DEBUG0("UHID_FEATURE from uhid-dev\n");
        break;
    case UHID_FEATURE_ANSWER:
        APPL_TRACE_DEBUG0("UHID_FEATURE_ANSWER from uhid-dev\n");
        break;

    default:
        APPL_TRACE_DEBUG1("Invalid event from uhid-dev: %u\n", ev.type);
    }

    return 0;
}

/*******************************************************************************
**
** Function create_thread
**
** Description creat a select loop
**
** Returns pthread_t
**
*******************************************************************************/
static inline pthread_t create_thread(void *(*start_routine)(void *), void * arg){
    APPL_TRACE_DEBUG0("create_thread: entered");
    pthread_attr_t thread_attr;

    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE);
    pthread_t thread_id = -1;
    if ( pthread_create(&thread_id, &thread_attr, start_routine, arg)!=0 )
    {
        APPL_TRACE_ERROR1("pthread_create : %s", strerror(errno));
        return -1;
    }
    APPL_TRACE_DEBUG0("create_thread: thread created successfully");
    return thread_id;
}

/*******************************************************************************
**
** Function btif_hh_poll_event_thread
**
** Description the polling thread which polls for event from UHID driver
**
** Returns void
**
*******************************************************************************/
static void *btif_hh_poll_event_thread(void *arg)
{

    btif_hh_device_t *p_dev = arg;
    APPL_TRACE_DEBUG2("%s: Thread created fd = %d", __FUNCTION__, p_dev->fd);
    struct pollfd pfds[1];
    int ret;
    pfds[0].fd = p_dev->fd;
    pfds[0].events = POLLIN;

    while(p_dev->hh_keep_polling){
        ret = poll(pfds, 1, 50);
        if (ret < 0) {
            APPL_TRACE_ERROR2("%s: Cannot poll for fds: %s\n", __FUNCTION__, strerror(errno));
            break;
        }
        if (pfds[0].revents & POLLIN) {
            APPL_TRACE_DEBUG0("btif_hh_poll_event_thread: POLLIN");
            ret = uhid_event(p_dev);
            if (ret){
                break;
            }
        }
    }

    p_dev->hh_poll_thread_id = -1;
    return 0;
}

static inline void btif_hh_close_poll_thread(btif_hh_device_t *p_dev)
{
    APPL_TRACE_DEBUG1("%s", __FUNCTION__);
    p_dev->hh_keep_polling = 0;
    if(p_dev->hh_poll_thread_id > 0)
        pthread_join(p_dev->hh_poll_thread_id,NULL);

    return;
}

void bta_hh_co_destroy(int fd)
{
    struct uhid_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.type = UHID_DESTROY;
    uhid_write(fd, &ev);
    close(fd);
}

int bta_hh_co_write(int fd, UINT8* rpt, UINT16 len)
{
    APPL_TRACE_DEBUG0("bta_hh_co_data: UHID write");
    struct uhid_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.type = UHID_INPUT;
    ev.u.input.size = len;
    if(len > sizeof(ev.u.input.data)){
        APPL_TRACE_WARNING1("%s:report size greater than allowed size",__FUNCTION__);
        return -1;
    }
    memcpy(ev.u.input.data, rpt, len);
    return uhid_write(fd, &ev);

}


/*******************************************************************************
**
** Function      bta_hh_co_open
**
** Description   When connection is opened, this call-out function is executed
**               by HH to do platform specific initialization.
**
** Returns       void.
*******************************************************************************/
void bta_hh_co_open(UINT8 dev_handle, UINT8 sub_class, tBTA_HH_ATTR_MASK attr_mask,
                    UINT8 app_id)
{
    UINT32 i;
    btif_hh_device_t *p_dev = NULL;

    if (dev_handle == BTA_HH_INVALID_HANDLE) {
        APPL_TRACE_WARNING2("%s: Oops, dev_handle (%d) is invalid...", __FUNCTION__, dev_handle);
        return;
    }

    for (i = 0; i < BTIF_HH_MAX_HID; i++) {
        p_dev = &btif_hh_cb.devices[i];
        if (p_dev->dev_status != BTHH_CONN_STATE_UNKNOWN && p_dev->dev_handle == dev_handle) {
            // We found a device with the same handle. Must be a device reconnected.
            APPL_TRACE_WARNING2("%s: Found an existing device with the same handle "
                                                                "dev_status = %d",__FUNCTION__,
                                                                p_dev->dev_status);
            APPL_TRACE_WARNING6("%s:     bd_addr = [%02X:%02X:%02X:%02X:%02X:]", __FUNCTION__,
                 p_dev->bd_addr.address[0], p_dev->bd_addr.address[1], p_dev->bd_addr.address[2],
                 p_dev->bd_addr.address[3], p_dev->bd_addr.address[4]);
                 APPL_TRACE_WARNING4("%s:     attr_mask = 0x%04x, sub_class = 0x%02x, app_id = %d",
                                  __FUNCTION__, p_dev->attr_mask, p_dev->sub_class, p_dev->app_id);

            if(p_dev->fd<0) {
                p_dev->fd = open(dev_path, O_RDWR | O_CLOEXEC);
                if (p_dev->fd < 0){
                    APPL_TRACE_ERROR2("%s: Error: failed to open uhid, err:%s",
                                                                    __FUNCTION__,strerror(errno));
                }else
                    APPL_TRACE_DEBUG2("%s: uhid fd = %d", __FUNCTION__, p_dev->fd);
            }
            p_dev->hh_keep_polling = 1;
            p_dev->hh_poll_thread_id = create_thread(btif_hh_poll_event_thread, p_dev);
            break;
        }
        p_dev = NULL;
    }

    if (p_dev == NULL) {
        // Did not find a device reconnection case. Find an empty slot now.
        for (i = 0; i < BTIF_HH_MAX_HID; i++) {
            if (btif_hh_cb.devices[i].dev_status == BTHH_CONN_STATE_UNKNOWN) {
                p_dev = &btif_hh_cb.devices[i];
                p_dev->dev_handle = dev_handle;
                p_dev->attr_mask  = attr_mask;
                p_dev->sub_class  = sub_class;
                p_dev->app_id     = app_id;
                p_dev->local_vup  = FALSE;

                btif_hh_cb.device_num++;
                // This is a new device,open the uhid driver now.
                p_dev->fd = open(dev_path, O_RDWR | O_CLOEXEC);
                if (p_dev->fd < 0){
                    APPL_TRACE_ERROR2("%s: Error: failed to open uhid, err:%s",
                                                                    __FUNCTION__,strerror(errno));
                }else{
                    APPL_TRACE_DEBUG2("%s: uhid fd = %d", __FUNCTION__, p_dev->fd);
                    p_dev->hh_keep_polling = 1;
                    p_dev->hh_poll_thread_id = create_thread(btif_hh_poll_event_thread, p_dev);
                }


                break;
            }
        }
    }

    if (p_dev == NULL) {
        APPL_TRACE_ERROR1("%s: Error: too many HID devices are connected", __FUNCTION__);
        return;
    }

    p_dev->dev_status = BTHH_CONN_STATE_CONNECTED;
    APPL_TRACE_DEBUG2("%s: Return device status %d", __FUNCTION__, p_dev->dev_status);
}


/*******************************************************************************
**
** Function      bta_hh_co_close
**
** Description   When connection is closed, this call-out function is executed
**               by HH to do platform specific finalization.
**
** Parameters    dev_handle  - device handle
**                  app_id      - application id
**
** Returns          void.
*******************************************************************************/
void bta_hh_co_close(UINT8 dev_handle, UINT8 app_id)
{
    UINT32 i;
    btif_hh_device_t *p_dev = NULL;

    APPL_TRACE_WARNING3("%s: dev_handle = %d, app_id = %d", __FUNCTION__, dev_handle, app_id);
    if (dev_handle == BTA_HH_INVALID_HANDLE) {
        APPL_TRACE_WARNING2("%s: Oops, dev_handle (%d) is invalid...", __FUNCTION__, dev_handle);
        return;
    }

    for (i = 0; i < BTIF_HH_MAX_HID; i++) {
        p_dev = &btif_hh_cb.devices[i];
        if (p_dev->dev_status != BTHH_CONN_STATE_UNKNOWN && p_dev->dev_handle == dev_handle) {
            APPL_TRACE_WARNING3("%s: Found an existing device with the same handle "
                                                        "dev_status = %d, dev_handle =%d"
                                                        ,__FUNCTION__,p_dev->dev_status
                                                        ,p_dev->dev_handle);
            btif_hh_close_poll_thread(p_dev);
            break;
        }
     }

}


/*******************************************************************************
**
** Function         bta_hh_co_data
**
** Description      This function is executed by BTA when HID host receive a data
**                  report.
**
** Parameters       dev_handle  - device handle
**                  *p_rpt      - pointer to the report data
**                  len         - length of report data
**                  mode        - Hid host Protocol Mode
**                  sub_clas    - Device Subclass
**                  app_id      - application id
**
** Returns          void
*******************************************************************************/
void bta_hh_co_data(UINT8 dev_handle, UINT8 *p_rpt, UINT16 len, tBTA_HH_PROTO_MODE mode,
                    UINT8 sub_class, UINT8 ctry_code, BD_ADDR peer_addr, UINT8 app_id)
{
    btif_hh_device_t *p_dev;
    UNUSED(peer_addr);

    APPL_TRACE_DEBUG6("%s: dev_handle = %d, subclass = 0x%02X, mode = %d, "
         "ctry_code = %d, app_id = %d",
         __FUNCTION__, dev_handle, sub_class, mode, ctry_code, app_id);

    p_dev = btif_hh_find_connected_dev_by_handle(dev_handle);
    if (p_dev == NULL) {
        APPL_TRACE_WARNING2("%s: Error: unknown HID device handle %d", __FUNCTION__, dev_handle);
        return;
    }
    // Send the HID report to the kernel.
    if (p_dev->fd >= 0) {
        bta_hh_co_write(p_dev->fd, p_rpt, len);
    }else {
        APPL_TRACE_WARNING3("%s: Error: fd = %d, len = %d", __FUNCTION__, p_dev->fd, len);
    }
}


/*******************************************************************************
**
** Function         bta_hh_co_send_hid_info
**
** Description      This function is called in btif_hh.c to process DSCP received.
**
** Parameters       dev_handle  - device handle
**                  dscp_len    - report descriptor length
**                  *p_dscp     - report descriptor
**
** Returns          void
*******************************************************************************/
void bta_hh_co_send_hid_info(btif_hh_device_t *p_dev, char *dev_name, UINT16 vendor_id,
                             UINT16 product_id, UINT16 version, UINT8 ctry_code,
                             int dscp_len, UINT8 *p_dscp)
{
    int result;
    struct uhid_event ev;

    if (p_dev->fd < 0) {
        APPL_TRACE_WARNING3("%s: Error: fd = %d, dscp_len = %d", __FUNCTION__, p_dev->fd, dscp_len);
        return;
    }

    APPL_TRACE_WARNING4("%s: fd = %d, name = [%s], dscp_len = %d", __FUNCTION__,
                                                                    p_dev->fd, dev_name, dscp_len);
    APPL_TRACE_WARNING5("%s: vendor_id = 0x%04x, product_id = 0x%04x, version= 0x%04x,"
                                                                    "ctry_code=0x%02x",__FUNCTION__,
                                                                    vendor_id, product_id,
                                                                    version, ctry_code);

//Create and send hid descriptor to kernel
    memset(&ev, 0, sizeof(ev));
    ev.type = UHID_CREATE;
    strncpy((char*)ev.u.create.name, dev_name, sizeof(ev.u.create.name) - 1);
    snprintf((char*)ev.u.create.uniq, sizeof(ev.u.create.uniq),
             "%2.2X:%2.2X:%2.2X:%2.2X:%2.2X:%2.2X",
             p_dev->bd_addr.address[5], p_dev->bd_addr.address[4],
             p_dev->bd_addr.address[3], p_dev->bd_addr.address[2],
             p_dev->bd_addr.address[1], p_dev->bd_addr.address[0]);
    ev.u.create.rd_size = dscp_len;
    ev.u.create.rd_data = p_dscp;
    ev.u.create.bus = BUS_BLUETOOTH;
    ev.u.create.vendor = vendor_id;
    ev.u.create.product = product_id;
    ev.u.create.version = version;
    ev.u.create.country = ctry_code;
    result = uhid_write(p_dev->fd, &ev);

    APPL_TRACE_WARNING4("%s: fd = %d, dscp_len = %d, result = %d", __FUNCTION__,
                                                                    p_dev->fd, dscp_len, result);

    if (result) {
        APPL_TRACE_WARNING2("%s: Error: failed to send DSCP, result = %d", __FUNCTION__, result);

        /* The HID report descriptor is corrupted. Close the driver. */
        close(p_dev->fd);
        p_dev->fd = -1;
    }
}


