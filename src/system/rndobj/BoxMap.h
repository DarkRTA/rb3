#pragma once
#include "math/Vec.h"
#include "math/Color.h"
#include "rndobj/Lit.h"

template <class T1, int T2>
class BoxLightArray {
public:
    BoxLightArray() : mNumElements(0) {}
    void Clear() { mNumElements = 0; }
    bool CanAddEntry() const { return mNumElements < T2; }
    T1 *AddEntry() { return &mArray[mNumElements++]; }
    void RemoveEntry() { mNumElements--; }
    unsigned int NumElements() const { return mNumElements; }
    const T1 &operator[](int idx) const { return mArray[idx]; }

    T1 mArray[T2]; // 0x0
    unsigned int mNumElements;
};

class BoxMapLighting {
public:
    // size 0x1c
    struct LightParams_Directional {
        Vector3 mDirection; // 0x0
        Hmx::Color mColor; // 0xc
    };

    // size 0x24
    struct LightParams_Point {
        Vector3 unk0; // 0x0
        Hmx::Color mColor; // 0xc
        float mRange; // 0x1c
        float mFalloffStart; // 0x20
    };

    // size 0x50
    struct LightParams_Spot {
        Vector3 unk0; // 0x0
        Hmx::Color mColor; // 0xc
        Vector3 unk1c; // 0x1c
        float unk28;
        float unk2c;
        float unk30;
        float unk34;
        Vector3 unk38; // 0x38
        float unk44; // 0x44 - beam length?
        float unk48; // 0x48 - top beam radius
        float unk4c; // 0x4c - bottom beam radius
    };

    BoxMapLighting();
    void Clear();
    bool QueueLight(RndLight *, float);
    bool CacheData(LightParams_Spot &);
    void ApplyQueuedLights(Hmx::Color *, const Vector3 *) const;

    void ApplyLight(Hmx::Color *, const LightParams_Directional &) const;
    void ApplyLight(Hmx::Color *, const LightParams_Point &, const Vector3 &) const;
    void
    ApplyLight(Hmx::Color *, const BoxLightArray<BoxMapLighting::LightParams_Spot, 50> &, const Vector3 &)
        const;

    unsigned int NumQueuedLights() const {
        return mQueued_Directional.NumElements() + mQueued_Point.NumElements()
            + mQueued_Spot.NumElements();
    }

    bool ParamsAt(LightParams_Directional *&pd) {
        if (mQueued_Directional.CanAddEntry()) {
            pd = mQueued_Directional.AddEntry();
            return true;
        } else
            return false;
    }
    bool ParamsAt(LightParams_Point *&pt) {
        if (mQueued_Point.CanAddEntry()) {
            pt = mQueued_Point.AddEntry();
            return true;
        } else
            return false;
    }
    bool ParamsAt(LightParams_Spot *&ps) {
        if (mQueued_Spot.CanAddEntry()) {
            ps = mQueued_Spot.AddEntry();
            return true;
        } else
            return false;
    }

    static Vector3 sAxisDir[6];

    BoxLightArray<LightParams_Directional, 50> mQueued_Directional; // 0x0
    BoxLightArray<LightParams_Point, 50> mQueued_Point; // 0x57c
    BoxLightArray<LightParams_Spot, 50> mQueued_Spot; // 0xc88
};