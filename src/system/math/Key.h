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
    void Add(const T1&, float, bool);
    void Remove(int); // used in RemoveKey
    void Remove(float, float);
    void FindBounds(float&, float&, int&, int&);

    float LastFrame() const {
        if(size() != 0) return back().frame;
        else return 0.0f;
    }

    // full method scratch (debug): https://decomp.me/scratch/IXqzR
    int AtFrame(float frame, T2& val) const {
        const Key<T1>* prev;
        const Key<T1>* next;
        float r;
        int ret = AtFrame(frame, prev, next, r);
        if(prev){
            Interp(prev->value, next->value, r, val);
        }
        return ret;
    }

    int AtFrame(float, const T1*&, const T1*&, float&) const; // very possible this went unused in RB3 in favor of the method directly below this one

    // fn_8039C750 in retail, for T1 = Symbol
    // scratch: https://decomp.me/scratch/R1SeP
    // scratch for T1 = float: https://decomp.me/scratch/GXfNX
    // inside this function contains another function, scratch here: https://decomp.me/scratch/cPad6
    int AtFrame(float frame, const Key<T1>*& prev, const Key<T1>*& next, float& ref) const {
        if(empty()){
            next = 0;
            prev = 0;
            ref = 0.0f;
            return -1;
        }
        else {
            const Key<T1>* frontKey = &front();
            if(frame < front().frame){
                next = &front();
                prev = &front();
                ref = 0.0f;
                return -1;
            }
            else if(frame >= back().frame){
                const Key<T1>* backKey = &back();
                next = backKey;
                prev = backKey;
                ref = 0.0f;
                return size() - 1;
            }
            else {
                int frameIdx = idunnolol(frame);
                prev = &this->operator[](frameIdx);
                next = &this->operator[](frameIdx + 1);
                float den = next->frame - prev->frame;
                MILO_ASSERT(den != 0, 0xE9);
                ref = (frame - prev->frame) / den;
                return frameIdx;
            }
        }
    }

    // looks like this gets the index in the Keys vector in which the frame ff is located?
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
            while (cnt + 1 < size() && SameFrame(&(*this)[cnt + 1], &(*this)[cnt])) {
                cnt++;
            }

            return cnt;
        }
    }

    bool SameFrame(const Key<T1>* k1, const Key<T1>* k2) const {
        return k1->frame == k2->frame ? true : false;
    }
};

template <class T1, class T2> void ScaleFrame(Keys<T1, T2>& keys, float scale){
    for(Keys<T1,T2>::iterator it = keys.begin(); it != keys.end(); ++it){
        (*it).frame *= scale;
    }
}

#endif
