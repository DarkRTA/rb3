#include "TrackWidget.h"
#include "math/Mtx.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Draw.h"
#include "rndobj/Env.h"
#include "rndobj/Text.h"
#include "utl/Loader.h"
#include "utl/Symbols.h"
#include "utl/BinStream.h"
#include "track/TrackDir.h"
#include "track/TrackWidgetImp.h"
#include <list>

INIT_REVS(TrackWidget)

TrackWidget::TrackWidget() : mMeshes(this, kObjListNoNull), mMeshesLeft(this, kObjListNoNull), mMeshesSpan(this, kObjListNoNull), mMeshesRight(this, kObjListNoNull),
    mEnviron(this, 0), mBaseLength(1.0f), mBaseWidth(1.0f), mXOffset(0), mYOffset(0), mZOffset(0), mTrackDir(0), mImp(0), mFont(this, 0), mTextObj(this, 0), mTextAlignment(RndText::kMiddleCenter),
    mTextColor(1.0f, 1.0f, 1.0f), mAltTextColor(1.0f, 1.0f, 1.0f), mMat(this, 0), mActive(0), mWideWidget(0), mAllowRotation(0), mAllowShift(0), mAllowLineRotation(0), mMaxTextInstances(0) {
    SyncImp();
}

TrackWidget::~TrackWidget(){
    delete mImp;
    mImp = 0;
}

BEGIN_COPYS(TrackWidget)
    CREATE_COPY_AS(TrackWidget, tw)
    MILO_ASSERT(tw, 66);
    COPY_SUPERCLASS_FROM(Hmx::Object, tw)
    COPY_SUPERCLASS_FROM(RndDrawable, tw)
    COPY_MEMBER_FROM(tw, mMeshes)
    COPY_MEMBER_FROM(tw, mWideWidget)
    COPY_MEMBER_FROM(tw, mMeshesLeft)
    COPY_MEMBER_FROM(tw, mMeshesSpan)
    COPY_MEMBER_FROM(tw, mMeshesRight)
    COPY_MEMBER_FROM(tw, mEnviron)
    COPY_MEMBER_FROM(tw, mBaseLength)
    COPY_MEMBER_FROM(tw, mBaseWidth)
    COPY_MEMBER_FROM(tw, mAllowRotation)
    COPY_MEMBER_FROM(tw, mFont)
    COPY_MEMBER_FROM(tw, mTextObj)
    COPY_MEMBER_FROM(tw, mTextAlignment)
    COPY_MEMBER_FROM(tw, mCharsPerInst)
    COPY_MEMBER_FROM(tw, mMaxTextInstances)
    COPY_MEMBER_FROM(tw, mWidgetType)
    COPY_MEMBER_FROM(tw, mMat)
    COPY_MEMBER_FROM(tw, mTextColor)
    COPY_MEMBER_FROM(tw, mAltTextColor)
    COPY_MEMBER_FROM(tw, mXOffset)
    COPY_MEMBER_FROM(tw, mYOffset)
    COPY_MEMBER_FROM(tw, mZOffset)
    COPY_MEMBER_FROM(tw, mAllowShift)
    COPY_MEMBER_FROM(tw, mAllowLineRotation)
END_COPYS

SAVE_OBJ(TrackWidget, 0x64)

BEGIN_LOADS(TrackWidget)
    LOAD_REVS(bs)
    ASSERT_REVS(15, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    if(gRev != 0) LOAD_SUPERCLASS(RndDrawable)
    bs >> mMeshes;
    if(gRev > 4){
        LOAD_BITFIELD(bool, mWideWidget)
        bs >> mMeshesLeft;
        bs >> mMeshesSpan;
        bs >> mMeshesRight;
    }
    bs >> mEnviron;
    if(gRev > 2) bs >> mBaseLength;
    if(gRev > 8) bs >> mBaseWidth;
    if(gRev == 2 || gRev == 3 || gRev == 4 || gRev == 5 || gRev == 6 || gRev == 7){
        bool bbb;
        bs >> bbb;
        if(bbb) mWidgetType = 1;
    }
    if(gRev > 3){
        LOAD_BITFIELD(bool, mAllowRotation)
    }
    if(gRev > 5){
        bs >> mFont;
        if(gRev < 8){
            bool bbb;
            bs >> bbb;
            if(bbb) mWidgetType = 2;
        }
    }
    if(gRev > 6){
        bs >> mTextObj;
        int u____;
        bs >> u____;
        MILO_ASSERT(u____ >= 0 && u____ <= ((1<<( 10 - 1)) - 1), 0xAF);
        mCharsPerInst = u____;
        bs >> u____;
        MILO_ASSERT(u____ >= 0 && u____ <= ((1<<( 10 - 1)) - 1), 0xB0);
        mMaxTextInstances = u____;
    }
    if(gRev > 7){
        int u____;
        bs >> u____;
        MILO_ASSERT(u____ >= 0 && u____ <= ((1<<( 3 - 1)) - 1), 0xB4);
        mWidgetType = u____;
        bs >> mMat;
    }
    if(gRev > 9) bs >> (int&)mTextAlignment;
    if(gRev > 10){
        bs >> mTextColor;
        bs >> mAltTextColor;
    }
    if(gRev > 0xB) bs >> mYOffset;
    if(gRev > 0xC){
        bs >> mXOffset;
        bs >> mZOffset;
    }
    if(gRev > 0xD){
        LOAD_BITFIELD(bool, mAllowShift)
    }
    if(gRev > 0xE){
        LOAD_BITFIELD(bool, mAllowLineRotation)
    }
    SyncImp();
END_LOADS

void TrackWidget::CheckValid() const {
    if(TheLoadMgr.EditMode() && mImp) mImp->CheckValid(mName);
}

void TrackWidget::Init(){ mImp->Init(); }

void TrackWidget::DrawShowing(){
    if(!mImp->Empty()){
        if(mEnviron && mEnviron != RndEnviron::sCurrent) mEnviron->Select(0);
        mImp->DrawInstances(mMeshes, mMaxMeshes);
    }
}

void TrackWidget::Poll(){
    if(mTrackDir){
        mImp->RemoveUntil(mTrackDir->CutOffY(), mBaseLength);
        mImp->Poll();
    }
}

#pragma push
#pragma dont_inline on
DECOMP_FORCEFUNC(TrackWidget, TrackWidget, Empty())
#pragma pop
int TrackWidget::Size() const { return mImp->Size(); }
float TrackWidget::GetFirstInstanceY(){ return mImp->GetFirstInstanceY(); }

void TrackWidget::AddInstance(Transform tf, float f){
    if(f) tf.m.y.y = NewYOffset(f) / mBaseLength;
    ApplyOffsets(tf);
    if(mImp->AddInstance(Transform(tf), 0) && mTrackDir->WarnOnResort()){
        MILO_WARN("%s instances resorted", mName);
    }
    UpdateActiveStatus();
}

void TrackWidget::AddTextInstance(const Transform& Ct, class String s, bool b) {
    Transform t = Ct;
    ApplyOffsets(t);
    if (mImp->AddTextInstance(t, s, b) && mTrackDir->WarnOnResort()) MILO_WARN("%s instances resorted", mName);
    UpdateActiveStatus();
}

void TrackWidget::AddMeshInstance(const Transform& Ct, RndMesh* m, float f) {
    if (mImp->AddMeshInstance(Ct, m, f) && mTrackDir->WarnOnResort()) MILO_WARN("%s instances resorted", mName);
    UpdateActiveStatus();
}

void TrackWidget::RemoveAt(float f){
    mImp->RemoveAt(NewYOffset(f), mXOffset, -1.0f);
}

void TrackWidget::RemoveAt(float f, int i){
    float y = NewYOffset(f);
    float x_added = mXOffset + mTrackDir->SlotAt(i).v.x;
    float f4;
    if(i > 0) f4 = Abs(x_added - mTrackDir->SlotAt(i - 1).v.x) / 2.0f;
    else f4 = Abs(mTrackDir->SlotAt(i + 1).v.x - x_added) / 2.0f;
    mImp->RemoveAt(y, x_added, f4);
}

void TrackWidget::ApplyOffsets(Transform& t) {
    t.v.x += mXOffset;
    t.v.y += mYOffset;
    t.v.z += mZOffset;
}

void TrackWidget::Clear() { mImp->Clear(); }

void TrackWidget::SetTextAlignment(RndText::Alignment a) {
    if (a == mTextAlignment) return;
    mTextAlignment = a;
    SyncImp();
}

// void TrackWidget::Mats(std::list<class RndMat*>& mats, bool) {
//     for (std::list<class RndMat*>::iterator i = mats.begin(); *i != NULL; i++) {


//     }
// }

void TrackWidget::SyncImp(){
    RELEASE(mImp);
    switch(mWidgetType){
        case 2:
            mImp = new CharWidgetImp(mFont, mTextObj, mCharsPerInst, mMaxTextInstances, mTextAlignment, Hmx::Color32(mTextColor), Hmx::Color32(mAltTextColor), mAllowLineRotation);
            break;
        case 3:
            mImp = new MatWidgetImp(mMat);
            break;
        case 1:
            mImp = new MultiMeshWidgetImp(mMeshes, mAllowRotation);
            break;
        default:
            mImp = new ImmediateWidgetImp(mAllowRotation);
            break;
    }
    CheckValid();
    if(TheLoadMgr.EditMode()) Init();
}

void TrackWidget::SetScale(float f){ mImp->SetScale(f); }

void TrackWidget::CheckScales() const {
    if(!mAllowRotation){
        for(ObjPtrList<RndMesh, ObjectDir>::iterator it = mMeshes.begin(); it != mMeshes.end(); ++it){
            RndMesh* cur = *it;
            if(!IsFloatOne(cur->mLocalXfm.m.x.x) || !IsFloatOne(cur->mLocalXfm.m.y.y) || !IsFloatOne(cur->mLocalXfm.m.z.z)){
                MILO_WARN("TrackWidget: %s does not have unit scale, but will be drawn on track with unit scale!", cur->Name());
            }
        }
    }
}

DataNode TrackWidget::OnSetMeshes(const DataArray* da){
    mMeshes.clear();
    for(int i = 2; i < da->Size(); i++){
        mMeshes.push_back(da->Obj<RndMesh>(i));
    }
    return DataNode(0);
}

DataNode TrackWidget::OnAddInstance(const DataArray* da) {
    Transform t;
    t.Reset();
    t.v.x = da->Float(2);
    t.v.y = da->Float(3);
    t.v.z = da->Float(4);
    AddInstance(t, 0);
    return DataNode(0);
}

DataNode TrackWidget::OnAddTextInstance(const DataArray* da) {
    Transform t;
    t.Reset();
    t.v.x = da->Float(2);
    t.v.y = da->Float(3);
    t.v.z = da->Float(4);
    class String s(da->Str(5));
    AddTextInstance(t, s, false);
    return DataNode(0);
}

DataNode TrackWidget::OnAddMeshInstance(const DataArray* da) {
    Transform t;
    t.Reset();
    t.v.x = da->Float(2);
    t.v.y = da->Float(3);
    t.v.z = da->Float(4);
    AddMeshInstance(t, da->Obj<RndMesh>(5), 0);
    return DataNode(0);
}

void TrackWidget::UpdateActiveStatus() {
    if (!mActive && !Empty()) {
        mTrackDir->AddActiveWidget(this);
        mActive = true;
    }
}

void TrackWidget::SetInactive() { mActive = false; }

BEGIN_HANDLERS(TrackWidget)
    HANDLE_ACTION(clear, Clear())
    HANDLE(set_meshes, OnSetMeshes)
    HANDLE(add_instance, OnAddInstance)
    HANDLE(add_text_instance, OnAddTextInstance)
    HANDLE(add_mesh_instance, OnAddMeshInstance)
    HANDLE_EXPR(size, Size())
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(575)
END_HANDLERS

#pragma push
#pragma pool_data off
BEGIN_PROPSYNCS(TrackWidget)
    SYNC_PROP_MODIFY_ALT(meshes, mMeshes, CheckScales())
    {
        static Symbol _s("wide_widget");
        if(sym == _s){
            if(_op == kPropSet){ mWideWidget = _val.Int(); }
            else _val = DataNode(mWideWidget);
            return true;
        }
    }
    SYNC_PROP(meshes_left, mMeshesLeft)
    SYNC_PROP(meshes_span, mMeshesSpan)
    SYNC_PROP(meshes_right, mMeshesRight)
    SYNC_PROP_STATIC(environ, mEnviron)
    SYNC_PROP(base_length, mBaseLength)
    SYNC_PROP(base_width, mBaseWidth)
    {
        static Symbol _s("max_meshes");
        if(sym == _s){
            if(_op == kPropSet){ mMaxMeshes = _val.Int(); }
            else _val = DataNode(mMaxMeshes);
            return true;
        }
    }
    SYNC_PROP_MODIFY_ALT(font, mFont, SyncImp())
    SYNC_PROP_MODIFY_ALT(text_obj, mTextObj, SyncImp())
    SYNC_PROP_MODIFY(text_alignment, (int&)mTextAlignment, SyncImp())
    SYNC_PROP_MODIFY_ALT(text_color, mTextColor, SyncImp())
    SYNC_PROP_MODIFY_ALT(alt_text_color, mAltTextColor, SyncImp())
    SYNC_PROP_MODIFY_ALT(mat, mMat, SyncImp())
    SYNC_PROP(x_offset, mXOffset)
    SYNC_PROP(y_offset, mYOffset)
    SYNC_PROP(z_offset, mZOffset)
    {
        static Symbol _s("allow_shift");
        if(sym == _s){
            if(_op == kPropSet){ mAllowShift = _val.Int(); }
            else _val = DataNode(mAllowShift);
            return true;
        }
    }
    {
        static Symbol _s("allow_line_rotation");
        bool bit = mAllowLineRotation;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mAllowLineRotation = bit;
            if(!(_op & (kPropSize|kPropGet))){
                SyncImp();
            }
            return ret;
        }
    }
    {
        static Symbol _s("allow_rotation");
        int bit = mAllowRotation;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mAllowRotation = bit;
            if(!(_op & (kPropSize|kPropGet))){
                SyncImp();
            }
            return ret;
        }
    }
    {
        static Symbol _s("chars_per_inst");
        int bit = mCharsPerInst;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mCharsPerInst = bit;
            if(!(_op & (kPropSize|kPropGet))){
                SyncImp();
            }
            return ret;
        }
    }
    {
        static Symbol _s("max_text_instances");
        int bit = mMaxTextInstances;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mMaxTextInstances = bit;
            if(!(_op & (kPropSize|kPropGet))){
                SyncImp();
            }
            return ret;
        }
    }
    {
        static Symbol _s("widget_type");
        int bit = mWidgetType;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mWidgetType = bit;
            if(!(_op & (kPropSize|kPropGet))){
                SyncImp();
            }
            return ret;
        }
    }
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS
#pragma pop
