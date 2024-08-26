#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "dwc_common/dwc_memfunc.h"

int DWCi_Auth_InitInterface(int id);
int DWCi_Auth_StartAuthentication(const char*, const char*, u64, DWCAllocFunc, DWCFreeFunc);
void DWCi_Auth_AbortAuthentication(void);
void DWCi_Auth_ProcessAuthentication(void);
int DWCi_Auth_GetErrorCode(void);
int DWCi_Auth_IsFinished(void);
int DWCi_Auth_IsSucceeded(void);

#ifdef __cplusplus
}
#endif
