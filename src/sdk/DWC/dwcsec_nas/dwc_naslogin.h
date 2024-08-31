#pragma once
#ifdef __cplusplus
extern "C" {
#endif

void DWC_NasLoginAsync(void);
int DWC_NasLoginProcess();
void DWC_NasLoginAbort();

#ifdef __cplusplus
}
#endif