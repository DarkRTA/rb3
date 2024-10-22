#pragma once
#include "game/BandUserMgr.h"
#include "obj/Object.h"
#include "meta_band/ProfileMessages.h"

class CharSync : public Hmx::Object {
public:
    CharSync(BandUserMgr*);
    virtual ~CharSync();
    virtual DataNode Handle(DataArray*, bool);

    void UpdateCharCache();

    DataNode OnMsg(const PrimaryProfileChangedMsg&);
    DataNode OnMsg(const ProfileChangedMsg&);

    static void Init(BandUserMgr*);

    BandUserMgr* mUserMgr; // 0x1c
};

extern CharSync* TheCharSync;