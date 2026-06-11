#include "os/CommerceMgr_Wii.h"
#include "system/meta/StorePackedMetadata.h"
#include "ec/result.h"
#include "system/utl/HttpWii.h"
#include "os/PlatformMgr.h"
#include "os/ContentMgr_Wii.h"
#include "ec/csup.h"
#include "revolution/sc/scsystem.h"

extern int EC_CancelOperation(unsigned long);
extern ECResult EC_GetProgress(unsigned long, ECResult *);
extern int EC_Connect();
extern int CM_CNTSDCachePopRSO(long);

uint SCCheckPCShoppingRestriction() {
    unsigned long dest [2];
    if (SCFindU32Item(dest, SC_ITEM_NET_CTPC) == 0) dest[0] = 0;
    return dest[0] >> 2 & 1;
}

char gMakeTitleIdString[5];
char gUsersPIN [8];


bool gAllowNeedSyncReturn = true;

char *gCommerceFilterName_OfferType = "offer_type";
char *gCommerceFilterValue_Album = "album";
char *gCommerceFilterValue_Everything = "*";
char *gCommerceFilterValue_Pack = "pack";
char *gCommerceFilterValue_Song = "song";
char *gCommerceFilterValuePurchasable = "PURCHASABLE";

const char *__FUNCTION__22256 = "_M_set_finish_idx";

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

bool WiiCommerceMgr::IsBusy() const { return mCommerceAsyncOpId != -1; }

bool WiiCommerceMgr::NeedSync() {
    int r = EC_GetIsSyncNeeded();
    return (bool)(gAllowNeedSyncReturn & r != -0xFE2);
}

bool WiiCommerceMgr::CheckPurchaseSync() { return true; }

void WiiCommerceMgr::GetTitleInfo() {
    // titleInfo is actually WiiCommerceMgr.mTitleInfo
    ECTitleInfo titleInfo;
    for (int i = 0; i < mTitleIdsNum; i++) {
        unsigned long long titleId = mTitleIds[i];
        long r = EC_GetTitleInfo(titleId, &titleInfo);
        if (r != -4050) {
            const char *titleIdString = MakeTitleIdString(titleId);
            MILO_LOG(
                "Store: titleinfo: %d - titleId = %s | isTmdPresent = %d | isOnDevice = %d | type = %d | version = %d\n",
                r,
                titleIdString,
                titleInfo.isTmdPresent,
                titleInfo.isOnDevice,
                titleInfo.type,
                titleInfo.version
            );
        } else {
            const char *titleIdString = MakeTitleIdString(titleId);
            MILO_LOG("Store: titleId = %s not owned.\n", titleIdString);
        }
    }
}

bool WiiCommerceMgr::SetParentalControlPin(String pin) {
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

unsigned int FileSizeToBlocks(unsigned int fileSize, bool unk) {
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

float WiiCommerceMgr::TimeoutForOp(WiiCommerceMgr::LastCommerceOperation lastOp) {
    switch (lastOp) {
        case kConnect:
            return 45000.0f;
        case kPurchaseDataTitle:
            return 45000.0f;
        case kListContentSetsOffers:
            return 120000.0f;
        default:
            return 59000.0f;
    }
}

void WiiCommerceMgr::WaitAsyncOp(long opId, WiiCommerceMgr::LastCommerceOperation opName) {
    mCommerceAsyncOpId = opId;
    mCommerceAsyncName = opName;
    mOpId = TimeoutForOp(opName);
    mCommerceTimeout.Restart();
    unke8 = 0;
}

const char *GetAttributeStr(ECContentCatalogInfo *info, char *name) {
    uint u1, u3 = 0, u4 = info->nAttributes;
    int i2, i5 = 0;
    const char *theName;
    while (u4 > u3) {
        i2 = strcmp((info->attributes)[i5].name, name);
        if (i2 == 0) {
            theName = (info->attributes)[u3 * 8].name;
            break;
        }
        i5 += 8;
        u3 += 1;
    }
    return theName;
}

int WiiCommerceMgr::PauseCommerce(bool pause) {
    ECResult resPtr [40];
    if (pause && mCommerceAsyncOpId != -1) return 0;

    TheNetCacheMgr->Unload();
    while (!TheNetCacheMgr->IsUnloaded()) {
        Timer::Sleep(5);
        //bctrl to Poll() here
        TheNetCacheMgr->Poll();
    }
    if (mCommerceAsyncOpId != -1) {
        EC_CancelOperation(mCommerceAsyncOpId);
        int ret;
        do {
            ret = EC_GetProgress(mCommerceAsyncOpId, resPtr);
            Timer::Sleep(5);
        } while (ret == ECResult_NotDone);
        mCommerceAsyncOpId = -1;
    }
    EC_SetParameter("PCPW", "");
    TheWiiContentMgr.RestartEcommerce();
    TheHttpWii.Stop();
    while (TheHttpWii.GetStatus() != 0)
        Timer::Sleep(5);
    ThePlatformMgr.EnableProfanity(true);
    unkf5 = true;
    return 1;
}

int WiiCommerceMgr::UnpauseCommerce() {
    Symbol s2, s3;
    DataArray *d4, *d5;
    DataNode *d6;

    const char *appId, *tin;

    int status;

    long customerSupportCode;

    int ret;

    if ((TheStoreMetadata.mFlags & 1) != 0) return 1;
    while (ThePlatformMgr.mCheckingProfanity != false) {
        Timer::Sleep(5);
        ThePlatformMgr.Poll();
    }
    ThePlatformMgr.EnableProfanity(false);
    TheHttpWii.Start();
    s2.mStr = Symbol("commerce").mStr;
    s3.mStr = Symbol("net").mStr;
    d4 = SystemConfig(s3, s2);
    Symbol sym = Symbol("appid");
    const char *loc30 = sym.mStr;
    d5 = d4->FindArray(loc30, true);
    d6 = &(d5->Node(1));
    appId = d6->Str(d5);

    sym = Symbol("pcpw");
    const char *loc34 = sym.mStr;
    d5 = d4->FindArray(loc34, true);
    d6 = &(d5->Node(1));
    d6->Str(d5);

    sym = Symbol("tin");
    const char *loc38 = sym.mStr;
    d5 = d4->FindArray(loc38, true);
    d6 = &(d5->Node(1));
    tin = d6->Str(d4);

    //AppId
    status = EC_SetParameter("AppId", appId);
    if (EC_FAIL(status)) {
        customerSupportCode = EC_GetCustomerSupportCode(status);
        MILO_WARN(
            "%s failed->%d  CustomerSupportCode->%d", 
            "EC_SetParameter(APP_ID)", 
            status, 
            customerSupportCode
        );
    }

    //TIN
    status = EC_SetParameter("TIN", tin);
    if (EC_FAIL(status)) {
        customerSupportCode = EC_GetCustomerSupportCode(status);
        MILO_WARN(
            "%s failed->%d  CustomerSupportCode->%d", 
            "EC_SetParameter(TIN)", 
            status, 
            customerSupportCode
        );
    }

    //Parental Control Pin
    uint restriction = SCCheckPCShoppingRestriction();
    mParentalControlsActive = (-restriction | restriction) >> 0x1F;
    if (restriction != 0) {
        ret = 9999;
        while (ret > -1) {
            sprintf(gUsersPIN, "%04d", ret);
            status = EC_SetParameter("PCPW", gUsersPIN);
            if (status == ECResult_Success || status == ECResult_NoPC) {
                MILO_LOG("WiiCommerceMgr: parental pin enabled %s\n", gUsersPIN);
            }
            ret--;
        }
    }
    if (TheWiiContentMgr.mMode == 0) 
        EC_SetParameter("SPACE_CHECK_POLICY", "SPACE_CHECK_ENTIRE_FS");
    
    customerSupportCode = EC_Connect();
    if (customerSupportCode < 1) {
        MILO_WARN("EC_Connect failed: %d", customerSupportCode);
        HandleError(kConnect, customerSupportCode, "");
        ret = 0;
    } else {
        WaitAsyncOp(customerSupportCode, kConnect);
        ret = 1;
    }
    return ret;
}

int WiiCommerceMgr::TitleIndex(unsigned long long titleId) {
    for (int i = 0; i < mTitleIdsNum; ++i) {
        if (titleId == mTitleIds[i]) {
            return i;
        }
    }

    return 0;
}
extern "C" {
int WiiCommerceMgr::CancelCurrentOperation() {
    int ret;
    long &id = this->mCommerceAsyncOpId;
    if (id != -1 && EC_CancelOperation(id) == ECResult_Success) {
        WaitAsyncOp(id, kCancel);
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}
}
void WiiCommerceMgr::MarkChanged(bool changed) {
    this[0x44].unkc4 = true; //??? what
    if (changed)
        TheWiiContentMgr.mDirty = true;
}

void WiiCommerceMgr::InitPreDownload() {
    ushort u1 = unk215c;
    void *__dest = &unk2168;
    unk2160 = 0;
    void *__src = (void *)((int)u1 * 2);
    *(int *)((int)&mTitleId + 4) = 0;
    *(int *)&mTitleId = 0;
    unsigned long u2;
    if (__dest != __src) {
        if (__dest != __src) { //same comparison again?
            __dest = memmove(__dest, __src, 0);
        }
        u2 = (int)__dest - unk2158 / 2;
        std_vec_range_assert(u2, 0xFFFF, __FUNCTION__22256);
        unk215c = (short)u2;
    }
    unk2168 = 1;
    unk417c = 0;
    unk4180 = -1;
    mCurrentFreeBlocks = 0;
    mRequestedDownloadBlocks = 0;
    mBlocksAfterDownload = 0;
    return;
}

void WiiCommerceMgr::CleanupAfterDownload() {
    long ret;
    if (TheWiiContentMgr.mMode == 0) {
        ret = CM_CNTSDCachePopRSO(-1);
        if (ret != 0)
            MILO_WARN("CM: Failed: Unmount, CNTSDCachePop() returned %d\n", ret);
    }
    InitPreDownload();
}

unsigned int WiiCommerceMgr::PricesRemaining() {
    return (unsigned int)(-unkb8 | unkb8) >> 0x1f;
}

unsigned int WiiCommerceMgr::OffersRemaining() {
    return (unsigned int)(-unk211c | unk211c) >> 0x1f;
}

bool WiiCommerceMgr::JustListedContentSetsPrices() {
    return mCommerceAsyncName == 2;
}

bool WiiCommerceMgr::ParentalControlsActive() {
    return mParentalControlsActive;
}

long WiiCommerceMgr::GetCurrentFreeBlocks() {
    return mCurrentFreeBlocks;
}

long WiiCommerceMgr::GetRequestedDownloadBlocks() {
    return mRequestedDownloadBlocks;
}

long WiiCommerceMgr::GetBlocksAfterDownload() {
    return mBlocksAfterDownload;
}

long WiiCommerceMgr::GetNeededBlocks() {
    return mNeededBlocks;
}

void WiiCommerceMgr::HandleError(WiiCommerceMgr::LastCommerceOperation lastOp, int p2, const char *p3) {
    DataNode l68, l60, l58, l50, l38, l30, l28;

    if (!(*(bool *)(0x80c7a18c))) {
        l68.mValue.symbol = NULL;
        l68.mValue.integer = 6;
        l68.mValue.real = 0.0f;
        l68.mValue.array = (DataArray *)0x6;
        l68.mValue.var = (DataNode *)0x0;
        l68.mValue.func = (DataFunc *)0x6;


    }
}

//CommerceMgrCancelCompleteMsg

CommerceMgrCancelCompleteMsg::~CommerceMgrCancelCompleteMsg() {}

//CommerceMgrOpCompleteMsg
CommerceMgrOpCompleteMsg::~CommerceMgrOpCompleteMsg() {}

