#pragma once
#include "net/Synchronize.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"

class InterstitialMgr : public Synchronizable, public Hmx::Object {
public:
    InterstitialMgr();
    virtual ~InterstitialMgr(){}
    virtual void SyncSave(BinStream&, unsigned int) const;
    virtual void SyncLoad(BinStream&, unsigned int);
    virtual bool HasSyncPermission() const;
    virtual DataNode Handle(DataArray*, bool);

    void SetFromConfig();
    void RefreshRandomSelection();
    void GetInterstitialsFromScreen(UIScreen*, std::vector<UIPanel*>&);
    UIPanel* PickInterstitialBetweenScreens(const char*, const char*);
    UIScreen* CurrentInterstitialToScreen(UIScreen*) const;
    void PrintOverlay(UIScreen*, UIScreen*);
    void CycleRandomOverride();

    std::map<Symbol, std::map<Symbol, DataArray*> > mScreenInterstitialMap; // 0x38
    std::map<Symbol, UIScreen*> mCurrentInterstitials; // 0x50
    int mRandomOverride; // 0x68
    int mRandomSelection; // 0x6c
};