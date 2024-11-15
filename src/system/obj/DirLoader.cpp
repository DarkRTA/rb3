#include "DirLoader.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "os/File.h"
#include "os/System.h"
#include "types.h"
#include "utl/BinStream.h"
#include "utl/ChunkStream.h"
#include "utl/FilePath.h"
#include "utl/Loader.h"
#include "utl/LogFile.h"
#include "utl/MakeString.h"
#include "os/Archive.h"
#include "os/Endian.h"
#include "obj/Utl.h"
#include "utl/MemPoint.h"
#include "utl/Symbols.h"
#include "utl/ClassSymbols.h"
#include "decomp.h"

class ObjectDir* DirLoader::sTopSaveDir;
bool gHostCached;
bool DirLoader::sPrintTimes = false;
bool DirLoader::sCacheMode = false;
int DirLoader::mbTrackObjMem;

namespace {
    std::map<Hmx::Object*, TrackObjMem*> gvTrackObjMem;
    MemPoint gTrackMemStack[16];
    MemPoint* gTrackMemStackPtr = gTrackMemStack;
    int gMalloced = 0;
}

void BeginTrackObjMem(const char* cc1, const char* cc2){
    if(DirLoader::mbTrackObjMem){
        *gTrackMemStackPtr++ = MemPoint();
    }
    if(gTrackMemStackPtr >= &gTrackMemStack[16]){
        MILO_FAIL("MemPoint Overflow");
    }
}

void EndTrackObjMem(Hmx::Object* obj, const char* cc1, const char* cc2){
    if(DirLoader::mbTrackObjMem){
        if(--gTrackMemStackPtr < &gTrackMemStack[0]){
            MILO_FAIL("MemPoint Underflow");
        }
        else {
            MemPointDelta delta = MemPoint() - *gTrackMemStackPtr;
            if(DirLoader::mbTrackObjMem > 1 && gTrackMemStackPtr == gTrackMemStack){
                if(!gvTrackObjMem[obj]){
                    TrackObjMem* mem = new TrackObjMem();
                    mem->unk0 = (char*)malloc(strlen(obj->ClassName().mStr) + 1);
                    gMalloced += strlen(obj->ClassName().mStr) + 1;
                    strcpy(mem->unk0, obj->ClassName().mStr);
                    mem->unk4 = (char*)malloc(strlen(obj->Name()) + 1);
                    gMalloced += strlen(obj->Name()) + 1;
                    strcpy(mem->unk4, obj->Name());
                    if(cc1){
                        mem->unk8 = (char*)malloc(strlen(cc1) + 1);
                        gMalloced += strlen(cc1) + 1;
                        strcpy(mem->unk8, cc1);
                    }
                    mem->unkc = new MemPointDelta(delta);
                    gvTrackObjMem[obj] = mem;
                }
                else {
                    TrackObjMem* mem = gvTrackObjMem[obj];
                    *mem->unkc += MemPoint() - *gTrackMemStackPtr;
                }
            }
        }
    }
}

TrackObjMem::TrackObjMem() : unk0(0), unk4(0), unk8(0), unkc(0) {}

DirLoader* DirLoader::Find(const FilePath& fp){
    if(fp.empty()) return 0;
    const std::list<Loader*>& refs = TheLoadMgr.mLoaders;
    for(std::list<Loader*>::const_iterator it = refs.begin(); it != refs.end(); ++it){
        if((*it)->mFile == fp){
            DirLoader* dl = dynamic_cast<DirLoader*>(*it);
            if(dl) return dl;
        }
    }
    return nullptr;
}

DirLoader* DirLoader::FindLast(const FilePath& fp){
    if(fp.empty()) return 0;
    const std::list<Loader*>& refs = TheLoadMgr.mLoaders;
    for(std::list<Loader*>::const_reverse_iterator it = refs.rbegin(); it != refs.rend(); ++it){
        if((*it)->mFile == fp){
            DirLoader* dl = dynamic_cast<DirLoader*>(*it);
            if(dl) return dl;
        }
    }
    return nullptr;
}

DECOMP_FORCEACTIVE(DirLoader, "unknown_dir", "%s\n");

void DirLoader::PrintLoaded(const char* text) {
    TextStream* cout = &TheDebug;
    LogFile* log = nullptr;
    if (text) {
        log = new LogFile(text);
        cout = log;
    }
    const std::list<Loader*>& refs = TheLoadMgr.mLoaders;
    for(std::list<Loader*>::const_iterator it = refs.begin(); it != refs.end(); ++it){
        Loader* cur = *it;
        if(cur && cur->IsLoaded()){
            const char* text2 = cur->mFile.c_str();
            if(*text2 == '\0') text2 = "unknown_dir";
            cout->Print(MakeString("%s\n",text2));
        }
    }
    if (log) delete log;
}

class ObjectDir* DirLoader::GetDir() {
    MILO_ASSERT(IsLoaded(), 364);
    mAccessed = true;
    return mDir;
}

class ObjectDir* DirLoader::LoadObjects(const FilePath& f, Loader::Callback* c, BinStream* b) {
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

DECOMP_FORCEACTIVE(DirLoader,
    "ObjectDir",
    "system",
    "dir_sort",
    "0"
)

void DirLoaderSortDefCtorSpawner(std::list<void*>& listmaybe){
    listmaybe.sort();
}

void DirLoader::SetCacheMode(bool b){
    sCacheMode = b;
}

const char* DirLoader::CachedPath(const char* cc, bool b){
    const char* ext = FileGetExt(cc);
    if((sCacheMode || b) && ext){
        if(streq(ext, "milo")){
            return MakeString("%s/gen/%s.milo_%s", FileGetPath(cc, 0), FileGetBase(cc, 0), PlatformSymbol(TheLoadMgr.GetPlatform()));
        }
    }
    return cc;
}

bool DirLoader::SaveObjects(const char*, class ObjectDir*) {
    MILO_ASSERT(0, 587);
    return 0;
}

DirLoader::DirLoader(const FilePath& f, LoaderPos p, Loader::Callback* c, BinStream* bs, class ObjectDir* d, bool b) : Loader(f, p),
    mRoot(), mOwnStream(false), mStream(bs), mObjects(NULL, kObjListAllowNull),
    mCallback(c), mDir(d), mPostLoad(0), mLoadDir(1), mDeleteSelf(0), mProxyName(0), mProxyDir(0), mTimer(), mAccessed(false), unk99(0) {
    if(d){
        mDeleteSelf = true;
        mProxyName = d->Name();
        class ObjectDir* dDir = d->Dir();
        mProxyDir = dDir;
        if(dDir) mProxyDir->AddRef(this);
        mDir->mLoader = this;
    }
    if(!bs && !d && !b){
        DataArray* da = SystemConfig()->FindArray("force_milo_inline", false);
        if(da){
            for(int i = 1; i < da->Size(); i++) {
                const char* filename = da->Str(i);
                if (FileMatch(f.c_str(), filename)) MILO_FAIL("Can't dynamically load milo files matching %s", filename);
            }
        }
    }
    mState = &DirLoader::OpenFile;
}

bool DirLoader::IsLoaded() const {
    return mState == &DirLoader::DoneLoading;
}

const char* DirLoader::StateName() const {
    if(mState == &DirLoader::OpenFile) return "OpenFile";
    else if(mState == &DirLoader::LoadHeader) return "LoadHeader";
    else if(mState == &DirLoader::LoadDir) return "LoadDir";
    else if(mState == &DirLoader::LoadResources) return "LoadResources";
    else if(mState == &DirLoader::CreateObjects) return "CreateObjects";
    else if(mState == &DirLoader::LoadObjs) return "LoadObjs";
    else if(mState == &DirLoader::DoneLoading) return "DoneLoading";
    else return "INVALID";
}

void DirLoader::PollLoading() {
    while(!TheLoadMgr.CheckSplit() && TheLoadMgr.GetFirstLoading() == this && !IsLoaded()){
        (this->*mState)();
    }
}

// this matches, but dear god i hope this isn't what HMX actually wrote
Symbol DirLoader::FixClassName(Symbol sym){
    if(mRev < 0x1C){
        if(sym == CharClipSamples) sym = CharClip;
        if(mRev < 0x1B){
            if(sym == BandMeshLauncher) sym = PartLauncher;
            if(mRev < 0x1A){
                if(sym == P9TransDraw) sym = CharTransDraw;
                if(mRev < 0x19){
                    if(sym == RenderedTex) sym = TexRenderer;
                    else if(sym == CompositeTexture) sym = LayerDir;
                    if(mRev < 0x18){
                        if(sym == BandFx) return WorldFx;
                        if(mRev < 0x16){
                            if(sym == Slider) return BandSlider;
                            if(mRev < 0x15){
                                if(sym == TextEntry) return BandTextEntry;
                                if(mRev < 0x14){
                                    if(sym == Placer) return BandPlacer;
                                    if(mRev < 0x13){
                                        if(sym == ButtonEx) return BandButton;
                                        else if(sym == LabelEx) return BandLabel;
                                        else if(sym == PictureEx) return BandPicture;
                                        if(mRev < 0x12){
                                            if(sym == UIPanel) return PanelDir;
                                            if(mRev < 0x10){
                                                if(sym == WorldInstance) return WorldObject;
                                                if(mRev < 0xF){
                                                    if(sym == View) return Group;
                                                    if(mRev < 7){
                                                        if(sym == String) return Line;
                                                        if(mRev < 6){
                                                            if(sym == MeshGenerator) return Generator;
                                                            if(mRev < 5){
                                                                if(sym == TexMovie) return Movie;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return sym;
}

void DirLoader::OpenFile() {
    mTimer.Start();
    const char* fileStr = mFile.c_str();
    if (*fileStr == '\0') {
        mRoot = FilePath::sRoot;
    } else {
        char buf[0x100];
        strcpy(buf, FileGetPath(fileStr, NULL));
        int len = strlen(buf) - 4;
        if(len > 0 && streq("/gen", buf + len)){
            buf[len] = 0;
        }
        mRoot = FileMakePath(FileRoot(), buf, NULL);
    }
    if (mStream == nullptr) {
        Archive* theArchive = TheArchive;
#ifdef MILO_DEBUG
        bool using_cd = UsingCD();
#else
        bool using_cd = true;
#endif
        bool cache_mode = sCacheMode;

        bool matches = false;
        if(gHostFile){
            if(FileMatch(fileStr, gHostFile)) matches = true;
        }
        if(matches){
            SetCacheMode(gHostCached);
            SetUsingCD(false);
            TheArchive = nullptr;
        }

        const char* path = CachedPath(fileStr, false);
        mStream = new ChunkStream(path, ChunkStream::kRead, 0x10000, true, kPlatformNone, false);
        mOwnStream = true;
        if (matches) {
            SetCacheMode(cache_mode);
            SetUsingCD(using_cd);
            TheArchive = theArchive;
        }
        if (mStream->Fail()) {
            if (mProxyDir){
                Cleanup(MakeString("%s: could not load: %s", PathName(mProxyDir), path));
                return;
            }
            else {
                Cleanup(MakeString("Could not load: %s", path));
                return;
            }
        }
    }
    mState = &DirLoader::LoadHeader;
}

bool DirLoader::SetupDir(Symbol sym){
    BeginTrackObjMem(sym.Str(), mFile.c_str());
    if(mDir){
        if(mDir->ClassName() != sym){
            TheDebugNotifier << MakeString(MakeString("%s: Proxy class %s not %s, converting", mFile.c_str(),
                mDir->ClassName(), sym)); // for some reason
            class ObjectDir* newDir = dynamic_cast<class ObjectDir*>(Hmx::Object::NewObject(sym));
            if(!newDir){
                Cleanup(MakeString("%s: Trying to make non ObjectDir proxy class %s s", mFile.c_str(), mDir->ClassName(), sym));
                return false;
            }
            newDir->TransferLoaderState(mDir);
            ReplaceObject(mDir, newDir, true, true, false);
            mDir = newDir;
        }
    }
    else {
        mDir = dynamic_cast<class ObjectDir*>(Hmx::Object::NewObject(sym));
    }
    mDir->SetPathName(mFile.c_str());
    EndTrackObjMem(mDir, 0, mFile.c_str());
    return true;
}

void DirLoader::ResolveEndianness(){
    int curRev = mRev;
    if(EndianSwap((unsigned int)curRev) < curRev){
        mRev = EndianSwap((unsigned int)mRev);
        mStream->UseLittleEndian(true);
    }
}

void DirLoader::LoadHeader() {
    EofType t;
    while(t = mStream->Eof(), t != NotEof){
        MILO_ASSERT(t == TempEof, 0x3E5);
        if(TheLoadMgr.CheckSplit()) return;
    }
    *mStream >> mRev;
    ResolveEndianness();
    if(mRev < 7){
        Cleanup(MakeString("Can't load old ObjectDir %s", mFile));
        return;
    }
    Symbol dirSym("RndDir");
    if(!Hmx::Object::RegisteredFactory(dirSym)){
        dirSym = "ObjectDir";
    }
    if(mRev > 0xD){
        Symbol symRead;
        *mStream >> symRead;
        symRead = FixClassName(symRead);
        char buf[0x80];
        mStream->ReadString(buf, 0x80);
        if(!Hmx::Object::RegisteredFactory(symRead)){
            MILO_WARN("%s: %s not registered, defaulting to %s", mFile.c_str(), symRead, dirSym);
            symRead = dirSym;
            mLoadDir = false;
        }
        if(!SetupDir(symRead)) return;
        int size1, size2;
        *mStream >> size1 >> size2;
        size1 += mDir->HashTableUsedSize() + 0x10;
        size2 += mDir->StrTableUsedSize() + 0x98;
        mDir->Reserve(size1, size2);
        mDir->SetName(buf, mDir);
    }
    else if(mRev > 0xC) {
        Symbol sa8;
        *mStream >> sa8;
        if(!SetupDir("ObjectDir")) return;
        mDir->SetName(FileGetBase(mFile.c_str(), 0), mDir);
        mDir->ObjectDir::Load(*mStream);
    }
    else {
        if(!SetupDir(dirSym)) return;
        mDir->SetName(FileGetBase(mFile.c_str(), 0), mDir);
    }
    mDir->mLoader = this;
    *mStream >> mCounter;
    if(mRev < 0xE){
        mDir->Reserve(mCounter * 2, mCounter * 25);
    }
    mState = &DirLoader::CreateObjects;
}

void DirLoader::CreateObjects(){
    while(mCounter-- != 0){
        Symbol classSym;
        *mStream >> classSym;
        classSym = FixClassName(classSym);
        char buf[0x80];
        mStream->ReadString(buf, 0x80);
        bool b8;
        if(mRev - 1U <= 6){
            *mStream >> b8;
        }
        Hmx::Object* obj;
        if(!Hmx::Object::RegisteredFactory(classSym)){
            MILO_WARN("%s: Can't make %s", mFile.c_str(), classSym);
            obj = nullptr;
        }
        else {
            BeginTrackObjMem(classSym.mStr, buf);
            obj = Hmx::Object::NewObject(classSym);
            if(mRev == 0x16 && dynamic_cast<class ObjectDir*>(obj)){
                RELEASE(obj);
            }
            else {
                obj->SetName(buf, mDir);
                EndTrackObjMem(obj, mProxyName, buf);
            }
        }
        mObjects.push_back(obj);
        if(TheLoadMgr.CheckSplit()) return;
    }
    if(mRev > 16){
        mState = &DirLoader::LoadDir;
    }
    else {
        *mStream >> mCounter;
        mState = &DirLoader::LoadResources;
    }
}

void DirLoader::LoadResources(){
    if(mCounter-- != 0){
        FilePathTracker fpt(mRoot.c_str());
        FilePath fp2;
        *mStream >> fp2;
        if(!fp2.empty()){
            TheLoadMgr.AddLoader(fp2, kLoadFront);
        }
    }
    else {
        if(mRev > 0xD) mState = &DirLoader::LoadDir;
        else mState = &DirLoader::LoadObjs;
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

void DirLoader::LoadDir(){
    if(mLoadDir){
        FilePathTracker tracker(mRoot.c_str());
        bool oldproxy = gLoadingProxyFromDisk;
        gLoadingProxyFromDisk = mProxyName;
        if(!mPostLoad){
            BeginTrackObjMem(mDir->ClassName().mStr, mDir->Name());
            mDir->PreLoad(*mStream);
            mPostLoad = true;
            EndTrackObjMem(mDir, 0, mDir->Name());
        }
        EofType t = TempEof;
        if(TheLoadMgr.GetFirstLoading() != this || (t = mStream->Eof(), t != NotEof)){
            MILO_ASSERT(t == TempEof, 0x4E4);
            gLoadingProxyFromDisk = oldproxy;
            return;
        }
        BeginTrackObjMem(mDir->ClassName().mStr, mDir->Name());
        mDir->PostLoad(*mStream);
        gLoadingProxyFromDisk = oldproxy;
        mPostLoad = false;
        EndTrackObjMem(mDir, 0, mDir->Name());
    }
    ReadDead(*mStream);
    mState = &DirLoader::LoadObjs;
}

void DirLoader::LoadObjs(){
    FilePathTracker tracker(mRoot.c_str());
    EofType t;
    while(!mObjects.empty()){
        t = mStream->Eof();
        if(t != NotEof){
            MILO_ASSERT(t == TempEof, 0x514);
        }
        else {
            Hmx::Object* obj = mObjects.front();
            if(obj){
                if(!mPostLoad){
                    BeginTrackObjMem(obj->ClassName().mStr, obj->Name());
                    obj->PreLoad(*mStream);
                    mPostLoad = true;
                    EndTrackObjMem(obj, mProxyName, obj->Name());
                }
                if(TheLoadMgr.GetFirstLoading() != this) return;
                BeginTrackObjMem(obj->ClassName().mStr, obj->Name());
                obj->PostLoad(*mStream);
                EndTrackObjMem(obj, mProxyName, obj->Name());
                mPostLoad = false;
                if(mRev > 1){
                    ReadDead(*mStream);
                }
            }
            else {
                MILO_ASSERT(mRev > 1, 0x54D);
                ReadDead(*mStream);
            }
            mObjects.pop_front();
        }
        if(TheLoadMgr.CheckSplit() || TheLoadMgr.GetFirstLoading() != this) return;
    }
    mState = &DirLoader::DoneLoading;
    Cleanup(0);
    if(TheLoadMgr.GetFirstLoading() != this) return;
    if(mCallback) mCallback->FinishLoading(this);
}

void DirLoader::DoneLoading(){}

void DirLoader::Replace(Hmx::Object* from, Hmx::Object* to) {
    MILO_ASSERT(from == mProxyDir && !to, 1393);
    mProxyDir = NULL;
    mProxyName = NULL;
    delete this; // uhhh.
}

void DirLoader::Cleanup(const char* s) {
    if (s) MILO_WARN(s);
    mObjects.clear();
    if(mOwnStream) RELEASE(mStream);
    if (mDir) {
        if (!IsLoaded()) {
            mDir->mLoader = NULL;
            if (mProxyName == NULL) {
                RELEASE(mDir);
            }
        }
        if (mProxyName != NULL) {
            if (mDir->Dir() == mDir){
                mDir->SetName(mProxyName, mProxyDir);
            }
        }
        if(IsLoaded() && mDir){
            mDir->SyncObjects();
        }
    }
    mState = &DirLoader::DoneLoading;
    mTimer.Stop();
    if(sPrintTimes){
        MILO_LOG("%s: %f ms\n", mFile, mTimer.Ms());
    }
    if(mCallback && (s || unk99)){
        mCallback->FailedLoading(this);
        mCallback = nullptr;
    }
    if(mDeleteSelf) delete this;
}

DirLoader::~DirLoader() {
    mDeleteSelf = 0;
    if (!IsLoaded()) {
        Cleanup(NULL);
    }
    else if(mDir){
        mDir->mLoader = 0;
        if(!mAccessed && !mProxyName){
            RELEASE(mDir);
        }
    }
    if(mProxyDir) mProxyDir->Release(this);
    if(mCallback && unk99){
        mCallback->FailedLoading(this);
        mCallback = 0;
    }
}

Hmx::Object* DirLoader::RefOwner() { return NULL; }
