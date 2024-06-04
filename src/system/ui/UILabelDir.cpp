#include "ui/UILabelDir.h"
#include "ui/UIColor.h"
#include "rndobj/Text.h"
#include "rndobj/Mesh.h"
#include "rndobj/Group.h"
#include "obj/ObjVersion.h"

INIT_REVS(UILabelDir)

UILabelDir::UILabelDir() : mDefaultColor(this, 0), mColors(), mTextObj(this, 0), mFocusAnim(this, 0), mPulseAnim(this, 0), mTopLeftHighlightBone(this, 0), 
    mTopRightHighlightBone(this, 0), mBottomLeftHighlightBone(this, 0), mBottomRightHighlightBone(this, 0), mHighlightMeshGroup(this, 0),
    mFocusedBackgroundGroup(this, 0), mUnfocusedBackgroundGroup(this, 0), mAllowEditText(0) {
    for(int i = 0; i < UIComponent::kNumStates; i++){
        mColors.push_back(ObjPtr<UIColor, ObjectDir>(this, 0));
    }
}

RndText* UILabelDir::TextObj(Symbol sym) const {
    return (mGennedFonts.size() > 0) ? (RndText*)mTextObj : GetGennedText(sym);
}

RndAnimatable* UILabelDir::FocusAnim() const { return mFocusAnim; }
RndAnimatable* UILabelDir::PulseAnim() const { return mPulseAnim; }
RndGroup* UILabelDir::HighlighMeshGroup() const { return mHighlightMeshGroup; }
RndMesh* UILabelDir::TopLeftHighlightBone() const { return mTopLeftHighlightBone; }
RndMesh* UILabelDir::TopRightHighlightBone() const { return mTopRightHighlightBone; }
RndMesh* UILabelDir::BottomLeftHighlightBone() const { return mBottomLeftHighlightBone; }
RndMesh* UILabelDir::BottomRightHighlightBone() const { return mBottomRightHighlightBone; }

void UILabelDir::SetColor(UIComponent::State state, UIColor* color){
    MILO_ASSERT(state < UIComponent::kNumStates, 0x86);
    mColors[state] = color;
}

SAVE_OBJ(UILabelDir, 0x9C)

void UILabelDir::SyncObjects(){
    RndDir::SyncObjects();
    UIFontImporter::FontImporterSyncObjects();
}

BEGIN_LOADS(UILabelDir)
    LOAD_SUPERCLASS(ObjectDir)
END_LOADS

void UILabelDir::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(9, 0);
    PushRev(packRevs(gAltRev, gRev), this);
    RndDir::PreLoad(bs);
}