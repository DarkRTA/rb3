#pragma once
#include "MatchmakingSettings.h"
#include "NetSession.h"
#include "obj/Object.h"
#include "utl/BinStream.h"

class NetSearchResult : public Hmx::Object {
public:
    NetSearchResult();
    virtual ~NetSearchResult();
    virtual DataNode Handle(DataArray*, bool);
    virtual void Load(BinStream&);
    virtual void Save(BinStream&) const;
    virtual bool Equals(const NetSearchResult*) const;

    static NetSearchResult* New();

    SessionData* mSessionData; // 0x1c
    MatchmakingSettings* mSettings; // 0x20
    int mNumOpenSlots; // 0x24
    String mHostName; // 0x28
};