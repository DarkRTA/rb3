#include "obj/DirUnloader.h"
#include "obj/DirItr.h"

DirUnloader::DirUnloader(ObjectDir* dir) : Loader(FilePath(dir->mPathName), kLoadFront), mObjects() {
    mObjects.reserve(dir->mHashTable.mSize / 2);
    for(ObjDirItr<Hmx::Object> it(dir, false); it != 0; ++it){
        if(it != dir){
            it->SetName(0, 0);
            mObjects.push_back(ObjPtr<Hmx::Object, ObjectDir>(this, it));
        }
    }
}

DirUnloader::~DirUnloader(){
    MILO_ASSERT(mObjects.empty(), 0x20);
}

const char* DirUnloader::DebugText(){ return MakeString("UnLoader: %s", mFile.c_str()); }