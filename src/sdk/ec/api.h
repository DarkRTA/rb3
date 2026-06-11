#ifndef EC_API_H
#define EC_API_H

#include <ec/dk.h>
#include <ec/asyncOp.h>
#include <ec/log.h>

class ECContentInfo {
    int field0x0; //size 0x4, offset 0x0
    short field0x4; //size 0x2, offset 0x4
    short field0x6; //size 0x2, offset 0x6
    int field0x8; //size 0x4, offset 0x8
    int field0xc; //size 0x4, offset 0xc
    void operator=(const ECContentInfo &other);
};

namespace ec {
    const char *buildDateTime = (char *)"Feb  8 2010 20:10:32";
    ECResult deleteTitleContent(unsigned long long);
    ECResult getTitleInfos(ECTitleInfo *, unsigned long *, unsigned long long, bool);
}

ECResult EC_Init(ECNameValue *, unsigned long);
int EC_Shutdown();
int EC_SetParameter(const char *, const char *);
ECResult EC_GetProgress(unsigned long, ECResult *);
int EC_CancelOperation(unsigned long);
ECResult EC_GetCachedBalance(int *);
ECResult EC_DeleteTitle();
int EC_GetTitleInfo(unsigned long long, ECTitleInfo *, int *);
ECResult EC_GetOverhead(int, int *, int *);
int EC_GetIsSyncNeeded();

#endif