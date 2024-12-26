#pragma once
#include "math/Primes.h"
#include "math/Sort.h"
#include "utl/Loader.h"
#include "os/Debug.h"
#include <string.h>

/**
 * @brief A keyless hash table.
 * 
 * @tparam T1 const char* type (?)
 * @tparam T2 the type to store into the hash table.
 */
template <class T1, class T2> class KeylessHash {
public:
    /** The collection of entries in the hash table. */
    T2* mEntries; // 0x0
    /** The hash table's size. */
    int mSize; // 0x4
    /** Whether or not this table owns its entries. */
    bool mOwnEntries; // 0x8
    /** The number of currently allocated entries in the table. */
    int mNumEntries; // 0xc
    /** The type T2 representing an empty hash table entry. */
    T2 mEmpty; // 0x10
    /** The type T2 representing a removed hash table entry. */
    T2 mRemoved;

    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    KeylessHash(int, const T2&, const T2&, T2*);
    ~KeylessHash();

    /** Get the entry in the hash table corresponding with the supplied key.
     * @param [in] key The key to search with.
     * @returns The corresponding entry, if it exists.
     */
    T2* Find(const char* const& key);

    /** Insert this value into the hash table.
     * @param [in] val The val to insert.
     * @returns The entry in the hash table containing the value.
     */
    T2* Insert(const T2& val);

    /** Resize the hash table.
     * @param [in] size The new desired size of the table.
     * @param [in] entries Where the newly resized hash table entries will be written. If this is NOT null, then this table does not own its entries.
     */
    void Resize(int size, T2* entries);

    /** Get the first valid entry in the table from the supplied entry.
     * @param [in] entry The indexed entry in the table to begin searching from.
     * @returns The first valid entry from the supplied entry, if it exists.
     */
    T2* FirstFrom(T2* entry);

    // getters
    int Size() const { return mSize; }
    int UsedSize() const { return mNumEntries; }

    /** Advance the index to search the supplied hash table with.
     * The hash table implementation is a circular buffer,
     * so if the end is reached, loop back to index zero.
     */
    void Advance(int& idx){
        idx++;
        if(idx == mSize) idx = 0;
    }

    // keep these in here so that they're inlined - needed for ObjDirItr

    /** Get the very first valid entry in the table. */
    T2* Begin(){ return FirstFrom(mEntries); }
    /** Get the next valid entry in the table from the supplied entry. */
    T2* Next(T2* entry){ return FirstFrom(&entry[1]); }
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
    if(entry == mEntries + mSize) return nullptr;
    else return entry;
}

template <class T1, class T2>
T2* KeylessHash<T1, T2>::Find(const char* const& key){
    if(mEntries){
        int i = HashString(key, mSize);
        MILO_ASSERT(i >= 0, 0x88);

        for(; mEntries[i] != mEmpty; Advance(i)){
            if(mEntries[i] != mRemoved){
                if(streq((const char *)mEntries[i], key)) return &mEntries[i];
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
    while(mEntries[i] != mEmpty && mEntries[i] != mRemoved && !streq((const char*)mEntries[i], valStr)){
        Advance(i);
    }
    if(mEntries[i] == mEmpty){
        mNumEntries++;
        if(mNumEntries > mSize / 2 && mOwnEntries){
            MILO_ASSERT(mSize, 0xB5);
            Resize(mSize * 2, 0);
            if(!LOADMGR_EDITMODE && MakeStringInitted()){
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
void KeylessHash<T1, T2>::Resize(int size, T2* entries){
    MILO_ASSERT(size > mNumEntries * 2, 0xF3);
    bool owned;
    if(entries) owned = false;
    else {
        size = NextHashPrime(size);
        entries = new T2[size];
        owned = true;
    }
    for(int i = 0; i < size; i++){
        entries[i] = mEmpty;
    }
    mNumEntries = 0;
    for(T2* it = Begin(); it != 0; it = Next(it)){
        int i = HashString(*it, size);
        MILO_ASSERT(i >= 0, 0x108);
        while(entries[i] != mEmpty){
            i++;
            if(i == size) i = 0;
        }
        mNumEntries++;
        entries[i] = *it;
    }
    if(mOwnEntries) delete [] mEntries;
    mEntries = entries;
    mSize = size;
    mOwnEntries = owned;
}
