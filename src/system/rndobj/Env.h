#ifndef RNDOBJ_ENV_H
#define RNDOBJ_ENV_H
#include "rndobj/Trans.h"
#include "types.h"
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "math/Vec.h"
#include "rndobj/Lit.h"
#include "rndobj/ColorXfm.h"
#include "math/Color.h"

class _GXColor;

class RndEnviron : public Hmx::Object {
public:
    RndEnviron();
    virtual ~RndEnviron();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    OBJ_CLASSNAME(Environ);
    OBJ_SET_TYPE(Environ);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Select(const Vector3*);
    virtual void ApplyApproxLighting(const _GXColor*);
    virtual bool HasPointCubeTex(void) const;
    virtual bool IsFake(RndLight*) const;
    virtual bool IsReal(RndLight*) const;

    void RemoveLight(RndLight*);
    void ReclassifyLights();
    void OnRemoveAllLights();
    DataNode OnAllowableLights_Real(const DataArray*);
    DataNode OnAllowableLights_Approx(const DataArray*);
    bool FogEnable() const;
    bool IsLightInList(const RndLight*, const ObjPtrList<RndLight, class ObjectDir>&) const;
    bool IsValidRealLight(const RndLight*) const;

    DELETE_OVERLOAD

    ObjPtrList<RndLight, class ObjectDir> mLightsReal;
    ObjPtrList<RndLight, class ObjectDir> mLightsApprox;
    ObjPtrList<RndLight, class ObjectDir> mLightsOld;
    Hmx::Color mAmbientColor;
    // mNumLightsReal, mNumLightsApprox, mNumLightsPoint, mNumLightsProj
    int i0;
    int i1;
    int i2;
    int i3;
    int i4;
    bool mHasPointCubeTex; // 0x70
    ObjOwnerPtr<RndEnviron, class ObjectDir> mOwner; // 0x74
    bool mFog; // 0x80
    float f1, f2, f3, f4, f5, f6;
    bool unk9c;
    float unka0, unka4, unka8;
    ObjPtr<RndTransformable, class ObjectDir> mTrans; // 0x84
    float unkb8, unkbc, unkc0, unkc4;
    RndColorXfm mColorXfm;
    bool unk14c, unk14d, unk14e;
    float unk150;
    Timer mTimer; // 0x90
    float unk188, unk18c, unk190, unk194;
    bool b;
    bool mAnimateFromPreset;
    bool mAmbientOcclusion; // 0x14E

    static RndEnviron* sCurrent;
    static Vector3 sCurrentPos;
    static bool sCurrentPosSet;
    // static BoxMapLighting sGlobalLighting;
    DECLARE_REVS
};

#endif
