#ifndef RVL_SDK_WPAD_INTERNAL_ENCRYPT_H
#define RVL_SDK_WPAD_INTERNAL_ENCRYPT_H

/* no public header */

/*******************************************************************************
 * headers
 */

#include <types.h>

#include <revolution/wpad/WPAD.h> // WPADChannel

/*******************************************************************************
 * functions
 */

#ifdef __cplusplus
	extern "C" {
#endif

void WPADiCreateKey(WPADChannel chan);
void WPADiCreateKeyFor3rd(WPADChannel chan);
void WPADiDecode(WPADChannel chan, byte_t *data, u16 length, u16 startIndex);

#ifdef __cplusplus
	}
#endif

#endif // RVL_SDK_WPAD_INTERNAL_ENCRYPT_H
