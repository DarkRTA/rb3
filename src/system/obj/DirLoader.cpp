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
#include "os/Archive.h"
#include "utl/Symbols.h"

bool gHostCached;
bool DirLoader::sCacheMode = false;

void BeginTrackObjMem(const char* cc1, const char* cc2){

}

void EndTrackObjMem(Hmx::Object* obj, const char* cc1, const char* cc2){

}

const char* memStrs[] = { "MemPoint Overflow", "MemPoint Underflow" };

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

static const char* moreDirLoaderStrs[] = { "ObjectDir", "system", "dir_sort", "0" };

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
    mState = OpenFile;
}

bool DirLoader::IsLoaded() const {
    return mState == DoneLoading;
}

const char* DirLoader::StateName() const {
    if(mState == OpenFile) return "OpenFile";
    else if(mState == LoadHeader) return "LoadHeader";
    else if(mState == LoadDir) return "LoadDir";
    else if(mState == LoadResources) return "LoadResources";
    else if(mState == CreateObjects) return "CreateObjects";
    else if(mState == LoadObjs) return "LoadObjs";
    else if(mState == DoneLoading) return "DoneLoading";
    else return "INVALID";
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
    if (mFile.empty()) {
        mRoot = FilePath::sRoot;
    } else {
        char buf[0x100];
        strcpy(buf, FileGetPath(fileStr, NULL));
        int len = strlen(buf);
        if(len - 4 > 0){
            bool isGen = strcmp("/gen", buf + len) == 0;
            if(isGen) buf[len] = 0;
        }
        mRoot = FileMakePath(FileRoot(), buf, NULL);
    }
    if (mStream == 0) {
        Archive* theArchive = TheArchive;
        bool cache_mode = sCacheMode;
        bool using_cd = UsingCD();

        bool matches = false;
        if(gHostFile){
            if(FileMatch(fileStr, gHostFile)) matches = true;
        }
        if(matches){
            SetCacheMode(gHostCached);
            SetUsingCD(false);
            TheArchive = 0;
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
                Cleanup(MakeString("%s/gen/%s", PathName(mProxyDir), path));
                return;
            }
            else {
                Cleanup(MakeString("%s", path));
                return;
            }
        }
    }
    mState = LoadHeader;
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
    mDeleteSelf = 0;
    if (!IsLoaded()) {
        Cleanup(NULL);
    }
    else if(mDir){
        mDir->mLoader = 0;
        if(!mAccessed && !mProxyName){
            delete mDir;
            mDir = 0;
        }
    }
    if(mProxyDir) mProxyDir->Release(this);
    if(mCallback && unk99){
        mCallback->FailedLoading(this);
        mCallback = 0;
    }
}
