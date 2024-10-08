#pragma once
#include "ui/UIPanel.h"
#include "net/Synchronize.h"
#include "obj/MsgSource.h"
#include "math/Rand.h"
#include "meta_band/OvershellSlot.h"

class SessionMgr;
class BandUserMgr;

enum OvershellActiveStatus {
    kOvershellInactive = 0,
    kOvershellInShell = 1,
    kOvershellInGameShell = 2,
    kOvershellInSong = 3
};

class OvershellPanel : public UIPanel, public Synchronizable, public MsgSource {
public:
    OvershellPanel(SessionMgr*, BandUserMgr*);
    OBJ_CLASSNAME(OvershellPanel);
    OBJ_SET_TYPE(OvershellPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~OvershellPanel();
    virtual void Enter();
    virtual void Exit();
    virtual bool Exiting() const;
    virtual void Poll();
    virtual void FinishLoad();
    virtual void SyncSave(BinStream&, unsigned int);
    virtual void SyncLoad(BinStream&, unsigned int);
    virtual bool HasSyncPermission() const;
    virtual void OnSynchronized(unsigned int);

    bool CanGuitarPlayKeys() const;
    void UpdateAll();
    void EndOverrideFlow(OvershellOverrideFlow, bool);
    bool IsFinding() const;
    bool InSong() const;

    std::vector<OvershellSlot*> unk70; // 0x70
    std::vector<int> unk78; // 0x78
    OvershellOverrideFlow mPanelOverrideFlow; // 0x80
    OvershellActiveStatus mActiveStatus; // 0x84
    bool mSongOptionsRequired; // 0x88
    bool unk89;
    bool unk8a;
    std::vector<int> unk8c;
    SessionMgr* mSessionMgr; // 0x94
    BandUserMgr* mBandUserMgr; // 0x98
    BandUser* mPartRestrictedUser; // 0x9c
    TrackType mPartRestriction; // 0xa0
    Difficulty mMinimumDifficulty; // 0xa4
    Rand mPartResolver; // 0xa8
    int unk4b8; // 0x4b8
    bool unk4bc;
    std::vector<int> unk4c0;
    bool unk4c8;
    int unk4cc;
};