#pragma once
#include "meta_band/UIEvent.h"
#include "obj/MsgSource.h"
#include <vector>

class UIEventQueue {
public:
    std::vector<UIEvent*> mEventQueue; // 0x0
};

class UIEventMgr : public MsgSource {
public:
    UIEventMgr(){}
    virtual DataNode Handle(DataArray*, bool);
    virtual ~UIEventMgr();
};

extern UIEventMgr* TheUIEventMgr;