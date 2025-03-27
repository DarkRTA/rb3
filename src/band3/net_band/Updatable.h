#pragma once
#include "obj/Msg.h"

class ContextWrapper;

class Updatable {
public:
    Updatable() : mContextWrapper(0) {}
    virtual ~Updatable() {}
    virtual void Update(Message *) = 0;
    virtual void SetWrapper(ContextWrapper *w) {
        MILO_ASSERT(mContextWrapper == NULL, 0x1D);
        mContextWrapper = w;
    }

    ContextWrapper *mContextWrapper; // 0x4
};

class IdUpdater : public Updatable {
public:
    IdUpdater(unsigned int id) : mRetCode(0), mID(id) {}
    virtual ~IdUpdater() {}
    virtual void Update(Message *msg) { (*msg)[1] = mRetCode; }

    char mRetCode; // 0x8
    unsigned int mID; // 0xc
};