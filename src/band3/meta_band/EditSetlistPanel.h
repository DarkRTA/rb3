#pragma once
#include "bandobj/PatchDir.h"
#include "game/Defines.h"
#include "meta_band/BandProfile.h"
#include "net_band/DataResults.h"
#include "net_band/RockCentralMsgs.h"
#include "os/PlatformMgr.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"
#include "utl/Str.h"

class EditSetlistPanel : public UIPanel {
public:
    enum EditState {
        kEntering = 0,
        kCheckingProfanity = 4
    };
    enum FailureReason {
    };
    enum UIState {
    };
    EditSetlistPanel();
    OBJ_CLASSNAME(EditSetlistPanel);
    OBJ_SET_TYPE(EditSetlistPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~EditSetlistPanel();
    virtual void Enter();
    virtual bool Exiting() const;
    virtual void Poll();
    virtual void Unload();
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);

    void CleanupStringVerify();
    void SetEditState(EditState);
    void VerifyStrings(const char *, const char *);
    bool CreateSetlist(bool);
    bool EditSetlist(LocalBandUser *, LocalSavedSetlist *);
    bool CreateBattle();
    Symbol GetMessageToken();
    Symbol GetTitleToken();
    RndTex *GetArtTex();
    void DoneEditing();
    void FailWithReason(FailureReason);
    void VerifyStringsComplete(bool, bool);
    int SymToDayCount(Symbol);
    int SymToTimeUnits(Symbol);
    Symbol DayCountToSym(int);
    void MessageOK();

    DataNode OnMsg(const UITransitionCompleteMsg &);
    DataNode OnMsg(const RockCentralOpCompleteMsg &);
    DataNode OnMsg(const DWCProfanityResultMsg &);
    NEW_OBJ(EditSetlistPanel);
    static void Init() { REGISTER_OBJ_FACTORY(EditSetlistPanel); }

    String mSetlistName; // 0x38
    String mSetlistDescription; // 0x44
    ScoreType unk50; // 0x50
    int unk54;
    int unk58;
    PatchDescriptor mSetlistArt; // 0x5c
    bool unk64;
    DataResultList unk68;
    int unk80;
    int unk84;
    BandProfile *mProfile; // 0x88
    LocalSavedSetlist *mEditingSetlist; // 0x8c
    unsigned short **unk90;
    char *unk94;
    bool unk98;
    int unk9c; // 0x9c - mode? 0 = create setlist, 1 = edit setlist, 2 = create battle
    EditState mEditState; // 0xa0
    FailureReason unka4; // 0xa4
};