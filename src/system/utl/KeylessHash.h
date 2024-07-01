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

    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    KeylessHash(int, const T2&, const T2&, T2*);
    ~KeylessHash();

    T2* Find(const char* const& key);
    T2* Insert(const T2& val);
    void Resize(int, T2*);
    T2* FirstFrom(T2* entry);

    void Advance(int& idx){
        idx++;
        if(idx == mSize) idx = 0;
    }

    // keep these in here so that they're inlined - needed for ObjDirItr    
    T2* FirstFromStart(){ return FirstFrom(mEntries); }
    T2* FirstFromNext(T2* entry){ return FirstFrom(&entry[1]); }
};

template <class T1, class T2>
KeylessHash<T1, T2>::KeylessHash(int i, const T2& tmp1 , const T2& tmp2 , T2* tmp_ptr ){
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

template <class T1, class T2>
KeylessHash<T1, T2>::~KeylessHash(){
    if(mOwnEntries){
        delete [] mEntries;
    }
}

template <class T1, class T2>
T2* KeylessHash<T1, T2>::FirstFrom(T2* entry){
    for(; entry < mEntries + mSize && (*entry == mEmpty || *entry == mRemoved); entry++);
    if(entry == mEntries + mSize) return 0;
    else return entry;
}

inline bool KeysMatch(const char* k1, const char* k2){ return strcmp(k1, k2) == 0; }

template <class T1, class T2>
T2* KeylessHash<T1, T2>::Find(const char* const& key){
    if(mEntries){
        int i = HashString(key, mSize);
        MILO_ASSERT(i >= 0, 0x88);

        for(; mEntries[i] != mEmpty; Advance(i)){
            if(mEntries[i] != mRemoved){
                if(KeysMatch((const char *)mEntries[i], key)) return &mEntries[i];
            }
        }
    }
    return 0;
}

template <class T1, class T2>
T2* KeylessHash<T1, T2>::Insert(const T2& val){
    MILO_ASSERT(val != mEmpty && val != mRemoved, 0x9A);
    if(!mEntries){
        MILO_ASSERT(mOwnEntries, 0x9E);
        Resize(0x19, 0);
    }
    int i = HashString((const char*)val, mSize);
    MILO_ASSERT(i >= 0, 0xA4);
}

#endif
