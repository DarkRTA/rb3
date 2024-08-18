#ifndef RVL_SDK_WPAD_INTERNAL_WUD_HID_HOST_H
#define RVL_SDK_WPAD_INTERNAL_WUD_HID_HOST_H

/* no public header */

/*******************************************************************************
 * headers
 */

#include "context_bte.h"

/*******************************************************************************
 * functions
 */

#ifdef __cplusplus
	extern "C" {
#endif

void WUDiHidHostEventCallback(tBTA_HH_EVT event, tBTA_HH *p_data);

#ifdef __cplusplus
	}
#endif

#endif // RVL_SDK_WPAD_INTERNAL_WUD_HID_HOST_H
