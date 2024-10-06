#ifndef RNDOBJ_TEXRENDERER_H
#define RNDOBJ_TEXRENDERER_H
#include "rndobj/Draw.h"
#include "rndobj/Anim.h"
#include "rndobj/Poll.h"

class RndTex;
class RndCam;

class RndTexRenderer : public RndDrawable, public RndAnimatable, public RndPollable {
public:
    RndTexRenderer();
    OBJ_CLASSNAME(TexRenderer);
    OBJ_SET_TYPE(TexRenderer);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual void ListDrawChildren(std::list<RndDrawable*>&);
    virtual void DrawPreClear(){ DrawToTexture(); }
    virtual void UpdatePreClearState();
    virtual ~RndTexRenderer();
    virtual void Enter();
    virtual void SetFrame(float, float);
    virtual float StartFrame();
    virtual float EndFrame();
    virtual void ListAnimChildren(std::list<RndAnimatable*>&) const;
    virtual void ListPollChildren(std::list<RndPollable*>&) const;
    virtual void DrawBefore(){}
    virtual void DrawAfter(){}

    void DrawToTexture();
    void InitTexture();
    DataNode OnGetRenderTextures(DataArray*);
    void SetDraw(RndDrawable* draw){
        mDraw = draw;
        mDirty = true;
    }

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndTexRenderer)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndTexRenderer)
    }

    bool mDirty; // 0x38
    bool mForce; // 0x39
    bool mDrawPreClear; // 0x3a
    bool mDrawWorldOnly; // 0x3b
    bool mDrawResponsible; // 0x3c
    bool mNoPoll; // 0x3d
    bool mPrimeDraw; // 0x3e
    bool mFirstDraw; // 0x3f
    bool mForceMips; // 0x40
    float mImposterHeight; // 0x44
    ObjPtr<RndTex, ObjectDir> mOutputTexture; // 0x48
    ObjPtr<RndDrawable, ObjectDir> mDraw; // 0x54
    ObjPtr<RndCam, ObjectDir> mCam; // 0x60
    ObjPtr<RndCam, ObjectDir> mMirrorCam; // 0x6c
};

#endif
