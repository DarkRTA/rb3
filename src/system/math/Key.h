#ifndef UTL_KEY_H
#define UTL_KEY_H
#include <vector>
#include "math/Rot.h" // so that Vector2 is textstream-able

// thank god for the RB2 dump
template <class T> class Key {
public:
    Key() : frame(0.0f) {}
    T value;
    float frame;

    // I found a weak copy ctor and weak operator=(const Key<T>&)
    // not sure if we need to explicitly write these or not
};

template <class T> TextStream& operator<<(TextStream& ts, const Key<T>& key){
    ts << "(frame:" << key.frame << " value:" << key.value << ")";
    return ts;
}

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
    void Remove(int); // used in RemoveKey

    int AtFrame(float frame, T2& val) const {
        const Key<T1>* prev;
        const Key<T1>* next;
        float r;
        int ret = AtFrame(frame, prev, next, r);
        if(r != 0.0f){
            Interp(prev->value, next->value, r, val);
        }
        return ret;
    }

    // void SetVal(const T1& prevVal, const T1& nextVal, float r, T1& val){
    //     if(r < 1.0f){
    //         nextVal = prevVal;
    //     }
    //     val = nextVal;
    // }

    // // this is what SymbolAt calls
    // int AtFrame(float frame, T2& val) const {
    //     const Key<T1>* prev;
    //     const Key<T1>* next;
    //     float r;
    //     int idx = AtFrame(frame, prev, next, r);
    //     // if(prev) // if prev is not null, call Interp for T1's type - for ObjectKeys, this'll call the Interp(ObjectStage&) method
    //     if(prev){
    //         // SetVal(&prev->value, &next->value, r, val);
    //         if(r < 1.0f){
    //             next = prev;
    //         }
    //         val = next->value;
    //     }
    //     return idx;
        
    // }

    int AtFrame(float, const T1*&, const T1*&, float&) const; // very possible this went unused in RB3 in favor of the method directly below this one

    // fn_8039C750 in retail, for T1 = Symbol
    // scratch: https://decomp.me/scratch/R1SeP
    // scratch for T1 = float: https://decomp.me/scratch/GXfNX
    // inside this function contains another function, scratch here: https://decomp.me/scratch/cPad6
    int AtFrame(float frame, const Key<T1>*& key1, const Key<T1>*& key2, float& ref) const {
        if(empty()){
            key2 = 0;
            key1 = 0;
            ref = 0.0f;
            return -1;
        }
        else {
            const Key<T1>* key = &front();
            if(frame < key->frame){
                key2 = key;
                key1 = key;
                ref = 0.0f;
                return -1;
            }
            else {
                const Key<T1>* otherKey = &back();
                if(frame >= otherKey->frame){
                    const Key<T1>* otherKeyToRet = &back();
                    key2 = otherKeyToRet;
                    key1 = otherKeyToRet;
                    ref = 0.0f;
                    return size() - 1;
                }
                else {
                    // scratch for this function: https://decomp.me/scratch/cPad6
                    // scratch for this function when T1 = float: https://decomp.me/scratch/ZrNr0
                    int somethingidk = idunnolol(frame);
                    key1 = &this->operator[](somethingidk);
                    key2 = &this->operator[](somethingidk + 1);
                    float den = key2->frame - key1->frame;
                    MILO_ASSERT(den != 0, 0xE9);
                    ref = (frame - key1->frame) / den;
                    return somethingidk;
                }
            }
        }
    }

    int idunnolol(float ff) const {
        if(empty() || (ff < front().frame)) return -1;
        else {
            int cnt = 0;
            int threshold = size();
            while(threshold > cnt + 1){
                int newCnt = cnt + threshold >> 1;
                const Key<T1>* keyHere = &(*this)[newCnt];
                if(ff < keyHere->frame) threshold = newCnt;
                if(!(ff < keyHere->frame)) cnt = newCnt;
            }

            while (cnt + 1 < size() && test2(&(*this)[cnt + 1], &(*this)[cnt])) {
                cnt++;
            }
            
            // while(cnt + 1 > size()){
            //     const Key<T1>* key1 = &this->operator[](cnt);
            //     const Key<T1>* key2 = &this->operator[](cnt + 1);
            //     if(key1->frame == key2->frame) break;
            //     cnt++;
            // }
            return cnt;
        }
    }

    bool test2(const Key<T1>* k1, const Key<T1>* k2) const {
        return k1->frame == k2->frame ? true : false;
    }
};

#endif
