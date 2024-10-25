#pragma once
#include "game/NetGameMsgs.h"
#include "obj/Object.h"
#include "utl/Str.h"
#include <set>

class BandMachine : public Hmx::Object {
public:
    BandMachine();
    virtual ~BandMachine(){}
    virtual DataNode Handle(DataArray*, bool);
    virtual bool IsLocal() const = 0;
    virtual String GetPrimaryBandName();

    String GetPrimaryProfileName();
    void Reset();
    void SyncSave(BinStream&, unsigned char) const;
    void SyncLoad(BinStream&, unsigned char);
    NetUIState GetNetUIState() const;
    int GetNetUIStateParam() const;
    bool HasSong(int) const;
    bool HasProGuitarOrBass(int) const;

    NetUIState mNetUIState; // 0x1c
    int mNetUIStateParam; // 0x20
    std::set<int> mSongs; // 0x24
    std::set<int> mSongsWithProStrings; // 0x3c
    String mCurrentSongPreview; // 0x54
    String mPrimaryBandName; // 0x60
    String mPrimaryProfileName; // 0x6c
    int mPrimaryMetaScore; // 0x78
};