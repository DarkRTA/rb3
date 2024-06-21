#ifndef RNDOBJ_MATANIM_H
#define RNDOBJ_MATANIM_H
#include "rndobj/Anim.h"
#include "rndobj/Mat.h"
#include "utl/Key.h"

class RndMatAnim : public RndAnimatable {
public:
    class TexPtr : public ObjPtr<RndTex, ObjectDir> {
    public:
        TexPtr();
        TexPtr(RndTex*);
    };

    class TexKeys : public Keys<TexPtr, RndTex*> {
    public:
        TexKeys(Hmx::Object*);
        TexKeys& operator=(const TexKeys&);
        Hmx::Object* mOwner;
    };

    RndMatAnim();
    OBJ_CLASSNAME(MatAnim);
    OBJ_SET_TYPE(MatAnim);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndMatAnim(){}
    virtual void SetFrame(float, float);
    virtual float EndFrame();
    virtual Hmx::Object* AnimTarget(){ return mMat; }
    virtual void SetKey(float);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Print();

    void SetMat(RndMat*);
    void LoadStage(BinStream&);
    void LoadStages(BinStream&);
    Keys<Vector3, Vector3>& TransKeys();
    Keys<Vector3, Vector3>& ScaleKeys();
    TexKeys& GetTexKeys();
    Keys<Vector3, Vector3>& RotKeys();
    Keys<float, float>& AlphaKeys();
    Keys<Hmx::Color, Hmx::Color>& ColorKeys();

    DECLARE_REVS
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndMatAnim)
    static void Init(){ REGISTER_OBJ_FACTORY(RndMatAnim) }
    static Hmx::Object* sOwner;

    ObjPtr<RndMat, ObjectDir> mMat; // 0x10
    ObjOwnerPtr<RndMatAnim, ObjectDir> mKeysOwner; // 0x1c
    Keys<Hmx::Color, Hmx::Color> mColorKeys; // 0x28
    Keys<float, float> mAlphaKeys; // 0x30
    Keys<Vector3, Vector3> mTransKeys; // 0x38
    Keys<Vector3, Vector3> mScaleKeys; // 0x40
    Keys<Vector3, Vector3> mRotKeys; // 0x48
    TexKeys mTexKeys; // 0x50
};

#endif
