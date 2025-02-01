#pragma once
#include "rndobj/Anim.h"
#include "rndobj/Mat.h"
#include "math/Key.h"

/**
 * @brief A class for animating Mats.
 * Original _objects description:
 * "MatAnim objects animate material properties."
 */
class RndMatAnim : public RndAnimatable {
public:
    class TexPtr : public ObjPtr<RndTex> {
    public:
        TexPtr();
        TexPtr(RndTex *);
    };

    class TexKeys : public Keys<TexPtr, RndTex *> {
    public:
        TexKeys(Hmx::Object *);
        TexKeys &operator=(const TexKeys &);
        int Add(RndTex *, float, bool);

        Hmx::Object *mOwner;
    };

    RndMatAnim();
    OBJ_CLASSNAME(MatAnim);
    OBJ_SET_TYPE(MatAnim);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual ~RndMatAnim() {}
    virtual void SetFrame(float, float);
    virtual float EndFrame();
    virtual Hmx::Object *AnimTarget() { return mMat; }
    virtual void SetKey(float);
    virtual void Replace(Hmx::Object *, Hmx::Object *);
    virtual void Print();

    /** Load one animation stage from the BinStream.
     * A stage consists of trans, scale, rot and texture keys in that order.
     */
    void LoadStage(BinStream &); // possibly private
    /** Load all animation stages from the BinStream. */
    void LoadStages(BinStream &);

    // getters/setters
    void SetMat(RndMat *);
    Keys<Vector3, Vector3> &TransKeys() { return mKeysOwner->mTransKeys; }
    Keys<Vector3, Vector3> &ScaleKeys() { return mKeysOwner->mScaleKeys; }
    TexKeys &GetTexKeys() { return mKeysOwner->mTexKeys; }
    Keys<Vector3, Vector3> &RotKeys() { return mKeysOwner->mRotKeys; }
    Keys<float, float> &AlphaKeys() { return mKeysOwner->mAlphaKeys; }
    Keys<Hmx::Color, Hmx::Color> &ColorKeys() { return mKeysOwner->mColorKeys; }
    RndMatAnim *KeysOwner() const { return mKeysOwner; }

    DECLARE_REVS
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndMatAnim)
    static void Init() { REGISTER_OBJ_FACTORY(RndMatAnim) }
    static Hmx::Object *sOwner;

    /** The Mat to animate. */
    ObjPtr<RndMat> mMat; // 0x10
    /** The MatAnim that owns all of these keys. */
    ObjOwnerPtr<RndMatAnim> mKeysOwner; // 0x1c
    /** The collection of Color keys. */
    Keys<Hmx::Color, Hmx::Color> mColorKeys; // 0x28
    /** The collection of alpha keys. */
    Keys<float, float> mAlphaKeys; // 0x30
    /** The collection of position keys. */
    Keys<Vector3, Vector3> mTransKeys; // 0x38
    /** The collection of scale keys. */
    Keys<Vector3, Vector3> mScaleKeys; // 0x40
    /** The collection of rotation keys. */
    Keys<Vector3, Vector3> mRotKeys; // 0x48
    /** The collection of texture keys. */
    TexKeys mTexKeys; // 0x50
};

void Interp(const RndMatAnim::TexPtr &, const RndMatAnim::TexPtr &, float, RndTex *&);
