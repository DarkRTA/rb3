#pragma once
#include "obj/Dir.h"
#include "rndobj/Trans.h"

class Character;
class CharClip;
class CharBone;

void CharUtlResetHair(Character*);
void CharUtlInit();
void CharUtlMergeBones(ObjectDir*, ObjectDir*, int);
RndTransformable* CharUtlFindBoneTrans(const char*, ObjectDir*);
bool CharUtlIsAnimatable(RndTransformable*);
void CharUtlResetTransform(ObjectDir*);
CharBone* CharUtlFindBone(const char*, ObjectDir*);
CharBone* GrabBone(CharBone*, ObjectDir*);

class CharUtlBoneSaver {
public:
    CharUtlBoneSaver(ObjectDir*);
    ~CharUtlBoneSaver();

    ObjectDir* mDir; // 0x0
    std::vector<Transform> mXfms; // 0x4
};

class ClipPredict {
public:
    ClipPredict(CharClip*, const Vector3&, float);
    void SetClip(CharClip*);
    void Predict(float, float);
    float Angle() const { return mAng; }

    CharClip* mClip; // 0x0
    void* mAngChannel; // 0x4
    void* mPosChannel; // 0x8
    Vector3 mPos; // 0xc
    float mAng; // 0x18
    Vector3 mLastPos; // 0x1c
    float mLastAng; // 0x28
};
