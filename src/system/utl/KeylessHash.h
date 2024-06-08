#ifndef UTL_KEYLESSHASH_H
#define UTL_KEYLESSHASH_H
#include "math/Primes.h"
#include "math/Sort.h"
#include "os/Debug.h"
#include <string.h>

template <class T1, class T2> class KeylessHash {
public:
    T2* mEntries; // 0x0
    int mSize; // 0x4
    bool mOwnEntries; // 0x8
    int mNumEntries; // 0xc
    T2 mEmpty; // 0x10
    T2 mRemoved;

    KeylessHash(int i, const T2& tmp1 = T2(), const T2& tmp2 = T2(), T2* tmp_ptr = NULL){
        mEmpty = tmp1;
        mRemoved = tmp2;
        if(tmp_ptr){
            mSize = i;
            mEntries = tmp_ptr;
            mOwnEntries = false;
        }
        else if(i != 0){
            mSize = NextHashPrime(i);
            mEntries = new T2[mSize];
            mOwnEntries = true;
        }
        else {
            mSize = 0;
            mEntries = 0;
            mOwnEntries = true;
        }
        for(int i = 0; i < mSize; i++){
            mEntries[i] = mEmpty;
        }
        mNumEntries = 0;
    }

    ~KeylessHash(){
        if(mOwnEntries){
            delete [] mEntries;
        }
    }
    
    DELETE_OVERLOAD;

    T2* Find(const char* const& key){
        if(mEntries){
            int i = HashString(key, mSize);
            MILO_ASSERT(i >= 0, 0x88);

            T2* it;
            while(it = &mEntries[i], *it != mEmpty){
                if(*it != mRemoved){
                    bool matched = strcmp(*it, key) == 0;
                    if(matched) return it;
                }
                if(++i == mSize) i = 0;
            }
        }
        return 0;
    }

    T2* Insert(const T2& val){
        // MILO_ASSERT(val != mEmpty && val != mRemoved, 0x9A);
        // if(!mEntries){
        //     MILO_ASSERT(mOwnEntries, 0x9E);
        //     Resize(0x19, 0);
        // }
        // int i = HashString(val, mSize);
        // MILO_ASSERT(i >= 0, 0xA4);
    }

    void Resize(int, T2*);
    
    T2* FirstFrom(T2* entry){
        for(; entry < mEntries + mSize && (*entry == mEmpty || *entry == mRemoved); entry++);
        if(entry == mEntries + mSize) return 0;
        else return entry;
    }
};

#endif
