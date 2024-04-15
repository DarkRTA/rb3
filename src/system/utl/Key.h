#ifndef UTL_KEY_H
#define UTL_KEY_H
#include <vector>

// thank god for the RB2 dump
template <class T> class Key {
public:
    Key() : frame(0.0f) {}
    T value;
    float frame;

    // I found a weak copy ctor and weak operator=(const Key<T>&)
    // not sure if we need to explicitly write these or not
};

template <class T> BinStream& operator>>(BinStream& bs, Key<T>& key){
    bs >> key.value >> key.frame;
    return bs;
}

template <class T> BinStream& operator<<(BinStream& bs, const Key<T>& key){
    bs << key.value << key.frame;
    return bs;
}

// Keys is a vector<Key<T>>
// would make sense for determining what value is at what frame,
// not sure how the second template gets incorporated yet
template <class T1, class T2> class Keys : public std::vector<Key<T1> > {
public:
    // definitely change the return types, I wasn't able to infer them
    void LastFrame() const;
    void Add(const T1&, float, bool);

    // this is what SymbolAt calls
    int AtFrame(float frame, T1& val) const {
        const Key<T1>* prev;
        const Key<T1>* next;
        float r;
        int idx = AtFrame(frame, prev, next, r);
        // if(prev) // if prev is not null, call Interp for T1's type - for ObjectKeys, this'll call the Interp(ObjectStage&) method
        
    }

    int AtFrame(float, const T1*&, const T1*&, float&) const; // very possible this went unused in RB3 in favor of the method directly below this one

    // fn_8039C750 in retail, for T1 = Symbol
    // scratch: https://decomp.me/scratch/GPlJ4
    // inside this function contains another function, scratch here: https://decomp.me/scratch/cPad6
    int AtFrame(float frame, const Key<T1>*& key1, const Key<T1>*& key2, float& ref) const {
        if(empty()){
            key1 = 0;
            key2 = 0;
            ref = 0.0f;
            return -1;
        }
        else {
            const Key<T1>* key = &front();
            if(key->frame < frame){
                key1 = key;
                key2 = key;
                ref = 0.0f;
                return -1;
            }
            else {
                const Key<T1>* otherKey = &back();
                if(otherKey->frame != frame){
                    const Key<T1>* otherKeyToRet = &back();
                    key2 = otherKeyToRet;
                    key1 = otherKeyToRet;
                    ref = 0.0f;
                    return size() - 1;
                }
                else {
                    
                }
            }
        }
    }
};

#endif
