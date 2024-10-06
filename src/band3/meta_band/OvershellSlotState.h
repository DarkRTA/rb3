#pragma once
#include "obj/Object.h"
#include "meta_band/OvershellSlot.h"
#include "obj/Msg.h"

enum OvershellSlotStateID {

};

class OvershellSlotState : public Hmx::Object {
public:
    OvershellSlotState(DataArray*, OvershellSlot*);
    virtual ~OvershellSlotState(){}

    OvershellSlotStateID GetStateID() const;
    Symbol GetView();
    void UpdateView();

    DataNode HandleMsg(const Message&);

    OvershellSlotStateID mStateID; // 0x1c
    OvershellSlot* mSlot; // 0x20
};

class OvershellSlotStateMgr {
public:
    OvershellSlotStateMgr();
    ~OvershellSlotStateMgr();
    void Init(DataArray*, OvershellSlot*);
    OvershellSlotState* GetSlotState(OvershellSlotStateID);

    std::vector<OvershellSlotState*> mStates; // 0x0
};