#ifndef RVL_SDK_EC_H
#define RVL_SDK_EC_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _ECTitleInfo {
    unsigned long long titleId;
    long isTmdPresent;
    long isOnDevice;
    unsigned long type;
    unsigned long version;
    unsigned long occupiedUserBlocks;
    unsigned long occupiedUserInodes;
    unsigned long occupiedSysBlocks;
    unsigned long occupiedSysInodes;
} ECTitleInfo;

typedef struct _ECNameValue {
    const char *name;
    void *value;
} ECNameValue;

int EC_Init(ECNameValue *funcs, int numFuncs);
int EC_Shutdown();
int EC_DeleteContents(unsigned long long titleId, unsigned short *contents, int numContents);
int EC_SetParameter(const char *paramId, const char *value);
int EC_GetIsSyncNeeded();
int EC_GetTitleInfo(unsigned long long titleId, ECTitleInfo *titleInfo);

#ifdef __cplusplus
}
#endif
#endif
