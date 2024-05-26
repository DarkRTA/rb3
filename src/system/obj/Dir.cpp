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

#pragma push
#pragma dont_inline on
void ObjectDir::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0x1B, 0);
    if(gRev > 0x15) Hmx::Object::LoadType(bs);
    else if(gRev - 2 < 0xF) Hmx::Object::Load(bs);
    // ...
    PushRev(packRevs(gAltRev, gRev), this);
}
#pragma pop

bool ObjectDir::AllowsInlineProxy(){
    return mInlineProxy;
}

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