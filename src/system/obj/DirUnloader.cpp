#include "obj/DirUnloader.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Rnd.h"
#include "rndwii/Rnd.h"
#include "utl/Loader.h"

DirUnloader::DirUnloader(ObjectDir *dir)
    : Loader(FilePath(dir->GetPathName()), kLoadFront), mObjects() {
    mObjects.reserve(dir->mHashTable.Size() / 2);
    for (ObjDirItr<Hmx::Object> it(dir, false); it != 0; ++it) {
        Hmx::Object *cur = it;
        if (cur != dir) {
            cur->SetName(0, 0);
            mObjects.push_back(ObjPtr<Hmx::Object>(this, cur));
        }
    }
}

DirUnloader::~DirUnloader() { MILO_ASSERT(mObjects.empty(), 0x20); }

bool DirUnloader::IsLoaded() const { return false; }

void DirUnloader::PollLoading() {
    MILO_ASSERT(gSuppressPointTest>=0, 0x33);
    gSuppressPointTest++;
    TheLoadMgr.StartAsyncUnload();
    while (!TheLoadMgr.CheckSplit() && TheLoadMgr.GetFirstLoading() == this) {
        if (mObjects.empty()) {
            delete this;
            break;
        }
        Hmx::Object *obj = mObjects.back();
        if (obj)
            delete obj;
        mObjects.pop_back();
    }
    TheLoadMgr.FinishAsyncUnload();
    MILO_ASSERT(gSuppressPointTest>0, 0x47);
    gSuppressPointTest--;
}

const char *DirUnloader::DebugText() { return MakeString("UnLoader: %s", mFile.c_str()); }