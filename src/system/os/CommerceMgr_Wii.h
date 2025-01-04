#pragma once
#include "obj/Msg.h"

class WiiCommerceMgr : public MsgSource {
public:
    WiiCommerceMgr();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~WiiCommerceMgr();

    bool InitCommerce(Hmx::Object*);
    void DestroyCommerce();

    static unsigned long long MakeDataTitleId(const char*);

    int unk1c;
    int unk20;
    int unk24;
    Timer unk28;
    float unk58;
};

extern WiiCommerceMgr TheWiiCommerceMgr;