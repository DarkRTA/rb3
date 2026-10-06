#pragma once
#include "obj/Msg.h"
#include "revolution/ec/ec.h"
#include "utl/NetCacheMgr.h"
#include "meta/StoreOffer.h"

#define MEMFREE(mem) \
        _MemFree(mem); \
        mem = 0

class WiiCommerceMgr : public MsgSource {
public:
    enum LastCommerceOperation {
        kConnect,
        kListTitleContents,
        kListContentSetsPrice,
        kDownloadContents,
        kDownloadTitle,
        kListContentSetsPurchase,
        kPurchaseDataTitle,
        kCancel,
        kListContentSetsOffers,
        kGetTitleInfo,
        kDownloadTitleAndContents
    };
    WiiCommerceMgr();
    virtual DataNode Handle(DataArray *, bool);
    virtual ~WiiCommerceMgr();
    virtual void Init();

    bool InitCommerce(Hmx::Object *);
    void DestroyCommerce();
    bool IsBusy() const;
    bool CheckPurchaseSync();
    bool NeedSync();
    void GetTitleInfo();
    bool SetParentalControlPin(String pin);
    void WaitAsyncOp(long, WiiCommerceMgr::LastCommerceOperation);
    int PauseCommerce(bool);
    int UnpauseCommerce();
    void HandleError(WiiCommerceMgr::LastCommerceOperation, int, const char *);
    int TitleIndex(unsigned long long);
    int CancelCurrentOperation();
    void MarkChanged(bool);
    void InitPreDownload();
    void CleanupAfterDownload();
    unsigned int PricesRemaining();
    unsigned int OffersRemaining();
    bool JustListedContentSetsPrices();
    bool ParentalControlsActive();
    long GetCurrentFreeBlocks();
    long GetRequestedDownloadBlocks();
    long GetBlocksAfterDownload();
    long GetNeededBlocks();
    bool UpdateTitle(unsigned long long);
    bool UpdateTitle(StorePurchaseable *, bool);
    bool UpdateTitleAndContents();
    bool UpdateTitleAndContents(unsigned long long);
    bool RequestPurchase(unsigned long long titleId, const char *what);

    static float TimeoutForOp(WiiCommerceMgr::LastCommerceOperation);

    static unsigned long long MakeDataTitleId(const char *);

    long mCommerceAsyncOpId; // 1c
    LastCommerceOperation mCommerceAsyncName; // 20
    int unk24; // 24
    Timer mCommerceTimeout; // 28
    //bool mChanged; // 58
    float mOpId; // 58
    unsigned long long mTitleId; // 60
    long mPrice; // 68
    char *mAttributes[6]; // 6c
    int unk84; // 84
    unsigned long mAttributesNum; // 88
    unsigned long long *mTitleIds; // 8c
    unsigned long mTitleIdsNum; // 90
    void *unk94; // 94
    int unk98; // 98
    void *unka8; // a8
    long unkac; // ac
    unsigned int unkb4; // b4
    ECAttributeFilterEx unkb8;

    char *unkc4; // c4
    char *unkc8;
    int unke4; // e4
    int unke8; // e8
    int customerSupportCode; // ec - customer support code?
    bool unkf0; // f0
    bool unkf1; // f1
    bool mParentalControlsActive; // f2
    bool unkf3; // f3
    bool unkf5; // f5
    Hmx::Object *mObj; // 2114
    int unk2118; // 2118
    unsigned int unk211c; // 211c - offers remaining?
    void *unk2120; // 2120
    short unk251c; // 251c
    bool unk2150; // 2150
    bool unk2151; // 2151
    int unk2154; // 2154
    std::_Vector_impl<unsigned short> unk2158; // 2158
    short unk215c; // 215c
    int unk2160; // 2160
    u8 unk2168; // 2168
    int unk417c; // 417c
    int unk4180; // 4180
    long mCurrentFreeBlocks; // 4184
    long mRequestedDownloadBlocks; // 4188
    long mBlocksAfterDownload; // 418c
    long mNeededBlocks; // 4190
    bool unk4194; // 4194
    int *unk4198; // 4198
    int *unk419c; // 419c
    unsigned long unk41a4; // 41a4
    unsigned long unk41a0; // 41a0

};

extern WiiCommerceMgr TheWiiCommerceMgr;



char *MakeTitleIdString(unsigned long long titleId);

const char *GetAttributeStr(ECContentCatalogInfo *, char *);

class CommerceMgrCancelCompleteMsg : public Message {
public:
    CommerceMgrCancelCompleteMsg();
    ~CommerceMgrCancelCompleteMsg();
private:
};

class CommerceMgrOpCompleteMsg : public Message {
public:
    CommerceMgrOpCompleteMsg();
    ~CommerceMgrOpCompleteMsg();
private:
};
