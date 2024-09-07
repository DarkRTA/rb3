#pragma once
#ifdef __cplusplus
extern "C" {
#endif

void DWC_SvlGetTokenAsync(int, int*);
int DWC_SvlProcess();
void DWC_SvlAbort();

#ifdef __cplusplus
}
#endif
