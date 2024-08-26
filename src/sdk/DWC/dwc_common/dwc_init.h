#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "dwc_common/dwc_memfunc.h"

BOOL DWC_Init(int id, const char* name, int gamecode, DWCAllocFunc alloc, DWCFreeFunc free);
void DWC_Shutdown(void);

#ifdef __cplusplus
}
#endif
