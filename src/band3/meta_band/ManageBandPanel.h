#pragma once
#include "MetaMessages.h"
#include "meta_band/BandProfile.h"
#include "meta_band/CharProvider.h"
#include "meta_band/ProfileMessages.h"
#include "meta_band/StandInProvider.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include "rndobj/Tex.h"
#include "ui/UIListProvider.h"
#include "ui/UIPanel.h"

class VignetteViewerProvider : public UIListProvider, public Hmx::Object {
public:
    VignetteViewerProvider() : unk20(0) {}
    virtual ~VignetteViewerProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual int NumData() const { return mEntries.size(); }
    virtual DataNode Handle(DataArray*, bool);

    bool IsLocked(int);
    Symbol GetScreen(int);

    DataArray* unk20; // 0x20
    std::vector<Symbol> mEntries; // 0x24
};

class ManageBandPanel : public UIPanel {
public:
    enum ManageBandState {
        kManageBandNone = 0,
        kManageBandMain = 1,
        kManageBandStandins = 2
    };

    ManageBandPanel();
    OBJ_CLASSNAME(ManageBandPanel);
    OBJ_SET_TYPE(ManageBandPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~ManageBandPanel();
    virtual void Enter();
    virtual void Exit();
    virtual void Unload();

    void RefreshToMainState();
    void RefreshToStandinsState();
    void RefreshAll();
    void SetManageBandState(ManageBandState);
    void CheckForKickoutCondition();
    void SetProfile(BandProfile*);
    void ClearProfile();
    RndTex* GetBandLogoTex();
    StandInProvider* GetStandInProvider();
    CharProvider* GetCharProvider();
    VignetteViewerProvider* GetHistoryProvider();
    void UpdateCharacterFromStandInList(int);
    void UpdateCharacterFromCharList(int);
    void ShowCharacter();
    void HideCharacter();
    void RefreshStandinList();
    void SetSelectedStandIn(int);
    void SetStandIn(int);
    void QueueRewardVignette(Symbol);
    BandProfile* GetProfile(){ return mProfile; }
    int GetSelectedStandIn() const { return mSelectedStandIn; }
    ManageBandState GetManageBandState(){ return mManageBandState; }

    DataNode OnMsg(const SigninChangedMsg&);
    DataNode OnMsg(const ProfileChangedMsg&);

    ManageBandState mManageBandState; // 0x38
    int unk3c; // 0x3c
    int mSelectedStandIn; // 0x40
    StandInProvider* mStandInProvider; // 0x44
    CharProvider* mCharProvider; // 0x48
    BandProfile* mProfile; // 0x4c
    VignetteViewerProvider* mHistoryProvider; // 0x50
};