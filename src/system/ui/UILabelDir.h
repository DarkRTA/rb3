#pragma once
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

/** "Top-level resource object for UILabels" */
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

    /** "color to use when no other color is defined for a state" */
    ObjPtr<UIColor> mDefaultColor; // 0x26c
    /** The colors to use depending on the label's state.
     * This vector is expected to be of size UIComponent::kNumStates.
     * Original _objects descriptions:
     * "color when label is normal"
     * "color when label is focused"
     * "color when label is disabled"
     * "color when label is selecting"
     * "color when label is selected"
     */
    std::vector<ObjPtr<UIColor> > mColors; // 0x278
    ObjPtr<RndText> mTextObj; // 0x280
    ObjPtr<RndAnimatable> mFocusAnim; // 0x28c
    ObjPtr<RndAnimatable> mPulseAnim; // 0x298
    ObjPtr<RndMesh> mTopLeftHighlightBone; // 0x2a4
    ObjPtr<RndMesh> mTopRightHighlightBone; // 0x2b0
    ObjPtr<RndMesh> mBottomLeftHighlightBone; // 0x2bc
    ObjPtr<RndMesh> mBottomRightHighlightBone; // 0x2c8
    ObjPtr<RndGroup> mHighlightMeshGroup; // 0x2d4
    ObjPtr<RndGroup> mFocusedBackgroundGroup; // 0x2e0
    ObjPtr<RndGroup> mUnfocusedBackgroundGroup; // 0x2ec
    /** "allow non-localized text with this resource?" */
    bool mAllowEditText; // 0x2f8
};
