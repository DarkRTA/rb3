#include "UIResource.h"
#include "os/Debug.h"
#include "utl/Loader.h"
#include <cstddef>

UIResource::UIResource(const FilePath& f) : mRefCount(0), mResourcePath(f), mDir() {}

void UIResource::Load(bool b) {
    if (mRefCount == 0) {
        if (mDir.mDir != NULL && mDir.mDir->IsDirPtr() && mDir.mDir != NULL) { // ?????
            TheLoadMgr.PollUntilLoaded(NULL, NULL);
        }
    }
    if (b) PostLoad();
}

void UIResource::PostLoad() {

}

void UIResource::Release() {
    if (mDir.mDir) {
        MILO_ASSERT(mRefCount > 0, 47);
        if (--mRefCount == 0) ForceRelease();
    }

}

void UIResource::ForceRelease() {

}
