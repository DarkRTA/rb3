#include "net_band/ContextWrapper.h"
#include "Protocol/ProtocolCallContext.h"
#include "os/Debug.h"
#include <cstddef>

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

ContextWrapperPool::ContextWrapperPool() : unk8ca0(0), unk8ca4(0) {}