#ifndef UTL_KEYLESSHASH_H
#define UTL_KEYLESSHASH_H
#include "math/Primes.h"

// forward declaration
namespace Hmx {
    class Object;
}

// ObjectDir::Entry?
struct Entry {
    const char* name;
    Hmx::Object* obj;
};

template <class T1, class T2> class KeylessHash {
public:
    T2* mEntries; // 0x0
    int mSize; // 0x4
    bool mOwnEntries; // 0x8
    int mNumEntries; // 0xc
    T2 mEmpty; // 0x10
    T2 mRemoved;

    KeylessHash(int i, const T2& tmp1, const T2& tmp2, T2* tmp_ptr){
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

    ~KeylessHash();
    T1 Find(const T1&);
    int Insert(const T2&);
    void Resize(int, T2*);
    T2* FirstFrom(T2*);
};

#endif
