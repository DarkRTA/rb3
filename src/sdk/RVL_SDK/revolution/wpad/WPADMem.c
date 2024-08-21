#include <revolution/WPAD/WPADMem.h>
#include "WPADMem.h"
#if 0

/*******************************************************************************
 * headers
 */

#include <types.h>

#include "WPAD.h"

#if 0
#include <revolution/OS/OSInterrupt.h>
#endif

#include "context_rvl.h"

/*******************************************************************************
 * functions
 */

void WPADiClearMemBlock(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	p_wpd->memBlock.at_0x00 = 0;
	p_wpd->memBlock.at_0x04 = 0;
	p_wpd->memBlock.at_0x08 = 0;
	p_wpd->memBlock.at_0x0c = 0;
	p_wpd->memBlock.at_0x10 = NULL;
}

WPADResult WPADWriteExtReg(WPADChannel chan, const void *data, u16 length,
                           WPADExtRegType extReg, u16 address, WPADCallback *cb)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	BOOL success;
	BOOL intrStatus;
	BOOL handshakeFinished;

	WPADResult status = WPAD_ESUCCESS;

	intrStatus = OSDisableInterrupts();

	status = p_wpd->status;
	handshakeFinished = p_wpd->handshakeFinished;

	OSRestoreInterrupts(intrStatus);

	if (status == WPAD_ENODEV)
		goto end;

	if (!handshakeFinished)
	{
		status = WPAD_ECOMM;
		goto end;
	}

	u32 finalAddress = (address & 0xffff) | (extReg << 16) | (1 << 26);

	success =
		WPADiSendWriteData(&p_wpd->stdCmdQueue, data, length, finalAddress, cb);
	status = success ? WPAD_CESUCCESS : WPAD_CECOMM;

end:
	if (status != WPAD_ESUCCESS && cb)
		(*cb)(chan, status);

	return status;
}
#endif
