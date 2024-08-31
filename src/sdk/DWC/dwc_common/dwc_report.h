#pragma once
#ifdef __cplusplus
extern "C" {
#endif

void DWC_SetReportLevel(int level);
void DWC_Printf(int id, const char* format, ...);

#ifdef __cplusplus
}
#endif
