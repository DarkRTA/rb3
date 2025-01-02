#pragma once
#include "obj/Msg.h"

class WiiCommerceMgr : public MsgSource {
public:
    WiiCommerceMgr();

    bool InitCommerce(Hmx::Object*);
    void DestroyCommerce();

    static unsigned long long MakeDataTitleId(const char*);
};

extern WiiCommerceMgr TheWiiCommerceMgr;