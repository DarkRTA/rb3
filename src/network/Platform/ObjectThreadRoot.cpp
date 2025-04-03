#include "ObjectThread.h"
#include "network/Platform/ObjectThread.h"
#include "Platform/String.h"

namespace Quazal {
    unsigned int ObjectThreadRoot::s_uiDefaultPrio = 17;

    ObjectThreadRoot::ObjectThreadRoot(const String &str)
        : mName(str), mHandle(new(__FILE__, 0xAC) Handle()), mThreadID(0), mLaunched(0),
          mFinished(0) {
        mThreadPrio = s_uiDefaultPrio;
    }

    ObjectThreadRoot::~ObjectThreadRoot() { RELEASE(mHandle); }
}