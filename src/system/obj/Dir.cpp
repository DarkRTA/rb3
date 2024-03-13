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

// ObjectDir::ObjectDir() {
//     ObjectDir::Entry entry1, entry2;
//     mHashTable = new KeylessHash<const char*, ObjectDir::Entry>(0, entry1, entry2, 0);
// }

void ObjectDir::PostSave(BinStream& bs){
    SyncObjects();
}

bool ObjectDir::AllowsInlineProxy(){
    return mInline;
}
