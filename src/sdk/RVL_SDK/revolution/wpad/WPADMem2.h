#ifndef RVL_SDK_WPAD_INTERNAL_MEMORY_H
#define RVL_SDK_WPAD_INTERNAL_MEMORY_H

#include <revolution/WPAD/WPADMem.h>

/*******************************************************************************
 * headers
 */

#include <revolution/WPAD/WPAD.h> // WPADChannel

/*******************************************************************************
 * types
 */

#ifdef __cplusplus
	extern "C" {
#endif

struct WPADMemBlock
{
	int signed		at_0x00;	// size 0x04, offset 0x00
	int signed		at_0x04;	// size 0x04, offset 0x04
	short signed	at_0x08;	// size 0x02, offset 0x08
	// 2 bytes padding (probably alignment, see WPADiClearMemBlock)
	int signed		at_0x0c;	// size 0x04, offset 0x0c
	WPADCallback	*at_0x10;	// size 0x04, offset 0x10
}; // size 0x14

/*******************************************************************************
 * functions
 */

void WPADiClearMemBlock(WPADChannel chan);

#ifdef __cplusplus
	}
#endif

#endif // RVL_SDK_WPAD_INTERNAL_MEMORY_H
