#include "UIResource.h"
#include "os/Debug.h"
#include "utl/Loader.h"
#include <cstddef>

UIResource::UIResource(const FilePath& f) : mRefCount(0), mResourcePath(f), mDir() {}

void UIResource::Load(bool b) {
    if (mRefCount == 0) {
        mDir.LoadFile(mResourcePath, b, true, kLoadFront, false);
    }
    if (!b) PostLoad();
}

void UIResource::PostLoad() {
    if(!mRefCount) mDir.PostLoad(0);
    mRefCount++;
}

void UIResource::Release() {
    if (mDir.Ptr()) {
        MILO_ASSERT(mRefCount > 0, 47);
        if (--mRefCount == 0) ForceRelease();
    }

}

void UIResource::ForceRelease() {
    mRefCount = 0;
    mDir = 0;
}
