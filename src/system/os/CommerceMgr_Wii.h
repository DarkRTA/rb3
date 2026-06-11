#pragma once
#include "obj/Msg.h"
#include "revolution/ec/ec.h"
#include "utl/NetCacheMgr.h"

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

    static float TimeoutForOp(WiiCommerceMgr::LastCommerceOperation);

    static unsigned long long MakeDataTitleId(const char *);

    long mCommerceAsyncOpId; // 1c
    LastCommerceOperation mCommerceAsyncName; // 20
    int unk24; // 24
    Timer mCommerceTimeout; // 28
    bool mChanged; // 3c
    float mOpId; // 58
    unsigned long long mTitleId; // 60
    long mPrice; // 68
    char *mAttributes[7]; // 6c
    unsigned long mAttributesNum; // 88
    unsigned long mTitleIdsNum; // 8c
    unsigned long long *mTitleIds; // 90
    unsigned int unkb4; // b4
    unsigned int unkb8; // b8
    bool unkc4; // c4
    int unke8; // e8
    void *unkf0; // f0
    bool mParentalControlsActive; // f2
    bool unkf5; // f5
    unsigned int unk211c; // 211c - offers remaining?
    short unk251c; // 251c
    int unk2158; // 2158
    short unk215c; // 215c
    int unk2160; // 2160
    u8 unk2168; // 2168
    int unk417c; // 417c
    int unk4180; // 4180
    long mCurrentFreeBlocks; // 4184
    long mRequestedDownloadBlocks; // 4188
    long mBlocksAfterDownload; // 418c
    long mNeededBlocks; // 4190

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
