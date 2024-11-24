#pragma once
#include <vector>
#include "math/Utl.h"
#include "math/Rot.h" // so that Vector2 is textstream-able

// thank god for the RB2 dump
/**
 * @brief A keyframe.
 * 
 * @tparam T The value of this keyframe.
 */
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
/**
 * @brief A specialized vector for keyframes.
 * 
 * @tparam T1 The value type stored inside each keyframe.
 * @tparam T2 The interpolated value type (see AtFrame).
 */
template <class T1, class T2> class Keys : public std::vector<Key<T1> > {
public:
    /** Get the number of keyframes in this collection. */
    int NumKeys() const { return size(); }

    // used in RemoveKey
    /** Remove the key at the given index.
     * @param [in] The index in the vector to remove.
     */
    void Remove(int idx){
        erase(begin() + idx);
    }

    // fn_806570E8 for Vector3, fn_8065783C for Quat
    /** Given a start and end frame, get the closest start and end indices of this vector.
     * NOTE: if both the start and end frame are 0, they will be overwritten to the first and last frame,
     * istart will become 0, and iend will become the last index of the vector.
     * @param [in] fstart The start frame.
     * @param [in] fend The end frame.
     * @param [out] istart The index of the last key whose frame <= the start frame.
     * @param [out] iend The index of the first key whose frame >= the end frame.
     */
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
            istart = KeyLessEq(Max(fstart, front().frame));
            iend = KeyGreaterEq(Min(fend, back().frame));
        }
    }

    // matches in retail with the right inline settings: https://decomp.me/scratch/hWbQQ
    /** Sort the keys by their frames. */
    void Sort(){
        int vecSize = size();
        for(int i = 1; i < vecSize; i++){
            Key<T1> key = (*this)[i];
            
            int j;
            for(j = i; 0 < j && key.frame < (*this)[j-1].frame; j--){
                (*this)[j] = (*this)[j-1];
            }
            if(j != i) (*this)[j] = key;
        }
    }

    /** Get the first frame of the keys. */
    float FirstFrame() const {
        if(size() != 0) return front().frame;
        else return 0.0f;
    }

    /** Get the last frame of the keys. */
    float LastFrame() const {
        if(size() != 0) return back().frame;
        else return 0.0f;
    }

    // fn_805FC18C for Vector3
    /** Add a value to the keys at a given frame.
     * @param [in] val The value to add.
     * @param [in] frame The frame at which this value will be.
     * @param [in] unique If true, overwrite the existing value at this frame. Otherwise, create a new keyframe.
     * @returns The index in the vector corresponding to this new keyframe.
     */
    int Add(const T1& val, float frame, bool unique){
        int bound = KeyGreaterEq(frame);
        if(unique && bound != size() && frame == (*this)[bound].frame){
            (*this)[bound].value = val;
        }
        else {
            while(bound < size() && frame == (*this)[bound].frame){
                bound++;
            }
            insert(&(*this)[bound], Key<T1>(val, frame));
        }
        return bound;
    }

    // fn_80653DE0 for Vector3 and fn_80653CE4 for Hmx::Quat
    /** Remove a range of keyframes.
     * @param [in] fstart The start frame of the range to remove.
     * @param [in] fend The end frame of the range to remove.
     */
    int Remove(float fstart, float fend){
        int bound1 = KeyGreaterEq(fstart);
        int bound2 = KeyGreaterEq(fend);
        erase(&(*this)[bound1], &(*this)[bound2]);
        return bound1;
    }

    // full method scratch (debug): https://decomp.me/scratch/IXqzR
    /** Get the value associated with the supplied frame.
     * @param [in] frame The keyframe to get a value from.
     * @param [out] val The retrieved value.
     * @returns The index in the vector where this keyframe resides.
     */
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
    /** Get the value associated with the supplied frame.
     * @param [in] frame The keyframe to get a value from.
     * @param [out] prev The previous key relative to the keyframe we want.
     * @param [out] next The next key relative to the keyframe we want.
     * @param [out] ref TODO: unknown
     * @returns The index in the vector where this keyframe resides.
     */
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
                int frameIdx = KeyLessEq(frame); // fn_805FBF50 in retail for T1, T2 = TexPtr, RndTex*
                prev = &(*this)[frameIdx];
                next = &(*this)[frameIdx + 1];
                float den = next->frame - prev->frame;
                MILO_ASSERT(den != 0, 0xE9);
                ref = (frame - prev->frame) / den;
                return frameIdx;
            }
        }
    }

    /** Get the index of the last possible keyframe KF, such that KF's frame <= the supplied frame.
     * @param [in] frame The supplied frame.
     * @returns The index of the keyframe that satisfies the condition above.
     */
    int KeyLessEq(float frame) const {
        if(empty() || (frame < front().frame)) return -1;
        else {
            int cnt = 0;
            int threshold = size();
            while(threshold > cnt + 1){
                int newCnt = (cnt + threshold) >> 1;
                if(frame < (*this)[newCnt].frame) threshold = newCnt;
                if(!(frame < (*this)[(int)newCnt].frame)) cnt = newCnt;
            }
            while (cnt + 1 < size() && (*this)[cnt + 1].SameFrame((*this)[cnt])) cnt++;
            return cnt;
        }
    }

    /** Get the index of the first possible keyframe KF, such that KF's frame >= the supplied frame.
     * @param [in] frame The supplied frame.
     * @returns The index of the keyframe that satisfies the condition above.
     */
    int KeyGreaterEq(float frame) const {
        if(empty() || (frame <= front().frame)) return 0;
        else {
            const Key<T1>& backKey = back();
            if(frame > backKey.frame){
                return size();
            }
            else {
                int cnt = 0;
                int threshold = size() - 1;
                while(threshold > cnt + 1){
                    int newCnt = (cnt + threshold) >> 1;
                    if(frame > (*this)[newCnt].frame) cnt = newCnt;
                    if(!(frame > (*this)[(int)newCnt].frame)) threshold = newCnt;
                }
                while (threshold > 1 && (*this)[threshold - 1].SameFrame((*this)[threshold])) threshold--;
                return threshold;
            }
        }
    }

    // returns the first Key that fits in the range of frames f1 to f2
    Key<T1>* GetFirstInRange(float f1, float f2){
        int idx = KeyLessEq(f1);
        if(idx == -1) return 0;
        else {
            if(f2 >= (*this)[idx].frame) return 0;
            else return &(*this)[idx];
        }
    }

    void KeysLessEq(float f, int& iref1, int& iref2) const {
        iref2 = -1;
        iref1 = -1;
        if(empty() || f < front().frame) return;
        int i1 = 0;
        int i2 = size();
        while(i2 > i1 + 1){
            int i5 = i1 + i2 >> 1;
            const Key<T1>& cur = (*this)[i5];
            if(f < cur.frame)  i2 = i5;
            if(!(f < cur.frame)) i1 = i5;
        }
        iref2 = i1;
        iref1 = i1;
        while(i1 - 1 >= 0 && (*this)[i1-1].SameFrame((*this)[i1])){
            i1--;
            iref1 = i1;
        }
        while(i1 + 1 < size() && (*this)[i1+1].SameFrame((*this)[i1])){
            i1++;
            iref2 = i1;
        }
    }
};

/** Scale keyframes by a supplied multiplier.
 * @param [in] keys The collection of keys to multiply the frames of.
 * @param [in] scale The multiplier value.
 */
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
