#pragma once
#include "obj/Data.h"
#include "obj/Object.h"
#include "game/BandUser.h"
#include "beatmatch/PlayerTrackConfig.h"
#include "game/PracticeSectionProvider.h"
#include "game/Defines.h"

class BandUser;

class GameConfig : public Hmx::Object {
public:
    GameConfig();
    virtual ~GameConfig();
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);

    Difficulty GetAverageDifficulty() const;
    bool CanEndGame() const;
    int GetTrackNum(const UserGuid &) const;
    Symbol GetController(BandUser *) const;
    void ChangeDifficulty(BandUser *, int);
    void AssignTracks();
    bool IsInstrumentUsed(Symbol) const;
    void AssignTrack(BandUser *);
    void RemoveUser(BandUser *);
    void GetSectionBounds(int, float &, float &) const;
    void GetSectionBoundsTick(int, int &, int &) const;
    void ChangeRandomSeed();
    void GetPracticeSections(int &, int &) const;
    void OnSetRemoteUserTrackType(User *, Symbol);
    void OnSetRemoteUserDifficulty(User *, Symbol);
    int GetFxSwitchPosition(LocalBandUser *);
    bool WantCoda();
    void AutoAssignMissingSlots();

    DataNode OnGetSectionBounds(DataArray *);
    DataNode OnGetSectionBoundsTick(DataArray *);
    DataNode OnGetSection(DataArray *);
    DataNode OnSetSection(DataArray *);
    DataNode ForEach(const DataArray *, bool);

    PlayerTrackConfigList *GetConfigList() const { return mPlayerTrackConfigList; }

    PlayerTrackConfigList *mPlayerTrackConfigList; // 0x1c
    PracticeSectionProvider *mPracticeSectionProvider; // 0x20
    float mSongLimitMs; // 0x24
    int mPracticeSections[2]; // 0x28
    int mPracticeSpeed; // 0x30
    bool mPracticeMode; // 0x34
};

extern GameConfig *TheGameConfig;