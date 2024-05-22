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
    OBJ_CLASSNAME(UIPicture)
    OBJ_SET_TYPE(UIPicture)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual ~UIPicture();
    virtual void SetTypeDef(DataArray*);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Exit();
    virtual void Poll();
    virtual bool IsEmptyValue() const;
    virtual void FinishValueChange();
    
    void UpdateTexture(const FilePath&);
    void FinishLoading();
    void CancelLoading();
    void SetHookTex(bool);
    void SetTex(const FilePath&);
    void HookupMesh();

    DECLARE_REVS;
    DELETE_OVERLOAD

    ObjPtr<RndMesh, class ObjectDir> mMesh; // 0x12c
    FilePath mTexFile; // 0x138
    FilePath mLoadedFile; // 0x144
    RndTex* mTex; // 0x150
    FileLoader* mLoader; // 0x154
    bool mHookTex; // 0x158
    FilePath mDelayedTexFile; // 0x15c

};

#endif // UI_UIPICTURE_H
