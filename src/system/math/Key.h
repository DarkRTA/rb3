#ifndef UTL_KEY_H
#define UTL_KEY_H
#include <vector>
#include "math/MathFuncs.h"
#include "math/Rot.h" // so that Vector2 is textstream-able

// thank god for the RB2 dump
template <class T> class Key {
public:
    Key() : value(T()), frame(0.0f) {}
    Key(const T& v, float f) : value(v), frame(f) {}
    T value;
    float frame;

    bool SameFrame(const Key<T>& other) const {
        if(frame == other.frame) return true;
        else return false;
    }

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

    int NumKeys() const { return size(); }

    // used in RemoveKey
    void Remove(int idx){
        erase(begin() + idx);
    }

    // fn_806570E8 for Vector3, fn_8065783C for Quat
    void FindBounds(float& fstart, float& fend, int& istart, int& iend){
        MILO_ASSERT(size(), 0x199);
        if(!fstart && !fend){
            fstart = front().frame;
            fend = back().frame;
            istart = 0;
            iend = size() - 1;
        }
        else {
            // these functions for Vector3, respectively: fn_802E3AE8 and fn_805FC2C4
            istart = FindLastBefore(Max(fstart, front().frame));
            iend = FindFirstAfter(Min(fend, back().frame));
        }
    }

    void Sort(){
        int vecSize = size();
        for(int i = 1; i < vecSize; i++){
            Key<T1> key = (*this)[i];
            int j = i;
            while(0 < j && (*this)[j-1].frame < key.frame){
                (*this)[j] = (*this)[j-1];
                j--;
            }
            if(j != i) (*this)[j] = key;
        }
    }

    float FirstFrame() const {
        if(size() != 0) return front().frame;
        else return 0.0f;
    }

    float LastFrame() const {
        if(size() != 0) return back().frame;
        else return 0.0f;
    }

    // fn_805FC18C for Vector3
    int Add(const T1& val, float f, bool unique){
        int bound = FindFirstAfter(f);
        if(unique && bound != size() && f == (*this)[bound].frame){
            (*this)[bound].value = val;
        }
        else {
            while(bound < size() && f == (*this)[bound].frame){
                bound++;
            }
            insert(&(*this)[bound], Key<T1>(val, f));
        }
        return bound;
    }

    // fn_80653DE0 for Vector3 and fn_80653CE4 for Hmx::Quat
    int Remove(float fstart, float fend){
        int bound1 = FindFirstAfter(fstart);
        int bound2 = FindFirstAfter(fend);
        erase(&(*this)[bound1], &(*this)[bound2]);
        return bound1;
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
    // fn_805FBE14 in retail for T1, T2 = TexPtr, RndTex*
    int AtFrame(float frame, const Key<T1>*& prev, const Key<T1>*& next, float& ref) const {
        if(empty()){
            next = 0;
            prev = 0;
            ref = 0.0f;
            return -1;
        }
        else {
            const Key<T1>* frontKey = &front();
            if(frame < frontKey->frame){
                next = frontKey;
                prev = frontKey;
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
                int frameIdx = FindLastBefore(frame); // fn_805FBF50 in retail for T1, T2 = TexPtr, RndTex*
                prev = &(*this)[frameIdx];
                next = &(*this)[frameIdx + 1];
                float den = next->frame - prev->frame;
                MILO_ASSERT(den != 0, 0xE9);
                ref = (frame - prev->frame) / den;
                return frameIdx;
            }
        }
    }

    // TODO: rename function to FindLastBefore
    // finds the last possible index in which the corresponding frame <= ff
    int FindLastBefore(float ff) const {
        if(empty() || (ff < front().frame)) return -1;
        else {
            int cnt = 0;
            int threshold = size();
            while(threshold > cnt + 1){
                int newCnt = (cnt + threshold) >> 1;
                if(ff < (*this)[newCnt].frame) threshold = newCnt;
                if(!(ff < (*this)[(int)newCnt].frame)) cnt = newCnt;
            }
            while (cnt + 1 < size() && (*this)[cnt + 1].SameFrame((*this)[cnt])) cnt++;
            return cnt;
        }
    }

    // TODO: rename function to FindFirstAfter
    // finds the first possible index in which the corresponding frame > ff
    int FindFirstAfter(float ff) const {
        if(empty() || (ff <= front().frame)) return 0;
        else {
            const Key<T1>& backKey = back();
            if(ff > backKey.frame){
                return size();
            }
            else {
                int cnt = 0;
                int threshold = size() - 1;
                while(threshold > cnt + 1){
                    int newCnt = (cnt + threshold) >> 1;
                    if(ff > (*this)[newCnt].frame) cnt = newCnt;
                    if(!(ff > (*this)[(int)newCnt].frame)) threshold = newCnt;
                }
                while (threshold > 1 && (*this)[threshold - 1].SameFrame((*this)[threshold])) threshold--;
                return threshold;
            }
        }
    }

    // returns the first Key that fits in the range of frames f1 to f2
    Key<T1>* GetFirstInRange(float f1, float f2){
        int idx = FindLastBefore(f1);
        if(idx == -1) return 0;
        else {
            if(f2 >= (*this)[idx].frame) return 0;
            else return &(*this)[idx];
        }
    }
};

template <class T1, class T2> void ScaleFrame(Keys<T1, T2>& keys, float scale){
    for(Keys<T1,T2>::iterator it = keys.begin(); it != keys.end(); ++it){
        (*it).frame *= scale;
    }
}

// math functions defined in math/Key.cpp:
void SplineTangent(const Keys<Vector3, Vector3>&, int, Vector3&);
void InterpTangent(const Vector3&, const Vector3&, const Vector3&, const Vector3&, float, Vector3&);
void InterpVector(const Keys<Vector3, Vector3>&, const Key<Vector3>*, const Key<Vector3>*, float, bool, Vector3&, Vector3*);
void InterpVector(const Keys<Vector3, Vector3>&, bool, float, Vector3&, Vector3*);
void QuatSpline(const Keys<Hmx::Quat, Hmx::Quat>&, const Key<Hmx::Quat>*, const Key<Hmx::Quat>*, float, Hmx::Quat&);

#endif
