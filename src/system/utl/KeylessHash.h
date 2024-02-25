#ifndef UTL_KEYLESSHASH_H
#define UTL_KEYLESSHASH_H

// forward declaration
namespace Hmx {
    class Object;
}

struct Entry {
    const char* name;
    Hmx::Object* obj;
};

template <class T1, class T2> class KeylessHash {
public:
    Entry* mEntries;
    int mSize;
    bool mOwnEntries;
    int mNumEntries;
    Entry mEmpty;
    Entry mRemoved;

    KeylessHash(int, const T2&, const T2&, T2*);
    ~KeylessHash();
    T1 Find(const T1&);
    int Insert(const T2&);
    void Resize(int, T2*);
    T2* FirstFrom(T2*);
};

#endif
