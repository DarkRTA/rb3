#pragma once
#include "meta/StoreOffer.h"
#include "meta/StoreEnumeration.h"
#include "meta/StorePreviewMgr.h"
#include "ui/UIPanel.h"

enum StoreError {
    kStoreErrorSuccess = 0,
    kStoreErrorNoContent = 1,
    kStoreErrorCacheNoSpace = 2,
    kStoreErrorCacheRemoved = 3,
    kStoreErrorLiveServer = 4,
    kStoreErrorStoreServer = 5,
    kStoreErrorSignedOut = 6,
    kStoreErrorNoMetadata = 7,
    kStoreErrorEcommerce = 8,
    kStoreErrorNoEula = 9
};

enum SessionStatus {
    kSessionNone = 0,
    kSessionCreating = 1,
    kSessionCreated = 2
};

class StorePanel : public UIPanel {
public:
    StorePanel();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~StorePanel();
    virtual void Enter();
    virtual void Exit();
    virtual bool Exiting() const;
    virtual bool Unloading() const;
    virtual void Poll();
    virtual void Load();
    virtual void Unload();
    virtual bool IsLoaded() const;
    virtual void PollForLoading();
    
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual bool IsSongInLibrary(const int&) const = 0;
    virtual void ExitStore(StoreError) const = 0;
    virtual int StoreUser() const = 0; // fix ret type
    virtual void MakeNewOffer(const StorePackedOfferBase*, bool) = 0;
    virtual StoreOffer* FindOffer(Symbol) const = 0;
    virtual bool EnumerateSubsetOfOfferIDs() const { return false; }
    virtual void LoadArt(const char*, UIPanel*);
    virtual void PopulateOffers(DataArray*, bool);
    virtual void EnumerateOffers(bool);
    virtual int UpdateOffers(const std::list<EnumProduct>&, bool); // fix ret type
    virtual void UpdateFromEnumProduct(StorePurchaseable*, const EnumProduct*);
    virtual void LoadMetadata();
    virtual bool IsMetadataLoaded();
    virtual void StoreUserProfileSwappedToUser(LocalUser*) = 0;

    void SetSource(Symbol, bool);
    void SetSourceToBackup();
    void SetStoreMode(Symbol);
    void CancelArt();
    bool ToggleTestOffers();

    static StorePanel* Instance();

    std::vector<StoreOffer*> unk38;
    std::vector<int> unk40;
    std::vector<int> unk48;
    bool mLoadOK; // 0x50
    bool mShowTestOffers; // 0x51
    std::list<StorePanel*> unk54;
    NetCacheLoader* mPendingArtLoader; // 0x5c
    RndTex* mAlbumTex; // 0x60
    UIPanel* mPendingArtCallback; // 0x64
    StorePreviewMgr* mStorePreviewMgr; // 0x68
    WiiEnumeration* mEnum; // wiienumeration
    bool unk70;
    bool unk71;
    int mPurchaser; // 0x74
    Symbol mSource; // 0x78
    Symbol mBackupSource; // 0x7c
    SessionStatus mSessionStatus; // 0x80
    StorePurchaseable* mCurrentOffer; // 0x84
    bool mCurrentOfferUpgrade; // 0x88
    bool unk89;
    int mStoreMode; // 0x8c
};