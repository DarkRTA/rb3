#pragma once
#include "Protocol/ProtocolCallContext.h"
#include "net_band/DataResults.h"
#include "obj/Object.h"
#include "os/Timer.h"

class ContextWrapper {
public:
    ContextWrapper();
    ~ContextWrapper();

    void SetCallbackObject(Hmx::Object *, Updatable *, bool, int);
    void Reset();
    void Poll();

    Hmx::Object *mCallbackObject; // 0x0
    Updatable *mUpdatable; // 0x4
    bool mDeleteUpdatable; // 0x8
    int mId; // 0xc
    Quazal::ProtocolCallContext *mContext; // 0x10
    Timer mTimeout; // 0x18
};

class ContextWrapperPool {
public:
    ContextWrapperPool();
    void Poll();
    void CancelOutstandingContexts(Hmx::Object *);
    void FailAllContexts();
    ContextWrapper *NewContextWrapper(Hmx::Object *, Updatable *, bool, int);

    ContextWrapper mContextWrappers[500]; // 0x0
    int unk8ca0; // 0x8ca0
    int unk8ca4; // 0x8ca4
};