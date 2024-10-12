#include "bandobj/FingerShape.h"
#include "os/Debug.h"
#include "beatmatch/RGUtl.h"

FingerShape::FingerShape(RndDir* dir) : mLastState(new RGState()), mFretNumberShowAnim(0), mFretNumberPositionAnim(0), mFretNumberText(0), mLastFretNumber(-1), mAnimPeriod(1.0f), mLefty(0) {
    MILO_ASSERT(dir, 0x1F);
    mFretHeightAnims.reserve(6);
    mFretHeightAnims.push_back(dir->Find<RndAnimatable>("Bone01.anim", true));
    mFretHeightAnims.push_back(dir->Find<RndAnimatable>("Bone02.anim", true));
    mFretHeightAnims.push_back(dir->Find<RndAnimatable>("Bone03.anim", true));
    mFretHeightAnims.push_back(dir->Find<RndAnimatable>("Bone04.anim", true));
    mFretHeightAnims.push_back(dir->Find<RndAnimatable>("Bone05.anim", true));
    mFretHeightAnims.push_back(dir->Find<RndAnimatable>("Bone06.anim", true));
    mContourAngleAnims.reserve(7);
    mContourHeightAnims.push_back(dir->Find<RndAnimatable>("shareBone_0low1_trans.tnm", true));
    mContourHeightAnims.push_back(dir->Find<RndAnimatable>("shareBone_12_trans.tnm", true));
    mContourHeightAnims.push_back(dir->Find<RndAnimatable>("shareBone_23_trans.tnm", true));
    mContourHeightAnims.push_back(dir->Find<RndAnimatable>("shareBone_34_trans.tnm", true));
    mContourHeightAnims.push_back(dir->Find<RndAnimatable>("shareBone_45_trans.tnm", true));
    mContourHeightAnims.push_back(dir->Find<RndAnimatable>("shareBone_56_trans.tnm", true));
    mContourHeightAnims.push_back(dir->Find<RndAnimatable>("shareBone_6high_trans.tnm", true));
    mContourAngleAnims.reserve(7);
    mContourAngleAnims.push_back(dir->Find<RndAnimatable>("shareBone_0low1_rot.tnm", true));
    mContourAngleAnims.push_back(dir->Find<RndAnimatable>("shareBone_12_rot.tnm", true));
    mContourAngleAnims.push_back(dir->Find<RndAnimatable>("shareBone_23_rot.tnm", true));
    mContourAngleAnims.push_back(dir->Find<RndAnimatable>("shareBone_34_rot.tnm", true));
    mContourAngleAnims.push_back(dir->Find<RndAnimatable>("shareBone_45_rot.tnm", true));
    mContourAngleAnims.push_back(dir->Find<RndAnimatable>("shareBone_56_rot.tnm", true));
    mContourAngleAnims.push_back(dir->Find<RndAnimatable>("shareBone_6high_rot.tnm", true));
    mFretNumberShowAnim = dir->Find<RndAnimatable>("fret_number_show.anim", true);
    mFretNumberPositionAnim = dir->Find<RndAnimatable>("fret_number_pos.tnm", true);
    mFretNumberText = dir->Find<RndText>("fret_numbers_chord.txt", true);
    mAnimPeriod = dir->Property("anim_period", true)->Float();
}

FingerShape::~FingerShape(){
    RELEASE(mLastState);
}

void FingerShape::Update(const RGState& state, bool b1, bool b2){
    if((state != *mLastState) || b2){
        int i74 = -1;
        int i78 = -1;
        bool range = RGGetHeldFretRange(state, i74, i78);
        int num = range ? 1 - i74 : 0;
        for(int i = 0; i < 6; i++){
            float clamped = Clamp<int>(0, 6, num + state.GetFret(i));
            UpdateAnim(mFretHeightAnims[i], clamped, b1);
            if(i == 0){
                UpdateAnim(mContourHeightAnims[i], clamped, b1);
                UpdateAnim(mContourAngleAnims[i], -clamped, b1);
            }
            if(i < 5){
                int idx = i + 1;
                float clamped2 = Clamp<int>(0, 6, num + state.GetFret(idx));
                float minclamp = Min(clamped, clamped2);
                float f1 = clamped - clamped2;
                if(mLefty) f1 = -f1;
                UpdateAnim(mContourHeightAnims[idx], minclamp, b1);
                UpdateAnim(mContourAngleAnims[idx], f1, b1);
            }
            if(i == 5){
                UpdateAnim(mContourHeightAnims[6], clamped, b1);
                UpdateAnim(mContourAngleAnims[6], clamped, b1);
            }
        }
        UpdateFretNumber(state, b1);
        *mLastState = state;
    }
}

void FingerShape::Reset(bool b){
    Update(RGState(), b, false);
}

#include "utl/Symbols.h"

void FingerShape::UpdateAnim(RndAnimatable* anim, float frame, bool b){
    Symbol sym = b ? dest : range;
    float frametouse = b ? anim->GetFrame() : frame;
    anim->Animate(0.0f, false, 0.0f, RndAnimatable::k30_fps_ui, frametouse, frame, mAnimPeriod, 1.0f, sym);
}

void FingerShape::UpdateFretNumber(const RGState& state, bool b){
    int i44 = -1;
    int i48 = -1;
    RGGetFretLabelInfo(state, i44, i48);
    float posframe = mFretNumberPositionAnim->GetFrame();
    float f2 = 0;
    if(i48 > 0){
        if(mLefty) posframe = 5 - i44;
        else posframe = i44;
        f2 = 1.0f;
        if(i48 != mLastFretNumber){
            mFretNumberText->SetText(RGFretNumberToString(i48));
            mLastFretNumber = i48;
        }
    }
    UpdateAnim(mFretNumberPositionAnim, posframe, b && mFretNumberShowAnim->GetFrame() != 0);
    UpdateAnim(mFretNumberShowAnim, f2, b);
}
