#pragma once
#include "ui/UIPanel.h"
#include "net/Synchronize.h"
#include "obj/MsgSource.h"
#include "math/Rand.h"
#include "meta_band/OvershellSlot.h"

class SessionMgr;
class BandUserMgr;

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

    std::vector<int> unk70; // 0x70
    std::vector<int> unk78; // 0x78
    int unk80;
    int unk84;
    bool unk88;
    bool unk89;
    bool unk8a;
    std::vector<int> unk8c;
    int unk9c;
    int unka0;
    int unka4;
    Rand unka8; // 0xa8
};