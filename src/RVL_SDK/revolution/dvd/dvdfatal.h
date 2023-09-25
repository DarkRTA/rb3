#ifndef RVL_SDK_DVD_FATAL_H
#define RVL_SDK_DVD_FATAL_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

void __DVDShowFatalMessage(void);
bool32 DVDSetAutoFatalMessaging(bool32 enable);
bool32 __DVDGetAutoFatalMessaging(void);
void __DVDPrintFatalMessage(void);

#ifdef __cplusplus
}
#endif
#endif
