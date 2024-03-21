#ifndef UI_UIPICTURE_H
#define UI_UIPICTURE_H

#include "obj/Object.h"
#include "ui/Screenshot.h"
#include "ui/UIComponent.h"
#include "ui/UITransitionHandler.h"
#include "obj/Dir.h"
#include "rndobj/Mesh.h"
#include "rndobj/Tex.h"
#include "utl/FilePath.h"
#include "utl/Loader.h"

class UIPicture : public UIComponent, public UITransitionHandler {
public:
    UIPicture();
    virtual ~UIPicture();
    OBJ_CLASSNAME(UIPicture)
    OBJ_SET_TYPE(UIPicture)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SetTypeDef(DataArray *);
    virtual void Poll();
    virtual void Exit();
    virtual bool IsEmptyValue() const;

    void FinishValueChange();
    void UpdateTexture(const FilePath&);
    void FinishLoading();
    void CancelLoading();
    void SetHookTex(bool);
    void SetTex(const FilePath&);
    void HookupMesh();
    DELETE_OVERLOAD

    int offset[0xF];

    ObjPtr<RndMesh, ObjectDir> mMesh;
    FilePath mTexFile;
    FilePath mLoadedFile;
    RndTex* mTex;
    FileLoader* mLoader;
    bool mHookTex;
    FilePath mDelayedTexFile;

    DECLARE_REVS
};

#endif // UI_UIPICTURE_H
