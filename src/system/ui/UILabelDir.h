#ifndef UI_UILABELDIR_H
#define UI_UILABELDIR_H
#include "rndobj/Dir.h"
#include "ui/UIColor.h"
#include "ui/UIFontImporter.h"
#include "ui/UIComponent.h"
#include "rndobj/Text.h"
#include "rndobj/Mesh.h"
#include "rndobj/Group.h"

// forward decs
class UIColor;
class RndText;
class RndMesh;
class RndGroup;

class UILabelDir : public RndDir, public UIFontImporter {
public:
    UILabelDir();
    OBJ_CLASSNAME(UILabelDir)
    OBJ_SET_TYPE(UILabelDir)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual ~UILabelDir(){}
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    
    RndText* TextObj(Symbol) const;
    RndAnimatable* FocusAnim() const;
    RndAnimatable* PulseAnim() const;
    RndGroup* HighlighMeshGroup() const;
    RndMesh* TopLeftHighlightBone() const;
    RndMesh* TopRightHighlightBone() const;
    RndMesh* BottomLeftHighlightBone() const;
    RndMesh* BottomRightHighlightBone() const;
    void SetColor(UIComponent::State, UIColor*);
    void GetStateColor(UIComponent::State, Hmx::Color&) const;

    DECLARE_REVS;
    NEW_OVERLOAD
    DELETE_OVERLOAD

    NEW_OBJ(UILabelDir)
    static void Init(){
        REGISTER_OBJ_FACTORY(UILabelDir)
    }

    ObjPtr<UIColor, ObjectDir> mDefaultColor; // 0x26c
    std::vector<ObjPtr<UIColor,ObjectDir> > mColors; // 0x278
    ObjPtr<RndText, ObjectDir> mTextObj; // 0x280
    ObjPtr<RndAnimatable, ObjectDir> mFocusAnim; // 0x28c
    ObjPtr<RndAnimatable, ObjectDir> mPulseAnim; // 0x298
    ObjPtr<RndMesh, ObjectDir> mTopLeftHighlightBone; // 0x2a4
    ObjPtr<RndMesh, ObjectDir> mTopRightHighlightBone; // 0x2b0
    ObjPtr<RndMesh, ObjectDir> mBottomLeftHighlightBone; // 0x2bc
    ObjPtr<RndMesh, ObjectDir> mBottomRightHighlightBone; // 0x2c8
    ObjPtr<RndGroup, ObjectDir> mHighlightMeshGroup; // 0x2d4
    ObjPtr<RndGroup, ObjectDir> mFocusedBackgroundGroup; // 0x2e0
    ObjPtr<RndGroup, ObjectDir> mUnfocusedBackgroundGroup; // 0x2ec
    bool mAllowEditText; // 0x2f8
};

#endif
