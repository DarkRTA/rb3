
#include "CharBonesBlender.h"
#include "CharGuitarString.h"
#include "CharLookAt.h"
#include "CharMeshHide.h"
#include "CharMirror.h"
#include "CharNeckTwist.h"
#include "CharPosConstraint.h"
#include "CharSleeve.h"
#include "CharTransCopy.h"
#include "CharTransDraw.h"
#include "CharUpperTwist.h"
#include "CharWeightSetter.h"
#include "ClipCollide.h"
#include "FileMergerOrganizer.h"
#include "Waypoint.h"
#include "char/CharClipGroup.h"
#include "char/CharClipSet.h"
#include "char/CharCollide.h"
#include "char/CharCuff.h"
#include "char/CharDriver.h"
#include "char/CharDriverMidi.h"
#include "char/CharEyeDartRuleset.h"
#include "char/CharEyes.h"
#include "char/CharFaceServo.h"
#include "char/CharForeTwist.h"
#include "char/CharHair.h"
#include "char/CharIKFingers.h"
#include "char/CharIKFoot.h"
#include "char/CharIKHand.h"
#include "char/CharIKHead.h"
#include "char/CharIKMidi.h"
#include "char/CharIKRod.h"
#include "char/CharIKScale.h"
#include "char/CharIKSliderMidi.h"
#include "char/CharInterest.h"
#include "char/CharLipSync.h"
#include "char/CharLipSyncDriver.h"
#include "char/CharPollGroup.h"
#include "char/CharServoBone.h"
#include "char/CharTaskMgr.h"
#include "char/CharWeightable.h"
#include "char/FileMerger.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "char/Char.h"
#include "char/Character.h"
#include "char/CharBoneDir.h"
#include "char/CharBoneOffset.h"
#include "char/CharBones.h"
#include "char/CharBlendBone.h"
#include "char/CharBoneTwist.h"
#include "char/CharClip.h"
#include "char/CharUtl.h"
#include "obj/DataFunc.h"

CharDebug TheCharDebug;

DataNode CharDebug::OnSetObjects(DataArray *a) {
    TheCharDebug.SetObjects(a);
    return 0;
}

void CharDeferHighlight(Hmx::Object *obj) { TheCharDebug.Once(obj); }

inline void CharDebug::Init() {
    DataRegisterFunc("char_debug", OnSetObjects);
    mOverlay = RndOverlay::Find("char_debug", true);
    mOverlay->SetCallback(this);
}

void CharInit() {
#ifdef MILO_DEBUG
    TheCharDebug.Init();
#endif
    Character::Init();
    CharBonesObject::Init();
    CharBoneOffset::Init();
    CharBlendBone::Init();
    CharBone::Init();
    CharBonesBlender::Init();
    CharBoneTwist::Init();
    CharClip::Init();
    CharClipSet::Init();
    CharClipGroup::Init();
    CharCollide::Init();
    CharCuff::Init();
    CharDriver::Init();
    CharDriverMidi::Init();
    CharEyes::Init();
    CharInterest::Init();
    CharEyeDartRuleset::Init();
    CharFaceServo::Init();
    CharForeTwist::Init();
    CharHair::Init();
    CharIKFingers::Init();
    CharIKFoot::Init();
    CharIKHand::Init();
    CharIKHead::Init();
    CharIKMidi::Init();
    CharIKSliderMidi::Init();
    CharIKRod::Init();
    CharIKScale::Init();
    CharLipSync::Init();
    CharLipSyncDriver::Init();
    CharLookAt::Init();
    CharMeshHide::Init();
    CharMirror::Init();
    CharNeckTwist::Init();
    CharPollGroup::Init();
    CharPosConstraint::Init();
    CharServoBone::Init();
    CharSleeve::Init();
    CharTaskMgr::Init();
    CharTransDraw::Init();
    CharTransCopy::Init();
    CharUpperTwist::Init();
    CharWeightable::Init();
    CharWeightSetter::Init();
    Waypoint::Init();
    CharGuitarString::Init();
    FileMerger::Init();
    CharBoneDir::Register();
    ClipCollide::Init();
    FileMergerOrganizer::Init();
    PreloadSharedSubdirs("char");
    CharBoneDir::Init();
    CharUtlInit();
    TheDebug.AddExitCallback(CharTerminate);
}

void CharTerminate() {
    TheDebug.RemoveExitCallback(CharTerminate);
    Character::Terminate();
    CharBoneDir::Terminate();
}

float CharDebug::UpdateOverlay(RndOverlay *, float) {}