#ifndef UTL_KEYLESSHASH_H
#define UTL_KEYLESSHASH_H
#include "math/Primes.h"
#include "math/Sort.h"
#include "utl/Loader.h"
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
KeylessHash<T1, T2>::KeylessHash(int size, const T2& empty, const T2& removed, T2* entries){
    mEmpty = empty;
    mRemoved = removed;
    if(entries){
        mSize = size;
        mEntries = entries;
        mOwnEntries = false;
    }
    else if(size != 0){
        mSize = NextHashPrime(size);
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
    const char* valStr = (const char*)val;
    int i = HashString(valStr, mSize);
    MILO_ASSERT(i >= 0, 0xA4);
    while(mEntries[i] != mEmpty && mEntries[i] != mRemoved && !KeysMatch((const char*)mEntries[i], valStr)){
        Advance(i);
    }
    if(mEntries[i] == mEmpty){
        mNumEntries++;
        if(mNumEntries > mSize / 2 && mOwnEntries){
            MILO_ASSERT(mSize, 0xB5);
            Resize(mSize * 2, 0);
            if(!TheLoadMgr.EditMode() && MakeStringInitted()){
                MILO_WARN("Resizing hash table (%d)", mSize);
            }
            return Insert(val);
        }
        if(mNumEntries >= mSize){
            MILO_FAIL("Hash table full (%d)", mSize);
        }
    }
    mEntries[i] = val;
    return &mEntries[i];
}

template <class T1, class T2>
void KeylessHash<T1, T2>::Resize(int size, T2* val){
    MILO_ASSERT(size > mNumEntries * 2, 0xF3);
    bool owned;
    if(val) owned = false;
    else {
        size = NextHashPrime(size);
        val = new T2[size];
        owned = true;
    }
    for(int i = 0; i < size; i++){
        val[i] = mEmpty;
    }
    mNumEntries = 0;
    for(T2* it = FirstFromStart(); it != 0; it = FirstFromNext(it)){
        int i = HashString(*it, size);
        MILO_ASSERT(i >= 0, 0x108);
        while(val[i] != mEmpty){
            i++;
            if(i == size) i = 0;
        }
        mNumEntries++;
        val[i] = *it;
    }
    if(mOwnEntries) delete [] mEntries;
    mEntries = val;
    mSize = size;
    mOwnEntries = owned;
}

#endif
