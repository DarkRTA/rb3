#pragma once
#include "obj/Object.h"
#include "net_band/DataResults.h"
#include "game/BandUserMgr.h"
#include "bandobj/OvershellDir.h"
#include "meta_band/SessionMgr.h"
#include "bandobj/BandLabel.h"

class OvershellPanel;
class OvershellSlotState;
class OvershellSlotStateMgr;
class PassiveMessageQueue;
class CharProvider;
class SessionUsersProvider;
class OvershellProfileProvider;
class OvershellPartSelectProvider;
class CymbalSelectionProvider;

enum OvershellOverrideFlow {
    kOverrideFlow_None = 0,
    kOverrideFlow_SongSettings = 1,
    kOverrideFlow_RegisterOnline = 2
};

class OvershellSlot : public Hmx::Object {
public:
    OvershellSlot(int, OvershellPanel*, OvershellDir*, BandUserMgr*, SessionMgr*);
    virtual ~OvershellSlot();
    virtual DataNode Handle(DataArray*, bool);
    virtual void SetTypeDef(DataArray*);
    virtual class ObjectDir* DataDir();

    bool InOverrideFlow(OvershellOverrideFlow) const;

    OvershellSlotStateMgr* mStateMgr; // 0x1c
    OvershellSlotState* mState; // 0x20
    int unk24;
    int unk28;
    BandLabel* unk2c;
    OvershellPanel* mOvershell; // 0x30
    BandUserMgr* mBandUserMgr; // 0x34
    SessionMgr* mSessionMgr; // 0x38
    int mSlotNum; // 0x3c
    std::vector<int> unk40;
    std::vector<int> unk48;
    OvershellDir* mOvershellDir; // 0x50
    bool unk54;
    bool unk55;
    Symbol unk58;
    bool unk5c;
    bool mInGame; // 0x5d
    bool unk5e;
    std::vector<int> mPotentialUsers; // 0x60 - PotentialUserEntry - seems to be 3 words long
    DataResultList mLinkingCodeResultList; // 0x68
    bool unk80;
    bool unk81;
    int unk84;
    int unk88;
    PassiveMessageQueue* mMessageQueue; // 0x8c
    int unk90;
    CharProvider* mCharProvider; // 0x94
    SessionUsersProvider* unk98;
    SessionUsersProvider* unk9c;
    OvershellProfileProvider* mSwappableProfilesProvider; // 0xa0
    OvershellPartSelectProvider* mPartSelectProvider; // 0xa4
    CymbalSelectionProvider* mCymbalProvider; // 0xa8
};