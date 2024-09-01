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
#include <list>

INIT_REVS(TrackWidget)

TrackWidget::TrackWidget() : mMeshes(this, kObjListNoNull), mMeshesLeft(this, kObjListNoNull), mMeshesSpan(this, kObjListNoNull), mMeshesRight(this, kObjListNoNull),
    mEnviron(this, 0), mBaseLength(1.0f), mBaseWidth(1.0f), mOffset(0.0f, 0.0f, 0.0f), mTrackDir(0), mImp(0), mFont(this, 0), mTextObj(this, 0), mTextAlignment(RndText::kMiddleCenter),
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
    COPY_MEMBER_FROM(tw, mOffset)
    COPY_MEMBER_FROM(tw, mAllowShift)
    COPY_MEMBER_FROM(tw, mAllowLineRotation)
END_COPYS

SAVE_OBJ(TrackWidget, 0x64)

// void TrackWidget::Load(BinStream& bs) { // bitfield and stack nonsense abound
//     bool x, y, z, a;
//     int i, u____;
//     LOAD_REVS(bs)
//     ASSERT_REVS(15, 0)
//     Hmx::Object::Load(bs);
//     if (gRev > 0) RndDrawable::Load(bs);
//     bs >> unk_0x20;
//     if (gRev > 4) {
//         bs >> x;
//         unk_0xD0_1 = x;
//         bs >> unk_0x30;
//         bs >> unk_0x40;
//         bs >> unk_0x50;
//     }
//     bs >> unk_0x60;
//     if (gRev > 2) bs >> unk_0x6C;
//     if (gRev > 8) bs >> unk_0x70;
//     if ((u16)(gRev + 0xFFFE) <= 5) { // ?
//         bs >> y;
//         if (!y) {
//             //mWidgetType = y;
//         }
//     }
//     if (gRev > 3) {
//         bs >> z;
//         unk_0xD0_2 = z;
//     }
//     if (gRev > 5) {
//         bs >> unk_0x88;
//         if (gRev < 8) {
//             bs >> x;
//             if (x) ; // i have no idea
//         }
//     }
//     if (gRev > 6) {
//         bs >> unk_0x94;
//         bs >> u____;
//         MILO_ASSERT(u____ >= 0 && u____ <= ((1<<( 10 - 1)) - 1), 175);
//         bs >> i;
//         MILO_ASSERT(u____ >= 0 && u____ <= ((1<<( 10 - 1)) - 1), 176);
//     }
//     if (gRev > 7) {


//         bs >> unk_0xC4;
//     }
//     if (gRev > 9) {
//         bs >> i;
//         mAlignment = (RndText::Alignment)i;
//     }
//     if (gRev > 10) {
//         bs >> unk_0xA4;
//         bs >> unk_0xB4;
//     }
//     if (gRev > 11) bs >> unk_0x74.y;
//     if (gRev > 12) {
//         bs >> unk_0x74.x;
//         bs >> unk_0x74.z;
//     }
//     if (gRev > 13) {
//         bs >> y;
//         unk_0xD0_3 = y;
//     }
//     if (gRev > 14) {
//         bs >> x;
//         mWidgetType = x;
//     }

//     SyncImp();
// }

// void TrackWidget::CheckValid() const {
//     if (!TheLoadMgr.EditMode()) return;
//     if (unk_0x84 == NULL) return;
//     unk_0x84->CheckValid(mName);
// }

// void TrackWidget::Init() { unk_0x84->Init(); }

// void TrackWidget::DrawShowing() {
//     if (!unk_0x84->Empty()) {
//         if (&(*unk_0x60) != NULL && &(*unk_0x60) != RndEnviron::sCurrent) unk_0x60->Select(NULL);

//         unk_0x84->DrawInstances(unk_0x20, unk_0xD0_7);
//     }
// }

// void TrackWidget::Poll() {
//     if (unk_0x80) {
//         unk_0x84->RemoveUntil(unk_0x80->CutOffY(), unk_0x6C);
//         unk_0x84->Poll();
//     }
// }

// bool TrackWidget::Empty() { return unk_0x84->Empty(); }
// float TrackWidget::GetFirstInstanceY() { return unk_0x84->GetFirstInstanceY(); }

// void TrackWidget::AddInstance(Transform t, float f) { // these are all boned because Transform::operator= is inlined psq nonsense
//     if (f != 0) {
//         t.m.y.y = (unk_0x80->SecondsToY(f) + unk_0x74.y) / unk_0x6C;
//     }
//     ApplyOffsets(t);
//     if (unk_0x84->AddInstance(t, f) && unk_0x80->unk_0x20C) MILO_WARN("%s instances resorted", mName);
//     UpdateActiveStatus();
// }

// void TrackWidget::AddTextInstance(const Transform& Ct, class String s, bool b) {
//     Transform t = Ct;
//     ApplyOffsets(t);
//     if (unk_0x84->AddTextInstance(t, s, b) && unk_0x80->unk_0x20C) MILO_WARN("%s instances resorted", mName);
//     UpdateActiveStatus();
// }

// void TrackWidget::AddMeshInstance(const Transform& Ct, RndMesh* m, float f) {
//     if (unk_0x84->AddMeshInstance(Ct, m, f) && unk_0x80->unk_0x20C) MILO_WARN("%s instances resorted", mName);
//     UpdateActiveStatus();
// }

// void TrackWidget::RemoveAt(float f) {
//     unk_0x84->RemoveAt(unk_0x80->SecondsToY(f) + unk_0x74.y, unk_0x74.x, -1);
// }

// void TrackWidget::ApplyOffsets(Transform& t) {
//     t.v += unk_0x74; 
// }

// void TrackWidget::Clear() { unk_0x84->Clear(); }

// void TrackWidget::SetTextAlignment(RndText::Alignment a) {
//     if (a == mAlignment) return;
//     mAlignment = a;
//     SyncImp();
// }

// void TrackWidget::Mats(std::list<class RndMat*>& mats, bool) {
//     for (std::list<class RndMat*>::iterator i = mats.begin(); *i != NULL; i++) {

        
//     }
// }

// void TrackWidget::SyncImp() {
//     delete unk_0x84; // genius move; can't have an out-of-sync widget if you just Make A New One
//     unk_0x84 = 0;
//     switch (mWidgetType) {
//         case 2:
//             //unk_0x84 = new CharWidgetImp/*(NULL, NULL, 0, 0, RndText::kAlignCenterRight)*/;
//         case 3:
//             unk_0x84 = new MultiMeshWidgetImp(unk_0x20, unk_0xD0_2);
//         case 1:
//         default:
//             unk_0x84 = new ImmediateWidgetImp(!unk_0xD0_2);
//     }
//     CheckValid();
//     if (TheLoadMgr.mEditMode) Init();
// }

// DataNode TrackWidget::OnSetMeshes(const DataArray* da) {
//     unk_0x20.clear();
//     for (int i = 2; i < da->Size(); i++)
//         unk_0x20.push_back(da->Obj<RndMesh>(i));
//     return DataNode();
// }

// DataNode TrackWidget::OnAddInstance(const DataArray* da) {
//     Transform t;
//     t.SetFromDA(da);
//     AddInstance(t, 0);
//     return DataNode();
// }

// DataNode TrackWidget::OnAddTextInstance(const DataArray* da) {
//     Transform t;
//     t.SetFromDA(da);
//     class String s(da->Str(5));
//     AddTextInstance(t, s, false);
//     return DataNode();
// }

// DataNode TrackWidget::OnAddMeshInstance(const DataArray* da) {
//     Transform t;
//     t.SetFromDA(da);
//     AddMeshInstance(t, da->Obj<RndMesh>(5), 0);
//     return DataNode();
// }

void TrackWidget::UpdateActiveStatus() {
    if (!mActive && !mImp->Empty()) {
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
    HANDLE_EXPR(size, mImp->Size())
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
            if(_op == kPropSet){ mWideWidget = _val.Int(0); }
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
            if(_op == kPropSet){ mMaxMeshes = _val.Int(0); }
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
    SYNC_PROP(x_offset, mOffset.x)
    SYNC_PROP(y_offset, mOffset.y)
    SYNC_PROP(z_offset, mOffset.z)
    {
        static Symbol _s("allow_shift");
        if(sym == _s){
            if(_op == kPropSet){ mAllowShift = _val.Int(0); }
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