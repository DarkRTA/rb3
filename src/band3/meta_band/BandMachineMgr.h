#pragma once
#include "game/NetGameMsgs.h"
#include "obj/MsgSource.h"

class BandMachineMgr : public MsgSource {
public:
    void RefreshPrimaryProfileInfo();
};