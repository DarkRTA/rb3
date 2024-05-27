#ifndef OBJ_OBJDIRITER_H
#define OBJ_OBJDIRITER_H
#include "obj/Dir.h"
#include "utl/KeylessHash.h"

template <class T> class ObjDirItr {
public:
    ObjDirItr(ObjectDir* dir, bool b) : mDir(b ? dir : 0), mSubDir(dir), mWhich(0) {
        if(!dir){
            mObj = 0;
            mEntry = 0;
        }
        else {
            mEntry = dir->mHashTable.FirstFrom(dir->mHashTable.mEntries);
            Advance();
        }
    }

    ObjDirItr& operator++(){
        if(mEntry){
            mEntry = mSubDir->mHashTable.FirstFrom(0); // fix the input param
            Advance();
        }
        return *this;
    }

    void Advance();

    ObjectDir* mDir;
    ObjectDir* mSubDir;
    ObjectDir::Entry* mEntry;
    T* mObj;
    int mWhich;
};

#endif
