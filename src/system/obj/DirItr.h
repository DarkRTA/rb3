#ifndef OBJ_OBJDIRITER_H
#define OBJ_OBJDIRITER_H
#include "obj/Dir.h"
#include "utl/KeylessHash.h"

template <class T> class ObjDirItr {
public:
    // https://decomp.me/scratch/Qfa92
    ObjDirItr(ObjectDir* dir, bool b) : mDir(b ? dir : 0), mSubDir(dir), mWhich(0) {
        if(dir){
            // https://decomp.me/scratch/GNNj2 - KeylessHash::FirstFromStart?
            mEntry = dir->mHashTable.FirstFromStart();
            Advance();
        }
        else {
            mObj = 0;
            mEntry = 0;
        }
    }

    // https://decomp.me/scratch/47NK0
    ObjDirItr& operator++(){
        if(mEntry){
            // https://decomp.me/scratch/oVgXk - KeylessHash::FirstFromNext?
            mEntry = mSubDir->mHashTable.FirstFromNext(mEntry);
            Advance();
        }
        return *this;
    }

    operator T*(){ return mObj; }
    T* operator->() { return mObj; }

    // https://decomp.me/scratch/1uXoZ
    void Advance(){
        while(mEntry){
            mObj = dynamic_cast<T*>(mEntry->obj);
            if(mObj) return;
            mEntry = mSubDir->mHashTable.FirstFromNext(mEntry);
        }
        if(mDir){
            int nextwhich = ++mWhich;
            mSubDir = mDir->NextSubDir(nextwhich);
            if(mSubDir){
                mEntry = mSubDir->mHashTable.FirstFromStart();
                Advance();
                return;
            }
        }
        mObj = 0;
    }

    ObjectDir* mDir;
    ObjectDir* mSubDir;
    ObjectDir::Entry* mEntry;
    T* mObj;
    int mWhich;
};

#endif
