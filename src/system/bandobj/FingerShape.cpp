#include "bandobj/FingerShape.h"
#include "os/Debug.h"

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
    mAnimPeriod = dir->Property("anim_period", true)->Float(0);
}

FingerShape::~FingerShape(){
    RELEASE(mLastState);
}