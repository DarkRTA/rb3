#pragma once
#include "obj/Object.h"

class LockStepMgr : public Hmx::Object {
public:
    LockStepMgr(const char*, Hmx::Object*);
    virtual ~LockStepMgr();
    virtual DataNode Handle(DataArray*, bool);

    int unk1c;
    std::vector<int> unk20;
    bool unk28;
    Hmx::Object* unk2c;
};