#include "obj/Dir.h"

#include "obj/Object.h"

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

ObjectDir::ObjectDir() : mHashTable(0, Entry(), Entry(), 0), mStringTable(0), mProxyFile(), mProxyOverride(0), 
    mInline(1), mLoader(0), mIsSubDir(0), unk58(0), mPathName(gNullStr), fpath2(), unk74(0), unk78(0), unk7c(gNullStr) {
    
}

void ObjectDir::PostSave(BinStream& bs){
    SyncObjects();
}

bool ObjectDir::AllowsInlineProxy(){
    return mInline;
}
