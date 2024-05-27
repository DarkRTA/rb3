#include "obj/Dir.h"
#include "obj/Object.h"
#include "obj/ObjVersion.h"

const char* kNotObjectMsg = "Could not find %s in dir \"%s\"";

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

bool ObjectDir::IsProxy() const {
    return this != mDir;
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
    for(int i = mInlinedDirs.size(); i >= 0; i--){
        ObjDirPtr<ObjectDir>& ptr = mInlinedDirs[i].dir;
        ptr.IsLoaded();
        ptr->Dir();
        ptr.GetFile();
        ptr.PostLoad(0);
        ptr = ObjDirPtr<ObjectDir>();
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
        TheDebug << MakeString("rev stack $this mismatch (%08x != %08x\n", o, &back.obj);
        TheDebug << MakeString("curr obj: %s %s\n", o->ClassName(), PathName(o));
        TheDebug << MakeString("stack obj: %s %s\n", back.obj->ClassName(), PathName(back.obj));
        TheDebug << MakeString("rev stack (%08x %s %s != %08x %s %s)\n", o, o->ClassName(), PathName(o), &back.obj, back.obj->ClassName(), PathName(back.obj));
    }
    sRevStack.pop_back();
    return back.revs;
}