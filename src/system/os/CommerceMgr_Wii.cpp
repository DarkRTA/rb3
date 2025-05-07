#include "os/CommerceMgr_Wii.h"
#include "system/meta/StorePackedMetadata.h"
#include "revolution/ec/ec.h"

char gMakeTitleIdString[5];

bool gAllowNeedSyncReturn = true;

char *gCommerceFilterName_OfferType = "offer_type";
char *gCommerceFilterValue_Album = "album";
char *gCommerceFilterValue_Everything = "*";
char *gCommerceFilterValue_Pack = "pack";
char *gCommerceFilterValue_Song = "song";
char *gCommerceFilterValuePurchasable = "PURCHASABLE";

WiiCommerceMgr::WiiCommerceMgr() {
    mAttributes[0] = "Prices";
    mAttributes[1] = "MaxUserFileSize";
    mAttributes[2] = "MaxUserInodes";
    mAttributes[3] = gCommerceFilterName_OfferType;
    mAttributes[4] = "offer_id";
    mAttributes[5] = "index_version";
    mAttributesNum = 6;
}

WiiCommerceMgr::~WiiCommerceMgr() {}

void WiiCommerceMgr::Init() {
    SetName("commerce_mgr", ObjectDir::sMainDir);
    TheStoreMetadata.Init();
}

bool WiiCommerceMgr::IsBusy() const {
    return mCommerceAsyncOpId != -1;
}

bool WiiCommerceMgr::NeedSync() {
    int r = EC_GetIsSyncNeeded();
    return (bool)(gAllowNeedSyncReturn & r != -0xFE2);
}

bool WiiCommerceMgr::CheckPurchaseSync() {
    return true;
}

void WiiCommerceMgr::GetTitleInfo() {
    // titleInfo is actually WiiCommerceMgr.mTitleInfo
    ECTitleInfo titleInfo;
    for (int i = 0; i < mTitleIdsNum; i++) {
        unsigned long long titleId = mTitleIds[i];
        long r = EC_GetTitleInfo(titleId, &titleInfo);
        if (r != -4050) {
            const char *titleIdString = MakeTitleIdString(titleId);
            MILO_LOG("Store: titleinfo: %d - titleId = %s | isTmdPresent = %d | isOnDevice = %d | type = %d | version = %d\n",
                r, titleIdString, titleInfo.isTmdPresent, titleInfo.isOnDevice, titleInfo.type, titleInfo.version);
        } else {
            const char *titleIdString = MakeTitleIdString(titleId);
            MILO_LOG("Store: titleId = %s not owned.\n", titleIdString);
        }
    }
}

bool WiiCommerceMgr::SetParentalControlPin(String pin)
{
    const char *pinStr = pin.c_str();
    int ret = EC_SetParameter("PCPW", pinStr);
    return (ret == 0 || ret == -4075);
}

unsigned long long WiiCommerceMgr::MakeDataTitleId(const char *cc) {
    struct {
        union {
            unsigned long long u64parts;
            unsigned int u32parts[2];
            char charparts[0x8];
        };
    } tidParts;
    tidParts.u32parts[0] = 0x00010005;
    tidParts.u32parts[1] = 0;
    tidParts.charparts[4] = cc[0];
    tidParts.charparts[5] = cc[1];
    tidParts.charparts[6] = cc[2];
    tidParts.charparts[7] = cc[3];
    return tidParts.u64parts;
}

unsigned int FileSizeToBlocks(unsigned int fileSize, bool unk)
{
    if (unk) {
        fileSize += 0x3FFF;
    }
    return fileSize >> 14;
}

char *MakeTitleIdString(unsigned long long titleId) {
    struct {
        union {
            unsigned long long u64parts;
            unsigned int u32parts[2];
            char charparts[0x8];
        };
    } tidParts;
    tidParts.u64parts = titleId;
    gMakeTitleIdString[0] = tidParts.charparts[4];
    gMakeTitleIdString[1] = tidParts.charparts[5];
    gMakeTitleIdString[2] = tidParts.charparts[6];
    gMakeTitleIdString[3] = tidParts.charparts[7];
    return gMakeTitleIdString;
}