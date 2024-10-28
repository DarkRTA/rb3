#pragma once
#include "LockStepMgr.h"
#include "obj/Object.h"

class NetSync : public Hmx::Object {
public:
    NetSync();
    virtual ~NetSync();
    virtual DataNode Handle(DataArray*, bool);

    bool IsBlockingTransition() const;

    static void Init();
    static void Terminate();

    bool unk1c; // 0x1c
    int unk20; // 0x20
    int unk24; // 0x24
    bool unk28; // 0x28
    bool unk29; // 0x29
    LockStepMgr* mUILockStep; // 0x2c
};

extern NetSync* TheNetSync;