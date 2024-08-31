#ifndef UI_UIPROXY_H
#define UI_UIPROXY_H
#include "ui/UIComponent.h"
#include "obj/Dir.h"
#include "rndobj/Dir.h"

class UIProxy : public UIComponent {
public:
    UIProxy();
    OBJ_CLASSNAME(UIProxy)
    OBJ_SET_TYPE(UIProxy)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual RndDrawable* CollideShowing(const Segment&, float&, Plane&);
    virtual int CollidePlane(const Plane&);
    virtual ~UIProxy(){}
    virtual void SetTypeDef(DataArray*);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Poll();

    void UpdateDir();
    void SyncDir();
    void SetProxyDir(const FilePath&, bool);
    void SetProxyDir(RndDir*);
    DataNode OnSetProxyDir(DataArray*);
    RndDir* ProxyDir() const { return mDir; }

    DECLARE_REVS;

    ObjDirPtr<RndDir> mDir; // 0x10c
    ObjPtr<RndEnviron, ObjectDir> mEnv; // 0x118
    RndTransformable* mMainTrans; // 0x124
    Transform mOldXfm; // 0x128
    bool mSyncOnMove; // 0x158
    bool mPolled; // 0x159
};

#endif
