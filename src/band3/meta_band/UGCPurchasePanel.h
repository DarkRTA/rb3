#pragma once
#include "game/BandUser.h"
#include "net_band/DataResults.h"
#include "ui/UIPanel.h"

class UGCPurchasePanel : public UIPanel {
public:
    enum PurchaseState {
        kUninitialized = 0
    };
    UGCPurchasePanel();
    OBJ_CLASSNAME(UGCPurchasePanel);
    OBJ_SET_TYPE(UGCPurchasePanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~UGCPurchasePanel() {}
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual void Unload();
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);

    int mPurchaseState; // 0x38
    LocalBandUser *mUser; // 0x3c
    Symbol mSong; // 0x40
    const char *mOfferID; // 0x44
    int mPurchaser; // 0x48
    bool unk4c; // 0x4c
    DataResultList mResultList; // 0x50
};