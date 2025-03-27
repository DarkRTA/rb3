#include "net_band/ContextWrapper.h"
#include "net_band/RockCentral.h"
#include "network/Platform/String.h"
#include "network/Protocol/ProtocolCallContext.h"
#include "network/Services/BackEndServices.h"
#include "net_band/RockCentralMsgs.h"
#include "os/CritSec.h"
#include "os/Debug.h"
#include <cstddef>

namespace {
    CriticalSection gContextCrit;
}

ContextWrapper::ContextWrapper()
    : mCallbackObject(0), mUpdatable(0), mDeleteUpdatable(0), mId(-1), mContext(0) {}

ContextWrapper::~ContextWrapper() { delete mContext; }

void ContextWrapper::SetCallbackObject(Hmx::Object *o, Updatable *u, bool b, int i) {
    MILO_ASSERT(mContext == NULL, 0x2D);
    mCallbackObject = o;
    mUpdatable = u;
    mDeleteUpdatable = b;
    mId = i;
    mContext = new Quazal::ProtocolCallContext();
    mTimeout.Restart();
}

void ContextWrapper::Reset() {
    RELEASE(mContext);
    mCallbackObject = nullptr;
    if (mDeleteUpdatable)
        delete mUpdatable;
    mUpdatable = nullptr;
    mDeleteUpdatable = false;
}

int ContextWrapper::Poll() {
    int ret = 0;
    if (mContext) {
        switch (mContext->GetState()) {
        case 0:
            break;
        case 1:
            if (mTimeout.SplitMs() > 30000.0f)
                ret = 2;
            break;
        case 2: {
            RockCentralOpCompleteMsg msg(true, 0, mId);
            if (mCallbackObject) {
                if (mUpdatable)
                    mUpdatable->Update(&msg);
                mCallbackObject->Handle(msg, true);
            }
            ret = 1;
        } break;
        case 3:
        case 4: {
            MILO_LOG(
                "Encountered qError [%s]\n",
                (const char *)Quazal::BackEndServices::FormatQErrorCodeString(
                    "", mContext->unk20.m_iReturnCode
                )
                    .m_szContent
            );
            RockCentralOpCompleteMsg msg(false, 0, mId);
            if (mCallbackObject) {
                mCallbackObject->Handle(msg, true);
            }
            ret = 1;
        } break;
        default:
            MILO_LOG(
                "ContextWrapper::Poll(): got unknown state %d\n",
                (int)mContext->GetState()
            );
            break;
        }
    } else
        ret = 1;

    if (ret == 1)
        Reset();
    return ret;
}

ContextWrapperPool::ContextWrapperPool() : unk8ca0(0), unk8ca4(0) {}

ContextWrapper *
ContextWrapperPool::NewContextWrapper(Hmx::Object *o, Updatable *u, bool b, int x) {
    CritSecTracker cst(&gContextCrit);
    for (int i = 0; i < 500; i++) {
        if (!mContextWrappers[i].mContext) {
            mContextWrappers[i].SetCallbackObject(o, u, b, x);
            if (unk8ca4 < i)
                unk8ca4 = i;
            if (unk8ca0 < i)
                unk8ca0 = i;
            return &mContextWrappers[i];
        }
    }
    MILO_WARN("ContextWrapperPool ran out of contexts!");
    if (o) {
        RockCentralOpCompleteMsg msg(false, 11, x);
        o->Handle(msg, true);
    }
    return nullptr;
}

void ContextWrapperPool::CancelOutstandingContexts(Hmx::Object *o) {
    CritSecTracker cst(&gContextCrit);
    for (int i = 0; i <= unk8ca4; i++) {
        if (mContextWrappers[i].mContext && mContextWrappers[i].mCallbackObject == o) {
            mContextWrappers[i].Reset();
        }
    }
}

void ContextWrapperPool::FailAllContexts() {
    CritSecTracker cst(&gContextCrit);
    int cap = unk8ca4;
    for (int i = 0; i <= cap; i++) {
        if (mContextWrappers[i].mContext) {
            RockCentralOpCompleteMsg msg(false, 0, mContextWrappers[i].mId);
            if (mContextWrappers[i].mCallbackObject) {
                mContextWrappers[i].mCallbackObject->Handle(msg);
            }
            mContextWrappers[i].Reset();
        }
    }
}

void ContextWrapperPool::Poll() {
    CritSecTracker cst(&gContextCrit);
    bool b1 = true;
    int cap = unk8ca4;
    int poll = 0;
    for (int i = 0; i <= cap; i++) {
        if (mContextWrappers[i].mContext) {
            b1 = false;
            poll = mContextWrappers[i].Poll();
            if (poll == 2)
                break;
        }
    }
    if (poll == 2) {
        TheRockCentral.ForceLogout();
        FailAllContexts();
        return;
    } else if (b1 && unk8ca4 != 0) {
        unk8ca4 = 0;
    }
}