#pragma once
#include "meta_band/SavedSetlist.h"
#include "net_band/DataResults.h"
#include "obj/Object.h"
#include "rndobj/Tex.h"
#include "utl/NetCacheLoader.h"

class MusicLibraryNetSetlists : public Hmx::Object {
public:
    class SetlistArtRecord {
    public:
        int unk0;
        RndTex *unk4;
    };
    MusicLibraryNetSetlists();
    virtual ~MusicLibraryNetSetlists();
    virtual DataNode Handle(DataArray *, bool);

    void Poll();
    void CleanUp();
    void RefreshSetlists();
    bool IsSetlistArtReady(Symbol) const;
    RndTex *GetSetlistArt(Symbol) const;
    void RefreshSetlistArt();
    void FinishGettingSetlistArt(bool);
    void RefreshArchivedBattles();
    void CleanUpArt();
    void ParseDataResultsIntoSetlists(bool);

    DataNode OnMsg(const RockCentralOpCompleteMsg &);

    bool mFailed; // 0x1c
    bool mSucceeded; // 0x1d
    std::vector<NetSavedSetlist *> unk20;
    std::vector<NetSavedSetlist *> unk28;
    DataResultList mDataResults; // 0x30
    bool unk48;
    RndTex *mPendingSetlistArt; // 0x4c
    Symbol unk50;
    NetCacheLoader *mSetlistArtLoader; // 0x54
    std::list<SetlistArtRecord> mSetlists; // 0x58
};