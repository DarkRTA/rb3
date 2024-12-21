#pragma once
#include "obj/Msg.h"

class WiiCommerceMgr : public MsgSource {
public:
    WiiCommerceMgr();

    void InitCommerce(Hmx::Object*);
    void DestroyCommerce();
};

extern WiiCommerceMgr TheWiiCommerceMgr;