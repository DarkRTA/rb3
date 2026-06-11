#ifndef RVL_SDK_EC_H
#define RVL_SDK_EC_H

#pragma once
#include "types.h"
#include "revolution/esp/esp.h"

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

typedef struct _ECMoney {
    // total size: 0x40
    char amount[32]; // offset 0x0, size 0x20
    char currency[32]; // offset 0x20, size 0x20
} ECMoney;

typedef struct _ECLicensePricing {
    // total size: 0x8C
    long itemId; // offset 0x0, size 0x4
    ECMoney price; // offset 0x4, size 0x40
    ESLpEntry limits[8]; // offset 0x44, size 0x40
    unsigned long nLimits; // offset 0x84, size 0x4
    unsigned long licenseType; // offset 0x88, size 0x4
} ECLicensePricing;

typedef struct _ECRating {
    // total size: 0x10
    char * name; // offset 0x0, size 0x4
    char * rating; // offset 0x4, size 0x4
    long age; // offset 0x8, size 0x4
    char * descriptors; // offset 0xC, size 0x4
} ECRating;

typedef struct _ECContentCatalogInfo {
    // total size: 0x30
    unsigned long long titleId; // offset 0x0, size 0x8
    ECRating * ratings; // offset 0x8, size 0x4
    unsigned long nRatings; // offset 0xC, size 0x4
    ECLicensePricing *licensePricings; // offset 0x10, size 0x4
    unsigned long nLicensePricings; // offset 0x14, size 0x4
    ECNameValue *attributes; // offset 0x18, size 0x4
    unsigned long nAttributes; // offset 0x1C, size 0x4
    long isTitleIncluded; // offset 0x20, size 0x4
    unsigned short * indexes; // offset 0x24, size 0x4
    unsigned long nIndexes; // offset 0x28, size 0x4
} ECContentCatalogInfo;

int EC_Init(ECNameValue *funcs, int numFuncs);
int EC_Shutdown();
int EC_DeleteContents(
    unsigned long long titleId, unsigned short *contents, int numContents
);
int EC_SetParameter(const char *paramId, const char *value);
int EC_GetIsSyncNeeded();
int EC_GetTitleInfo(unsigned long long titleId, ECTitleInfo *titleInfo);

#ifdef __cplusplus
}
#endif
#endif
