#include "os/CommerceMgr_Wii.h"
#include "system/meta/StorePackedMetadata.h"
#include "ec/result.h"
#include "system/utl/HttpWii.h"
#include "os/PlatformMgr.h"
#include "os/ContentMgr_Wii.h"
//#include "ec/csup.h"
#include "revolution/sc/scsystem.h"

extern "C" {
    extern int EC_CancelOperation(unsigned long);
    extern int EC_GetOverhead(int, int *, int *);
    extern int EC_GetCustomerSupportCode(int);
    extern ECResult EC_GetProgress(unsigned long, ECResult *);
    extern int EC_Connect();
    extern int CM_CNTSDCachePopRSO(long);
    extern int EC_DownloadTitle(unsigned long long, int);
    extern long NCDGetCurrentIpConfig(const char *ip); //? is the parameter the ip?
    
}
extern int CM_CNTSDCacheClearRSO();

uint SCCheckPCShoppingRestriction() {
    unsigned long dest [2];
    if (SCFindU32Item(dest, SC_ITEM_NET_CTPC) == 0) dest[0] = 0;
    return dest[0] >> 2 & 1;
}

char gMakeTitleIdString[5];
char gUsersPIN [8];


bool gAllowNeedSyncReturn = true;
bool gNetUseTimedSleep;

int gLastErrorReturnValue;
char gLastErrorDesc [128];

char *gCommerceFilterName_OfferType = "offer_type";
char *gCommerceFilterValue_Album = "album";
char *gCommerceFilterValue_Everything = "*";
char *gCommerceFilterValue_Pack = "pack";
char *gCommerceFilterValue_Song = "song";
char *gCommerceFilterValuePurchasable = "PURCHASABLE";
char *gTempRequestOfferId;
char *gTempOfferIdValues;

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
    return (bool)(gAllowNeedSyncReturn & EC_GetIsSyncNeeded() != -0xFE2);
}

bool WiiCommerceMgr::CheckPurchaseSync() { return true; }

void WiiCommerceMgr::GetTitleInfo() {
    // titleInfo is actually WiiCommerceMgr.mTitleInfo
    ECTitleInfo titleInfo;
    for (unsigned long i = 0; i < mTitleIdsNum; i++) {
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

const char *GetAttributeStr(const ECContentCatalogInfo *info, char *name) {
    for (uint i = 0; i < info->nAttributes; i += 1) {
        if (streq((info->attributes)[i].name, name))
            return (const char *)(info->attributes)[i].value;
    }
    return NULL;
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
    unk4194 = true; //??? what
    if (changed)
        TheWiiContentMgr.mDirty = true;
}

void WiiCommerceMgr::InitPreDownload() {
    ushort u1 = unk215c;
    void *__dest = &unk2168;
    unk2160 = 0;
    void *__src = (void *)((int)u1 * 2);
    mTitleId = 0;
    unsigned long u2;
    if (__dest != __src) {
        if (__dest != __src) { //same comparison again?
            __dest = memmove(__dest, __src, 0);
        }
        u2 = (int)__dest - unk2158.size() / 2;
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
    //return (unsigned int)(-*(unsigned int *)unkb8 | unkb8) >> 0x1f;
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

bool WiiCommerceMgr::InitCommerce(Hmx::Object *obj) {
    if (--unk2154 < 2) {
        gLastErrorReturnValue = 0;
        gLastErrorDesc[0] = '\0';
        customerSupportCode = 0;
        long err = NCDGetCurrentIpConfig("");
        if (err < 0) {
            gLastErrorReturnValue = err;
            int supportCode = EC_GetCustomerSupportCode(err);
            customerSupportCode = supportCode;
            MILO_WARN("WiiCommerceMgr: no network config, %d, %d", err, supportCode);
            if (err == -7) {
                customerSupportCode = 50299; //0xC47B
            }
            return false;
        }
        unk94 = _MemAlloc(0x780, 0x20);
        unk2120 = _MemAlloc(0x4DB20, 0x20);
        unkac = 0x80000;
        unka8 = _MemAlloc(0x80000, 0x20);
        DataArray *config = SystemConfig("store", "titles");
        mTitleIds = (unsigned long long *)config->mSize;

    } else {
        mObj = obj;
        return true;
    }
}

void WiiCommerceMgr::DestroyCommerce() {
    if (--unk2154 <= 0) {
        if (unk2154 < 0) {
            unk2154 = 0;
        } else {
            PauseCommerce(false);
            if (TheWiiContentMgr.mMode == 0)
                CM_CNTSDCacheClearRSO();
            if (unka8) {
                MEMFREE(unka8);
            }
            if (unk94) {
                MEMFREE(unk94);
            }
            if (unk2120) {
                MEMFREE(unk2120);
            }
            if (mTitleIdsNum) {
                _MemFree((void *)mTitleIdsNum);
                mTitleIdsNum = 0;
            }
            gNetUseTimedSleep = false;
            unkf1 = false;
        }
    }
}

bool WiiCommerceMgr::UpdateTitle(unsigned long long titleId) {
    if (TheWiiContentMgr.mMode == 0) {
        long ret = CM_CNTSDCacheClearRSO();
        if (ret != 0) {
            MILO_WARN("CM_CNTSDCacheClearRSO failed: %d", ret);
            HandleError(kDownloadTitle, -0xfa1, "");
            return false;
        }
        ret = 0;
        unsigned long huh;
        OpResult res = WiiContentMgr::CheckNANDSpace(unk41a0, unk41a4, huh, true);
        if (res != kOpSuccess) {
            MILO_WARN("DownloadSpecifiedContentUnits failed: (%d): spaceCheck: cu (%d), need (%d)", res, unk41a0, ret);
            HandleError(kDownloadTitle, -4001, "");
            return false;
        }
        //CM_CNTSDCache something something
    }
}

bool WiiCommerceMgr::UpdateTitle(StorePurchaseable *offer, bool upgrade) {
    if (upgrade)
        return UpdateTitle(offer->GetUpgradeTitleId());
    return UpdateTitle(offer->GetTitleId());
}

bool WiiCommerceMgr::UpdateTitleAndContents(unsigned long long titleId) {
    int ret = EC_DownloadTitle(titleId, 2);
    if (ret <= 0) {
        HandleError(kDownloadTitleAndContents, ret, "");
        return false;
    }
    WaitAsyncOp(ret, kDownloadTitleAndContents);
    return true;
}

bool WiiCommerceMgr::UpdateTitleAndContents() {
    DataArray *config = SystemConfig(store, titles);
    return UpdateTitleAndContents(MakeDataTitleId(String(config->Str(1))));
}

bool WiiCommerceMgr::RequestPurchase(unsigned long long titleId, const char *offerId) {
    mTitleId = titleId;
    unke4 = 2;
    unk98 = 0x28;
    strncpy(gTempRequestOfferId, offerId, 0x10);
    gTempRequestOfferId[0x10] = '\0';
    gTempOfferIdValues = gTempRequestOfferId;
    unkc4 = "offer_id";
    unkc8 = gTempOfferIdValues;
}

//CommerceMgrCancelCompleteMsg

CommerceMgrCancelCompleteMsg::~CommerceMgrCancelCompleteMsg() {}

//CommerceMgrOpCompleteMsg
CommerceMgrOpCompleteMsg::~CommerceMgrOpCompleteMsg() {}

