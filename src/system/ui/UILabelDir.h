#ifndef UI_UILABELDIR_H
#define UI_UILABELDIR_H
#include "rndobj/Dir.h"
#include "ui/UIFontImporter.h"
#include "ui/UIComponent.h"

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
    virtual ~UILabelDir(); // defining this causes an ambiguity error
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

    DECLARE_REVS;

    ObjPtr<UIColor, ObjectDir> mDefaultColor;
    std::vector<ObjPtr<UIColor,ObjectDir> > mColors;
    ObjPtr<RndText, ObjectDir> mTextObj;
    ObjPtr<RndAnimatable, ObjectDir> mFocusAnim;
    ObjPtr<RndAnimatable, ObjectDir> mPulseAnim;
    ObjPtr<RndMesh, ObjectDir> mTopLeftHighlightBone;
    ObjPtr<RndMesh, ObjectDir> mTopRightHighlightBone;
    ObjPtr<RndMesh, ObjectDir> mBottomLeftHighlightBone;
    ObjPtr<RndMesh, ObjectDir> mBottomRightHighlightBone;
    ObjPtr<RndGroup, ObjectDir> mHighlightMeshGroup;
    ObjPtr<RndGroup, ObjectDir> mFocusedBackgroundGroup;
    ObjPtr<RndGroup, ObjectDir> mUnfocusedBackgroundGroup;
    bool mAllowEditText;
};

#endif
