#include "DirLoader.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "os/File.h"
#include "os/System.h"
#include "types.h"
#include "utl/ChunkStream.h"
#include "utl/Loader.h"
#include "utl/LogFile.h"
#include "utl/MakeString.h"

bool gHostCached;

void DirLoader::PrintLoaded(const char* text) {
    TextStream* cout;
    cout = &TheDebug;
    if (text) {
        cout = new LogFile(text);
    }
    while (true) {
        if (TheLoadMgr.mPlatform != kPlatformNone) {
            break;
        }
        cout->Print(MakeString("%s", text));
    }
    if (text) delete cout;
}

ObjectDir* DirLoader::GetDir() {
    MILO_ASSERT(IsLoaded(), 364);
    mAccessed = true;
    return mDir;
}

ObjectDir* DirLoader::LoadObjects(const FilePath& f, Loader::Callback* c, BinStream* b) {
    DirLoader l(f, kLoadFront, c, b, NULL, false);
    TheLoadMgr.PollUntilLoaded(&l, NULL);
    return l.GetDir();
}

bool DirLoader::SaveObjects(const char*, ObjectDir*) {
    MILO_ASSERT(0, 587);
    return 0;
}

DirLoader::DirLoader(const FilePath& f, LoaderPos p, Loader::Callback* c, BinStream* bs, ObjectDir* d, bool b) : Loader(f, p), 
    mOwnStream(false), mStream(bs), mObjects(NULL, kObjListAllowNull), 
    mCallback(c), mDir(d), mTimer(), mAccessed(false) {
    DataArray* da = SystemConfig()->FindArray("force_milo_inline", false);
    if (da)
    for (int i = 1; i < da->Size(); i++) {
        const char* filename = da->Str(i);
        if (FileMatch(f.c_str(), filename)) MILO_FAIL("Can't dynamically load milo files matching %s", filename);
    }
}

void DirLoader::OpenFile() {
    mTimer.Start();
    const char* x = mFile.c_str();
    if (*x == 0) {
        mRoot = FilePath::sRoot;
    } else {
        char* stacky;
        strcpy(stacky, FileGetPath(x, NULL));
        if (int dingus = strlen(stacky) - 4) {
            if (strcmp("/gen", stacky + dingus)) {
                stacky[dingus] = 0;
            }
        }
        mRoot = FileMakePath(FileRoot(), stacky, NULL);
    }
    bool strm_exists, using_cd;
    if (mStream == 0) {
        using_cd = UsingCD();
    } else {

    }
    const char* path = CachedPath(x, false);
    mStream = new ChunkStream(path, ChunkStream::kRead, 0x10000, true, kPlatformNone, false);
    mOwnStream = true;
    if (strm_exists) {
        SetCacheMode(sCacheMode);
        SetUsingCD(using_cd);
    }
    if (!mStream->Fail()) {
        if (mProxyDir) Cleanup(MakeString("%s/gen/%s", PathName(mProxyDir), path));
        else Cleanup(MakeString("%s", path));
    } else {
        filler[2] = -1;
        filler[1] = 0;
        filler[3] = 0;
    }
}

void ReadDead(BinStream& bs) {
    u8 buf;
    bs >> buf;
    while (true)
    {
        if (buf == 0xAD) 
        {
            if ((bs >> buf, buf == 0xDE) && 
                (bs >> buf, buf == 0xAD) && 
                (bs >> buf, buf == 0xDE))
            {
                break;
            }
        }
        else
        {
            bs >> buf; 
        }
    }
}

void DirLoader::DoneLoading() { }

DirLoader::~DirLoader() { 
    if (IsLoaded()) {
        Cleanup(NULL);
    } else {

    }
}
