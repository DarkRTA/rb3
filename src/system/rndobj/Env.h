#ifndef RNDOBJ_ENV_H
#define RNDOBJ_ENV_H
#include "rndobj/Trans.h"
#include "types.h"
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "math/Vec.h"
#include "rndobj/Lit.h"
#include "rndobj/ColorXfm.h"


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
    bool IsLightInList(const RndLight*, const ObjPtrList<RndLight, ObjectDir>&) const;
    bool IsValidRealLight(const RndLight*) const;

    DELETE_OVERLOAD

    ObjPtrList<RndLight, ObjectDir> mLightsReal;
    ObjPtrList<RndLight, ObjectDir> mLightsApprox;
    ObjPtrList<RndLight, ObjectDir> mLights3;
    float f0;
    float f1;
    float f2;
    float f3;
    int i0;
    int i1;
    int i2;
    int i3;
    int i4;
    bool mHasPointCubeTex; // 0x70
    ObjOwnerPtr<RndEnviron, ObjectDir> mOwner; // 0x74
    bool mFog; // 0x80
    ObjPtr<RndTransformable, ObjectDir> mTrans; // 0x84
    Timer mTimer; // 0x90
    int test;
    RndColorXfm mColor;
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
