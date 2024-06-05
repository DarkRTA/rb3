#include "obj/Dir.h"
#include "obj/Object.h"
#include "obj/ObjVersion.h"
#include "decomp.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"

const char* kNotObjectMsg = "Could not find %s in dir \"%s\"";

namespace {
    int gPreloadIdx = 0;
    ObjDirPtr<ObjectDir> gPreloaded[128];

    void DeleteShared(){

    }
}

INIT_REVS(ObjectDir);

BinStream& operator>>(BinStream& bs, InlineDirType& ty){
    unsigned char uc;
    bs >> uc;
    ty = (InlineDirType)uc;
    return bs;
}

Hmx::Object* Hmx::Object::NewObject(){
    return new Hmx::Object();
}

void ObjectDir::Reserve(int i, int j){
    if(mHashTable.mSize < i)
        mHashTable.Resize(i, 0);
    mStringTable.Reserve(j);
}

void ObjectDir::SetSubDir(bool b){
    if(b){
        mIsSubDir = true;
        SetName(0, 0);
        SetTypeDef(0);
    }
}

bool ObjectDir::HasSubDir(ObjectDir* dir){
    ObjectDir* subdir;
    int i = 0;
    do {
        subdir = NextSubDir(i);
        if(!subdir) return false;
    } while(subdir != dir);
    return true;
}

bool ObjectDir::SaveSubdirs(){
    bool ret = false;
    if(!IsProxy() || mProxyFile.empty() || gLoadingProxyFromDisk){
        ret = true;
    }
    return ret;
}

SAVE_OBJ(ObjectDir, 0x1A2)

InlineDirType ObjectDir::InlineSubDirType(){ return mInlineSubDirType; }

ObjectDir::ObjectDir()
    : mHashTable(0), mStringTable(0), mProxyOverride(false), mInlineProxy(true),
      mLoader(0), mIsSubDir(false), mInlineSubDirType(kInlineNever), mPathName(gNullStr),
      mCurCam(0), mAlwaysInlined(false), mAlwaysInlineHash(gNullStr) {
}

void ObjectDir::PostSave(BinStream& bs){
    SyncObjects();
}

void ObjectDir::Load(BinStream& bs){
    PreLoad(bs);
    PostLoad(bs);
    if(this != mDir && !mProxyFile.empty()){
        Loader* ldr = TheLoadMgr.GetLoader(mProxyFile);
        if(ldr) TheLoadMgr.PollUntilLoaded(ldr, 0);
    }
}

void ObjectDir::OldLoadProxies(BinStream& bs, int i){
    int x;
    bs >> x;
    if(x != 0) MILO_FAIL("Proxies not allowed here");
}

BinStream& operator>>(BinStream& bs, ObjectDir::Viewport& vp){
    bs >> vp.mXfm;
    if(ObjectDir::gRev < 0x12){
        int i;
        bs >> i;
    }
    return bs;
}

#pragma push
#pragma dont_inline on
void ObjectDir::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0x1B, 0);
    if(gRev > 0x15) Hmx::Object::LoadType(bs);
    else if(gRev - 2U <= 0xE) Hmx::Object::Load(bs);
    if(gRev < 3){
        int i, j;
        bs >> i >> j;
        Reserve(i, j);
    }
    if(gRev > 0x19){
        if(gRev < 0x1B){
            bool b;
            bs >> b;
            mAlwaysInlined = b;
        }
        else bs >> mAlwaysInlined;
        int toAlloc;
        bs >> toAlloc;
        if(toAlloc){
            void* v = _MemOrPoolAlloc(toAlloc + 1, FastPool);
            mAlwaysInlineHash = (char*)v;
            bs.Read(v, toAlloc);
            ((char*)v)[toAlloc] = 0;
        }
    }
    if(gRev > 1){
        std::vector<Viewport> vec;
        int i;
        bs >> vec;
        bs >> i;
    }
    if(gRev > 0xC){
        if(gRev > 0x13){
            if(!gLoadingProxyFromDisk) bs >> mInlineProxy;
            else {
                bool b;
                bs >> b;
            }
        }
        if(gLoadingProxyFromDisk || mProxyOverride){
            bool fail = false;
            if(mProxyOverride && AllowsInlineProxy()) fail = true;
            if(fail) MILO_FAIL("You cannot override an inlined proxy!");
            FilePath fp;
            bs >> fp;
            mProxyOverride = false;
        }
        else {
            FilePath fp;
            bs >> fp;
            if(!fp.empty() && fp == mProxyFile){
                mProxyOverride = true;
            }
            else {
                mProxyFile = fp;
                mProxyOverride = false;
            }
        }
    }
    if(gRev - 2 < 9){
        char buf[0x80];
        bs.ReadString(buf, 0x80);
    }
    if(gRev - 4 < 7){
        char buf[0x80];
        bs.ReadString(buf, 0x80);
    }
    if(gRev == 5){
        char buf[0x80];
        bs.ReadString(buf, 0x80);
    }

    static std::vector<FilePath> inlinedSubDirs;
    static std::vector<FilePath> notInlinedSubDirs;
    if(gRev > 2){
        bs >> notInlinedSubDirs;
        std::vector<int> intVec;
        if(gRev == 0x17) bs >> intVec;
        if(gRev < 0x15) inlinedSubDirs.clear();
        else {
            bs >> mInlineSubDirType;
            bs >> inlinedSubDirs;
        }
        bool dirsSaved = SaveSubdirs();
    }
    if(gRev - 0xC < 2){
        OldLoadProxies(bs, gRev);
    }
    if(gRev < 0x13){

    }
    mIsSubDir = false;
    PushRev(packRevs(gAltRev, gRev), this);
}
#pragma pop

bool ObjectDir::AllowsInlineProxy(){
    return mInlineProxy;
}

#pragma push
#pragma dont_inline on
void ObjectDir::PostLoad(BinStream& bs){
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    for(int i = mInlinedDirs.size() - 1; i >= 0; i--){
        InlinedDir& iDir = mInlinedDirs[i];
        int tempgRev = gRev;
        iDir.dir.PostLoad(mLoader);
        gRev = tempgRev;
        if(iDir.inlineDirType == (InlineDirType)3){
            iDir.shared = true;
        }
        if(iDir.shared){
            FilePath& fp = iDir.file;
            DirLoader* last = DirLoader::FindLast(fp);
            if(last){
                if(last->IsLoaded()){
                    iDir.dir = last->GetDir();
                }
                else {
                    MILO_WARN("Can't share unloaded dir %s", fp);
                }
            }
        }
        else {
            if(iDir.dir.IsLoaded()){
                delete iDir.dir->mLoader;
                iDir.dir->mLoader = 0;
            }
        }
    }
    if(gRev > 0x17){
        int revs2 = bs.Cached() ? 0 : PopRev(this);
        int offset = PopRev(this);
        MILO_ASSERT(( 0) <= (offset) && (offset) <= ( mSubDirs.size()), 0x466);
        if(revs2 != 2){
            for(int i = mSubDirs.size() - offset - 1; i >= 0; i--){
                bool bbb = false;
                if(revs2 == 1){
                    bbb = PopRev(this) != 0;
                }
                ObjDirPtr<ObjectDir> inlinedDirPtr = PostLoadInlined();
                ObjDirPtr<ObjectDir>& curDirPtr = mSubDirs[i + offset];
                if(revs2 == 0 || bbb){
                    curDirPtr = inlinedDirPtr;
                }
                AddedSubDir(curDirPtr);
            }
            for(offset = offset - 1; offset >= 0; offset--){
                ObjDirPtr<ObjectDir>& offsetPtr = mSubDirs[offset];
                offsetPtr.PostLoad(mLoader);
                AddedSubDir(offsetPtr);
            }
        }
    }
    else {
        for(int i = 0; i < mSubDirs.size(); i++){
            ObjDirPtr<ObjectDir>& curDirPtr = mSubDirs[i];
            curDirPtr.PostLoad(mLoader);
            AddedSubDir(curDirPtr);
            if(curDirPtr.IsLoaded()){
                if(curDirPtr->InlineSubDirType() != kInlineNever){
                    delete curDirPtr->mLoader;
                    curDirPtr->mLoader = 0;
                }
            }
        }
    }
    if(gRev > 10){
        char buf[0x80];
        bs.ReadString(buf, 0x80);
        bs.ReadString(buf, 0x80);
        mCurCam = FindObject(buf, true);
    }
    if(gRev > 0x15) LoadRest(bs);
    else if(gRev > 0x10) Hmx::Object::Load(bs);
    HandleType(change_proxies_msg);
    if(mProxyOverride){
        bool overridden = false;
        mProxyOverride = false;
        if(TheLoadMgr.EditMode() || (IsProxy() && !AllowsInlineProxy())){
            overridden = true;
        }
        if(!overridden) MILO_FAIL("You cannot override an inlined proxy!");
    }
    else {
        if(IsProxy() && !mProxyFile.empty()){
            DeleteObjects();
            DeleteSubDirs();
            DirLoader* dl = new DirLoader(mProxyFile, kLoadFront, 0, InlineProxy(bs) ? &bs : 0, this, false);
        }
    }
}
#pragma pop

extern std::vector<ObjVersion> sRevStack;

int PopRev(Hmx::Object* o){
    while(sRevStack.back().obj != 0){
        sRevStack.pop_back();
    }
    ObjVersion& back = sRevStack.back();
    if(o != back.obj){
        TheDebug << MakeString("rev stack $this mismatch (%08x != %08x\n", o, back.obj);
        TheDebug << MakeString("curr obj: %s %s\n", o->ClassName(), PathName(o));
        TheDebug << MakeString("stack obj: %s %s\n", back.obj->ClassName(), PathName(back.obj));
        TheDebug << MakeString("rev stack (%08x %s %s != %08x %s %s)\n", o, o->ClassName(), PathName(o), back.obj, back.obj->ClassName(), PathName(back.obj));
    }
    sRevStack.pop_back();
    return back.revs;
}

void ObjectDir::TransferLoaderState(ObjectDir* otherDir){
    mProxyFile = otherDir->mProxyFile;
    mProxyOverride = otherDir->mProxyOverride;
    mLoader = otherDir->mLoader;
    otherDir->mLoader = 0;
}

void ObjectDir::SetProxyFile(const FilePath& fp, bool b){
    if(this == mDir){
        MILO_WARN("Can't set proxy file if own dir");
    }
    else {
        mProxyFile = fp;
        mProxyOverride = b;
        if(!b){
            DeleteObjects();
            DeleteSubDirs();
            if(!mProxyFile.empty()){
                TheLoadMgr.PollUntilLoaded(new DirLoader(mProxyFile, kLoadFront, 0, 0, this, false), 0);
            }
        }
    }
}

BEGIN_COPYS(ObjectDir)
    COPY_SUPERCLASS(Hmx::Object)
    if(ty != kCopyFromMax){
        CREATE_COPY(ObjectDir)
        BEGIN_COPYING_MEMBERS
            if(this == Dir()){
                for(int i = 0; i < mSubDirs.size(); i++){
                    RemovingSubDir(mSubDirs[i]);
                }
                COPY_MEMBER(mSubDirs)
                for(int i = 0; i < mSubDirs.size(); i++){
                    AddedSubDir(mSubDirs[i]);
                }
            }
            COPY_MEMBER(mInlineProxy)
            COPY_MEMBER(mInlineSubDirType)
        END_COPYING_MEMBERS
    }
END_COPYS

Hmx::Object* ObjectDir::FindObject(const char* name, bool parentDirs){
    Entry* entry = FindEntry(name, false);
    if(entry && entry->obj) return entry->obj;
    for(int i = 0; i < mSubDirs.size(); i++){
        if(mSubDirs[i]){
            Hmx::Object* found = mSubDirs[i]->FindObject(name, false);
            if(found) return found;
        }
    }
    if(strlen(name) != 0){
        if(strcmp(name, Name()) == 0){
            return this;
        }
    }
    if(parentDirs){
        ObjectDir* thisDir = Dir();
        if(thisDir && thisDir != this){
            return thisDir->FindObject(name, parentDirs);
        }
        if(this != sMainDir){
            return sMainDir->FindObject(name, false);
        }
    }
    return 0;
}

void ObjectDir::RemovingObject(Hmx::Object* obj){
    if(obj != mCurCam) return;
    else mCurCam = 0;
}

bool ObjectDir::InlineProxy(BinStream& bs){
    bool ret = false;
    if(AllowsInlineProxy() && bs.Cached()){
        ret = true;
    }
    return ret;
}

#pragma push
#pragma dont_inline on
// the KeylessHash methods should NOT be inlined, but the Entry ctor should
ObjectDir::Entry* ObjectDir::FindEntry(const char* name, bool add){
    if(name == 0 || *name == '\0') return 0;
    else {
        Entry* entry = mHashTable.Find(name);
        if(!entry && add){
            Entry newEntry;
            newEntry.name = SymbolCacheLookup(name);
            if(!newEntry.name){
                mStringTable.Add(newEntry.name);
            }
            entry = mHashTable.Insert(newEntry);
        }
        return entry;
    }
}
#pragma pop

ObjectDir* ObjectDir::NextSubDir(int& which){
    MILO_ASSERT(which >= 0, 0x695);
    ObjectDir* ret = this;
    if(which == 0) return ret;
    else {
        which--;
        ret = 0;
        for(int i = 0; i < mSubDirs.size(); i++){
            if(mSubDirs[i]){
                ret = mSubDirs[i]->NextSubDir(which);
                if(ret) break;
            }
        }
    }
    return ret;
}

bool ObjectDir::HasDirPtrs() const {
    std::vector<ObjRef*>::const_reverse_iterator rit = Refs().rbegin();
    std::vector<ObjRef*>::const_reverse_iterator ritEnd = Refs().rend();
    for(; rit != ritEnd; ++rit){
        if((*rit)->IsDirPtr()) return true;
    }
    return false;
}

BEGIN_HANDLERS(ObjectDir)
    HANDLE_ACTION(iterate, Iterate(_msg, true))
    HANDLE_ACTION(iterate_self, Iterate(_msg, false))
    HANDLE_ACTION(save_objects, DirLoader::SaveObjects(_msg->Str(2), this))
    HANDLE(find, OnFind)
    HANDLE_EXPR(exists, FindObject(_msg->Str(2), false) != 0)
    HANDLE_ACTION(sync_objects, SyncObjects())
    HANDLE_EXPR(is_proxy, Dir() != this)
    HANDLE_EXPR(proxy_dir, mLoader ? mLoader->mProxyDir : (Hmx::Object*)0)
    HANDLE_EXPR(proxy_name, mLoader ? (mLoader->mProxyName ? mLoader->mProxyName : "") : "")
END_HANDLERS

DataNode ObjectDir::OnFind(DataArray* da){
    Hmx::Object* found = FindObject(da->Str(2), false);
    if(da->Size() > 3){
        if(da->Int(3) != 0 && !found){
            MILO_FAIL("Couldn't find %s in %s", da->Str(2), Name());
        }
    }
    return DataNode(found);
}

#pragma push
#pragma dont_inline on
// Here to test KeylessHash
DECOMP_FORCEBLOCK(Dir, (KeylessHash<const char*, ObjectDir::Entry>* hash),
    hash->Find(0);
)
#pragma pop
