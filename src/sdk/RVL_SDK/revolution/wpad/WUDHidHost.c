#include "WUDHidHost.h"

/*******************************************************************************
 * headers
 */

#include <types.h>

#include "WUD.h"

#if 0
#include <revolution/OS/OSAssert.h>
#endif

#include "context_bte.h"
#include "context_rvl.h"

/*******************************************************************************
 * macros
 */

#define DEV_IS_NOT_WBC(dev_)	\
	(!WUDIsLinkedWBC() || (WUDIsLinkedWBC() && WUD_DEV_NAME_IS_CNT((dev_)->small.devName)))

/*******************************************************************************
 * local function declarations
 */

// callout functions
extern void bta_hh_co_data(UINT8 dev_handle, UINT8 *p_rpt, UINT16 len,
                           tBTA_HH_PROTO_MODE mode, UINT8 sub_class,
                           UINT8 app_id);
extern void bta_hh_co_open(UINT8 dev_handle, UINT8 sub_class, UINT16 attr_mask,
                           UINT8 app_id);
extern void bta_hh_co_close(UINT8 dev_handle, UINT8 app_id);
extern BOOLEAN bta_dm_co_get_compress_memory(tBTA_SYS_ID id, UINT8 **memory_p,
                                             UINT32 *memory_size);

/*******************************************************************************
 * functions
 */

void WUDiHidHostEventCallback(tBTA_HH_EVT event, tBTA_HH *p_data)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;
	WUDDevInfo *p_info;

	tBTA_HH_CONN *p_conn;
	tBTA_HH_CBDATA *p_cb;
	struct hh_event_15_data
	{
		u16	at_0x00;
		u16	at_0x02;
		u16	at_0x04;
		struct
		{
			UINT8	handle;
			// 1 byte padding (alignment? probably)
			UINT16	queueSize;
			UINT16	notAckNum;
		} at_0x06[];
	} *p_hh_e15;

	int i;
	switch (event)
	{
	case BTA_HH_ENABLE_EVT:
		p_wcb->hhFlags |= 1;
		break;

	case BTA_HH_OPEN_EVT:
		p_conn = &p_data->conn;

		if (p_conn->status == BTA_HH_OK)
		{
			p_info = WUDiGetDiscoverDevice();

			if (WUD_BDCMP(p_info->devAddr, p_conn->bda) != 0)
				p_info = WUDiGetDevInfo(p_conn->bda);

			OSAssert_Line(206, p_info != NULL);

			switch (p_info->at_0x59)
			{
			case 12:
				p_wcb->syncState = WUD_STATE_SYNC_REGISTER_DEVICE;
				break;

			case 2:
				p_wcb->syncState = WUD_STATE_SYNC_COMPLETE;
				break;
			}

			p_info->at_0x59 = 8;
			p_info->devHandle = p_conn->handle;

			p_wcb->connectedNum++;

			OSAssert_Line(220, p_conn->handle >= 0 && p_conn->handle < WUD_MAX_DEV_ENTRY);

			p_info = WUDiGetDevInfo(p_conn->bda);
			if (!p_info)
				p_info = WUDiGetDiscoverDevice();

			WUDiSetDevAddrForHandle(p_conn->handle, p_info->devAddr);
			WUDiSetQueueSizeForHandle(p_conn->handle, 0);
			WUDiSetNotAckNumForHandle(p_conn->handle, 0);

			if (p_info->at_0x5b == 3 || p_info->at_0x5b == 1)
				WUDiMoveTopSmpDevInfoPtr(p_info);
			else if (DEV_IS_NOT_WBC(p_info))
				WUDiMoveTopStdDevInfoPtr(p_info);

			WUDSetSniffMode(p_info->devAddr, 8);

			if (p_wcb->hidConnCB)
				(*p_wcb->hidConnCB)(p_info, TRUE);
		}
		else
		{
			if (p_wcb->syncState != WUD_STATE_START)
			{
				p_info = WUDiGetDiscoverDevice();
				if (WUD_BDCMP(p_conn->bda, p_info->devAddr) == 0
				    && p_info->at_0x59 == 2)
				{
					if (WUDiGetDevInfo(p_conn->bda)
					    && p_conn->status == BTA_HH_ERR_AUTH_FAILED)
					{
						WUDiRemoveDevice(p_conn->bda);
						p_wcb->linkedNum--;
					}

					p_wcb->syncState = WUD_STATE_ERROR;
				}
			}
			else
			{
				if (WUDiGetDevInfo(p_conn->bda)
					    && p_conn->status == BTA_HH_ERR_AUTH_FAILED)
				{
					p_info = WUDiGetDevInfo(p_conn->bda);
					if (p_info)
					{
						if (p_info->at_0x5b == 3 || p_info->at_0x5b == 1)
							WUDiMoveBottomSmpDevInfoPtr(p_info);
						else
							WUDiMoveBottomStdDevInfoPtr(p_info);
					}

					WUDiRemoveDevice(p_conn->bda);
					p_wcb->linkedNum--;
				}
			}
		}
		break;

	case BTA_HH_CLOSE_EVT:
		p_cb = &p_data->dev_status;

		p_wcb->connectedNum--;

		OSAssert_Line(305, p_cb->handle >= 0 && p_cb->handle < WUD_MAX_DEV_ENTRY);

		p_info = WUDiGetDevInfo(WUDiGetDevAddrForHandle(p_cb->handle));
		if (p_info)
		{
			if (p_info->at_0x5b == 3 || p_info->at_0x5b == 1)
				WUDiMoveTopOfDisconnectedSmpDevice(p_info);
			else if (DEV_IS_NOT_WBC(p_info))
				WUDiMoveTopOfDisconnectedStdDevice(p_info);
		}

		WUDiSetDevAddrForHandle(p_cb->handle, NULL);
		WUDiSetQueueSizeForHandle(p_cb->handle, 0);
		WUDiSetNotAckNumForHandle(p_cb->handle, 0);

		if (p_wcb->hidConnCB)
			(*p_wcb->hidConnCB)(p_info, FALSE);

		break;

	case BTA_HH_ADD_DEV_EVT:
		p_conn = &p_data->dev_info;

		p_info = WUDiGetDevInfo(p_conn->bda);
		OSAssert_Line(342, p_info != NULL);

		p_info->devHandle = p_conn->handle;
		WUDiSetDevAddrForHandle(p_conn->handle, p_info->devAddr);
		WUDiSetQueueSizeForHandle(p_conn->handle, 0);
		WUDiSetNotAckNumForHandle(p_conn->handle, 0);

		break;

	case BTA_HH_RMV_DEV_EVT:
		p_conn = &p_data->dev_info;
		break;

	case 15: // BTA_HH_API_ERR_EVT???
		p_hh_e15 = (struct hh_event_15_data *)p_data;

		p_wcb->bufferStatus0 = p_hh_e15->at_0x00;
		p_wcb->bufferStatus1 = p_hh_e15->at_0x02;

		if (p_wcb->linkedNum < p_hh_e15->at_0x04)
		{
			OSReport("WARNING: link num count is modified.\n");
			p_wcb->linkedNum = p_hh_e15->at_0x04;
		}

		for (i = 0; i < p_hh_e15->at_0x04; i++)
		{
			if (p_hh_e15->at_0x06[i].handle < WUD_MAX_DEV_ENTRY)
			{
				WUDiSetQueueSizeForHandle(p_hh_e15->at_0x06[i].handle,
				                          p_hh_e15->at_0x06[i].queueSize);
				WUDiSetNotAckNumForHandle(p_hh_e15->at_0x06[i].handle,
				                          p_hh_e15->at_0x06[i].notAckNum);
			}
		}

		break;
	}
}

extern void bta_hh_co_data(UINT8 dev_handle, UINT8 *p_rpt, UINT16 len,
                           tBTA_HH_PROTO_MODE mode __attribute__((unused)),
                           UINT8 sub_class __attribute__((unused)),
                           UINT8 app_id)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	if (app_id == 3 && p_wcb->hidRecvCB)
		(*p_wcb->hidRecvCB)(dev_handle, p_rpt, len);
}

extern void bta_hh_co_open(UINT8 dev_handle __attribute__((unused)),
                           UINT8 sub_class __attribute__((unused)),
                           UINT16 attr_mask __attribute__((unused)),
                           UINT8 app_id __attribute__((unused)))
{
	return;
}

extern void bta_hh_co_close(UINT8 dev_handle __attribute__((unused)),
                            UINT8 app_id __attribute__((unused)))
{
	return;
}

extern BOOLEAN bta_dm_co_get_compress_memory(tBTA_SYS_ID id
                                             __attribute__((unused)),
                                             UINT8 **memory_p
                                             __attribute__((unused)),
                                             UINT32 *memory_size
                                             __attribute__((unused)))
{
	BOOLEAN ret = FALSE;

	return ret;
}
