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
bool DirLoader::sCacheMode = false;

DirLoader* DirLoader::Find(const FilePath& fp){
    if(fp.empty()) return 0;
    std::list<Loader*>& refs = TheLoadMgr.mLoaders;
    for(std::list<Loader*>::iterator it = refs.begin(); it != refs.end(); it++){
        if((*it)->mFile == fp){
            DirLoader* dl = dynamic_cast<DirLoader*>(*it);
            if(dl) return dl;
        }
    }
    return 0;
}

DirLoader* DirLoader::FindLast(const FilePath& fp){
    if(fp.empty()) return 0;
    std::list<Loader*>& refs = TheLoadMgr.mLoaders;
    for(std::list<Loader*>::reverse_iterator it = refs.rbegin(); it != refs.rend(); it++){
        if((*it)->mFile == fp){
            DirLoader* dl = dynamic_cast<DirLoader*>(*it);
            if(dl) return dl;
        }
    }
    return 0;
}

void DirLoader::PrintLoaded(const char* text) {
    TextStream* cout = &TheDebug;
    if (text) {
        cout = new LogFile(text);
    }
    std::list<Loader*>& refs = TheLoadMgr.mLoaders;
    for(std::list<Loader*>::iterator it = refs.begin(); it != refs.end(); it++){
        if(*it && (*it)->IsLoaded()){
            FilePath& itFile = (*it)->mFile;
            const char* text2 = itFile.c_str();
            if(itFile.empty()) text2 = "unknown_dir";
            cout->Print(MakeString("%s\n", text2));
        }
    }
    if (cout) delete cout;
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

Symbol DirLoader::GetDirClass(const char* cc){
    ChunkStream cs(cc, ChunkStream::kRead, 0x10000, true, kPlatformNone, false);
    if(cs.Fail()){
        return Symbol("");
    }
    else {
        EofType t;
        while(t = cs.Eof(), t != NotEof){
            MILO_ASSERT(t == TempEof, 0x199);
        }
        int i;
        cs >> i;
        Symbol s;
        cs >> s;
        return s;
    }
}

void DirLoader::SetCacheMode(bool b){
    sCacheMode = b;
}

const char* DirLoader::CachedPath(const char* cc, bool b){
    const char* ext = FileGetExt(cc);
    if((sCacheMode || b) && ext){
        bool isMilo = strcmp(ext, "milo") == 0;
        if(isMilo){
            return MakeString("%s/gen/%s.milo_%s", FileGetPath(cc, 0), FileGetBase(cc, 0), PlatformSymbol(TheLoadMgr.mPlatform));
        }
    }
    return cc;
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
