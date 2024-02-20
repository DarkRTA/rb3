#include "UIResource.h"
#include "os/Debug.h"

UIResource::UIResource(const FilePath& f) : mResourcePath(f), mDir(0) {}

void UIResource::Load(bool b) {

}

void UIResource::PostLoad() {

}

void UIResource::Release() {
    if (mDir.mDir) {
        ASSERT(mRefCount > 0, 47);
        if (--mRefCount == 0) ForceRelease();
    }

}

void UIResource::ForceRelease() {

}
